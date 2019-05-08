FFLAGS = main.cpp nicholasJo.cpp brandonH.cpp nickolasL.cpp marbienJ.cpp adamO.cpp maps.cpp log.cpp
HFLAGS = nicholasJo.h brandonH.h nickolasL.h marbienJ.h adamO.h maps.h
CFLAGS = libggfonts.a -Wall -o game -lX11 -lGL -lGLU -lm
SFLAGS = -D SOUND \
		/usr/lib/x86_64-linux-gnu/libopenal.so /usr/lib/x86_64-linux-gnu/libalut.so \
		/usr/lib/x86_64-linux-gnu/libvorbis.so /usr/lib/x86_64-linux-gnu/libvorbisfile.so \
		/usr/lib/x86_64-linux-gnu/libogg.so
all: game

game: $(FFLAGS) $(HFLAGS)
	g++ -g $(FFLAGS) $(CFLAGS) -o game
	g++ serverCon.cpp -Wall -oserverCon -lssl -lcrypto	

sound: $(FFLAGS) $(HFLAGS)
	g++ -g $(FFLAGS) $(CFLAGS) $(SFLAGS) -o sound
	g++ serverCon.cpp -Wall -oserverCon -lssl -lcrypto	

unit: $(FFLAGS) $(HFLAGS)
	g++ -g $(FFLAGS) $(CFLAGS) -o game -D UNIT_TEST
	g++ serverCon.cpp -Wall -oserverCon -lssl -lcrypto	

clean:
	rm -f game
	rm -f sound
	rm -f *.o

