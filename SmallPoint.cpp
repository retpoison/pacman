#include "SmallPoint.h"
#include "PlayGround.h"


SmallPoint::SmallPoint(int x, int y)
{
  this->setBrush(Qt::yellow);
  this->setRect(0, 0, 5, 5);
  this->setPos(x+(BLOCK_SIZE/2), y+(BLOCK_SIZE/2));
}

