CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

all: rainforest

<<<<<<< HEAD
rainforest: rainforest.cpp log.cpp marbienJ.cpp
	g++ $(CFLAGS) rainforest.cpp marbienJ.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o rainforest
=======
rainforest: rainforest.cpp log.cpp nickolasL.cpp
	g++ $(CFLAGS) rainforest.cpp nickolasL.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o rainforest
>>>>>>> 8cb83e52e7646bc21bd3cff5de8acbf76478b0b0

clean:
	rm -f rainforest
	rm -f *.o

