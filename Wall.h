/**********************************************************************************
// Wall (Arquivo de Cabe�alho)
//
// Cria��o:		09 Jun 2019
// Atualiza��o: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Ponto de mudan�a de dire��o para a(s) bola(s)
//
**********************************************************************************/

#ifndef _BREAKOUT_WALL_H_
#define _BREAKOUT_WALL_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"			// tipos espec�ficos da engine
#include "Object.h"			// interface de Object


class Wall : public Object
{
public:

	Wall(ushort w, ushort h);
	~Wall();

	void Update() {};
	void Draw() {};
};
#endif