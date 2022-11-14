/**********************************************************************************
 Ball (Arquivo de Cabe�alho)

 Cria��o:		09 Jun 2019
 Atualiza��o: 09 Jun 2019
 Compilador:	Visual C++ 2019

 Descri��o:	Bola do jogo Breakout

**********************************************************************************/

#ifndef _BREAKOUT_BRICK_H_
#define _BREAKOUT_BRICK_H_

// ---------------------------------------------------------------------------------
// Inclus�es

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

	void OnCollision(Object* obj);		// resolu��o da colis�o
	void Destroy();						// destr�i

	void Update();						// atualiza��o do objeto
	void Draw();						// desenho do objeto
};


#endif