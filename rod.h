#ifndef ROD_H
#define ROD_H

#include "disk.h"

#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>
#include <QStack>

///
/// \brief The Rod class
/// Represents the Rod in the Hanoi-Game
///
class Rod
{
public:
    Rod(qreal x, qreal y, qreal width, qreal height, QColor color);
    ~Rod();

    QGraphicsRectItem* getRectangle();
    void putDiskOnTop(Disk* disk);
    Disk* removeDiskOnTop();
    int numberOfDisks();

private:
    QGraphicsRectItem* rectangle;
    QStack<Disk*> disks;
};

#endif // ROD_H
