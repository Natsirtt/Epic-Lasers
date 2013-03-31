#ifndef COMMONS_H
#define	COMMONS_H

#ifdef	__cplusplus
extern "C" {
#endif

  //Management of the game status

  typedef enum {
    null_status,
    main_menu,
    settings,
    in_game,
    paused,
    loading,
    quitting
  }
  gameStatus_t;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMONS_H */

