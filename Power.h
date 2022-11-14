
/**********************************************************************************
 Power (Arquivo de Cabe�alho)

 Cria��o:		09 Jun 2019
 Atualiza��o: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descri��o:	Poderes do jogo Breakout

**********************************************************************************/

#ifndef _BREAKOUT_POWER_H_
#define _BREAKOUT_POWER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"
#include "Object.h"
//#include "Player.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Timer.h"

class Player;

enum PowerType
{
	MORE, BULLETS, DARKNESS
};

class Power : public Object
{
private:
	TileSet* tileset = nullptr;
	Animation* anim = nullptr;

	float velY = 0.0f;					// velocidade da bola

public:
	Player* player = nullptr;
	PowerType powerType = MORE;				// tipo do poder
	bool picked = false;						// j� foi pego?
	bool extra = false;
	float duration = 0;							// dura��o, se tiver.
	Timer powerTimer;							// timer do poder, se tiver dura��o.

	Power(Player* pplayer, PowerType ppowerType, float posX, float posY);			// construtor
	~Power();							// destrutor

	void OnCollision(Object* obj);		// resolu��o da colis�o

	void Vel(float vY);
	float Vel();

	void Update();						// atualiza��o do objeto
	void Draw();						// desenho do objeto
};

inline float Power::Vel() {
	return velY;
}

inline void Power::Vel(float vY) {
	velY = vY;
}

#endif