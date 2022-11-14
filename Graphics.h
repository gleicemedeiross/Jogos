/**********************************************************************************
// Graphics (Arquivo de Cabe�alho)
// 
// Cria��o:		06 Abr 2011
// Atualiza��o:	24 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Graphics � uma classe que faz uso das fun��es do Direct3D para 
//              acessar o hardware de acelera��o gr�fica da placa de v�deo.
//
**********************************************************************************/

#ifndef _DESENVJOGOS_GRAPHICS_H_
#define _DESENVJOGOS_GRAPHICS_H_

// --------------------------------------------------------------------------------
// Inclus�es

#include <dxgi.h>			// infraestrutura gr�fica do DirectX
#include <d3d11.h>			// principais fun��es do Direct3D
#include "Window.h"			// cria e configura uma janela do Windows
#include "Types.h"			// tipos espec�ficos da engine

// --------------------------------------------------------------------------------

class Graphics
{
private:
	static ID3D11Device        * d3dDev;					// dispositivo gr�fico
	static ID3D11DeviceContext * d3dDevContext;				// contexto do dispositivo gr�fico
	D3D_FEATURE_LEVEL			 featureLevel;				// vers�o D3D suportada pelo hardware
	IDXGISwapChain             * swapChain;					// swap chain 			
	ID3D11RenderTargetView     * renderTargetView;			// render target view do backbuffer
	ID3D11BlendState           * blendState;				// configura��o da mistura de cores
	static D3D11_VIEWPORT		 viewport;					// viewport
	float						 bgColor[4];				// cor de fundo do backbuffer
	uint						 antialiasing;				// n�mero de amostras para antialiasing
	uint						 quality;					// n�vel de qualidade das amostras
	bool						 vSync;						// vertical sync 

public:
	Graphics();												// constructor
	~Graphics();											// destructor

	static ID3D11Device * Device();							// retorna dispositivo Direct3D
	static ID3D11DeviceContext * Context();					// retorna o contexto do dispositivo D3D
	static const D3D11_VIEWPORT * Viewport();				// retorna a viewport utilizada

	void Antialiasing(uint samples);						// ajusta o n�mero de amostras para antialiasing
	void VSync(bool state);									// liga/desliga vertical sync
	void Clear();											// limpa o backbuffer com a cor de fundo
	bool Present();											// apresenta desenho na tela
	bool Initialize(Window * window);						// inicializa o Direct3D
	
};

// --------------------------------------------------------------------------------
// M�todos Inline

// retorna dispositivo Direct3D
inline ID3D11Device * Graphics::Device()
{ return d3dDev; }

// retorna o contexto do dispositivo D3D
inline ID3D11DeviceContext * Graphics::Context()
{ return d3dDevContext; }

// retorna a viewport utilizada
inline const D3D11_VIEWPORT * Graphics::Viewport()
{	return &viewport; }

// liga/desliga vertical sync
inline void Graphics::VSync(bool state)
{ vSync = state; }

// limpa o bacbuffer para o pr�ximo quadro
inline void Graphics::Clear()
{ 	d3dDevContext->ClearRenderTargetView(renderTargetView, bgColor); }

// apresenta desenho na tela (troca backbuffer com frontbuffer)
inline bool Graphics::Present()
{ return SUCCEEDED(swapChain->Present(vSync, NULL)); }

// --------------------------------------------------------------------------------

#endif