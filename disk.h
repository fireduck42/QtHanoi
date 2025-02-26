#ifndef DISK_H
#define DISK_H

#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>

///
/// \brief The Rod class
/// Represents the Disk in the Hanoi-Game
///
class Disk
{
public:
    Disk(qreal x, qreal y, qreal width, qreal height, int diameter, QColor color);
    ~Disk();

    QGraphicsRectItem* getRectangle();
    int getDiameter();

private:
    QGraphicsRectItem* rectangle;
    int diameter;
};

#endif // DISK_H
