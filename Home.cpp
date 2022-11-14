/**********************************************************************************
// Home (Arquivo de Origem)
//
// Criação:		09 Jun 2019
// Atualização: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Tela de abertura do jogo Breakout
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "EndScreen.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
	backg = new Sprite("Resources/TitleScreen.png");
	help = new Sprite("Resources/help.png");
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
	delete backg;
	delete help;
}

// ------------------------------------------------------------------------------

void Home::Update()
{
	showHelp = false;
	// sai do jogo com a tecla ESC
	if (window->KeyUp(VK_ESCAPE))
		ctrlKeyESC = true;
	if (ctrlKeyESC && window->KeyDown(VK_ESCAPE))
		window->Close();

	if (window->KeyDown('A'))
		showHelp = true;

	// passa ao primeiro nível com ENTER
	if (window->KeyDown(VK_RETURN))
		Engine::Next<Level1>();
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
	backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);

	if (showHelp)
		help->Draw(float(window->CenterX()), float(window->CenterY()));
}

// ------------------------------------------------------------------------------