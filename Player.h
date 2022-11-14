/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:		09 Jun 2019
// Atualização: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Player do jogo Breakout
//
**********************************************************************************/

#ifndef _BREAKOUT_PLAYER_H_
#define _BREAKOUT_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"			// tipos específicos da engine
#include "Object.h"			// interface de Object
#include "Sprite.h"			// interface de Sprites
#include "Animation.h"
#include "TileSet.h"
#include "Timer.h"
#include "Power.h"
#include "Bullet.h"

// ---------------------------------------------------------------------------------
// Constantes Globais
constexpr auto VELOCITY = 720.0f;
// estados possíveis para o jogador
enum PLAYERSTATE { DEAD, INACTIVE, ACTIVE };

enum PLAYERSIZE { SMALL, MEDIUM, BIG };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
	Sprite* spriteT1 = nullptr;			// sprite do player indo para esquerda
	Sprite* spriteT2 = nullptr;			// sprite do player indo para direita
	Sprite* spriteT3 = nullptr;			// sprite do player indo para cima
	Sprite* spriteT4 = nullptr;			// sprite do player indo para baixo
	

	short tries = 3;					// número de tentativas

	TileSet* tileset[3] = { nullptr };
	Animation* anim[3] = { nullptr };
	Geometry* bboxes[3] = { nullptr };


	bool ctrlKeySpace = false;			// controle da tecla Space


public:
	uint state = INACTIVE;				// estado atual do jogador
	uint score = 0;						// placar do level
	Timer timerLevel;					// contador do tempo do level
	float velX = 0.0f;					// velocidade do player
	bool push = false;					// empurra a bola com mais força
	bool pull = false;					// puxa a bola
	Power* goodPower = nullptr;
	Power* badPower = nullptr;
	Power* badPower2 = nullptr;
	Bullet* bullets[4] = { nullptr };
	PLAYERSIZE playerSize = MEDIUM;

	Player();							// construtor
	~Player();							// destrutor

	void OnCollision(Object* obj);		// resolução da colisão
	TileSet* TileSet(uint tset);					// retorna o tileset do player
	void CreateBullets();


	void Tries(bool t);					// seta o número de tentativas
	short Tries();						// retorna o número de tentativas

	void Update();						// atualização do objeto
	void Draw();						// desenho do objeto
};

// ---------------------------------------------------------------------------------



inline TileSet* Player::TileSet(uint tset) {
	return tileset[tset];
}

inline short Player::Tries() {
	return tries;
}

#endif