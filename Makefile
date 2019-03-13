FFLAGS = main.cpp nicholasJo.cpp brandonH.cpp nickolasL.cpp Game.cpp maps.cpp
HFLAGS = nicholasJo.h brandonH.h nickolasL.h Game.h maps.h
all: game

game: $(FFLAGS) $(HFLAGS)
	g++ -g $(FFLAGS) libggfonts.a -Wall -o game -lX11 -lGL -lGLU -lm


clean:
	rm -f game
	rm -f *.o

