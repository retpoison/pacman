#include "Game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  Game *game = new Game();
  game->run();

  return a.exec();
}
