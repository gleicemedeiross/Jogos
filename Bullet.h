
/**********************************************************************************
 Bullet (Arquivo de Cabeçalho)

 Criação:		09 Jun 2019
 Atualização: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descrição:	Poderes do jogo Breakout

**********************************************************************************/

#ifndef _BREAKOUT_BULLET_H_
#define _BREAKOUT_BULLET_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

class Player;

class Bullet : public Object
{
private:
	Sprite* sprite = nullptr;

	float velY = 0.0f;					// velocidade da bola

public:
	bool picked = false;				// já foi pego?

	Bullet(float posX, float posY);		// construtor
	~Bullet();							// destrutor

	void OnCollision(Object* obj);		// resolução da colisão

	void Vel(float vY);
	float Vel();

	void Update();						// atualização do objeto
	void Draw();						// desenho do objeto
};

inline float Bullet::Vel() {
	return velY;
}

inline void Bullet::Vel(float vY) {
	velY = vY;
}

#endif