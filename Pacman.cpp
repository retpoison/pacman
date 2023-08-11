#include "Pacman.h"
#include "PlayGround.h"

#include <QKeyEvent>

Pacman::Pacman(PlayGround *pg, int x, int y)
{
  playground = pg;
  posture = 0;
  width = BLOCK_SIZE-2;
  changeDirection = right;
  this->setBrush(Qt::yellow);
  this->setRect(0, 0, width, width);
  this->setFlag(QGraphicsItem::ItemIsFocusable);
  this->setFocus();
  this->setPos(x, y);
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Left) 
    changeDirection = left;
  else if (event->key() == Qt::Key_Right) 
    changeDirection = right;
  else if (event->key() == Qt::Key_Up) 
    changeDirection = up;
  else if (event->key() == Qt::Key_Down) 
    changeDirection = down;
}

void Pacman::move()
{
  if (moveDirection != changeDirection && canChange())
  {
    moveDirection = changeDirection;
    changePosture();
  }

  if (!(isWall(moveDirection)))
  {
    switch (moveDirection)
    {
      case right:
        setPos(x()+2, y());
        break;
      case up:
        setPos(x(), y()-2);
        break;
      case left: 
        setPos(x()-2, y());
        break;
      case down:
        setPos(x(), y()+2);
        break;
    }
  }
  if (pos().x() >= playground->getWidth()) setPos(0, pos().y());
  if (pos().x() < 0) setPos(playground->getWidth(), pos().y());
}

void Pacman::changePosture()
{
  if (isWall(moveDirection)) return;

  if (posture > 2) posture = 0;

  angle = posture*30;

  this->setStartAngle((angle + (moveDirection*90))*16);
  this->setSpanAngle((360 - (angle*2)) * 16);
  posture++;
}

bool Pacman::isWall(int direction)
{
  if (int(pos().x()/BLOCK_SIZE) != int((pos().x()+width)/BLOCK_SIZE))
    return false;
  else if (int(pos().y()/BLOCK_SIZE) != int((pos().y()+width)/BLOCK_SIZE))
    return false;
 
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

bool Pacman::canChange()
{
  if ((moveDirection == right && changeDirection == left) || 
      (moveDirection == left && changeDirection == right) || 
      (moveDirection == up && changeDirection == down)    || 
      (moveDirection == down && changeDirection == up))
    return true;
  if (int(pos().x()/BLOCK_SIZE) != int((pos().x()+width)/BLOCK_SIZE))
    return false;
  else if (int(pos().y()/BLOCK_SIZE) != int((pos().y()+width)/BLOCK_SIZE))
    return false;
  else if ((isWall(changeDirection)))
    return false;
  else 
    return true;
}
