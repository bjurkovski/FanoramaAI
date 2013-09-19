#include <gtkmm/main.h>
#include <cstdlib>
#include <time.h>

#include "interface.h"
#include "avaliacoes.h"

int main(int argc, char* argv[])
{
    /* random seed for the evaluation function */
    srand(time(0));

    Gtk::Main kit(argc, argv);
	
	Interface jogo(avalia2);

	// Entra no loop da GTK
	Gtk::Main::run(jogo);

	return 0;
}
