#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>

#include "commons.h"
#include "menus.h"
#include "libs/glUtils.h"
#include "libs/config.h"
#include "libs/camera.h"

camCamera camera;
gameStatus_t gameStatus;

void quitProgram() {
  gu_SDLQuit(1);
}

void _gameStatusSwitcher() {
  switch(gameStatus) {
    case main_menu:
      gameStatus = mainMenuLoop();
      break;
    case in_game:
      
      break;
    case paused:
      
      break;
    case loading:
      
      break;
    case quitting:
      quitProgram();
      break;
    default:
      fprintf(stderr, "Unknown game status ! Returning to main menu\n");
      gameStatus = main_menu;
  }
}

int main(int argc, char *argv[]) {
  //First thing first, the game needs a SDL context and an OpenGL one
  SDL_Surface *screen;
  int configReturn = config_isAntialiasingActive();
  if (configReturn == -1) {
    fprintf(stderr, "Unable to create the config file. Have you got permission to run the program ? Aborting\n");
  } else if (configReturn == 0) {
    screen = gu_init_SDL("Epic-Lasers", 0);
  } else {
    screen = gu_init_SDL("Epic Lasers", config_getAntialiasingSamplesNb());
  }
  
  camInit(&camera);
  
  gu_init_GL();
  glMatrixMode(GL_PROJECTION);
  gluPerspective(50, (float) screen->w / screen->h, 1, 100);
  glMatrixMode(GL_MODELVIEW);
  
  camFixePosition(&camera, 0, 0, 10, 0, 0, 0, 0, 1, 0);
  
  //Starting the game, we arrive on the menu
  gameStatus = main_menu;
  
  _gameStatusSwitcher();
  
  return (EXIT_SUCCESS);
}

