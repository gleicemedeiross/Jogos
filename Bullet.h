
/**********************************************************************************
 Bullet (Arquivo de Cabe�alho)

 Cria��o:		09 Jun 2019
 Atualiza��o: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descri��o:	Poderes do jogo Breakout

**********************************************************************************/

#ifndef _BREAKOUT_BULLET_H_
#define _BREAKOUT_BULLET_H_

// ---------------------------------------------------------------------------------
// Inclus�es

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
	bool picked = false;				// j� foi pego?

	Bullet(float posX, float posY);		// construtor
	~Bullet();							// destrutor

	void OnCollision(Object* obj);		// resolu��o da colis�o

	void Vel(float vY);
	float Vel();

	void Update();						// atualiza��o do objeto
	void Draw();						// desenho do objeto
};

inline float Bullet::Vel() {
	return velY;
}

inline void Bullet::Vel(float vY) {
	velY = vY;
}

#endif