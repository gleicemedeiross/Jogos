/**********************************************************************************
 Ball (Arquivo de Cabeçalho)

 Criação:		09 Jun 2019
 Atualização: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descrição:	Bola do jogo Breakout

**********************************************************************************/

#ifndef _BREAKOUT_BRICK_H_
#define _BREAKOUT_BRICK_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h"
#include "Scene.h"

// Constantes

enum BrickColor {
	BLUE, GREEN, PURPLE, RED, ORANGE, LIGHTBLUE, YELLOW, DARKGREEN, GRAY, BROWN
};

enum BrickState {
	NORMAL, DAMAGED
};

class Brick : public Object
{
private:
	Sprite* spriteAtual = nullptr;
	Sprite* spriteNormal = nullptr;
	Sprite* spriteDamaged = nullptr;

public:
	BrickColor color = BLUE;			// cor do tijolo
	BrickState state = NORMAL;			// estado do tijolo
	ushort value = 0;					// valor do tijolo
	Scene* scene = nullptr;
	ushort brickid = 0;

	Brick(float brickX, float brickY, BrickColor brickColor, BrickState brickState, ushort brickValue, ushort bId);		// construtor
	~Brick();							// destrutor

	void OnCollision(Object* obj);		// resolução da colisão
	void Destroy();						// destrói

	void Update();						// atualização do objeto
	void Draw();						// desenho do objeto
};


#endif