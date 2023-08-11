#include "Ghost.h"
#include "PlayGround.h"

#include <cmath>

Ghost::Ghost(PlayGround *pg, const QColor &color, int x, int y)
{
  playground = pg;
  defaultColor = color;
  posture = 0;
  moveDirection = right;
  frightened = 0;
  moveSpeed = 2;
  
  width = BLOCK_SIZE-3;
  QPen pen;
  pen.setColor(Qt::transparent);
  this->setPen(pen);
  this->setBrush(defaultColor);
  this->setPos(x, y);

  makePolygons();
}

void Ghost::move()
{
  if (isInBlock() && int(pos().x()/BLOCK_SIZE) == 9 && int(pos().y()/BLOCK_SIZE) == 9)
  {
    setPos(x(), y()-2);
    moveDirection = up;
  }

  if (canChange()) findPath();

  if (!(isWall(moveDirection)))
  {
    switch (moveDirection)
    {
      case right:
        setPos(x()+moveSpeed, y());
        break;
      case up:
        setPos(x(), y()-moveSpeed);
        break;
      case left: 
        setPos(x()-moveSpeed, y());
        break;
      case down:
        setPos(x(), y()+moveSpeed);
        break;
    }
  }
  else findPath();

  if (pos().x() >= playground->getWidth()) setPos(0, pos().y());
  if (pos().x() < 0) setPos(playground->getWidth(), pos().y());
}

void Ghost::changePosture()
{
  posture = (-1*posture) + 1;
  this->setPolygon(polygons[posture]);
}

bool Ghost::isWall(int direction)
{
  if (!(isInBlock())) return false;
 
  int x = 0, y = 0;

  int px = pos().x()/BLOCK_SIZE;
  int py = pos().y()/BLOCK_SIZE;
  switch (direction) {
    case right:
      x = px+1;
      y = py;
      break;
    case up:
      x = px;
      y = py-1;
      break;
    case left:
      x = px-1;
      y = py;
      break;
    case down:
      x = px;
      y = py+1;
      break;
  }
  return playground->checkWall(x, y);
}

bool Ghost::canChange()
{
  if (!(isInBlock()))
    return false;
  else if (playground->checkIntersection(pos().x()/BLOCK_SIZE, pos().y()/BLOCK_SIZE))
    return true;
  else 
    return false;
}

void Ghost::findPath()
{
  int ones = playground->checkPaths(pos().x()/BLOCK_SIZE, pos().y()/BLOCK_SIZE);
  if (ones == 1) moveDirection = -moveDirection;
  else if (ones > 1) moveDirection = std::pow(-1, rand())*((rand() % 2)+1);
}

bool Ghost::isInBlock()
{
  if (int(pos().x()/BLOCK_SIZE) != int((pos().x()+width)/BLOCK_SIZE))
    return false;
  else if (int(pos().y()/BLOCK_SIZE) != int((pos().y()+width)/BLOCK_SIZE))
    return false;
  else 
    return true;
}
void Ghost::enableFrightened()
{
  frightened = 1;
  moveSpeed = 1;

  this->setBrush(Qt::darkBlue);
}

void Ghost::disableFrightened()
{
  frightened = 0;
  moveSpeed = 2;
  this->setBrush(defaultColor);
}

bool Ghost::frightenedMode()
{
  return frightened;
}

void Ghost::blink(int blinked)
{
  if (!(frightened)) return;

  if (blinked%2) 
    this->setBrush(Qt::darkBlue);
  else
    this->setBrush(Qt::white);
}

void Ghost::makePolygons()
{
  QPolygonF polygon_1, polygon_2;

  polygon_1 << QPointF{32, 11};
  polygon_1 << QPointF{32, 32};
  polygon_1 << QPointF{26, 26};
  polygon_1 << QPointF{20, 32};
  polygon_1 << QPointF{20, 26};
  polygon_1 << QPointF{12, 26};
  polygon_1 << QPointF{12, 32};
  polygon_1 << QPointF{6, 26};
  polygon_1 << QPointF{0, 32};
  polygon_1 << QPointF{0, 32};
  polygon_1 << QPointF{0, 22};
  polygon_1 << QPointF{0, 11};
  polygon_1 << QPointF{3, 6};
  polygon_1 << QPointF{8, 2};
  polygon_1 << QPointF{16, 0};
  polygon_1 << QPointF{24, 2};
  polygon_1 << QPointF{29, 6};
  polygon_1 << QPointF{32, 11};
  

  polygon_2 << QPointF{32, 11};
  polygon_2 << QPointF{32, 27};
  polygon_2 << QPointF{27, 32};
  polygon_2 << QPointF{22, 27};
  polygon_2 << QPointF{16, 32};
  polygon_2 << QPointF{10, 27};
  polygon_2 << QPointF{5, 32};
  polygon_2 << QPointF{0, 27};
  polygon_2 << QPointF{0, 22};
  polygon_2 << QPointF{0, 11};
  polygon_2 << QPointF{3, 6};
  polygon_2 << QPointF{8, 2};
  polygon_2 << QPointF{16, 0};
  polygon_2 << QPointF{24, 2};
  polygon_2 << QPointF{29, 6};
  polygon_2 << QPointF{32, 11};
 
  polygons[0] = polygon_1;
  polygons[1] = polygon_2;
}
