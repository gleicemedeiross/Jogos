/**********************************************************************************
// Graphics (C�digo Fonte)
// 
// Cria��o:		06 Abr 2011
// Atualiza��o:	24 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Graphics � uma classe que faz uso das fun��es do Direct3D para 
//              acessar o hardware de acelera��o gr�fica da placa de v�deo.
//
**********************************************************************************/

#include "Graphics.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

ID3D11Device * Graphics::d3dDev = nullptr;					// dispositivo gr�fico
ID3D11DeviceContext * Graphics::d3dDevContext = nullptr;	// contexto do dispositivo gr�fico 
D3D11_VIEWPORT	Graphics::viewport = { 0 };					// viewport

// ------------------------------------------------------------------------------

Graphics::Graphics() 
{
	// inicializa vari�veis membro
	swapChain			= nullptr;					// ponteiro para swap chain 
	renderTargetView	= nullptr;					// render target view
	blendState          = nullptr;					// mistura de cores
	featureLevel        = D3D_FEATURE_LEVEL_11_0;	// vers�o do Direct3D
	
	bgColor[0]			= 0.0f;						// componente Red
	bgColor[1]			= 0.0f;						// componente Green
	bgColor[2]			= 0.0f;						// componente Blue
	bgColor[3]			= 0.0f;						// componente Alpha (s�lido)

	antialiasing		= 1;						// n�mero de amostras para antialiasing
	quality				= 0;						// n�vel de qualidade das amostras
	vSync               = false;					// vertical sync desligado

	// define flags de depura��o quando compilador estiver no modo Debug
	uint createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// cria objeto para acessar dispositivo gr�fico
	D3D11CreateDevice(
		NULL,								// adaptador de v�deo (NULL = adaptador padr�o)
		D3D_DRIVER_TYPE_HARDWARE,			// tipo de driver D3D (Hardware, Reference ou Software)
		NULL,								// ponteiro para rasterizador em software
		createDeviceFlags,					// modo de depura��o ou modo normal
		NULL,								// featureLevels do Direct3D (NULL = maior suportada)
		0,									// tamanho do vetor featureLevels
		D3D11_SDK_VERSION,                  // vers�o do SDK do Direct3D
		&d3dDev,							// guarda o dispositivo D3D criado
		&featureLevel,						// vers�o do Direct3D utilizada
		&d3dDevContext);					// contexto do dispositivo D3D
}

// ------------------------------------------------------------------------------

Graphics::~Graphics()
{
	// libera blend state
	if (blendState)
	{
		blendState->Release();
		blendState = nullptr;
	}

	// libera render-target
	if (renderTargetView)
	{
		renderTargetView->Release();
		renderTargetView = nullptr;
	}

	// libera swap chain
	if (swapChain)
	{
		// Direct3D � incapaz de fechar quando em tela cheia
		swapChain->SetFullscreenState(false, NULL);
		swapChain->Release();
		swapChain = nullptr;
	}

	// libera contexto do dispositivo gr�fico
	if (d3dDevContext)
	{
		// restaura ao estado original
		d3dDevContext->ClearState();
		d3dDevContext->Release();
		d3dDevContext = nullptr;
	}

	// libera dispositivo gr�fico
	if (d3dDev)
	{
		d3dDev->Release();
		d3dDev = nullptr;
	}
}

// -----------------------------------------------------------------------------

// ajusta o n�mero de amostras para antialiasing
void Graphics::Antialiasing(uint samples)
{ 
	antialiasing = (samples > D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT ? D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT : samples);

	uint maxQuality = 0;
	d3dDev->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, samples, &maxQuality);
	
	if (maxQuality != 0)
		quality = maxQuality-1;
	else
	{
		antialiasing = 1;
		quality = 0;
	}
}

// -----------------------------------------------------------------------------

bool Graphics::Initialize(Window * window)
{
	// ajusta a cor de fundo do backbuffer
	// para a mesma cor de fundo da janela
	COLORREF color = window->Color();

	bgColor[0] = GetRValue(color)/255.0f;						// componente Red
	bgColor[1] = GetGValue(color)/255.0f;						// componente Green
	bgColor[2] = GetBValue(color)/255.0f;						// componente Blue
	bgColor[3] = 1.0f;											// componente Alpha (s�lido)

	// -------------------------------
	// Captura interfaces DXGI
	// -------------------------------

	// pega um ponteiro para o dispositivo Direct3D
	IDXGIDevice * dxgiDevice = nullptr;
	if FAILED(d3dDev->QueryInterface(__uuidof(IDXGIDevice), (void**) &dxgiDevice))
		return false;

	// pega adaptador controlado pelo dispositivo Direct3D (d3dDev)
	IDXGIAdapter * dxgiAdapter = nullptr;
	if FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &dxgiAdapter))
		return false;

	// pega um ponteiro para a DXGIFactory do adaptador
	IDXGIFactory * dxgiFactory = nullptr;
	if FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**) &dxgiFactory))
		return false;

	// -------------------------------
	// Enumera Modos de V�deo 
	// -------------------------------
	
	// enumerar os modos de v�deo garante a realiza��o de um pageflip (mudan�a de apontador) 
	// no lugar de um bitblit (c�pia de bits) quando se est� em modo tela cheia

	// enumera apenas a primeira sa�da do adaptador (ligada ao monitor padr�o)
	IDXGIOutput * dxgiOutput = nullptr;
	dxgiAdapter->EnumOutputs(0, &dxgiOutput);

	// pega o n�mero de modos de v�deo suportados pelo monitor no formato DXGI_FORMAT_R8G8B8A8_UNORM
	uint numModes = 0;
	dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_SCALING, &numModes, NULL);
	
	// cria uma lista dos modos de v�deo suportados por essa combina��o de placa de v�deo e monitor
	DXGI_MODE_DESC * displayModeList = new DXGI_MODE_DESC[numModes];
	dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_SCALING, &numModes, displayModeList);
	
	// pega as dimens�es da tela
	uint screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	uint screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// numerador e denominador da taxa de atualiza��o do v�deo
	uint num = 60;
	uint den = 1;

	// atualiza numerador e denominador com os valores de um modo de v�deo compat�vel com as dimens�es da tela
	for (uint i = 0; i < numModes; ++i)
	{
		if (displayModeList[i].Width == screenWidth && displayModeList[i].Height == screenHeight)
		{
			num = displayModeList[i].RefreshRate.Numerator;
			den = displayModeList[i].RefreshRate.Denominator;
		}
	}

	// -------------------------------
	// Cria uma Swap Chain 
	// -------------------------------

	// descri��o de uma swap chain
	DXGI_SWAP_CHAIN_DESC swapDesc = {0};
	swapDesc.BufferDesc.Width = uint(window->Width());			// largura do backbuffer
	swapDesc.BufferDesc.Height = uint(window->Height());		// altura do backbuffer
	swapDesc.BufferDesc.RefreshRate.Numerator = num;			// taxa de atualiza��o em hertz 
	swapDesc.BufferDesc.RefreshRate.Denominator = den;			// numerador � um inteiro e n�o um racional
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// formato de cores RGBA 8 bits
	swapDesc.SampleDesc.Count = antialiasing;					// amostras por pixel (antialiasing)
	swapDesc.SampleDesc.Quality = quality;						// n�vel de qualidade da imagem
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// utilize superf�cie como RENDER TARGET
	swapDesc.BufferCount = 1;									// n�mero de backbuffers
	swapDesc.OutputWindow = window->Id();						// identificador da janela
	swapDesc.Windowed = (window->Mode() == WINDOWED);			// modo janela ou tela cheia
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				// descarta superf�cie ap�s apresenta��o
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// usa tamanho do backbuffer para tela cheia

	// cria uma swap chain
	if FAILED(dxgiFactory->CreateSwapChain(d3dDev, &swapDesc, &swapChain))
		return false;

	// impede a DXGI de monitorar ALT-ENTER e alternar entre windowed/fullscreen
	if FAILED(dxgiFactory->MakeWindowAssociation(window->Id(), DXGI_MWA_NO_ALT_ENTER))
		return false;

	// -------------------------------
	// Cria uma Render Target View
	// -------------------------------

	// pega a superf�cie backbuffer de uma swapchain
	ID3D11Texture2D * backBuffer = nullptr;
	if FAILED(swapChain->GetBuffer(0, __uuidof(backBuffer), (void**)(&backBuffer)))
		return false;

	// cria uma render-target view do backbuffer
	if FAILED(d3dDev->CreateRenderTargetView(backBuffer, NULL, &renderTargetView))
		return false;
	
	// -------------------------------
	// Output/Viewport/Rasterizer
	// -------------------------------

	// liga uma render-target ao est�gio output-merger
	d3dDevContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

	// configura uma viewport
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = float(window->Width());
	viewport.Height = float(window->Height());
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

	// liga a viewport ao est�gio de rasteriza��o
    d3dDevContext->RSSetViewports(1, &viewport); 

	// ---------------------------------------------
	// Blend State
	// ---------------------------------------------

	// Equa��o de mistura de cores (blending):
	// finalColor = SrcColor * SrcBlend <OP> DestColor * DestBlend

	// Combinando superf�cies transparentes (Alpha Blending)
	// finalColor = SrcColor * ScrAlpha + DestColor * (1-SrcAlpha)

	D3D11_BLEND_DESC blendDesc = { 0 };
	blendDesc.AlphaToCoverageEnable = false;								// destaca a silhueta dos sprites
	blendDesc.IndependentBlendEnable = false;								// usa mesma mistura para todos os render targets
	blendDesc.RenderTarget[0].BlendEnable = true;							// habilita o blending
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;				// fator de mistura da fonte 
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;		// destino da mistura RGB � o alpha invertido 
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;					// opera��o de adi��o na mistura de cores
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;		// fonte da mistura Alpha � o alpha do pixel shader
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;	// destino da mistura Alpha � o alpha invertido
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;			// opera��o de adi��o na mistura de cores
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;					// componentes de cada pixel que podem ser sobrescritos

	// cria a blend state
	if FAILED(d3dDev->CreateBlendState(&blendDesc, &blendState))
		return false;

	// liga a blend state ao est�gio Output-Merger
	d3dDevContext->OMSetBlendState(blendState, nullptr, 0xffffffff);

	// -------------------------------
	// Libera interfaces DXGI
	// -------------------------------

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();
	dxgiOutput->Release();
	backBuffer->Release();

	// inicializa��o bem sucedida
	return true;
}

// -----------------------------------------------------------------------------
