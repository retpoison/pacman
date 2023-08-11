#include "PlayGround.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
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
#include <Qt>
#include <QBrush>
#include <QColor>
#include <QLabel>
#include <QTimer>

PlayGround::PlayGround()
{
  pScene = new QGraphicsScene();
  pView = new QGraphicsView();

  loadMap();
  makeDirection();
  makeIntersection();
  loadElements();
  pScene->setSceneRect(0, 0, width*BLOCK_SIZE, height*BLOCK_SIZE);
  pView->setFixedSize(width*BLOCK_SIZE, (height)*BLOCK_SIZE);
 
  pView->setAlignment(Qt::AlignBottom);
  pView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  pView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  pView->setBackgroundBrush(Qt::black);
  pView->setScene(pScene);
  
  pointText = new QGraphicsTextItem();
  pointText->setFont(QFont("Ubuntu Regular",16));
  pointText->setDefaultTextColor(Qt::white);
  pScene->addItem(pointText);

  frightenedPoint = 200;
  ghostsTimer = new QTimer(this);
  ghostsTimer->setSingleShot(true);
  connect(ghostsTimer, &QTimer::timeout, this, [=](){ghostsBlinking(blinkTimer);});
  
  blinkTimer = new QTimer(this);
  connect(blinkTimer, &QTimer::timeout, this, [=](){ghostsBlinking(blinkTimer);});
}

void PlayGround::readMap()
{
  // open map file
  std::ifstream file("map.txt");
  
  // get width and height of the map
  std::string str;
  getline(file, str);
  width = std::stoi(str);
  getline(file, str);
  height = std::stoi(str);

  for (int i = 0; i < height; i++)
  {
    getline(file, str);
    map.push_back(std::vector<char>());
    for (unsigned int j = 0; j < str.length(); j++)
    {
      map[i].push_back(str[j]);
    }
  }
  
  file.close();
}

void PlayGround::loadMap()
{
  readMap();

  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++)
    {
      switch (map[j][i]) 
      {
        case '#':
          // wall
          fill(i, j, "#1919a6");
          break;
        case '-':
          // door
          fill(i, j, "#69475d");
          break;
      }
    }
  }
}

void PlayGround::fill(int x, int y,const char *color) 
{
  QGraphicsRectItem *block = new QGraphicsRectItem();

  block->setRect(0, 0, BLOCK_SIZE, BLOCK_SIZE);
  block->setPos(x*BLOCK_SIZE, y*BLOCK_SIZE);
  block->setBrush(QColor(color));
  pScene->addItem(block);
}

void PlayGround::loadElements()
{
  score = new Score();
  pScene->addItem(score);

  QColor color[4] = {Qt::red, Qt::magenta, Qt::yellow, Qt::cyan};
  int ghostCount = 0;
  
  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++)
    {
      // load elements
      switch(map[j][i])
      {
        case 'C':
         // cherry = new Cherry(i*BLOCK_SIZE, j*BLOCK_SIZE);
//          pScene->addItem(cherry;
          break;
        case 'a':
          smallpoint.push_back(new SmallPoint(i*BLOCK_SIZE, j*BLOCK_SIZE));
          pScene->addItem(smallpoint.back());
          break;
        case 'A':
          bigpoint.push_back(new BigPoint(i*BLOCK_SIZE, j*BLOCK_SIZE));
          pScene->addItem(bigpoint.back());
          break;
      }
    }
  }

  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++)
    {
      // load elements
      switch(map[j][i])
      {
        case 'G':
          ghosts.push_back(new Ghost(this, color[ghostCount], i*BLOCK_SIZE, j*BLOCK_SIZE));
          ghostCount++;
          pScene->addItem(ghosts.back());
          break;
        case 'P':
          pacman = new Pacman(this, i*BLOCK_SIZE, j*BLOCK_SIZE);
          pScene->addItem(pacman);
          break;
      }
    }
  }
}

void PlayGround::makeDirection()
{
  paths = new int[height * width * 4];
  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++)
    {
      // make directions
      if (isPath(map[j][i]))
      {
        // right, up, left, down
        paths[j*width*4 + i*4 + 0] = (!(i+1 >= width) && isPath(map[j][i+1])) ? 1 : 0;
        paths[j*width*4 + i*4 + 1] = (!(j-1 < 0) && isPath(map[j-1][i])) ? 1 : 0;
        paths[j*width*4 + i*4 + 2] = (!(i-1 < 0) && isPath(map[j][i-1])) ? 1 : 0;
        paths[j*width*4 + i*4 + 3] = (!(j+1 >= height) && isPath(map[j+1][i])) ? 1 : 0;
      }
      else 
      {
        for (int k = 0; k < 4; k++) paths[j*width*4 + i*4 + k] = 0;
      }
    }
  }
}

void PlayGround::makeIntersection()
{
  intersection = new int[width * height];
  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++)
    {
      // make directions
      if (isPath(map[j][i]))
      {
        // right, left
        // up, down
        if ((paths[j*width*4 + i*4 + 0] == 1 || paths[j*width*4 + i*4 + 2] == 1)
         && (paths[j*width*4 + i*4 + 1] == 1 || paths[j*width*4 + i*4 + 3] == 1))
        {
          intersection[j*width + i] = 1;
        }
      }
      else 
      {
        intersection[j*width + i] = 0;
      }
    }
  }
}

bool PlayGround::isPath(char c)
{
  if (c != '#' && c != '!') return true;
  return false;
}

bool PlayGround::checkWall(int x, int y)
{
  return (map[y][x] == '#' || map[y][x] == '-') ? true : false;
}

bool PlayGround::checkIntersection(int x, int y)
{
  if (intersection[y*width + x] == 1) return true;
  return false;
}

int PlayGround::checkPaths(int x, int y)
{
  int ones = 0;
  for (int i = 0; i < 4; i++)
  {
    if (paths[y*width*4 + x*4 + i] == 1) ones++;
  }

  return ones;
}

void PlayGround::collisions()
{
  for (auto g: ghosts)
  {
    if (pacman->collidesWithItem(g))
    {
      if (g->frightenedMode())
      {
        g->disableFrightened();
        g->setPos(10*BLOCK_SIZE, 9*BLOCK_SIZE);
        score->increase(frightenedPoint);
        
        pointText->setPlainText(QString::number(frightenedPoint));
        pointText->setPos(pacman->pos().x()-10, pacman->pos().y()-10);
        QTimer *pointTimer = new QTimer();
        pointTimer->setSingleShot(true);
        connect(pointTimer, &QTimer::timeout, this, [=](){
            pointText->setPlainText(QString(""));
            delete pointTimer;
            });
        
        pointTimer->start(2000);
        frightenedPoint *= 2;
      }
      else
        QApplication::quit();
    }
  }

  int index = 0;
  for (auto sp: smallpoint)
  {
    if (pacman->collidesWithItem(sp))
    {
      score->increase(10);
      pScene->removeItem(sp);
      smallpoint.erase(smallpoint.begin() + index);
      index--;
    }
    index++;
  }
  
  index = 0;
  for (auto bp: bigpoint)
  {
    if (pacman->collidesWithItem(bp))
    {
      score->increase(50);
      pScene->removeItem(bp);
      bigpoint.erase(bigpoint.begin() + index);
      index--;
      enableFrightened();
    }
    index++;
  }
}

void PlayGround::enableFrightened()
{
  if (blinked)
  {
    blinkTimer->stop();
    ghostsTimer->stop();
  }
  blinked = 1;
  for (auto g : ghosts) g->enableFrightened();
  ghostsTimer->start(6000);
}

void PlayGround::disableFrightened()
{
  for (auto g : ghosts) g->disableFrightened();
  frightenedPoint = 200;
}

void PlayGround::ghostsBlinking(QTimer *blinkTimer)
{
  if (blinked == 1)
  {
    blinkTimer->start(200);
  }

  if (blinked >= 20)
  {
    blinked = 0;
    disableFrightened();
    blinkTimer->stop();
    return;
  }
  
  for (auto g : ghosts) g->blink(blinked);
  blinked++;
}

int PlayGround::getWidth()
{
  return width*BLOCK_SIZE;
}

void PlayGround::move()
{
  pacman->move();
  for (auto g : ghosts) g->move();
  collisions();
}

void PlayGround::changePosture()
{
  pacman->changePosture();
  for (auto g : ghosts) g->changePosture();
  for (auto b : bigpoint) b->changePosture();
}

void PlayGround::show()
{
  pView->show();
}

PlayGround::~PlayGround()
{
  delete[] intersection;
  delete[] paths;
  delete pScene;
  delete pView;

}
