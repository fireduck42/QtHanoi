#include "rod.h"

///
/// \brief Rod::Rod
/// \param x: x-Position of the rectangle representing the rod
/// \param y: y-Position of the rectangle representing the rod
/// \param width: width of the rectangle representing the rod
/// \param height: height of the rectangle representing the rod
/// \param color: color of the rectangle representing the rod
///
Rod::Rod(qreal x,
         qreal y,
         qreal width,
         qreal height,
         QColor color)
    : rectangle(new QGraphicsRectItem(x, y, width, height))
{
    rectangle->setBrush(QBrush(color));
}
///
/// \brief Disk::~Disk
/// Deallocate the graphic rectangle and the disks of the stack from memory
///
Rod::~Rod()
{
    delete rectangle;
    for (Disk *disk : disks)
    {
        delete disk;
    }
}
///
/// \brief Disk::getRectangle
/// \return the graphic rectangle
///
QGraphicsRectItem* Rod::getRectangle()
{
    return rectangle;
}
///
/// \brief Disk::putDiskOnTop
/// \param disk: disk to add
/// Adds disk to the top of the stack
///
void Rod::putDiskOnTop(Disk* disk)
{
    disks.push(disk);
}
///
/// \brief Disk::numberOfDisks
/// Remove disk from the top of the stack
/// \return current amount of disks on the stack
///
Disk* Rod::removeDiskOnTop()
{
    return disks.pop();
}
///
/// \brief Disk::numberOfDisks
/// \return current amount of disks on the stack
///
int Rod::numberOfDisks()
{
    return disks.count();
}
