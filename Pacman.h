#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include <QGraphicsEllipseItem>

class PlayGround;

class Pacman: public QGraphicsEllipseItem
{
public:
  Pacman(PlayGround* pg, int X, int Y);
  void move();
  void changePosture();
  bool isWall(int direction);
  void keyPressEvent(QKeyEvent *event);

private:
  enum direction {right, up, left, down};
  int width;
  int moveDirection;
  int changeDirection;
  int posture;
  int angle;
  PlayGround *playground;
  bool canChange();
};

#endif
