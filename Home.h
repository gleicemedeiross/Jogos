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

#ifndef _BREAKOUT_HOME_H_
#define _BREAKOUT_HOME_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
	Sprite * backg = nullptr;		// background
	Sprite* help = nullptr;
	bool ctrlKeyESC = false;		// controla o pressionamento do ESC

public:
	bool showHelp = false;
	void Init();					// inicializa jogo
	void Update();					// atualiza l�gica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// -----------------------------------------------------------------------------

#endif