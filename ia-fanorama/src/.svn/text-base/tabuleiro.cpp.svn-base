#include "tabuleiro.h"
using namespace std;

Tabuleiro::Tabuleiro(const int primeiro_jog, const int largura, const int altura) {
	this->largura = largura;
	this->altura = altura;
	inicializa(primeiro_jog);
}

void Tabuleiro::limpa() {
	for(int jog=0; jog<NUM_JOGADORES; jog++)
		for(int i=0; i<largura; i++)
			for(int j=0; j<altura; j++)
				pecas[jog][i*altura + j] = 0;
}

void Tabuleiro::inicializa(const int primeiro_jog) {
	// Inicializa pecas no tabuleiro
	limpa();
	for(int i = 0;i<NUM_JOGADORES;i++)
        num_pecas[i] = 0;
    
    for(int jog=0; jog<NUM_JOGADORES; jog++)
		for(int i=0; i<largura; i++) {
			// Alterna entre 2 e 3 pecas por coluna
			int limite;
			if((i<largura/2 && i%2) || (i>largura/2 && !(i%2)))
				limite = 3;
			else limite = 2;

			for(int j=0; j<limite; j++) {
                /* o primeiro jogador é na parte inferior do tabuleiro */
				int x = (jog==primeiro_jog) ? largura - i - 1 : i;
				int y = (jog==primeiro_jog) ? altura - j - 1 : j;
				pecas[jog][x*altura + y] = 1;
                num_pecas[jog]++;
			}
		}
}

int Tabuleiro::getLargura() {
	return largura;
}

int Tabuleiro::getAltura() {
	return altura;
}

void Tabuleiro::setPeca(const Posicao& pos, const int corPeca) {
	if(corPeca == CASA_VAZIA){
		for(int i=JOG_PRETO; i<NUM_JOGADORES; i++) {
			if(pecas[i][pos.getX()*altura + pos.getY()]){
				pecas[i][pos.getX()*altura + pos.getY()] = false;
				num_pecas[i]--;
			}
		}
	}
	else if(!pecas[JOG_BRANCO][pos.getX()*altura + pos.getY()] && !pecas[JOG_PRETO][pos.getX()*altura + pos.getY()]){
		pecas[corPeca][pos.getX()*altura + pos.getY()] = true;
		num_pecas[corPeca]++;
	}
}

void Tabuleiro::setPecas(const Posicao& origem, const Posicao& vetor, const int numPecas, const int cor) {
	for(int i=1; i<=numPecas; i++)
		setPeca(origem + (vetor*i), cor);
}

int Tabuleiro::operator()(int i, int j) {
	if(!pecas[JOG_BRANCO][i*altura + j] && !pecas[JOG_PRETO][i*altura + j])
		return CASA_VAZIA;
	else if(pecas[JOG_BRANCO][i*altura + j])
		return JOG_BRANCO;
	else
		return JOG_PRETO;
}

Tabuleiro& Tabuleiro::operator=(const Tabuleiro& tab) {
	largura = tab.largura;
	altura = tab.altura;
	for(int i=JOG_PRETO; i<NUM_JOGADORES; i++) {
		num_pecas[i] = tab.num_pecas[i];
		for(int x=0; x<largura; x++)
			for(int y=0; y<altura;y++)
				pecas[i][x*altura + y] = tab.pecas[i][x*altura + y];
	}
	return *this;
}

void Tabuleiro::swap(const Posicao& src, const Posicao& dst) {
	for(int i=JOG_PRETO; i<NUM_JOGADORES; i++) {
		bool temp = pecas[i][src.getX()*altura + src.getY()];
		pecas[i][src.getX()*altura + src.getY()] = pecas[i][dst.getX()*altura + dst.getY()];
		pecas[i][dst.getX()*altura + dst.getY()] = temp;
	}
}

void Tabuleiro::imprime() {
	//mascara para impressao do tabuleiro
	const char mascara[] = {'.', '#', '@'};

	for(int a=0; a<altura; a++) {
		for(int l=0; l<largura; l++)
			cout << mascara[operator()(l, a) + 1];
		cout << endl;
	}
}

int Tabuleiro::getNumPecas(const int jogador){
    if(jogador < 0 || jogador >= NUM_JOGADORES)
        return -1;
    return num_pecas[jogador];
}
