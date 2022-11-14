/**********************************************************************************
// Engine (Arquivo de Cabe�alho)
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

#ifndef _DESENVJOGOS_ENGINE_H_
#define _DESENVJOGOS_ENGINE_H_

// ---------------------------------------------------------------------------------

#include "Game.h"						// implementa��o do jogo
#include "Window.h"						// janela do jogo
#include "Graphics.h"					// hardware gr�fico
#include "Renderer.h"					// renderizador de sprites
#include "Timer.h"						// medidor de tempo

// ---------------------------------------------------------------------------------

class Engine
{
private:
	static Game* game;					// jogo a ser executado
	Timer  timer;						// medidor de tempo
	bool   paused;					    // estado do jogo

	float FrameTime();					// calcula o tempo do quadro
	int   Loop();						// inicia execu��o do jogo

public:
	static Window   * window;			// janela do jogo
	static Graphics * graphics;			// dispositivo gr�fico
	static Renderer * renderer;			// renderizador de sprites
	static float      frameTime;		// tempo do quadro atual

	Engine();							// construtor
	~Engine();							// destrutor

	int  Start(Game * level);			// inicia o la�o do jogo

	template<class T>
	static void Next()					// muda para pr�ximo n�vel do jogo
	{
		if (game)
		{
			game->Finalize();
			delete game;
			game = new T();
			game->Init();
		}
	};
};

// ---------------------------------------------------------------------------------

#endif