/**********************************************************************************
// EndScreen (Código Fonte)
//
// Criação:		09 Jun 2019
// Atualização: 04 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Nível 1 do jogo Breakout
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Wall.h"
#include "Brick.h"
#include "EndScreen.h"
#include "Player.h"
#include <string>
#include <fstream>
#include "Object.h"
#include "Font.h"
#include "Sprite.h"
#include "TileSet.h"


void EndScreen::Init() {

	// cria sprites do level
	if (!Game::stats.beat[0]) {
		backg = new Sprite("Resources/end.png");
	}
	else if (!Game::stats.beat[1]) {
		backg = new Sprite("Resources/end2.png");
	}
	else if (!Game::stats.beat[2]) {
		backg = new Sprite("Resources/end3.png");
	}
	else {
		backg = new Sprite("Resources/end4.png");
	}

	// cria o sprite de aviso para começar


	// cria fontes e desenha labels
	premier = new Font("Resources/premier.png");
	premier->Spacing(20);	
}

void EndScreen::Finalize() {
	delete backg;
	delete premier;
}

void EndScreen::Update()
{
	if (window->KeyDown(VK_ESCAPE))
	{
		// volta para a tela de abertura
		Game::stats.ballsLost = 0;
		Game::stats.bricksDestroyed = 0;
		Game::stats.beat[0] = false;
		Game::stats.beat[1] = false;
		Game::stats.beat[2] = false;
		Game::stats.score[0] = 0;
		Game::stats.score[1] = 0;
		Game::stats.score[2] = 0;

		Engine::Next<Home>();
	}
}

// ------------------------------------------------------------------------------

void EndScreen::Draw()
{
	// desenha cena
	backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);

	Color blue(0.5f, 0.5f, 0.8f, 1.0f);
	Color yellow(0.90f, 0.70f, 0.0f, 1.0f);

	string textAux = std::to_string(Game::stats.ballsLost);
	premier->Draw(635.0f + (112 - (textAux.length() * 16)), 277.f, textAux, yellow, Layer::FRONT, 0.80f);
	textAux = std::to_string(Game::stats.bricksDestroyed);
	premier->Draw(635.0f + (112 - (textAux.length() * 16)), 315.f, textAux, yellow, Layer::FRONT, 0.80f);
	textAux = std::to_string(Game::stats.score[0]);
	premier->Draw(635.0f + (112 - (textAux.length() * 16)), 397.f, textAux, yellow, Layer::FRONT, 0.80f);
	textAux = std::to_string(Game::stats.score[1]);
	premier->Draw(635.0f + (112 - (textAux.length() * 16)), 435.f, textAux, yellow, Layer::FRONT, 0.80f);
	textAux = std::to_string(Game::stats.score[2]);
	premier->Draw(635.0f + (112 - (textAux.length() * 16)), 473.f, textAux, yellow, Layer::FRONT, 0.80f);
	textAux = std::to_string(Game::stats.score[0] + Game::stats.score[1] + Game::stats.score[2]);
	premier->Draw(635.0f + (112 - (textAux.length() * 16)), 511.f, textAux, yellow, Layer::FRONT, 0.80f);
	
}

// ------------------------------------------------------------------------------