/**********************************************************************************
// Engine (C�digo Fonte)
//
// Cria��o:		15 Mai 2014
// Atualiza��o:	31 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	A fun��o da Engine � rodar jogos criados a partir da classe
//              abstrata Game. Todo jogo deve ser uma classe derivada de Game
//              e portanto deve implementar as fun��es membro Init, Update, Draw
//              e Finalize, que ser�o chamadas pelo motor em um la�o de tempo real.
//              Para usar a classe Engine, o programador deve criar uma inst�ncia
//              e chamar o m�todo Start(), passando um objeto derivado de Game.
//
**********************************************************************************/

#include "Engine.h"
#include <windows.h>
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------
// Inicializa��o de vari�veis est�ticas da classe

Game     * Engine::game      = nullptr;		// jogo em execu��o
Window   * Engine::window    = nullptr;		// janela do jogo
Graphics * Engine::graphics  = nullptr;		// dispositivo gr�fico
Renderer * Engine::renderer  = nullptr;		// renderizador de sprites 
float      Engine::frameTime = 0.0f;		// tempo do quadro atual

// -------------------------------------------------------------------------------

Engine::Engine()
{
	paused   = false;
	window   = new Window();
	graphics = new Graphics();
	renderer = new Renderer();
}

// -------------------------------------------------------------------------------

Engine::~Engine()
{
	if (game)
		delete game;

	delete renderer;
	delete graphics;
	delete window;
}

// -----------------------------------------------------------------------------

int Engine::Start(Game * level)
{
	game = level;

	// cria janela do jogo
	window->Create();

	// inicializa dispositivo gr�fico
	graphics->Initialize(window);

	// inicializa renderizador de sprites
	renderer->Initialize(window, graphics);

	// ajusta a resolu��o do Sleep para 1 milisegundo
	// requer uso da biblioteca winmm.lib
	timeBeginPeriod(1);

	int exitCode = Loop();

	// volta a resolu��o do Sleep ao valor original
	timeEndPeriod(1);

	return exitCode;
}

// -------------------------------------------------------------------------------

int Engine::Loop()
{
	// inicia contagem de tempo
	timer.Start();

	// inicializa��o do jogo
	game->Init();

	// mensagens do Windows
	MSG  msg = { 0 };

	// controle da tecla pause (registra novo 
	// pressionamento somente ap�s libera��o da tecla)
	bool pauseCtrl = true;

	// la�o principal do jogo
	do
	{
		// testa se tem mensagem do windows para tratar
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// -----------------------------------------------
			// Pausa/Resume Jogo
			// -----------------------------------------------

			if (pauseCtrl)
			{
				if (window->KeyDown('P'))
				{
					paused = !paused;
					pauseCtrl = false;

					if (paused)
						timer.Stop();
					else
						timer.Start();
				}
			}
			else
			{
				if (window->KeyUp('P'))
					pauseCtrl = true;
			}

			// -----------------------------------------------

			if (!paused)
			{
				// calcula o tempo do quadro
				frameTime = FrameTime();

				// atualiza��o do jogo 
				game->Update();

				// limpa a tela para o pr�ximo quadro
				graphics->Clear();

				// desenha o jogo
				game->Draw();

				// renderiza sprites
				renderer->Render();

				// apresenta o jogo na tela (troca backbuffer/frontbuffer)
				graphics->Present();
			}
			else
			{
				Sleep(15);
			}

			// ----------------------------------------------
		}

	} while (msg.message != WM_QUIT);

	// finaliza��o do jogo
	game->Finalize();

	// encerra aplica��o
	return int(msg.wParam);
}

// -----------------------------------------------------------------------------

float Engine::FrameTime()
{
	// ----- START DEBUG ----------
#ifdef _DEBUG
	static float totalTime = 0.0f;	// tempo total transcorrido 
	static uint  frameCount = 0;	// contador de frames transcorridos
#endif
	// ------ END DEBUG -----------

	// tempo do frame atual
	frameTime = timer.Reset();

	// ----- START DEBUG ----------
#ifdef _DEBUG
	// tempo acumulado dos frames
	totalTime += frameTime;

	// incrementa contador de frames
	frameCount++;

	// a cada 1000ms (1 segundo) atualiza indicador de FPS na janela
	if (totalTime >= 1.0f)
	{
		stringstream text;			// fluxo de texto para mensagens
		text << std::fixed;			// sempre mostra a parte fracion�ria
		text.precision(3);			// tr�s casas depois da v�rgula

		text << window->Title().c_str() << "    "
			<< "FPS: " << frameCount << "    "
			<< "Frame Time: " << frameTime * 1000 << " (ms)";

		SetWindowText(window->Id(), text.str().c_str());

		frameCount = 0;
		totalTime -= 1.0f;
	}
#endif
	// ------ END DEBUG ----------- 

	return frameTime;
}

// -----------------------------------------------------------------------------
