#include "BigPoint.h"
#include "PlayGround.h"

#include <QColor>

BigPoint::BigPoint(int x, int y)
{
  posture = 0;

  this->setBrush(color[posture]);
  this->setRect(0, 0, 15, 15);
  this->setPos(x+(BLOCK_SIZE/3), y+(BLOCK_SIZE/3));
}

void BigPoint::changePosture()
{
  posture = (posture*-1) + 1;
  this->setBrush(color[posture]);
}
