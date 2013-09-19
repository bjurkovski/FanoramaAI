#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <iostream>

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/frame.h>
#include "jogo.h"
#include "avaliacoes.h"

#ifndef M_PI
#define M_PI 3.1415
#endif

#define SQR(x) ((x)*(x))
#define CIRCULO 0, 2*M_PI
#define RAIO_COEF 0.6
#define RGB_BRANCO	0.9, 0.9, 0.9
#define RGB_PRETO	0.1, 0.1, 0.1
#define RGB_AZUL	0.1, 0.4, 0.9
#define RGB_VERMELHO 1, 0, 0

class Interface : public Jogo, public Gtk::Window {
	protected:
		Gtk::DrawingArea	telaJogo;
		Gtk::HBox			janela;
		Gtk::VBox			barraLateral;
		Gtk::Frame			frameInfo;
		Gtk::VBox			infoBox;
        Gtk::Label			labelTurno;
        Gtk::Label          labelNumTurno;
		Gtk::Label			labelNumBrancas;
		Gtk::Label			labelNumPretas;
		Gtk::Button			botaoNovoJogo;
        Gtk::Button         botaoComecarIA;
        Gtk::Frame			labelCor;
		Gtk::VBox			cores;
		Gtk::RadioButton	corBrancas;
		Gtk::RadioButton	corPretas;
    	Gtk::Frame          labelPrimeroJogador;
		Gtk::VBox			primeiroJogadorBox;
        Gtk::RadioButton    jogadorBranco;
        Gtk::RadioButton    jogadorPreto;
		Gtk::Frame			frameInimigo;
		Gtk::VBox			inimigoBox;
		Gtk::Label			labelFuncAval;
		Gtk::ComboBoxText	funcAval;
		Gtk::Label			labelNivel;
		Gtk::ComboBoxText	nivelDificuldade;
        Gtk::Button			passaVez;
        Gtk::Button			voltar;
		Gtk::Button			avancar;
		double			bordaX;
		double			bordaY;
		double			raioPeca;

		Posicao			selecionada;

        bool            fimDoJogo;
		small_int		vencedor;
		
        // Overload da movePeca de Jogo para poder atualizar a interface
		void			movePeca(const Posicao origem, const int direcao);
		void			desenhaCirculo(Cairo::RefPtr<Cairo::Context> cr, double raio, double R, double G, double B,  int x, int y);
		void			desenhaPeca(Cairo::RefPtr<Cairo::Context> cr, double R, double G, double B,  int x, int y);
		void			avancaJogada();
		void			voltaJogada();
		void			atualizaLabelTurno();
		void			atualizaTela();
		
        void			novoJogo();
        void            comecarIA();
	
        void            trocarPrimeiroJogador();
        void            trocarCorJogador();
		void			trocarFuncAval();
		void			trocarDificuldade();
        
        bool			desenha_jogo(GdkEventExpose* event);
		bool			clicou_jogo(GdkEventButton* event);
		void			clicou_passaVez();

        void            primeiroJogador();

        void            atualizaNumTurnos();
	public:
		Interface(int (*avaliacao)( Tabuleiro& tab, small_int* possivelComer, const small_int jogador));
		~Interface() {};
};

#endif
