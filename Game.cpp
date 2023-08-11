#include "Game.h"
#include "PlayGround.h"
#include "SmallPoint.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QRect>
#include <QPixmap>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <QTimer>

Game::Game()
{
  PlayGround playGround;
  moveTimer = new QTimer(this);
  connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));

  postureTimer = new QTimer(this);
  connect(postureTimer, SIGNAL(timeout()), this, SLOT(changePosture()));
}

void Game::move()
{
  playGround.move();
}

void Game::changePosture()
{
  playGround.changePosture();
}

void Game::run() 
{
  moveTimer->start(20);
  postureTimer->start(100);
  playGround.show();
}

Game::~Game()
{
  delete moveTimer;
  delete postureTimer;
}
