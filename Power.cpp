
/**********************************************************************************
 Power (Arquivo Fonte)

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
#include "Power.h"
#include "Breakout.h"
#include "TileSet.h"
#include "Animation.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"

Power::Power(Player* pplayer, PowerType ppowerType, float posX, float posY) {
	duration = 0.01f;
	powerType = ppowerType;
	extra = false;
	switch (ppowerType) {
		case MORE:
			duration = 10.0f;
			tileset = new TileSet("Resources/yellow_star.png", 1, 7);
			break;
		case DARKNESS:
			duration = 15.0f;
			tileset = new TileSet("Resources/dark_star.png", 1, 7);
			break;
		case BULLETS:
			duration = 6.f;
			tileset = new TileSet("Resources/dark_star.png", 1, 7);
			break;
	}
	anim = new Animation(tileset, 0.15f, true);
	picked = false;

	player = pplayer;

	powerTimer.Reset();
	powerTimer.Stop();

	Width(tileset->TileWidth());
	Height(tileset->TileHeight());
	bbox = new Rect(-int(Width()) / 2.0f, -int(Height()) / 2.0f, Width() / 2.0f, Height() / 2.0f);
	MoveTo(posX, posY);
	type = POWER;
	Vel(100);
}

Power::~Power() {
	delete tileset;
	delete anim;
	delete bbox;
}

void Power::Update() {
	if (!picked) {
		anim->NextFrame();
		Translate(0, Vel() * gameTime);
		if (Y() > window->Height()) {
			switch (powerType)
			{
			case MORE:
				player->goodPower = nullptr;
				Game::gScene->Delete(this, MOVING);
				break;
			case DARKNESS:
				player->badPower = nullptr;
				Game::gScene->Delete(this, MOVING);
				break;
			case BULLETS:
				player->badPower2 = nullptr;
				Game::gScene->Delete(this, MOVING);
				break;
			default:
				break;
			}
		}

	}
	else {
		if (powerTimer.Elapsed() > duration) {

			switch (powerType)
			{
			case MORE:
				player->goodPower = nullptr;
				Game::gScene->Delete(this, MOVING);
				break;
			case BULLETS:
				player->badPower2 = nullptr;
				Game::gScene->Delete(this, MOVING);
				break;
			case DARKNESS:
				player->badPower = nullptr;
				Game::dark = false;
				Game::gScene->Delete(this, MOVING);
				break;
			default:
				break;
			}
		}
		else if (powerType == BULLETS) {
			if (powerTimer.Elapsed() >= 3.f && !extra) {
				extra = true;
				player->CreateBullets();
			}
		}
	}
}

void Power::OnCollision(Object* obj) {

}

void Power::Draw() {
	if (!picked)
		anim->Draw(X(), Y());
}