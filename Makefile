FFLAGS = main.cpp nicholasJo.cpp brandonH.cpp nickolasL.cpp marbienJ.cpp adamO.cpp Game.cpp maps.cpp log.cpp
HFLAGS = nicholasJo.h brandonH.h nickolasL.h marbienJ.h adamO.h Game.h maps.h
CFLAGS = libggfonts.a -Wall -o game -lX11 -lGL -lGLU -lm
SFLAGS = -D SOUND /usr/lib/x86_64-linux-gnu/libopenal.so /usr/lib/x86_64-linux-gnu/libalut.so 
DFLAGS = -DDLC
all: game

game: $(FFLAGS) $(HFLAGS) 
	g++ -g $(FFLAGS) $(CFLAGS) $(DFLAGS)

sound: $(FFLAGS) $(HFLAGS)
	g++ -g $(FFLAGS) $(CFLAGS) $(SFLAGS)

clean:
	rm -f game
	rm -f *.o

