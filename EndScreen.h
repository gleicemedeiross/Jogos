/**********************************************************************************
// EndScreen (Arquivo de Cabeçalho)
//
// Criação:		09 Jun 2019
// Atualização: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Tela final do jogo Breakout
//
**********************************************************************************/

#ifndef _BREAKOUT_ENDSCREEN_H_
#define _BREAKOUT_ENDSCREEN_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"
#include "Ball.h"
#include "Font.h"
#include "TileSet.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class EndScreen : public Game
{
private:
	Sprite* backg = nullptr;		// background
	Sprite* gameOver = nullptr;			
	Sprite* congratulations = nullptr;

	Scene* scene = nullptr;			// cena
	Font* premier = nullptr;		// fonte do placar

public:
	void Init();					// inicializa jogo
	void Update();					// atualiza lógica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// -----------------------------------------------------------------------------

#endif