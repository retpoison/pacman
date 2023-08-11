#include "Score.h"
#include <QFont>

Score::Score()
{
    score = 0;

    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("Ubuntu Regular",16));
}

void Score::increase(int x)
{
    score += x;
    setPlainText(QString("Score: ") + QString::number(score));
}

