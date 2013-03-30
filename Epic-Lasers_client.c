#include <stdio.h>
#include <stdlib.h>

#include "commons.h"
#include "mainMenu.h"
#include "libs/glUtils.h"

gameStatus_t gameStatus;

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
    default:
      fprintf(stderr, "Unknown game status ! Returning to main menu\n");
      gameStatus = main_menu;
  }
}

int main(int argc, char *argv[]) {
  //First thing first, the game needs a SDL context and an OpenGL one
  SDL_Surface *screen = gu_init_SDL("Epic-Lasers", 0);
  gu_init_GL();
  //Starting the game, we arrive on the menu
  gameStatus = main_menu;
  
  _gameStatusSwitcher();
  
  return (EXIT_SUCCESS);
}

