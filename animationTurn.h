#ifndef ANIMATIONTURN_H
#define ANIMATIONTURN_H

#include "disk.h"

#include <QQueue>

///
/// \brief The AnimationTurn struct
/// Contains Disk and Points for a single Turn
///
struct AnimationTurn
{
    Disk* disk;
    QQueue<QPointF> targetPositions;
};

#endif // ANIMATIONTURN_H
