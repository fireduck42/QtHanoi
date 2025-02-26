#ifndef HANOIGAME_H
#define HANOIGAME_H

#include "animationTurn.h"
#include "disk.h"
#include "gameState.h"
#include "observer.h"
#include "rod.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>

///
/// \brief The HanoiGame class
/// Extends QGraphicsScene for Scene interaction
///
class HanoiGame : public QGraphicsScene
{
public:
    HanoiGame(int amountOfDisks,
              float turnsPerSecond);
    ~HanoiGame();
    void start();
    void pause();
    int getCurrentDiskAmount();
    float getTurnsPerSecond();
    void registerObserver(Observer* observer);
    void removeObserver(Observer* observer);

private:

    static inline int FRAMES_PER_SECOND = 60;
    static inline int UPDATE_TIME_MS = 1000 / FRAMES_PER_SECOND;
    static inline int DISK_HEIGHT = 20;
    static inline int DISK_WIDTH_PER_DIAMETER = 40;
    static inline int ANIMATION_HEIGHT = -300;
    static inline QColor ROD_COLOR = QColor(110, 83, 35);
    static inline QList<QColor> DISK_COLORS = {
        Qt::red,
        Qt::darkCyan,
        Qt::darkBlue,
        Qt::yellow,
        Qt::green,
        Qt::lightGray,
        Qt::magenta,
        Qt::darkGreen,
        Qt::black
    };

    int amountOfDisks;
    int turn;
    float turnsPerSecond;
    int totalFramesPerAnimation;
    int remainingFrames;
    Rod* leftRod;
    Rod* centerRod;
    Rod* rightRod;
    QTimer* timer;
    QList<Observer*> observers;
    QQueue<AnimationTurn> turns;
    GameState currentState;
    QPointF animationOffset;

    void initializeGame();
    void initializeGameAttributes();
    void renderScene();
    void renderRods();
    void renderDisks();

    void simulateGame();
    void recursiveShift(int numberOfDisks, Rod* start, Rod* spare, Rod* target);
    void move(Rod* start, Rod* target);
    QQueue<QPointF> getTurnAnimationPositions(Disk* disk, Rod* start, Rod* target);
    QPointF getAnimationPositionAboveRod(Disk* disk, Rod* rod);
    QPointF getAnimationPositionOnRod(Disk* disk, Rod* rod);

    void animateMovement(AnimationTurn& turn);
    void startNextTurn();

    bool isEndOfTurn();
    bool isGameFinished();

    void notifyObserversStates();
    void notifyObserversMoves();

private slots:
    void updateScene();
};

#endif // HANOIGAME_H
