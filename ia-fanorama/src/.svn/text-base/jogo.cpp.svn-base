#include "jogo.h"
using namespace std;

const int offset[8][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};
const int nivelDificuldade[] = {2, 4, 5, 6, 7, 8};

void imprimeIP(InfoPilha ip) {
	std::cout << "Turno: " << ip.jogador << " | NumComidas: " << ip.numComidas << std::endl;
	std::cout << "UltimaPosIA: " << ip.ultimaPosIA.toString() << " | UltimoMovIA: " << ip.ultimoMovIA << std::endl;
	std::cout << "UltimaPos: " << ip.ultimaPos.toString() << " | UltimoMov: " << ip.ultimoMov << std::endl;
	std::cout << "OrigemMov: " << ip.origemMov.toString() << " | DirecaoMov: " << ip.direcaoMov << std::endl;
	std::cout << "Comeu: " << ip.comeu << " | PodePassar: " << ip.podePassar << std::endl;
	cout << "PosicoesTabu:" << endl;
	for(VecPosicao::iterator it=ip.posicoes.begin(); it!=ip.posicoes.end(); it++)
		cout << it->toString() << " ";
}

Jogo::Jogo(int (*avaliacao)( Tabuleiro& tab, small_int* possivelComer, const small_int jogador)) : tabuleiro() {
	setAvaliacao(avaliacao);
}

Jogo::Jogo(const Jogo& jogo) {
	copia(jogo);
}

void Jogo::setAvaliacao(int (*avaliacao)(Tabuleiro& tab, small_int* possivelComer, const small_int jogador)) {
	avalia = avaliacao;
}

void Jogo::novoJogo(const small_int jogHumano, const small_int primeiroJogador, const int dificuldade) {
	turno = primeiroJogador; 
	numTurnos = 0;
	jogador = jogHumano;
	posicoes.clear();
	tabuleiro.inicializa(primeiroJogador);
	inMinimax = false;
	podePassar = false;
	setDificuldade(dificuldade);

	ultimaPos.setIndefinida();
	ultimoMov = INDEFINIDO;
	ultimoMovIA = INDEFINIDO;
	comeu = false;
	geraMovsObrigatorios();

	limpaPilha(pilhaVoltar);
	limpaPilha(pilhaAvancar);
}

void Jogo::copia(const Jogo& jogo) {
	tabuleiro = jogo.tabuleiro;
	numTurnos = jogo.numTurnos;
	turno = jogo.turno;
	jogador = jogo.jogador;

	ultimaPosIA = jogo.ultimaPosIA;
	ultimoMovIA = jogo.ultimoMovIA;
	ultimaPos = jogo.ultimaPos;
	ultimoMov = jogo.ultimoMov;

	for(int i=0; i<MAX_MOVIMENTOS; i++)
		movimentos[i] = jogo.movimentos[i];

	jogadaObrigatoria = jogo.jogadaObrigatoria;
	
	for(int i=0; i<LARGURA; i++)
		for(int j=0; j<ALTURA; j++)
			for(int k=0; k<MAX_MOVIMENTOS; k++)
				possivelComer[i][j][k] = jogo.possivelComer[i][j][k];
	
	comeu = jogo.comeu;
	podePassar = jogo.podePassar;
	posicoes.assign(jogo.posicoes.begin(), jogo.posicoes.end());
	inMinimax = jogo.inMinimax;
	avalia = jogo.avalia;
}

Jogo& Jogo::operator=(const Jogo& jogo) {
	copia(jogo);
	return *this;
}


void Jogo::limpaMovimentos() {
	for(int i=0; i<8; i++)
		movimentos[i] = false;
}

void Jogo::limpaPossiveisComidas() {
	jogadaObrigatoria = false;
	for(int x=0; x<tabuleiro.getLargura(); x++)
		for(int y=0; y<tabuleiro.getAltura(); y++)
			for(int mov=0; mov<MAX_MOVIMENTOS; mov++)
				possivelComer[x][y][mov] = 0;
}

void Jogo::avancaJogada(){
	cout << "Avancar desabilitado [por enquanto]...." << endl;
	/*
	cout << "Avancar..." << endl;
	if(!pilhaAvancar.empty()) {
		infoPilha = pilhaAvancar.top();

		turno = infoPilha.jogador;
		ultimaPos = infoPilha.ultimaPos;
		ultimaPosIA = infoPilha.ultimaPosIA;
		ultimoMovIA = infoPilha.ultimoMovIA;
		comeu = infoPilha.comeu;
		podePassar = infoPilha.podePassar;

		//Atualiza o número de turnos se o jogador não comeu nenhuma peça ou se ele passou a vez
		if (infoPilha.numComidas == 0) {
			numTurnos++;
		}
		//Se o jogador não passou a vez e então movimenta as peças
		else if (infoPilha.numComidas > 0) {
			Posicao ofs(offset[infoPilha.direcaoMov][0], offset[infoPilha.direcaoMov][1]);
			Posicao destino = ofs + infoPilha.origemMov;
			tabuleiro.swap(infoPilha.origemMov, destino);
			tabuleiro.setPecas(destino, ofs, infoPilha.numComidas, CASA_VAZIA);
			turno = infoPilha.jogador;
		}

		//teste:
		//if(turno == infoPilha.jogador)
		//	podePassar = true;
		
		pilhaVoltar.push(infoPilha);
		//empilhaEstado(pilhaVoltar);
		pilhaAvancar.pop();
	}
	//limpaSelecionada();
	geraMovsObrigatorios();
	*/
}

void Jogo::voltaJogada(){
	if(!pilhaVoltar.empty()) {
		infoPilha = pilhaVoltar.top();

		ultimaPos = infoPilha.ultimaPos;
		ultimoMov = infoPilha.ultimoMov;
		posicoes.assign(infoPilha.posicoes.begin(), infoPilha.posicoes.end());
		ultimaPosIA = infoPilha.ultimaPosIA;
		ultimoMovIA = infoPilha.ultimoMovIA;
		comeu = infoPilha.comeu;
		podePassar = infoPilha.podePassar;

		Posicao destino, ofs;
		if(infoPilha.direcaoMov != INDEFINIDO) {
			ofs = Posicao(offset[(int)infoPilha.direcaoMov][0], offset[(int)infoPilha.direcaoMov][1]);
			destino = infoPilha.origemMov + ofs;
			if(!infoPilha.origemMov.isIndefinida())
				tabuleiro.swap(destino, infoPilha.origemMov);
		}

		//Atualiza o número de turnos se o jogador não comeu nenhuma peça ou se ele passou a vez
		if(/*infoPilha.numComidas == 0*/ turno != infoPilha.jogador) {
			numTurnos--;
		}
		//Se o jogador não passou a vez e então movimenta as peças
		if(infoPilha.numComidas>0 && infoPilha.direcaoMov!=INDEFINIDO && !infoPilha.origemMov.isIndefinida()) {
			tabuleiro.setPecas(destino, ofs, infoPilha.numComidas, 1 - infoPilha.jogador);
		}

		turno = infoPilha.jogador;

		pilhaAvancar.push(infoPilha);
		pilhaVoltar.pop();
	}
	geraMovsObrigatorios();
}

void Jogo::setDificuldade(const int dificuldade) {
	if(dificuldade>=0 && dificuldade<NUM_DIFICULDADES)
		nivelMinimax = nivelDificuldade[dificuldade];
}


// http://pt.wikipedia.org/wiki/Minimax
int Jogo::minimax(const int numNiveis, Tabuleiro& tab, int alpha, int beta, 
				  Posicao* peca, small_int* movPeca, const int nivelAtual) {
	//*
	if(nivelAtual == numNiveis || tabuleiro.getNumPecas(JOG_BRANCO)==0
		|| tabuleiro.getNumPecas(JOG_PRETO)==0) {
		return avalia(tab, (small_int*)possivelComer, turno);
		/* DEBUG
		for(int kkk=0; kkk<nivelAtual; kkk++)
			cout << "=";
		cout << " [" << (int)turno << "] " << a << endl;
		//*/
	}else {
		if(peca) *peca = Posicao();
		if(movPeca) *movPeca = INDEFINIDO;

		// Testa se é possível realizar um movimento vazio (passar a vez)
		if(podePassar) {
			int turnoAntigo = turno;
			trocaTurno(false);
			int valorMov;
			if(turno==turnoAntigo)
				valorMov = minimax(numNiveis, tab, alpha, beta, NULL, NULL, nivelAtual+1);
			else
				valorMov = -minimax(numNiveis, tab, -beta, -alpha, NULL, NULL, nivelAtual+1);
			voltaJogada();

			/* DEBUG
			for(int kkk=0; kkk<nivelAtual; kkk++)
				cout << "=";
			cout << " " << mult << " [" << (int)turno << "] Passando: " << valorMov 
				<< " / " << alpha << ", " << beta << endl;
			//*/

			if(valorMov > alpha) {
				alpha = valorMov;
				if(peca) *peca = Posicao();
				if(movPeca) *movPeca = INDEFINIDO;
			}
	
			if(beta<=alpha) return alpha;
		}

		// Testa todos os movimentos possiveis no estado atual
		for (int i = 0; i<tab.getLargura(); i++)
			for (int j = 0; j<tab.getAltura(); j++)
				if (tab(i,j) == turno){
                    Posicao pos(i,j);
					geraMovimentos(pos);
					for(int mov=0; mov<MAX_MOVIMENTOS; mov++)
						if(movimentos[mov]) {
							int turnoAntigo = turno;
							movePeca(Posicao(i,j), mov, true);
							int valorMov;
							if(turno==turnoAntigo)
								valorMov = minimax(numNiveis, tab, alpha, beta, NULL, NULL, nivelAtual+1);
							else
								valorMov = -minimax(numNiveis, tab, -beta, -alpha, NULL, NULL, nivelAtual+1);
							voltaJogada();

							/* DEBUG
							for(int kkk=0; kkk<nivelAtual; kkk++)
								cout << "=";
							cout << " " << mult << " [" << (int)turno << "] " << Posicao(i,j).toString() 
								<< " => " << offset[mov][0] << ", " << offset[mov][1] << ": " 
								<< valorMov << " / " << alpha << ", " << beta << endl;
							//*/

							if(valorMov > alpha) {
								alpha = valorMov;
								if(peca) *peca = Posicao(i, j);
								if(movPeca) *movPeca = mov;
							}

							if(beta<=alpha) return alpha;

							geraMovimentos(pos);
						}
				}
			
		return alpha;
	}
	//*/
}

bool Jogo::posicaoRepetida(const Posicao pos) {
	// Verifica se 'pos' já foi visitada pelo jogador nesse turno
	for(vector<Posicao>::iterator p=posicoes.begin(); p != posicoes.end(); p++)
		if(*p == pos)
			return true;
	return false;
}

void Jogo::geraMovimentos(Posicao& selecionada) {
	limpaMovimentos();
	if(!selecionada.isIndefinida())
	{
		if(ultimaPos.isIndefinida() || ultimaPos==selecionada) {
			int fim;
			// Verifica se a peça selecinada tem 4 ou 8 vizinhos válidos (com arestas entre eles)
			if((selecionada.getX() + selecionada.getY())%2 == 0)
				fim = 4;
			else fim = 8;

			// Percorre todos os vizinhos válidos dessa peça
			for(int mov=0; mov<fim; mov++)
			{
				// Calcula a posição x,y desse vizinho
				int x = selecionada.getX() + offset[mov][0];
				int y = selecionada.getY() + offset[mov][1];

				// Verifica se a posição desse vizinho está dentro dos limites do tabuleiro
				if(x >= 0 && y >= 0 &&
					x < tabuleiro.getLargura() && y < tabuleiro.getAltura())
				{
					Posicao pos(x, y);
					// Não permite que o jogador mova uma peça que não coma ninguém caso possa comer alguma na rodada
                    if(jogadaObrigatoria && possivelComer[x][y][mov] == 0)
						movimentos[mov] = false;
					// Não permite que o jogador mova a peça para uma posição anterior
					else if(posicaoRepetida(pos))
						movimentos[mov] = false;
					// Permite apenas que o jogados mova suas peças para posições vazias
					else if(tabuleiro(x, y) == CASA_VAZIA)
						movimentos[mov] = true;
					else movimentos[mov] = false;
				}
				else movimentos[mov] = false;
			}
		}
	}
}

void Jogo::geraMovsObrigatorios() {
	limpaPossiveisComidas();

	bool jogPodeComer = false;
	for(int x=0; x<tabuleiro.getLargura(); x++)
		for(int y=0; y<tabuleiro.getAltura(); y++)
			if(ultimaPos.isIndefinida() ||
				(x==ultimaPos.getX() && y==ultimaPos.getY()))
				if(tabuleiro(x,y) == turno)
				{
					Posicao pos(x, y);
					geraMovimentos(pos);
					for(int mov=0; mov<8; mov++)
						if(movimentos[mov]){
							Posicao dest(x+offset[mov][0], y+offset[mov][1]);
							possivelComer[dest.getX()][dest.getY()][mov] = podeComer(dest, mov);
							if(possivelComer[dest.getX()][dest.getY()][mov]) jogPodeComer = true;
                        }
				}

	jogadaObrigatoria = jogPodeComer;
	limpaMovimentos();
}

void Jogo::empilhaEstado(Pilha& pilha, const Posicao origem, const small_int direcao) {
	infoPilha.origemMov = origem;
	infoPilha.direcaoMov = direcao;
	infoPilha.ultimaPos = ultimaPos;
	infoPilha.ultimoMov = ultimoMov;
	infoPilha.jogador = turno;

	if(direcao!=INDEFINIDO) {
		Posicao destino(origem.getX()+offset[(int)direcao][0], origem.getY()+offset[(int)direcao][1]);
		infoPilha.numComidas = possivelComer[destino.getX()][destino.getY()][(int)direcao];
	}
	else
		infoPilha.numComidas = 0;

	infoPilha.posicoes.assign(posicoes.begin(), posicoes.end());
	infoPilha.ultimoMovIA = ultimoMovIA;
	infoPilha.ultimaPosIA = ultimaPosIA;
	infoPilha.comeu = comeu;
	infoPilha.podePassar = podePassar;
	
	pilha.push(infoPilha);
}

void Jogo::limpaPilha(Pilha& pilha) {
	while(!pilha.empty()) pilha.pop();
}

bool Jogo::movePeca(const Posicao origem, const small_int direcao, const bool troca_turno) {
	Posicao destino(origem.getX()+offset[(int)direcao][0], origem.getY()+offset[(int)direcao][1]);
	empilhaEstado(pilhaVoltar, origem, direcao);
	limpaPilha(pilhaAvancar);

	// Troca a posição da peça da sua origem para o seu destino
	tabuleiro.swap(origem, destino);
	posicoes.push_back(origem);

	ultimoMov = direcao;
	if(turno != jogador) ultimoMovIA = direcao;
	else ultimoMovIA = INDEFINIDO;

	// Reinicializa a flag que indica se a jogada comeu alguma peça do oponente
	comeu = false;
	comer(destino, direcao);
	
	// Se o jogador jogar outra vez, deve mover a mesma peça
	ultimaPos = destino;
	limpaMovimentos();
	geraMovsObrigatorios();

	if(turno != jogador) {
		ultimoMovIA = ultimoMov;
		ultimaPosIA = ultimaPos;
	}
	else {
		ultimoMovIA = INDEFINIDO;
	}

    /* O jogador pode jogar de novo
     * si o ele pode comer o proximo turno
     */
	if(comeu && jogadaObrigatoria) podePassar = true;
    else return trocaTurno(true);

	return false;
}

int Jogo::podeComer(const Posicao destino, const small_int direcao) {
	// Inicialização da variável que indica se uma determinada peça pode comer outra
	bool podecomer = true;
	int numComidas = 0;

	// Salva o destino da peça (que se movimentou) nas variáveis 
	int x = destino.getX();
	int y = destino.getY();

	// Enquanto for possível comer uma peça
	while(podecomer) {
		// Se locomove para a próxima possição na linha do movimento da peça
		x += offset[(int)direcao][0];
		y += offset[(int)direcao][1];

		// Se a peça estiver em uma dos extremos do tabuleiro, então não é possível comer mais peças
		if(x < 0 || y < 0 || x >= tabuleiro.getLargura() || y >= tabuleiro.getAltura())
			podecomer = false;
		// Se houver uma peça de mesma cor do jogador ou uma casa vazia, não é possível comer mais peças
		else if(tabuleiro(x,y) == turno || tabuleiro(x,y) == CASA_VAZIA)
			podecomer = false;
		// Caso contrário (há uma peça do oponente, essa peça é comida e continua a sua busca
		else
			numComidas++;
	}

	return numComidas;
}

bool Jogo::comer(const Posicao destino, const small_int direcao) {
	int x = destino.getX();
	int y = destino.getY();
	int numComidas = possivelComer[x][y][(int)direcao];

	tabuleiro.setPecas(destino, Posicao(offset[(int)direcao][0], offset[(int)direcao][1]), numComidas, CASA_VAZIA);

	if(numComidas>0) comeu = true;
	return (numComidas>0);
}

bool Jogo::trocaTurno(const bool moveu) {
	if(!moveu)
		empilhaEstado(pilhaVoltar, Posicao(), INDEFINIDO);

    numTurnos++;
	
    limpaMovimentos();
	posicoes.clear();
	comeu = false;
	podePassar = false;
	ultimaPos.setIndefinida();
	ultimoMov = INDEFINIDO;
	//Seleciona o outro jogador
	turno = 1 - turno;
	geraMovsObrigatorios();

	if(turno!=jogador && !inMinimax) {
		return true;
	}

	return false;
}

void Jogo::chamaMinimax() {
	do {
		if(tabuleiro.getNumPecas(JOG_BRANCO)>0 && tabuleiro.getNumPecas(JOG_PRETO)>0) {
			Posicao peca;
			small_int movPeca;
			int alpha=-INFINITO-1, beta=INFINITO+1;
			//cout << "Pre-Minimax" << endl;
			//imprime();
			inMinimax = true;
			minimax(nivelMinimax, tabuleiro, alpha, beta, &peca, &movPeca);
			inMinimax = false;
			//cout << "Movimento Escolhido: " << peca.toString() << " => " << (int)offset[movPeca][0] << ", " << (int)offset[movPeca][1] << endl;
			//cout << "===========" << endl;
			if(movPeca==INDEFINIDO) trocaTurno(false);
			else movePeca(peca, movPeca, true);
			//cout << "Pos-Minimax" << endl;
			//imprime();
		}
	} while(comeu);
}

void Jogo::imprime() {
	tabuleiro.imprime();
	cout << "Humano: " << jogador << " | Turno: " << turno << " | NumTurnos: " << numTurnos << endl;
	cout << "UltimaPos: " << ultimaPos.toString() << " | UltimaPosIA: " << ultimaPosIA.toString() << endl;

	cout << "UltimoMov: ";
	if(ultimoMov != INDEFINIDO)
		cout << Posicao(offset[(int)ultimoMov][0], offset[(int)ultimoMov][1]).toString() << endl;
	else cout << "INDEFINIDO" << endl;

	cout << "UltimoMovIA: ";
	if(ultimoMovIA != INDEFINIDO)
		cout << Posicao(offset[(int)ultimoMovIA][0], offset[(int)ultimoMovIA][1]).toString() << endl;
	else cout << "INDEFINIDO" << endl;
	
	cout << "Comeu: " << comeu << " | PodePassar: " << podePassar << endl;

	cout << "PosicoesTabu:" << endl;
	for(VecPosicao::iterator it=posicoes.begin(); it!=posicoes.end(); it++)
		cout << it->toString() << " ";
}


void Jogo::trocarPrimeiroJogador(const small_int primeiroJogador){
   if(numTurnos == 0 && ultimoMov == INDEFINIDO){
        turno = primeiroJogador;
        tabuleiro.inicializa(primeiroJogador);
        posicoes.clear();
        geraMovsObrigatorios();
    }
}

void Jogo::trocarCorJogador(const small_int jogHumano){
    if(numTurnos == 0)
        jogador = jogHumano;
}

/* Condicoes para o fim de jogo:
 *  - Um jogador nao possui pecas, o outro vence
 *  - Um jogador nao consegue se mover, o outro vence
 *  - Foram feitas mais de 50 jogadas, vitoria ou empate
 */
bool Jogo::fimDoJogo(small_int* jog) {
	int dif = 0; /* numPecasBranco - numPecasPreto */
	int vencedor = 0;

	if(tabuleiro.getNumPecas(JOG_PRETO) == 0)
		vencedor = JOG_BRANCO;
	else if(tabuleiro.getNumPecas(JOG_BRANCO) == 0)
		vencedor = JOG_PRETO;
	else if(numTurnos >= MAX_TURNOS) {
		dif = tabuleiro.getNumPecas(JOG_BRANCO) - tabuleiro.getNumPecas(JOG_PRETO);
		if(dif < -PECAS_PARA_VITORIA)
			vencedor = JOG_PRETO;
		else if(dif > PECAS_PARA_VITORIA)
			vencedor = JOG_BRANCO;
		else
			vencedor = EMPATE;
	}
	else if(adversarioBloqueado())
		vencedor = turno;
	else
		return false;

	if(jog) *jog = vencedor;

	return true;
}

int Jogo::getNumTurnos(){
    return numTurnos; 
}
        
bool Jogo::adversarioBloqueado(){
	int num_vizinhos = 0;

	/* we have to check if the opponent is stuck after
	 * the last move
	 */
	for(int x = 0; x < tabuleiro.getLargura(); x++)
		for(int y = 0; y < tabuleiro.getAltura(); y++)
			if(tabuleiro(x,y) == (turno + 1) % 2) {
					num_vizinhos = ((x + y)%2 == 0) ? 4 : 8;
					for(int i = 0; i< num_vizinhos; i++) {
						Posicao pos_vizinho(x + offset[i][0], y + offset[i][1]);
						if(pos_vizinho.getX() >= 0 && pos_vizinho.getY() >= 0 &&
							pos_vizinho.getX() < tabuleiro.getLargura() && pos_vizinho.getY() < tabuleiro.getAltura() &&
							tabuleiro(pos_vizinho.getX(), pos_vizinho.getY()) == CASA_VAZIA)
							return false;
					}
			}
	return true;    
}
