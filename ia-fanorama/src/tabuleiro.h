#ifndef _TABULEIRO_H_
#define _TABULEIRO_H_

#include <bitset>
#include <iostream>
#include <cassert>

#include "posicao.h"

#define LARGURA 7
#define ALTURA 5

enum {
	CASA_VAZIA = -1,
	JOG_PRETO,
	JOG_BRANCO,
	NUM_JOGADORES
};

class Tabuleiro {
	protected:
		std::bitset<ALTURA * LARGURA>	pecas[NUM_JOGADORES];
        int                             num_pecas[NUM_JOGADORES];
		int								largura;
		int								altura;

	public:
		Tabuleiro(const int primeiro_jog=JOG_BRANCO, const int largura=LARGURA, const int altura=ALTURA);
		~Tabuleiro() {};

		void limpa();
		void inicializa(const int primeiro_jog);

		int getLargura();
		int getAltura();

		void swap(const Posicao& src, const Posicao& dst);
		void setPeca(const Posicao& pos, const int corPeca);
		void setPecas(const Posicao& origem, const Posicao& vetor, const int numPecas, const int cor);

		int operator()(const int i, const int j);
		Tabuleiro& operator=(const Tabuleiro& tab);
		void imprime();

        int getNumPecas(const int jog); 
};

#endif
