GCC=gcc
RM=rm -f
LIBS=-lGLU -lGL -lm
LIBS_SDL=-lSDL_image `sdl-config --libs`
CFLAGS=--std=c99 -Wall
CFLAGS_SDL=`sdl-config --cflags` -Wall