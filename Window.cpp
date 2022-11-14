/**********************************************************************************
// Window (C�digo Fonte)
// 
// Cria��o:		19 Mai 2007
// Atualiza��o:	13 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	A classe abstrai todos os detalhes de configura��o de
//              uma janela para um jogo. 
//
**********************************************************************************/

#include "Window.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe
bool Window::windowKeys[256] = { 0 };						// estado do teclado/mouse
int	 Window::windowMouseX = 0;								// posi��o do mouse no eixo x
int	 Window::windowMouseY = 0;								// posi��o do mouse no eixo y

// -------------------------------------------------------------------------------
// Construtor

Window::Window()
{
	hInstance		= GetModuleHandle(NULL);				// identificador da aplica��o
	windowHandle	= 0;									// identificador da janela do jogo
	windowWidth		= GetSystemMetrics(SM_CXSCREEN);		// a janela ocupa toda a tela (tela cheia)
	windowHeight	= GetSystemMetrics(SM_CYSCREEN);		// a janela ocupa toda a tela (tela cheia)
	windowIcon		= LoadIcon(NULL, IDI_APPLICATION);		// �cone padr�o de uma aplica��o
	windowCursor	= LoadCursor(NULL, IDC_ARROW);			// cursor padr�o de uma aplica��o
	windowColor	    = RGB(0,0,0);							// cor de fundo padr�o � preta
	windowTitle		= string("Windows Game");				// t�tulo padr�o da janela
	windowStyle		= WS_POPUP | WS_VISIBLE;				// estilo para tela cheia
	windowMode		= FULLSCREEN;							// modo padr�o � tela cheia
	windowPosX		= 0;									// posi��o inicial da janela no eixo x
	windowPosY		= 0;									// posi��o inicial da janela no eixo y
	windowCenterX   = windowWidth/2.0f;						// centro da janela no eixo x
	windowCenterY	= windowHeight/2.0f;					// centro da janela no eixo y
}

// -------------------------------------------------------------------------------

void Window::Mode(int mode)
{
	windowMode = mode;

	if (mode == WINDOWED)
	{
		// modo em janela
		windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE; 
	}
	else
	{
		// modo em tela cheia ou sem bordas
		windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE; 
	} 
}

// -------------------------------------------------------------------------------

void Window::Size(int width, int height)
{ 
	// window size
	windowWidth = width; 
	windowHeight = height;

	// calcula a posi��o do centro da janela
	windowCenterX = windowWidth/2.0f;
	windowCenterY = windowHeight/2.0f;

	// ajusta a posi��o da janela para o centro da tela
	windowPosX = (GetSystemMetrics(SM_CXSCREEN)/2) - (windowWidth/2);
	windowPosY = (GetSystemMetrics(SM_CYSCREEN)/2) - (windowHeight/2);
}

// -------------------------------------------------------------------------------

void Window::Print(string text, int x, int y, COLORREF color)
{
	// esta fun��o exibe o texto na posi��o (x,y) da tela usando a cor especificada
	// ela usa a GDI do Windows (lenta) e deve ser usada apenas para depura��o

	// pega o contexto do dispositivo gr�fico
	HDC xdc = GetDC(windowHandle); 

	// define a cor do texto
	SetTextColor(xdc, color);

	// define o fundo do texto como transparente
	SetBkMode(xdc, TRANSPARENT);

	// mostra o texto
	TextOut(xdc, x, y, text.c_str(), text.size());

	// libera o contexto do dispositivo
	ReleaseDC(windowHandle, xdc);
}

// -------------------------------------------------------------------------------

bool Window::Create()
{
	WNDCLASSEX wndClass; 
	
	// definindo uma classe de janela chamada "GameWindow"
	wndClass.cbSize         = sizeof(WNDCLASSEX);
	wndClass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= Window::WinProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= windowIcon;
	wndClass.hCursor		= windowCursor; 
	wndClass.hbrBackground	= (HBRUSH) CreateSolidBrush(windowColor);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= "GameWindow";
	wndClass.hIconSm        = windowIcon;

	// registrando "GameWindow"
	if (!RegisterClassEx(&wndClass))
		return false;

	// criando uma janela baseada na classe "GameWindow" 
	windowHandle = CreateWindowEx(
		NULL,							// estilos extras
		"GameWindow",					// nome da "window class"
		windowTitle.c_str(),			// t�tulo da janela
		windowStyle,					// estilo da janela
		windowPosX, windowPosY,			// posi��o (x,y) inicial
		windowWidth, windowHeight,		// largura e altura da janela
		NULL,							// identificador da janela pai
		NULL,							// identificador do menu
		hInstance,						// identificador da aplica��o
		NULL);							// par�metros de cria��o

	// Ao usar o modo em janela � preciso levar em conta que as barras 
	// e bordas ocupam espa�o na janela. O c�digo abaixo ajusta o tamanho
	// da janela de forma que a �rea cliente do jogo fique no tamanho 
	// (windowWidth x windowHeight)

	if (windowMode == WINDOWED)
	{
		// ret�ngulo com o tamanho da �rea cliente desejada
		RECT winRect = {0, 0, windowWidth, windowHeight};

		// ajusta o tamanho do ret�ngulo
		AdjustWindowRectEx(&winRect,
			GetWindowStyle(windowHandle),
			GetMenu(windowHandle) != NULL,
			GetWindowExStyle(windowHandle));

		// atualiza posi��o da janela
		windowPosX = (GetSystemMetrics(SM_CXSCREEN)/2) - ((winRect.right - winRect.left)/2);
		windowPosY = (GetSystemMetrics(SM_CYSCREEN)/2) - ((winRect.bottom - winRect.top)/2);

		// redimensiona janela com uma chamada a MoveWindow
		MoveWindow(
			windowHandle,                  // identificador da janela
			windowPosX,                    // posi��o x
			windowPosY,                    // posi��o y
			winRect.right - winRect.left,  // largura
			winRect.bottom - winRect.top,  // altura
			TRUE);						   // repintar
	}

	// retorna estado da inicializa��o (bem sucedida ou n�o)
	return (windowHandle ? true : false);
}

// -------------------------------------------------------------------------------

LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_MOUSEMOVE:			// movimento do mouse registrado
		windowMouseX = LOWORD(lParam);
		windowMouseY = HIWORD(lParam);
		return 0;

	case WM_KEYDOWN:			// tecla do teclado pressionada
	case WM_LBUTTONDOWN:		// bot�o esquerdo do mouse pressionado
	case WM_MBUTTONDOWN:		// bot�o do meio do mouse pressionado
	case WM_RBUTTONDOWN:		// bot�o direito do mouse pressionado
		windowKeys[wParam] = true;
		return 0;

	case WM_KEYUP:				// tecla do teclado liberada
	case WM_LBUTTONUP:			// bot�o esquerdo do mouse liberado
	case WM_MBUTTONUP:			// bot�o do meio do mouse liberado
	case WM_RBUTTONUP:			// bot�o direito do mouse liberado
		windowKeys[wParam] = false;
		return 0;

	// descomente as linhas abaixo para impedir que ALT-F4 feche a janela
	//case WM_SYSKEYDOWN:
	//	if (wParam == VK_F4)
	//		return 0;
	//	break;

		// a janela foi destruida
	case WM_DESTROY: 
		// envia uma mensagem WM_QUIT para encerrar o loop da aplica��o
		PostQuitMessage(0);
		return 0;
    }

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// -----------------------------------------------------------------------------
