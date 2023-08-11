#include "Game.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  Game *game = new Game();
  game->run();
  
  a.exec();

  delete game;
  return 0;
}
