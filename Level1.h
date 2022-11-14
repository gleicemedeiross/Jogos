/**********************************************************************************
// Home (Arquivo de Cabe�alho)
//
// Cria��o:		09 Jun 2019
// Atualiza��o: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Tela de abertura do jogo Breakout
//
**********************************************************************************/

#ifndef _BREAKOUT_LEVEL1_H_
#define _BREAKOUT_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"
#include "Ball.h"
#include "Font.h"
#include "TileSet.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	Sprite* backg = nullptr;		// background
	Sprite* infobar = nullptr;		// infobar
	Sprite* walls = nullptr;		// muros
	Sprite* avisoEspaco = nullptr;  // aviso de come�o
	
	Sprite* tries[4] = { nullptr };	// tentativas
	TileSet* counter3s = nullptr;	// contador de 3 segundos
	Animation* anim3s = nullptr;	// anima��o de 3 segundos

	Scene* scene = nullptr;			// cena
	Player* player = nullptr;			//player
	Ball* ball = nullptr;			// bola
	Font* premier = nullptr;		// fonte do placar

	uint frameAtual = 0;			// contador de frame de anima��es
	Timer* timer1 = nullptr;		// contador1
	


	bool viewBBox = false;			// habilita visualiza��o da bounding box
	bool ctrlKeyB = false;			// controle da tecla B
	bool ctrlKeyShift = false;		// controle da tecla Shift
	bool ctrlKeySpace = false;		// controle da tecla Space

public:
	void Init();					// inicializa jogo
	void Update();					// atualiza l�gica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// -----------------------------------------------------------------------------

#endif