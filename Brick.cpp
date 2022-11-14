/**********************************************************************************
// PacMan (Código Fonte)
//
// Criação:		01 Jan 2013
// Atualização: 04 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exercício sobre detecção de colisão
//
**********************************************************************************/

#include "Ball.h"
#include "Player.h"
#include "Wall.h"
#include "Breakout.h"
#include "Brick.h"
#include "Game.h"

Brick::Brick(float brickX, float brickY, BrickColor brickColor, BrickState brickState, ushort brickValue, ushort bId) {

	scene = Game::gScene;

	switch (brickColor)
	{
	case BLUE:
		spriteNormal = new Sprite("Resources/bluebrick.png");
		spriteDamaged = new Sprite("Resources/bluedamagedbrick.png");
		break;
	case GREEN:
		spriteNormal = new Sprite("Resources/greenbrick.png");
		spriteDamaged = new Sprite("Resources/greendamagedbrick.png");
		break;
	case PURPLE:
		spriteNormal = new Sprite("Resources/purplebrick.png");
		spriteDamaged = new Sprite("Resources/purpledamagedbrick.png");
		break;
	case RED:
		spriteNormal = new Sprite("Resources/redbrick.png");
		spriteDamaged = new Sprite("Resources/reddamagedbrick.png");
		break;
	case ORANGE:
		spriteNormal = new Sprite("Resources/orangebrick.png");
		spriteDamaged = new Sprite("Resources/orangedamagedbrick.png");
		break;
	case LIGHTBLUE:
		spriteNormal = new Sprite("Resources/lightbluebrick.png");
		spriteDamaged = new Sprite("Resources/lightbluedamagedbrick.png");
		break;
	case YELLOW:
		spriteNormal = new Sprite("Resources/yellowbrick.png");
		spriteDamaged = new Sprite("Resources/yellowdamagedbrick.png");
		break;
	case DARKGREEN:
		spriteNormal = new Sprite("Resources/darkgreenbrick.png");
		spriteDamaged = new Sprite("Resources/darkgreendamagedbrick.png");
		break;
	case GRAY:
		spriteNormal = new Sprite("Resources/graybrick.png");
		spriteDamaged = new Sprite("Resources/graydamagedbrick.png");
		break;
	case BROWN:
		spriteNormal = new Sprite("Resources/brownbrick.png");
		spriteDamaged = new Sprite("Resources/browndamagedbrick.png");
		break;
	default:
		spriteNormal = new Sprite("Resources/bluebrick.png");
		spriteDamaged = new Sprite("Resources/bluedamagedbrick.png");
		break;
	}

	color = brickColor;
	state = brickState;
	brickid = bId;
	if (state == NORMAL)
		spriteAtual = spriteNormal;
	else
		spriteAtual = spriteDamaged;

	value = brickValue;

	Width(spriteNormal->Width());
	Height(spriteNormal->Height());
	bbox = new Rect(float(-int(Width()) / 2.f), float(-int(Height() / 2.f)), Width() / 2.f, Height() / 2.f);
	MoveTo(brickX - Width()/2, brickY - Height()/2);

	type = BRICK;

}

Brick::~Brick() {
	delete spriteNormal;
	delete spriteDamaged;
	delete bbox;
}

void Brick::Update() {
	if (state == NORMAL)
		spriteAtual = spriteNormal;
	else
		spriteAtual = spriteDamaged;
}

void Brick::OnCollision(Object * obj) {
}

void Brick::Destroy() {
	//scene->Delete(this, STATIC);
}

void Brick::Draw() {
	spriteAtual->Draw(X(), Y());
}