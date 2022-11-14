/**********************************************************************************
// Wall (Código Fonte)
//
// Criação:		09 Jun 2019
// Atualização: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Ponto de mudança de direção para a(s) bola(s)
//
**********************************************************************************/

#include "Breakout.h"
#include "Wall.h"

Wall::Wall(ushort w, ushort h) {
	width = w;
	height = h;

	bbox = new Rect(-w / 2.0f, -h / 2.0f, w / 2.0f, h / 2.0f);
	type = WALL;
}

Wall::~Wall() {
	delete bbox;
}