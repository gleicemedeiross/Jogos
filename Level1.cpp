/**********************************************************************************
// Level1 (Código Fonte)
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
#include "Level1.h"
#include "Player.h"
#include <string>
#include <fstream>
#include "Object.h"
#include "Font.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Level2.h"
#include "EndScreen.h"

constexpr auto LVLTIME = 240.f;

void Level1::Init() {  
	timer1 = new Timer();
	timer1->Reset();
	timer1->Stop();

	// cria o gerenciador da cena
	scene = new Scene();
	Game::gScene = scene;

	// cria sprites do level
	backg = new Sprite("Resources/bg1.png");
	infobar = new Sprite("Resources/infobar.png");
	walls = new Sprite("Resources/walls.png");

	counter3s = new TileSet("Resources/counter.png", 1, 3);
	anim3s = new Animation(counter3s, 0.001f, true);



	// cria sprites auxiliares
	avisoEspaco = new Sprite("Resources/press_space.png");

	// cria sprites que mostram quantas tentativas restam
	tries[0] = new Sprite("Resources/ball0.png");
	tries[1] = new Sprite("Resources/ball1.png");
	tries[2] = new Sprite("Resources/ball2.png");
	tries[3] = new Sprite("Resources/ball3.png");

	// cria o sprite de aviso para começar


	// cria fontes e desenha labels
	premier = new Font("Resources/premier.png");
	premier->Spacing(20);

	// cria o jogador
	player = new Player();
	scene->Add(player, MOVING);

	// cria a bola
	ball = new Ball(player);
	scene->Add(ball, MOVING);


	// cria walls a partir do arquivo
	Wall* wall;
	ushort width, height, value, brickState, brickColor;
	float posX, posY;

	std::ifstream fin;
	fin.open("Walls.txt");
	fin >> width;
	while (!fin.eof())
	{
		if (fin.good()) {
			// lê a linha com as informações
			fin >> height; fin >> posX; fin >> posY;
			wall = new Wall(width, height);
			wall->MoveTo(posX, posY);
			scene->Add(wall, STATIC);
		}
		else {
			// ignora comentários
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}
		fin >> width;
	}
	fin.close();

	// cria bricks a partir do arquivo
	Brick* brick;
	uint totalBricks = 0;

	fin.open("L1Bricks.txt");
	fin >> value;
	while (!fin.eof())
	{
		if (fin.good()) {
			// lê a linha com as informações
			totalBricks++;
			fin >> brickColor; fin >> brickState; fin >> posX; fin >> posY;
			brick = new Brick(posX, posY, (BrickColor) brickColor, (BrickState) brickState, value, totalBricks);
			brick->MoveTo(posX, posY);
			scene->Add(brick, STATIC);
		}
		else {
			// ignora comentários
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}
		fin >> value;
	}
	fin.close();
	Game::stats.totalBricks[0] = totalBricks;
}

void Level1::Finalize() {
	delete scene;
	delete backg;
	delete infobar;
	delete walls;
	delete avisoEspaco;
	delete anim3s;
	delete counter3s;
	delete timer1;
	for (auto i : tries)
		delete i;
}

void Level1::Update()
{
	// habilita/desabilita bounding box
	if (window->KeyUp('B'))
		ctrlKeyB = true;
	if (ctrlKeyB && window->KeyDown('B'))
	{
		viewBBox = !viewBBox;
		ctrlKeyB = false;
	}



	if (window->KeyDown(VK_ESCAPE))
	{
		// volta para a tela de abertura
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
	else if (window->KeyDown('N'))
	{
		// passa manualmente para o próximo nível
		Game::stats.beat[0] = true;
		Engine::Next<Level2>();
	}
	else
	{
		// atualiza cena
		scene->Update();
		scene->CollisionDetection();
		ball->invX = false;
		ball->invY = false;
		Game::stats.score[0] = player->score;
		anim3s->NextFrame();
		// se o player acabou de perder uma bola, mostra o timer
		if (player->state == DEAD) {

			if (player->Tries() >= 0) {
				if (timer1->stoped) {
					timer1->Reset();
				}
				if (timer1->Elapsed() <= 1) {
					anim3s->Frame(2);
				}
				else if (timer1->Elapsed() <= 2) {
					anim3s->Frame(1);
				}
				else if (timer1->Elapsed() <= 3) {
					anim3s->Frame(0);
				}
				else if (timer1->Elapsed() > 3) {
					timer1->Stop();
					player->state = ACTIVE;
					player->timerLevel.Start();
				}
			}
		}
		// se acabou as bolas, tchau
		if (player->Tries() == -1) {
			Engine::Next<EndScreen>();
		}
		else if (player->score > 0 && player->timerLevel.Elapsed() > LVLTIME) {
			Engine::Next<EndScreen>();
		}
		else if (Game::stats.bricksDestroyed >= Game::stats.totalBricks[0]) {
			Engine::Next<Level2>();
		}
	}
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
	// desenha cena
	backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	infobar->Draw(float(window->CenterX()), float(window->CenterY()), 0.3f);
	walls->Draw(float(window->CenterX()), float(window->CenterY()), 0.3f);
	scene->Draw();

	Color blue(0.5f, 0.5f, 0.8f, 1.0f);
	Color yellow(0.90f, 0.70f, 0.0f, 1.0f);

	int num = 119;
	int num2 = 81118;
	string textAux = std::to_string(player->score);
	premier->Draw(838.0f + (112 - (textAux.length() * 16)), 23.f, textAux, yellow, Layer::FRONT, 0.80f);
	//textAux = std::to_string(num2);
	if (player->state != INACTIVE)
		textAux = std::to_string(int(LVLTIME) - int(player->timerLevel.Elapsed()));
	else
		textAux = std::to_string(int(LVLTIME));
	premier->Draw(598.0f + (96 - (textAux.length() * 16)), 23.f, textAux, yellow, Layer::FRONT,0.80f);
	
	
	
	switch (player->Tries())
	{
		case 3:
			tries[3]->Draw(446.f, 23.f, Layer::FRONT);
			break;
		case 2:
			tries[2]->Draw(446.f, 23.f, Layer::FRONT);
			break;
		case 1:
			tries[1]->Draw(446.f, 23.f, Layer::FRONT);
			break;
		default:
			tries[0]->Draw(446.f, 23.f, Layer::FRONT);
			break;
	}

	switch (player->state)
	{
		case INACTIVE:
			avisoEspaco->Draw(window->CenterX(), window->CenterY()+150,.3f);
			break;
		case DEAD:
			anim3s->Draw(window->CenterX(), window->CenterY() + 150, .3f);
			break;
	default:
		break;
	}

	// desenha bounding box dos objetos
	if (viewBBox)
	{
		Engine::renderer->BeginPixels();
		scene->Begin();
		Object* obj = nullptr;
		while (obj = scene->Next())
			Engine::renderer->Draw(obj->bbox, 0xffff00ff);
		Engine::renderer->EndPixels();
	}
}

// ------------------------------------------------------------------------------