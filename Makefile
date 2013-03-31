GCC=gcc
RM=rm -f
LIBS=-lGLU -lGL -lm
LIBS_SDL=-lSDL_image `sdl-config --libs`
CFLAGS=-pedantic -std=c99 -Wall
CFLAGS_SDL=`sdl-config --cflags` -Wall
DIR_LIBS=libs
MAKE_LIBS=make --directory=libs

all: Epic-Lasers_client Epic-Lasers_server

Epic-Lasers_client: Epic-Lasers_client.o menus.o $(DIR_LIBS)/config.o $(DIR_LIBS)/glUtils.o $(DIR_LIBS)/camera.o $(DIR_LIBS)/sdlKeyUtils.o $(DIR_LIBS)/intList.o $(DIR_LIBS)/fblList.o
	$(GCC) -o $@ $^ $(LIBS_SDL) $(LIBS)

Epic-Lasers_server: Epic-Lasers_server.o
	$(GCC) -o $@ $^ $(LIBS_SDL) $(LIBS)

Epic-Lasers_client.o: Epic-Lasers_client.c commons.h menus.h
	$(GCC) -c $(CFLAGS) $(CFLAGS_SDL) $<

menus.o: menus.c menus.h commons.h $(DIR_LIBS)/sdlKeyUtils.h
	$(GCC) -c $(CFLAGS) $(CFLAGS_SDL) $<

config.o:
	$(MAKE_LIBS) config.o

camera.o:
	$(MAKE_LIBS) camera.o

sdlKeyUtils.o:
	$(MAKE_LIBS) sdlKeyUtils.o

glUtils.o:
	$(MAKE_LIBS) glUtils.o

intList.o:
	$(MAKE_LIBS) intList.o

fblUtils.o:
	$(MAKE_LIBS) fblUtils.o

clean: cleanHere
	$(MAKE_LIBS) clean

cleanHere:
	$(RM) *.o