FFLAGS = main.cpp nicholasJo.cpp brandonH.cpp nickolasL.cpp
all: game

game: $(FFLAGS)
	g++ $(FFLAGS) libggfonts.a -Wall -o game -lX11 -lGL -lGLU -lm


clean:
	rm -f game
	rm -f *.o

