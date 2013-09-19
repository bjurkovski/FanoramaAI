GAME_NAME = fanorama
CC = g++
CFLAGS = -Wall `pkg-config gtkmm-2.4 --cflags --libs`
OBJECTS = interface.o jogo.o tabuleiro.o avaliacoes.o posicao.o

all: $(GAME_NAME)

$(GAME_NAME): main.cpp $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.cpp %.h
	$(CC) $< -c -o $@ $(CFLAGS) 

clean:
	rm *.o $(GAME_NAME)

