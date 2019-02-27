FFLAGS = main.cpp nicholasJo.cpp MainMenu.cpp GameState.cpp
all: MainMenu

MainMenu: $(FFLAGS)
	g++ $(FFLAGS) libggfonts.a -Wall -o MainMenu -lX11 -lGL -lGLU -lm


clean:
	rm -f MainMenu
	rm -f *.o

