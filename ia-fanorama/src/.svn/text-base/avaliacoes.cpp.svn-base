#include "avaliacoes.h"
// Adicionar outras heuristicas aqui (mudar a que deve ser utilizada na "main.cpp")

int avalia_base(Tabuleiro& tab, small_int* possivelComer, const small_int jogador){
    return tab.getNumPecas(jogador) - tab.getNumPecas(1 - jogador);
}

int avalia1(Tabuleiro& tab, small_int* possivelComer, const small_int jogador)
{
	
    if(tab.getNumPecas(1 - jogador) == 0)
		return INFINITO;

	if(tab.getNumPecas(jogador) == 0)
		return -INFINITO;
	
    int numeroPossivelComer = 0;	
	for(int i=0; i<LARGURA; i++)
		for(int j=0; j<ALTURA; j++)
			for(int k=0; k<MAX_MOVIMENTOS; k++)
				numeroPossivelComer += possivelComer[(i*ALTURA+j)*MAX_MOVIMENTOS + k];
	
	int value = 10*tab.getNumPecas(jogador) - 20*tab.getNumPecas(1 - jogador);
    int random_value = (double) rand() / RAND_MAX * value * RANDOM_PERCENTAGE;
    return value + random_value;
}

int avalia2(Tabuleiro& tab, small_int* possivelComer, const small_int jogador)
{
	if(tab.getNumPecas(1 - jogador) == 0)
		return INFINITO;

	if(tab.getNumPecas(jogador) == 0)
		return -INFINITO;

	int base = avalia_base(tab, possivelComer, jogador);
	int dist = 0;
	int desempate = rand()%10;

	return 1000*base + 10*dist + desempate;
}
