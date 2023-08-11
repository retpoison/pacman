#ifndef BIGPOINT_H
#define BIGPOINT_H

#include <QGraphicsEllipseItem>
#include <QColor>

class BigPoint : public QGraphicsEllipseItem
{
public:
  BigPoint(int x, int y);
  void changePosture();

private:
  QColor color[2] = {Qt::yellow, Qt::transparent};
  int posture;
};
#endif
