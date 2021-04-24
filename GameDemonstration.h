 /*
  GameDemonstration.h - Demonstrace jednoduché hry
*/
#ifndef GAMEDEMONSTRATION_h
#define GAMEDEMONSTRATION_h
#define GAME_PERIOD_IN_MICROS 40000
#include "Game.h"

class GameDemonstration : public Game
{
  public:
    GameDemonstration();
    void init();

  void handleGame();

    
  protected:
  long _lastSyncTime;
  
};

#endif
