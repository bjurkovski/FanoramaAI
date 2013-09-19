#include "interface.h"
using namespace std;

const int offset[8][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};

enum {AVALIA1, AVALIA2, NUM_FUNCOES};
Glib::ustring strFuncAval[] = {"Le Boulanger", "Capitao Nascimento"};
FuncaoAvaliacao funcsAval[] = {avalia1,			avalia2};

Glib::ustring strDificuldade[] = {"Bozo", "Facil", "Medio", "Dificil", "Diabolico", "Chuck Norris"};

const char * str_vencedor[] = {
    "<span font-family=\"sans\" size=\"xx-large\">Empate !</span>",
    "<span font-family=\"sans\" size=\"xx-large\">O jogador preto ganha !</span>",
    "<span font-family=\"sans\" size=\"xx-large\">O jogador branco ganha !</span>"};

const char * turnos[] = {"<b>Preto</b>", "<b>Branco</b>"};

Interface::Interface(int (*avaliacao)( Tabuleiro& tab, small_int* possivelComer, const small_int jogador)): Jogo(avaliacao),
						telaJogo(),
						janela(),
						barraLateral(),
						frameInfo("Turno"),
						infoBox(),
						labelTurno(),
                        labelNumTurno(),
						labelNumBrancas("__"),
						labelNumPretas("::"),
						botaoNovoJogo("Novo Jogo"),
                        botaoComecarIA("Comecar IA"),
						labelCor("Cor do Jogador"),
						cores(),
						corBrancas("Brancas"),
						corPretas("Pretas"),
                        labelPrimeroJogador("Primero jogador"),
						primeiroJogadorBox(),
                        jogadorBranco("Brancas"),
                        jogadorPreto("Pretas"),
						frameInimigo("Inimigo"),
						inimigoBox(),
						labelFuncAval("Funcao de Avaliacao:"),
						funcAval(),
						labelNivel("Nivel de Dificuldade:"),
						nivelDificuldade(),
                        passaVez("Passa a Vez")
{
	set_title("FanoramIA");
	resize(750, 500);
	set_resizable(false);
    
    fimDoJogo = false;
    vencedor = INDEFINIDO;
	ultimoMovIA = INDEFINIDO;

    atualizaNumTurnos();

	// Registra os callbacks para tratar sinais de clique, desenho, etc
	avancar.signal_clicked().connect(sigc::mem_fun(*this, &Interface::avancaJogada));
	voltar.signal_clicked().connect(sigc::mem_fun(*this, &Interface::voltaJogada));
	botaoNovoJogo.signal_clicked().connect(sigc::mem_fun(*this, &Interface::novoJogo));
	botaoComecarIA.signal_clicked().connect(sigc::mem_fun(*this, &Interface::comecarIA));
	passaVez.signal_clicked().connect(sigc::mem_fun(*this, &Interface::clicou_passaVez));
	telaJogo.signal_expose_event().connect(sigc::mem_fun(*this, &Interface::desenha_jogo), false);
	telaJogo.signal_button_press_event().connect(sigc::mem_fun(*this, &Interface::clicou_jogo), false);
	telaJogo.add_events(Gdk::BUTTON_PRESS_MASK);
    corBrancas.signal_toggled().connect(sigc::mem_fun(*this, &Interface::trocarCorJogador));
    jogadorBranco.signal_toggled().connect(sigc::mem_fun(*this, &Interface::trocarPrimeiroJogador));
	nivelDificuldade.signal_changed().connect(sigc::mem_fun(*this, &Interface::trocarDificuldade));
	funcAval.signal_changed().connect(sigc::mem_fun(*this, &Interface::trocarFuncAval));
    
	voltar.add_pixlabel("voltar.png", "Voltar");
	avancar.add_pixlabel("avancar.png", "Avancar");

    /* para escrever em "bold" */ 
    labelTurno.set_use_markup();

    // Seta o radioButton corBrancas, como inicialmente ativo
	corBrancas.set_active();
	// Uni os dois radioButtons em um mesmo grupo, logo só é possível selecionar um deles
	Gtk::RadioButton::Group corGroup = corBrancas.get_group();
	corPretas.set_group(corGroup);

	// Preenche as funcoes de avaliacao
	for(int fa=0; fa<NUM_FUNCOES; fa++)
		funcAval.append_text(strFuncAval[fa]);
	funcAval.set_active_text(strFuncAval[AVALIA1]);

	// Preenche os niveis de dificuldade
	for(int dif=0; dif<NUM_DIFICULDADES; dif++)
		nivelDificuldade.append_text(strDificuldade[dif]);
	nivelDificuldade.set_active_text(strDificuldade[NIVEL_FACIL]);

    // Misma cosa para o primeiro jogador
    jogadorBranco.set_active();
    Gtk::RadioButton::Group jogadorGroup = jogadorBranco.get_group();
    jogadorPreto.set_group(jogadorGroup);

	telaJogo.set_size_request(600, 480);
	janela.add(telaJogo);

	barraLateral.add(frameInfo);
	frameInfo.add(infoBox);
	infoBox.add(labelTurno);
    infoBox.add(labelNumTurno);
	infoBox.add(labelNumBrancas);
	infoBox.add(labelNumPretas);
	barraLateral.add(botaoNovoJogo);
    barraLateral.add(botaoComecarIA);
	// Adiciona a interface as opções de cor das peças
	barraLateral.add(labelCor);
	labelCor.add(cores);
	cores.add(corBrancas);
	cores.add(corPretas);
    // Adiciona a escolha do primeiro jogador
    barraLateral.add(labelPrimeroJogador);
	labelPrimeroJogador.add(primeiroJogadorBox);
    primeiroJogadorBox.add(jogadorBranco);
    primeiroJogadorBox.add(jogadorPreto);
	barraLateral.add(frameInimigo);
	frameInimigo.add(inimigoBox);
	// Adiciona as opcoes de funcao de avaliacao
	inimigoBox.add(labelFuncAval);
	inimigoBox.add(funcAval);
	// Adiciona a barra lateral as opções de nível de dificuldade
	inimigoBox.add(labelNivel);
	inimigoBox.add(nivelDificuldade);
	barraLateral.add(passaVez);
	barraLateral.add(voltar);
	barraLateral.add(avancar);

	janela.add(barraLateral);
	
	add(janela);
	show_all_children();
	novoJogo();
}

void Interface::movePeca(const Posicao origem, const int direcao) {
    bool minimax = Jogo::movePeca(origem, direcao);
	selecionada.setIndefinida();
	atualizaLabelTurno();
    atualizaNumTurnos();
    atualizaTela();
	
	if(minimax){
		//small_int auxNumTurnos = numTurnos;
		chamaMinimax();
		//numTurnos = auxNumTurnos;
	}

	// TO DO: lembrar de colocar esse 'if' dentro de Jogo
    if(Jogo::fimDoJogo(&vencedor)){
        fimDoJogo = true;
        return;
    }

	atualizaLabelTurno();
    atualizaNumTurnos();
    atualizaTela();
}

void Interface::trocarPrimeiroJogador(){
    if(jogadorBranco.get_active()) 
       Jogo::trocarPrimeiroJogador(JOG_BRANCO);
    else
       Jogo::trocarPrimeiroJogador(JOG_PRETO);
    atualizaLabelTurno();
    atualizaTela();
}

void Interface::trocarCorJogador(){
   if(corBrancas.get_active()) 
       Jogo::trocarCorJogador(JOG_BRANCO);
   else
       Jogo::trocarCorJogador(JOG_PRETO);
}

void Interface::trocarFuncAval() {
	Glib::ustring fAval = funcAval.get_active_text();
	if(!(fAval.empty()))
		for(int fa=0; fa<NUM_FUNCOES; fa++)
			if(fAval == strFuncAval[fa]) {
				Jogo::setAvaliacao(funcsAval[fa]);
				return;
			}
}

void Interface::trocarDificuldade() {
	Glib::ustring nivel = nivelDificuldade.get_active_text();
	if(!(nivel.empty()))
		for(int dif=0; dif<NUM_DIFICULDADES; dif++)
			if(nivel == strDificuldade[dif]) {
				setDificuldade(dif);
				return;
			}
}

void Interface::comecarIA(){
    botaoComecarIA.set_sensitive(false);
	chamaMinimax();
	atualizaLabelTurno();
	atualizaNumTurnos();
	atualizaTela();
}

void Interface::desenhaCirculo(Cairo::RefPtr<Cairo::Context> cr, double raio, double R, double G, double B,  int x, int y) {
	cr->set_source_rgb(R,G,B);
	cr->arc(bordaX + raioPeca + x*2*raioPeca,
			bordaY + raioPeca + y*2*raioPeca,
			raio, CIRCULO);
	cr->fill();
	cr->stroke();
}

void Interface::desenhaPeca(Cairo::RefPtr<Cairo::Context> cr, double R, double G, double B,  int x, int y) {
	desenhaCirculo(cr, RAIO_COEF*raioPeca, R, G, B, x, y);
}

void Interface::clicou_passaVez() {
	bool minimax = trocaTurno();
	if(minimax)
		chamaMinimax();

	atualizaLabelTurno();
    atualizaNumTurnos();
	selecionada.setIndefinida();
    atualizaTela();
}

void Interface::avancaJogada(){
	Jogo::avancaJogada();
	atualizaLabelTurno();
	atualizaNumTurnos();
	atualizaTela();	
}

void Interface::voltaJogada() {
	Jogo::voltaJogada();
	atualizaLabelTurno();
	atualizaNumTurnos();
	atualizaTela();	
}


void Interface::atualizaLabelTurno() {
	labelTurno.set_label(turnos[(int)turno]);
}

void Interface::atualizaTela() {
	// Atualização da tela do jogo
	Glib::RefPtr<Gdk::Window> win = telaJogo.get_window();
	if (win) {
        Gdk::Rectangle r(0, 0, telaJogo.get_allocation().get_width(), telaJogo.get_allocation().get_height());
        win->invalidate_rect(r, false);
	}

	avancar.set_sensitive(!pilhaAvancar.empty());
	voltar.set_sensitive(!pilhaVoltar.empty());
	passaVez.set_sensitive(podePassar);
	char str[100];
	sprintf(str, "Pecas Brancas: #%d", tabuleiro.getNumPecas(JOG_BRANCO));
	labelNumBrancas.set_text(str);
	sprintf(str, "Pecas Pretas: #%d", tabuleiro.getNumPecas(JOG_PRETO));
	labelNumPretas.set_text(str);
}

void Interface::novoJogo() {
	int jogador;
	if(corBrancas.get_active()) jogador = JOG_BRANCO;
	else jogador = JOG_PRETO;
  
    selecionada.setIndefinida();
    fimDoJogo = false;

    int primeiroJogador;
    if(jogadorBranco.get_active()) primeiroJogador = JOG_BRANCO;
    else primeiroJogador = JOG_PRETO;

	Jogo::novoJogo(jogador,primeiroJogador, NIVEL_FACIL);
	trocarDificuldade();
    atualizaNumTurnos();
	botaoComecarIA.set_sensitive(true);
    atualizaLabelTurno();
    /* precisa para retirar circulos vermelhos
     * quando o jogador passa sua vez
     */
	atualizaTela();
}

// Desenhar na tela
bool Interface::desenha_jogo(GdkEventExpose* event) {
	// EXEMPLO COPIADO:
	// http://library.gnome.org/devel/gtkmm-tutorial/unstable/sec-cairo-drawing-lines.html.en

	// DRAW IMAGE:
	// http://library.gnome.org/devel/gtkmm-tutorial/unstable/sec-draw-images.html.en

	// DRAWING FUNCTIONS DOCUMENTATION:
	// http://cairographics.org/documentation/cairomm/reference/classCairo_1_1Context.html

	// Janela na qual vamos desenhar
	Glib::RefPtr<Gdk::Window> window = telaJogo.get_window();
	if(window)
	{
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		// Redesenha apenas o tamanho alocado para o widget, cortando o resto fora
		cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
		cr->clip();

		// Cor de fundo
		cr->set_source_rgb(RGB_PRETO);
		cr->paint();

		// Define raio das pecas de acordo com a borda horizontal e vertical
    	bordaX = 0.027 * telaJogo.get_width();
		bordaY = 0.07 * telaJogo.get_height();
        
		double rX = (telaJogo.get_width() - 2*bordaX) / (2*tabuleiro.getLargura());
		double rY = (telaJogo.get_height() - 2*bordaY) / (2*tabuleiro.getAltura());
		raioPeca = min(rX, rY);

		//Desenha o tabuleiro a partir de uma imagem
		Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("tabuleiro.png");
		image->render_to_drawable(window, telaJogo.get_style()->get_black_gc(),
								0, 0, 0, 0, image->get_width(), image->get_height(),
								Gdk::RGB_DITHER_NONE, 0, 0);
		
		
		cr->set_line_width(5.0);
		if(ultimoMovIA != INDEFINIDO) {
			if(jogador == JOG_BRANCO) cr->set_source_rgb(RGB_PRETO);
			else cr->set_source_rgb(RGB_BRANCO);

			int destX = ultimaPosIA.getX() - offset[(int)ultimoMovIA][0];
			int destY = ultimaPosIA.getY() - offset[(int)ultimoMovIA][1];

			cr->move_to(bordaX + raioPeca + ultimaPosIA.getX() * 2*raioPeca, bordaY + raioPeca + ultimaPosIA.getY() * 2*raioPeca);
			cr->line_to(bordaX + raioPeca + destX * 2*raioPeca, bordaY + raioPeca + destY * 2*raioPeca);
			cr->stroke();
		}

		cr->set_line_width(1.0);
		// Percorre todas as posições do tabuleiro com o objetivo de desenhar as peças
		for(int x=0; x<tabuleiro.getLargura(); x++)
			for(int y=0; y<tabuleiro.getAltura(); y++)
			{
				// Verifica se a peça deve ser preta ou branca, ou se não há peça nesse local
				if(tabuleiro(x,y) == JOG_PRETO)
					desenhaPeca(cr, RGB_PRETO, x, y);
				else if(tabuleiro(x,y) == JOG_BRANCO)
					desenhaPeca(cr, RGB_BRANCO, x, y);
				else continue;
			}

		
		// Verifica se uma peça foi selecionada
		if(!selecionada.isIndefinida()) {
			// Redesenha a peça com outra cor
			desenhaPeca(cr, RGB_AZUL, selecionada.getX(), selecionada.getY());
		}
		
		// Percorre a lista de todos os vizinhos dessa peça
		for(int mov=0; mov<8; mov++)
			// Caso esse vizinho seja válido
			if(movimentos[mov])
			{
				// Desenha uma esfera com a metade do tamanho da peça, indicando o 
				// possível destino da peça
				int x = selecionada.getX() + offset[mov][0];
				int y = selecionada.getY() + offset[mov][1];
				desenhaCirculo(cr, RAIO_COEF/2*raioPeca, RGB_VERMELHO, x, y);
			}

        if(fimDoJogo){
            int pango_x=0,pango_y=0;
            Glib::RefPtr<Pango::Layout> pangoLayout = Pango::Layout::create (cr);
            cr->set_source_rgb(RGB_VERMELHO);
            pangoLayout->set_markup(str_vencedor[vencedor+1]);
            /* escrever ao meio de telaJogo */
            pangoLayout->get_pixel_size(pango_x,pango_y);
            cr->move_to(telaJogo.get_width()/2-pango_x/2,telaJogo.get_height()/2-pango_y/2);
            pangoLayout->update_from_cairo_context(cr);  //gets cairo cursor position
            pangoLayout->add_to_cairo_context(cr);       //adds text to cairos stack of stuff to be drawn
            cr->fill();
            cr->stroke();
       }
	}

	return true;
}

bool Interface::clicou_jogo(GdkEventButton* event) {
    /* desativar signal se o jogo é terminado */
    if(fimDoJogo) return false;

	int pecaX = (event->x - bordaX)/(2*raioPeca);
	int pecaY = (event->y - bordaY)/(2*raioPeca);

	double centroX = bordaX + raioPeca + pecaX*2*raioPeca;
	double centroY = bordaY + raioPeca + pecaY*2*raioPeca;
	double dist = SQR(event->x - centroX) + SQR(event->y - centroY);
	double raio2 = SQR(RAIO_COEF*raioPeca);

	// Verifica se a posição está dentro do tabuleiro
	if(pecaX < tabuleiro.getLargura() && pecaY < tabuleiro.getAltura() && dist < raio2) {
		// Verifica se a peça é do tom das peças do jogador
		if(tabuleiro(pecaX, pecaY) == turno) {
			selecionada = Posicao(pecaX, pecaY);
			geraMovimentos(selecionada);
		}
		else {
			bool moveu = false;
			for(int mov=0; mov<8; mov++) 
				if(movimentos[mov])
					if(selecionada.getX()+offset[mov][0] == pecaX && selecionada.getY()+offset[mov][1] == pecaY) {
						movePeca(selecionada, mov);
						moveu = true;
						break;
					}

			if(!moveu) { selecionada.setIndefinida(); limpaMovimentos(); }
		}
	}
    else { selecionada.setIndefinida(); limpaMovimentos(); }

	atualizaTela();
	
    return true;
}

void Interface::atualizaNumTurnos(){
    stringstream str;
    str << "Turno #"<<Jogo::getNumTurnos();
    labelNumTurno.set_label(str.str());
}
