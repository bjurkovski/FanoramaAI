#ifndef _AVALIACOES_H_
#define _AVALIACOES_H_

#include <cstdlib>

#include "definicoes.h"
#include "tabuleiro.h"

#define RANDOM_PERCENTAGE 0.1

typedef int (*FuncaoAvaliacao)(Tabuleiro&, small_int*, const small_int);

int avalia_base(Tabuleiro& tab, small_int* possivelComer, const small_int jogador);
int avalia1(Tabuleiro& tab, small_int* possivelComer, const small_int jogador);
int avalia2(Tabuleiro& tab, small_int* possivelComer, const small_int jogador);

#endif