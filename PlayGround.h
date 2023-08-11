#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#define BLOCK_SIZE 35

#include "Pacman.h"
#include "Cherry.h"
#include "Ghost.h"
#include "SmallPoint.h"
#include "BigPoint.h"
#include "Score.h"

#include <vector>
#include <array>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>

class PlayGround: public QObject
{
  Q_OBJECT
public:
  PlayGround();
  ~PlayGround();
  void show();
  bool checkWall(int x, int y);
  bool checkIntersection(int x, int y);
  int checkPaths(int x, int y);
  int getWidth();

  void move();
  void changePosture();

private:
  int width;
  int height;
  int blinked;
  int frightenedPoint;
  int *paths;
  int *intersection;
   
  Pacman *pacman;
  Cherry *cherry; 
  Score *score;
  QTimer *ghostsTimer;
  QTimer *blinkTimer;
  QGraphicsScene *pScene;
  QGraphicsView *pView;
  QGraphicsTextItem *pointText;
  std::vector<std::vector<char>> map;
  std::vector<SmallPoint*> smallpoint;
  std::vector<BigPoint*> bigpoint;
  std::vector<Ghost*> ghosts;

  void readMap();
  void loadMap();
  void fill(int x, int y, const char *color);
  void loadElements();
  void makeDirection();
  void makeIntersection();
  bool isPath(char c);
  void collisions();
  void enableFrightened();
  void disableFrightened();

private slots:
  void ghostsBlinking(QTimer*);
};

#endif
