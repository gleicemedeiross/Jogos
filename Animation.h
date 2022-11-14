/**********************************************************************************
// Animation (Arquivo de Cabe�alho)
// 
// Cria��o:		28 Set 2011
// Atualiza��o: 11 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Classe para animar seq��ncias em folha de sprites
//
**********************************************************************************/

#ifndef _DESENVJOGOS_ANIMATION_H_
#define _DESENVJOGOS_ANIMATION_H_

// ---------------------------------------------------------------------------------

#include "Sprite.h"												// tipo sprite para renderiza��o
#include "TileSet.h"											// folha de sprites da anima��o
#include "Timer.h"												// tempo entre quadros da anima��o
#include "Types.h"												// tipos espec�ficos da engine

#include <unordered_map>										// biblioteca STL				
using std::unordered_map;										// usando tabelas de dispers�o
using std::pair;												// usando pares de elementos

typedef pair<uint*, uint> AnimSeq;								// seq��ncia <vetor, tam>
typedef unordered_map<uint, AnimSeq> HashTable;					// tabela de dispers�o <uint, AnimSeq>

// ---------------------------------------------------------------------------------

class Animation
{
private:
	uint  iniFrame;												// quadro inicial da seq��ncia
	uint  endFrame;												// quadro final da seq��ncia
	uint  frame;												// quadro atual da anima��o	
	bool  animLoop;												// anima��o em loop infinito
	float animDelay;											// espa�o de tempo entre quadros (em segundos)
	Timer timer;												// medidor de tempo entre quadros da anima��o
	TileSet * tileSet;											// ponteiro para folha de sprites da anima��o
	SpriteData sprite;											// sprite a ser desenhado
	HashTable table;											// tabela com seq��ncias de anima��o
	uint * sequence;											// seq��ncia atualmente selecionada

public:
	Animation(TileSet* tiles, float delay, bool repeat);		// construtor
	~Animation();												// destrutor	

	void Add(uint id, uint * seq, uint seqSize);				// adiciona seq��ncia de anima��o
	void Select(uint id);										// seleciona seq��ncia atual

	void Draw(													// desenha o quadro atual da anima��o
		float x, float y, float z = 0.5f,						// coordenadas da tela
		Color color = { 1, 1, 1, 1 });							// efeito de cor

	void Draw(													// desenha um quadro da folha de sprites	
		uint aFrame,											// quadro da folha a desenhar
		float x, float y, float z = 0.5f,						// coordenadas da tela
		Color color = { 1, 1, 1, 1 });							// efeito de cor

	void Frame(uint aFrame);									// define o frame atual da anima��o
	uint Frame();												// retorna o frame de anima��o ativo

	bool Inactive();											// verifica se a anima��o j� encerrou
	void NextFrame();											// passa para o pr�ximo frame da anima��o
	void Restart();												// reinicia a animac�o (pelo primeiro frame da seq��ncia)
}; 

// ---------------------------------------------------------------------------------
// fun��es membro inline

// desenha quadro atual da anima��o
inline void Animation::Draw(float x, float y, float z, Color color)
{ sequence ? Draw(sequence[frame], x, y, z, color) : Draw(frame, x, y, z, color); }

// define o frame atual da anima��o
inline void Animation::Frame(uint aFrame)
{ frame = aFrame; }

// retorna o frame de anima��o ativo
inline unsigned Animation::Frame()
{ return (sequence ? sequence[frame] : frame); }

// verifica se a anima��o j� encerrou
inline bool Animation::Inactive()
{ return !animLoop && (frame > endFrame || (frame == endFrame && timer.Elapsed(animDelay))); }

// reinicia a animac�o (pelo primeiro frame da sequencia)
inline void Animation::Restart()
{ frame = 0; timer.Start(); }

// ---------------------------------------------------------------------------------

#endif