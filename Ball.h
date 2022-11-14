/**********************************************************************************
 Ball (Arquivo de Cabeçalho)

 Criação:		09 Jun 2019
 Atualização: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descrição:	Bola do jogo Breakout

**********************************************************************************/

#ifndef _BREAKOUT_BALL_H_
#define _BREAKOUT_BALL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h"

// Constantes

constexpr float MINX = 200.0f;
constexpr float MAXX = 2000.0f;
constexpr float MINY = 400.0f;
constexpr float MAXY = 550.0f;

class Ball : public Object
{
private:
	Sprite* sprite = nullptr;
	Sprite* dark_power = nullptr;		// escuridão

	float velX = 0.0f;					// velocidade da bola
	float velY = 0.0f;					// velocidade da bola

public:
	Player* player = nullptr;
	uint state = INACTIVE;				// estado atual do jogador
	bool invX = false;
	bool invY = false;

	Ball(Player* player);								// construtor
	~Ball();							// destrutor

	void OnCollision(Object* obj);		// resolução da colisão

	float VelX();						// retorna a velocidade X da bola
	float VelY();						// retorna a velocidade Y da bola

	void VelX(float vel);				// seta a velocidade X da bola
	void VelY(float vel);				// seta a velocidade Y da bola
	void Vel(float vX, float vY);

	void Update();						// atualização do objeto
	void Draw();						// desenho do objeto
};

inline float Ball::VelX() {
	return velX;
}

inline float Ball::VelY() {
	return velY;
}

inline void Ball::Vel(float vX, float vY) {
	VelX(vX); VelY(vY);
}

#endif