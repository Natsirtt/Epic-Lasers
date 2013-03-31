#include <unistd.h>

#include "menus.h"
#include "libs/glUtils.h"
#include "libs/sdlKeyUtils.h"

keyBinder kb;

gameStatus_t eventCatcher(SDL_Event *event) {
  switch (event->type) {
    case SDL_KEYDOWN:
      skuKeyPressed(&kb, event->key.keysym.sym);
      if (skuIsPressed(&kb, SDLK_ESCAPE)) {
        return quitting;
      }
      break;
    case SDL_KEYUP:
      skuKeyReleased(&kb, event->key.keysym.sym);
      break;
    case SDL_QUIT:
      return quitting;
      break;
  }
  return null_status;
}

void _mainMenuDisplay() {
  glColor3f(1, 1, 1);
  gu_drawPara(30, 30, 30);
}

gameStatus_t mainMenuLoop() {
  gameStatus_t newStatus;
  SDL_Event event;
  skuInitKeyBinder(&kb);

  gu_init_display(_mainMenuDisplay);
  while (newStatus == null_status || newStatus == settings || newStatus == main_menu) {
    while (SDL_PollEvent(&event)) {
      newStatus = eventCatcher(&event);
    }
    gu_display();
  }
  return quitting;
}