/**********************************************************************************
// Wall (Arquivo de Cabeçalho)
//
// Criação:		09 Jun 2019
// Atualização: 09 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Ponto de mudança de direção para a(s) bola(s)
//
**********************************************************************************/

#ifndef _BREAKOUT_WALL_H_
#define _BREAKOUT_WALL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"			// tipos específicos da engine
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