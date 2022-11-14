/**********************************************************************************
// Wall (C�digo Fonte)
//
// Cria��o:		09 Jun 2019
// Atualiza��o: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Ponto de mudan�a de dire��o para a(s) bola(s)
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