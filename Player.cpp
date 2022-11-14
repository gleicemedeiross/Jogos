/**********************************************************************************
// Player (Código Fonte)
//
// Criação:		01 Jan 2013
// Atualização: 04 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Player do jogo PacMan
//
**********************************************************************************/

#include "Breakout.h"
#include "Player.h"
#include "Wall.h"
#include "TileSet.h"
#include "Animation.h"
#include "Game.h"
#include "Bullet.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
	push = pull = false;
	tileset[SMALL] = new ::TileSet("Resources/player_small.png", 80, 25, 3, 3);
	tileset[MEDIUM] = new ::TileSet("Resources/player.png", 118, 25, 3, 3);
	tileset[BIG] = new ::TileSet("Resources/player_big.png", 140, 25, 3, 3);
	anim[SMALL] = new Animation(tileset[SMALL], 0.05f, true);
	anim[MEDIUM] = new Animation(tileset[MEDIUM], 0.05f, true);
	anim[BIG] = new Animation(tileset[BIG], 0.05f, true);

	// imagem do pacman é 118x26 (com borda transparente de 4 pixels)
	uint tw = tileset[SMALL]->TileWidth(), th = tileset[SMALL]->TileHeight();
	bboxes[SMALL] = new Rect(float(-int(tw) /2), float(-int(th) /2 + 6), float(tw) / 2.f, float(th) / 2.f);
	tw = tileset[MEDIUM]->TileWidth(), th = tileset[MEDIUM]->TileHeight();
	Width(tw);
	Height(th);
	bboxes[MEDIUM] = new Rect(float(-int(tw) / 2), float(-int(th) / 2 + 6), float(tw) / 2.f, float(th) / 2.f);

	tw = tileset[BIG]->TileWidth(), th = tileset[BIG]->TileHeight();
	bboxes[BIG] = new Rect(float(-int(tw) / 2), float(-int(th) / 2 + 6), float(tw) / 2.f, float(th) / 2.f);

	bbox = bboxes[MEDIUM];
	MoveTo(479.5f, 700.5f);
	bbox->MoveTo(X(), Y());
	type = PLAYER;
	playerSize = MEDIUM;
	velX = 0.0f;
	tries = 3;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete tileset[0];
	delete tileset[1];
	delete tileset[2];
	delete anim[0];
	delete anim[1];
	delete anim[2];
	delete bboxes[0];
	delete bboxes[1];
	delete bboxes[2];
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == BALL)
		obj->OnCollision(this);
	if (obj->Type() == WALL) {
		if (X() > obj->X())
			MoveTo(obj->X() + (obj->Width() / 2) + (Width() / 2), Y());
		if (X() < obj->X())
			MoveTo(obj->X() - (obj->Width() / 2) - (Width() / 2), Y());
	}
	else if (obj->Type() == POWER) {
		Power* newObj = (Power*)obj;
		if (!newObj->picked) {
			newObj->powerTimer.Start();
			newObj->picked = true;
			if (newObj->powerType == PowerType::MORE) {
				if (playerSize == SMALL) {
					playerSize = MEDIUM;
					bbox = bboxes[MEDIUM];
					uint tw = tileset[MEDIUM]->TileWidth(), th = tileset[MEDIUM]->TileHeight();
					Width(tw);
					Height(th);
					bbox->MoveTo(X(), Y());
				}
				else if (playerSize == MEDIUM) {
					playerSize = BIG;
					bbox = bboxes[BIG];
					uint tw = tileset[BIG]->TileWidth(), th = tileset[BIG]->TileHeight();
					Width(tw);
					Height(th);
					bbox->MoveTo(X(), Y());
				}
			}
			else if (newObj->powerType == PowerType::DARKNESS) {
				Game::dark = true;
				Game::multiplier += 0.5f;
			}
			else if (newObj->powerType == PowerType::BULLETS) {
				CreateBullets();
				Game::multiplier += 0.2f;
			}
		}
	}
	else if (obj->Type() == BULLET) {
		Bullet* newObj = (Bullet*)obj;
		if (!newObj->picked) {
			newObj->picked = true;
			if (playerSize == BIG) {
				playerSize = MEDIUM;
				bbox = bboxes[MEDIUM];
				uint tw = tileset[MEDIUM]->TileWidth(), th = tileset[MEDIUM]->TileHeight();
				Width(tw);
				Height(th);
				bbox->MoveTo(X(), Y());
			}
			else if (playerSize == MEDIUM) {
				playerSize = SMALL;
				bbox = bboxes[SMALL];
				uint tw = tileset[SMALL]->TileWidth(), th = tileset[SMALL]->TileHeight();
				Width(tw);
				Height(th);
				bbox->MoveTo(X(), Y());
			}
		}
	}
}

void Player::CreateBullets() {
	if (bullets[1] == nullptr) {
		bullets[0] = new Bullet(336, 100);
		bullets[1] = new Bullet(648, 100);
		Game::gScene->Add(bullets[0], MOVING);
		Game::gScene->Add(bullets[1], MOVING);
	}
	else if (bullets[3] == nullptr) {
		bullets[2] = new Bullet(336, 100);
		bullets[3] = new Bullet(648, 100);
		Game::gScene->Add(bullets[2], MOVING);
		Game::gScene->Add(bullets[3], MOVING);
	}
}


// ---------------------------------------------------------------------------------

void Player::Update()
{
	anim[playerSize]->NextFrame();
	if (state == INACTIVE) {
		if (score == 0) {
			// habilita/desabilita bounding box
			if (window->KeyUp(VK_SPACE))
				ctrlKeySpace = true;
			if (ctrlKeySpace && window->KeyDown(VK_SPACE))
			{
				state = ACTIVE;
				ctrlKeySpace = false;
				timerLevel.Reset();
			}
		}
	}
	else {
		if (state == DEAD)
			timerLevel.Stop();

		push = false;
		pull = false;
		velX = 0;
		if (window->KeyDown(VK_LEFT))
		{
			velX = -VELOCITY;
		}
		if (window->KeyDown(VK_RIGHT))
		{
			velX = VELOCITY;
		}
		if (window->KeyDown('Z'))
			push = true;
		else if (window->KeyDown('X'))
			pull = true;
		// atualiza posição
		Translate(velX * gameTime, 0);

		//// mantém player dentro da tela
		//if (x - 59 < 31)
		//	MoveTo(31.f + 59.f, Y());

		//if (x + 59 > window->Width()-33)
		//	MoveTo(window->Width() -33.0f - 59.f, Y());
	}
	
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
	/*switch (state)
	{
	case T1: spriteT1->Draw(x, y, 0.2f); break;
	case T2: spriteT2->Draw(x, y, 0.2f); break;
	case T3: spriteT3->Draw(x, y, 0.2f); break;
	default:
		spriteT1->Draw(x, y, 0.2f); break;
	}*/

	anim[playerSize]->Draw(x, y, 0.35f);
}

// ---------------------------------------------------------------------------------

void Player::Tries(bool t) {
	if (t) {
		if (tries < 3) {
			tries++;
		}
	}
	else {
		if (tries >= 0) {
			tries--;
		}
	}
}