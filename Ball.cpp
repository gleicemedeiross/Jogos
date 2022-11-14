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
#include "Power.h"
#include <stdlib.h>

Ball::Ball(Player* pl) {
	sprite = new Sprite("Resources/ball.png");
	dark_power = new Sprite("Resources/dark_power.png");
	player = pl;
	invX = false;
	invY = false;

	Width(sprite->Width());
	Height(sprite->Height());
	bbox = new Circle(float(Width())/2.f);
	//bbox = new Rect(float(-int(Width())/2), float(-int(Height()/2)), float(Width()/2), float(Height()/2));
	MoveTo(player->X(), player->Y() - (player->Height() / 2) + 6 - (sprite->Height() / 2));

	type = BALL;

	VelX(MINX);
	VelY(-MINY);
}

Ball::~Ball() {
	delete sprite;
	delete bbox;
}

void Ball::Update() {
	if (player->state == INACTIVE || player->state == DEAD) {
		MoveTo(player->X(), player->Y() - (player->Height() / 2) + 6 - (sprite->Height()/2) -1);
	}
	else {
		Translate(VelX() * gameTime, VelY() * gameTime);
	}
	if (Y() - Height() / 2 >= 720) {
		Game::stats.ballsLost++;
		MoveTo(player->X(), player->Y() - (player->Height() / 2) + 6 - (sprite->Height() / 2) - 1);
		player->state = DEAD;
		player->timerLevel.Stop();
		VelX(MINX);
		VelY(-MINY);
		player->Tries(false);
	}
}

void Ball::OnCollision(Object* obj) {
	float _top = Y() - float(Height() / 2.f),
		_bottom = Y() + float(Height() / 2.f),
		_left = X() - float(Width() / 2.f),
		_right = X() + float(Width() / 2.f),
		oTop = obj->Y() - float(obj->Height()/2.f),
		oBottom = obj->Y() + float(obj->Height()/2.f),
		oLeft = obj->X() - float(obj->Width()/2.f),
		oRight = obj->X() + float(obj->Width()/2.f);

	float offset = 0.f;

	Brick* brick = (Brick*)obj;

	switch (obj->Type()) {

		case BRICK:
		case PLAYER:
		case WALL:
			if (VelX() > 0 && VelY() > 0) {		//direita e baixo
				if (_right >= oLeft && _left < oLeft) {
					MoveTo(oLeft - offset -float(Width()/2.f), Y());
					if (!invX) {
						VelX(-VelX());
						invX = !invX;
					}
				} else if (_bottom >= oTop && _top < oTop) {
					MoveTo(X(), oTop - offset -float(Height()/2.f));
					if (!invY) {
						VelY(-VelY());
						invY = !invY;
					}
				}
			}
			else if (VelX() > 0 && VelY() < 0) { //direita e cima
				if (_right >= oLeft && _left < oLeft) {
					MoveTo(oLeft - offset -float(Width()/2.f), Y());
					if (!invX) {
						VelX(-VelX());
						invX = !invX;
					}
				} else if (_top <= oBottom && _bottom > oBottom) {
					MoveTo(X(), oBottom + offset + float(Height()/2.f));
					if (!invY) {
						VelY(-VelY());
						invY = !invY;
					}
				}
			}
			else if (VelX() < 0 && VelY() > 0) { //esquerda e baixo
				if (_left <= oRight && _right > oRight) {
					MoveTo(oRight + offset + float(Width()/2.f), Y());
					if (!invX) {
						VelX(-VelX());
						invX = !invX;
					}
				}
				else if (_bottom >= oTop && _top < oTop) {
					MoveTo(X(), oTop - offset - float(Height()/2.f));
					if (!invY) {
						VelY(-VelY());
						invY = !invY;
					}
				}
			}
			else {								//esquerda e cima
				if (_left <= oRight && _right > oRight) {
					MoveTo(oRight + offset + float(Width()/2.f), Y());
					if (!invX) {
						VelX(-VelX());
						invX = !invX;
					}
				}
				else if (_top <= oBottom && _bottom > oBottom) {
					MoveTo(X(), oBottom + offset + float(Height()/2.f));
					if (!invY) {
						VelY(-VelY());
						invY = !invY;
					}
				}
			}
			

			if (obj->Type() == PLAYER) {
				// se o player estiver com o turbo
				if (player->push) {
					Vel(VelX() * 1.15f, VelY() * 1.15f);
				}
				else if (player->pull) {
					Vel(VelX() * 0.83f, VelY() * 0.95f);
				}
				else {
					Vel(VelX() * 0.97f, VelY() * 0.98f);
				}
			} else if (obj->Type() == BRICK) {

				if (brick->state == NORMAL) {
					brick->state = DAMAGED;
					player->score += uint((brick->value/2)*(VelX()/1.2f)*Game::multiplier);
				}
				else {
					if (brick->color == GRAY) {
						switch (brick->value % 10) {
						case PowerType::MORE:
							player->goodPower = new Power(player, PowerType::MORE, brick->X(), brick->Y());
							brick->scene->Add(player->goodPower, MOVING);
							break;
						case PowerType::DARKNESS:
							player->badPower = new Power(player, PowerType::DARKNESS, brick->X(), brick->Y());
							brick->scene->Add(player->badPower, MOVING);
							break;
						case PowerType::BULLETS:
							player->badPower2 = new Power(player, PowerType::BULLETS, brick->X(), brick->Y());
							brick->scene->Add(player->badPower2, MOVING);
							break;
						}
					}

					player->score += uint(brick->value*(VelX()/1.2f)*Game::multiplier);
					Game::stats.bricksDestroyed++;
					Game::gScene->Delete(brick, STATIC);
				}
				Vel(VelX()*0.98f, VelY()*0.98f);
			}
			else {
				Vel(VelX()*0.98f, VelY()*0.98f);
			}
			break;
		default:
			break;
	}
}

void Ball::Draw() {
	sprite->Draw(X(), Y());
	if (Game::dark)
		dark_power->Draw(X(), Y(), 0.4f);
}

void Ball::VelX(float vel) {
	if (abs(vel) < MINX)
		velX = (vel < 0 ? -MINX : MINX);
	else if (abs(vel) > MAXX)
		velX = (vel < 0 ? -MAXX : MAXX);
	else
		velX = vel;
}

void Ball::VelY(float vel) {
	if (abs(vel) < MINY)
		velY = (vel < 0 ? -MINY : MINY);
	else if (abs(vel) > MAXY)
		velY = (vel < 0 ? -MAXY : MAXY);
	else
		velY = vel;
}