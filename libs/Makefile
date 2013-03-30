GCC=gcc
RM=rm -f
LIBS=-lGLU -lGL -lm
LIBS_SDL=-lSDL_image `sdl-config --libs`
CFLAGS=-pedantic -std=c99 -Wall
CFLAGS_SDL=`sdl-config --cflags` -Wall

all: sdlKeyUtils.o glUtils.o intList.o fblList.o camera.o config.o

config.o: config.c config.h
	$(GCC) -c $(CFLAGS) $<

camera.o: camera.c camera.h
	$(GCC) -c $(CFLAGS) $(CFLAGS_SDL) $<

sdlKeyUtils.o: sdlKeyUtils.c sdlKeyUtils.h intList.h fblList.h
	$(GCC) -c $(CFLAGS) $(CFLAGS_SDL) $<

intList.o: intList.c intList.h
	$(GCC) -c $(CFLAGS) $<

fblList.o: fblList.c fblList.h
	$(GCC) -c $(CFLAGS) $<

glUtils.o: glUtils.c glUtils.h
	$(GCC) -c $(CFLAGS) $(CFLAGS_SDL) $<

clean:
	$(RM) *.o
