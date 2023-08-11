#ifndef GHOST_H
#define GHOST_H

#include <QPen>
#include <QColor>
#include <QPolygonF>
#include <QGraphicsPolygonItem>

class PlayGround;

class Ghost: public QGraphicsPolygonItem
{
public:
  Ghost(PlayGround *pg, const QColor &color, int x, int y);
  void move();
  void changePosture();
  void enableFrightened();
  void disableFrightened();
  bool frightenedMode();
  void blink(int blinked);

private:
  enum direction {right=1, up=2, left=-1, down=-2};
  int width;
  int moveDirection;
  int posture;
  int frightened;
  int moveSpeed;
  QPen pen;
  PlayGround *playground;
  QPolygonF polygons[2];
  QColor defaultColor;
  void makePolygons();
  bool canChange();
  bool isWall(int direction);
  void findPath();
  bool isInBlock();
};

#endif
