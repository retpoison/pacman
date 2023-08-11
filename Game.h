#ifndef GAME_H
#define GAME_H

#include "PlayGround.h"

#include <vector>
#include <QTimer>

class Game: public QObject
{
  Q_OBJECT  
public:
  Game();
  ~Game();
  void run();
public slots:
  void move();
  void changePosture();
private:
  PlayGround playGround;
  QTimer *moveTimer, *postureTimer;
};

#endif
