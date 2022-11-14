
/**********************************************************************************
 Power (Arquivo de Cabeçalho)

 Criação:		09 Jun 2019
 Atualização: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descrição:	Poderes do jogo Breakout

**********************************************************************************/

#ifndef _BREAKOUT_POWER_H_
#define _BREAKOUT_POWER_H_

// ---------------------------------------------------------------------------------
// Inclusões

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
	bool picked = false;						// já foi pego?
	bool extra = false;
	float duration = 0;							// duração, se tiver.
	Timer powerTimer;							// timer do poder, se tiver duração.

	Power(Player* pplayer, PowerType ppowerType, float posX, float posY);			// construtor
	~Power();							// destrutor

	void OnCollision(Object* obj);		// resolução da colisão

	void Vel(float vY);
	float Vel();

	void Update();						// atualização do objeto
	void Draw();						// desenho do objeto
};

inline float Power::Vel() {
	return velY;
}

inline void Power::Vel(float vY) {
	velY = vY;
}

#endif