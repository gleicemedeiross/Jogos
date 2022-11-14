
/**********************************************************************************
 Bullet (Arquivo Fonte)

 Criação:		09 Jun 2019
 Atualização: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descrição:	Poderes do jogo Breakout

**********************************************************************************/


// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Breakout.h"
#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(float posX, float posY) {
	sprite = new Sprite("Resources/bullet.png");
	picked = false;

	Width(sprite->Width());
	Height(sprite->Height());
	bbox = new Rect(-int(Width()) / 2.0f, -int(Height()) / 2.0f, Width() / 2.0f, Height() / 2.0f);
	MoveTo(posX, posY);
	type = BULLET;
	Vel(250);
}

Bullet::~Bullet() {
	delete sprite;
	delete bbox;
}

void Bullet::Update() {
	if (!picked) {
		Translate(0, Vel() * gameTime);
		if (Y() > window->Height())
			Game::gScene->Delete(this, MOVING);
	}
	else {
		Game::gScene->Delete(this, MOVING);
	}
}

void Bullet::OnCollision(Object * obj) {

}

void Bullet::Draw() {
	if (!picked)
		sprite->Draw(X(), Y(), 0.41f);
}