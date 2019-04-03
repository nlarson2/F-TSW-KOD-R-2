FFLAGS = main.cpp nicholasJo.cpp brandonH.cpp nickolasL.cpp Game.cpp maps.cpp log.cpp
HFLAGS = nicholasJo.h brandonH.h nickolasL.h Game.h maps.h
CFLAGS = libggfonts.a -Wall -o game -lX11 -lGL -lGLU -lm
all: game

game: $(FFLAGS) $(HFLAGS)
	g++ -g $(FFLAGS) $(CFLAGS)

clean:
	rm -f game
	rm -f *.o

