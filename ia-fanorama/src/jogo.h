#ifndef _JOGO_H_
#define _JOGO_H_

#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

#include "definicoes.h"
//#include "posicao.h"
#include "tabuleiro.h"
#include "avaliacoes.h"

//#define NUMERO_NIVEIS 5
#define INDEFINIDO -1

#define EMPATE              -1
#define PECAS_PARA_VITORIA  3
#define MAX_TURNOS          50

#define MAXIMUM(x,y) (((x)>(y))?(x):(y))
#define MINIMUM(x,y) (((x)<(y))?(x):(y))

enum {
	NIVEL_BOZO=0,
	NIVEL_FACIL,
	NIVEL_MEDIO,
	NIVEL_DIFICIL,
	NIVEL_DIABOLICO,
	NIVEL_CHUCK_NORRIS,
	NUM_DIFICULDADES
};

typedef std::vector<Posicao> VecPosicao;

typedef struct {
	small_int	jogador;
	small_int	numComidas;
	Posicao		origemMov;
	small_int	direcaoMov;
	Posicao		ultimaPosIA;
	small_int	ultimoMovIA;
	Posicao		ultimaPos;
	small_int	ultimoMov;
	VecPosicao	posicoes;
	bool		comeu;
	bool		podePassar;
} InfoPilha;

typedef std::stack<InfoPilha> Pilha;

class Jogo {
	protected:
		Tabuleiro	tabuleiro;
		small_int	numTurnos;
		small_int	turno;

        /* jogador humano */
        small_int	jogador;

		Posicao		ultimaPosIA;
		small_int	ultimoMovIA;

		Posicao		ultimaPos;
		small_int	ultimoMov;

		bool		movimentos[8];

		bool		jogadaObrigatoria;
		small_int	possivelComer[LARGURA][ALTURA][MAX_MOVIMENTOS];
		bool		comeu;
		bool		podePassar;
		VecPosicao	posicoes;

		bool		inMinimax;
		int			nivelMinimax;
		int			(*avalia)( Tabuleiro& tab, small_int* possivelComer, const small_int jogador);

		/* Métodos */
		int		minimax(const int numNiveis, Tabuleiro& tab, int alpha, int beta,
						Posicao* peca=NULL, small_int* movPeca=NULL, const int nivelAtual=1);

		bool	movePeca(const Posicao origem, const small_int direcao, const bool troca_turno=false);
		int		podeComer(const Posicao destino, const small_int direcao);
		bool	comer(const Posicao destino, const small_int direcao);

		void	limpaMovimentos();
		void	limpaPossiveisComidas();

		void	geraMovimentos(Posicao& selecionada);
		void	geraMovsObrigatorios();

		bool	posicaoRepetida(const Posicao pos);
        bool	adversarioBloqueado();

		void	empilhaEstado(Pilha& pilha, const Posicao origem, const small_int direcao);
		void	limpaPilha(Pilha& pilha);

		void	copia(const Jogo& jogo);
	public:
		Jogo(int (*avaliacao)( Tabuleiro& tab, small_int* possivelComer, const small_int jogador));
		Jogo(const Jogo& jogo);
		~Jogo() { };
		void	novoJogo(const small_int jogHumano, const small_int primeiroJogador, const int dificuldade);

		Jogo&	operator=(const Jogo& jogo);

		bool	trocaTurno(const bool moveu=false);
		void	chamaMinimax();

		void	avancaJogada();
		void	voltaJogada();

		void	setDificuldade(const int dificuldade);
		
		void	setAvaliacao(int (*avaliacao)(Tabuleiro& tab, small_int* possivelComer, const small_int jogador));
		void	imprime();

        void	trocarPrimeiroJogador(const small_int primeiroJogador);
        void	trocarCorJogador(const small_int jogHumano);

        bool	fimDoJogo(small_int* vencedor);
        int		getNumTurnos();

        Pilha		pilhaVoltar;
		Pilha		pilhaAvancar;
		InfoPilha	infoPilha;
};

#endif
