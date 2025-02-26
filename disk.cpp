#include "disk.h"

///
/// \brief Disk::Disk
/// \param x: x-Position of the rectangle representing the disk
/// \param y: y-Position of the rectangle representing the disk
/// \param width: width of the rectangle representing the disk
/// \param height: height of the rectangle representing the disk
/// \param diameter: diameter of the disk
/// \param color: color of the rectangle representing the disk
///
Disk::Disk(qreal x,
           qreal y,
           qreal width,
           qreal height,
           int diameter,
           QColor color)
    : rectangle(new QGraphicsRectItem(x, y, width, height))
    , diameter(diameter)
{
    rectangle->setBrush(QBrush(color));
}
///
/// \brief Disk::~Disk
/// Deallocate the graphic rectangle from memory
///
Disk::~Disk()
{
    delete rectangle;
}
///
/// \brief Disk::getRectangle
/// \return the graphic rectangle
///
QGraphicsRectItem* Disk::getRectangle()
{
    return rectangle;
}
///
/// \brief Disk::getDiameter
/// \return the diameter of the disk
///
int Disk::getDiameter()
{
    return diameter;
}
