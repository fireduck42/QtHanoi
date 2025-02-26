#include "hanoiGame.h"

///
/// \brief HanoiGame::HanoiGame
/// \param initialDiskAmount: amount of disks being used for the game
/// \param turnsPerSecond: amount of turns per second the animation is supossed to play
///
HanoiGame::HanoiGame(int initialDiskAmount,
                     float turnsPerSecond)
    : amountOfDisks(initialDiskAmount)
    , turn(0)
    , turnsPerSecond(turnsPerSecond)
    , totalFramesPerAnimation((FRAMES_PER_SECOND / 3) / turnsPerSecond)
    , remainingFrames(totalFramesPerAnimation)
{
    initializeGame();
    simulateGame();
}
///
/// \brief HanoiGame::~HanoiGame
/// Deallocate rods and timer from memory
///
HanoiGame::~HanoiGame()
{
    delete timer;
    delete leftRod;
    delete centerRod;
    delete rightRod;
    observers.clear();
}
///
/// \brief HanoiGame::initializeGame
/// Initializes Attributes and renders game starting position
///
void HanoiGame::initializeGame()
{
    initializeGameAttributes();
    renderScene();
    currentState = GameState::Ready;
}
///
/// \brief HanoiGame::initializeGameAttributes
/// Initializes Attributes Rods and Timer
///
void HanoiGame::initializeGameAttributes(){
    observers = QList<Observer*>();
    leftRod = new Rod(-500, -150, 20, 300, ROD_COLOR);
    centerRod = new Rod(0, -150, 20, 300, ROD_COLOR);
    rightRod = new Rod(500, -150, 20, 300, ROD_COLOR);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HanoiGame::updateScene);
}
///
/// \brief HanoiGame::renderScene
/// Adds all neccessary graphic-objects to the scene
///
void HanoiGame::renderScene(){
    renderRods();
    renderDisks();
}
///
/// \brief HanoiGame::renderRods
/// Adds the rectangles of three rods to the scene
///
void HanoiGame::renderRods(){
    addItem(leftRod->getRectangle());
    addItem(centerRod->getRectangle());
    addItem(rightRod->getRectangle());
}
///
/// \brief HanoiGame::renderDisks
/// Calculates and adds the rectangles of the disks to the scene
///
void HanoiGame::renderDisks() {
    QRectF leftRect = leftRod->getRectangle()->rect();

    for (int iter = amountOfDisks; iter > 0; --iter)
    {
        Disk* disk = new Disk(0, 0, iter * DISK_WIDTH_PER_DIAMETER, DISK_HEIGHT,
                              iter, DISK_COLORS[amountOfDisks - iter]);

        disk->getRectangle()->setPos(
            leftRect.x() - (iter * DISK_WIDTH_PER_DIAMETER - leftRect.width()) / 2,
            leftRect.y() - DISK_HEIGHT + leftRect.height() - (amountOfDisks - iter) * DISK_HEIGHT
            );

        addItem(disk->getRectangle());
        leftRod->putDiskOnTop(disk);
    }
}
///
/// \brief HanoiGame::simulateGame
/// Starts the hanoi recursive algorithm
///
void HanoiGame::simulateGame()
{
    recursiveShift(amountOfDisks, leftRod, centerRod, rightRod);
}
///
/// \brief HanoiGame::recursiveShift
/// \param numberOfDisks: number of disks being used in the current game
/// \param start: rod from which the disks should be moved
/// \param spare: rod to help move the disks
/// \param target: rod to which the disks should be moved
/// The hanoi recursive algorithm that moves the disks from the start to the target rod
///
void HanoiGame::recursiveShift(int numberOfDisks, Rod* start, Rod* spare, Rod* target)
{
    if (numberOfDisks > 0)
    {
        recursiveShift(numberOfDisks - 1, start, target, spare);
        move(start, target);
        recursiveShift(numberOfDisks - 1, spare, start, target);
    }
}
///
/// \brief HanoiGame::move
/// \param start: rod from which the disk is taken away
/// \param target: rod to which the disk will be moved
/// Takes the disk from start to target and enqueues its animation for later
///
void HanoiGame::move(Rod* start, Rod* target)
{
    Disk* disk = start->removeDiskOnTop();
    turns.enqueue(
        AnimationTurn {disk,
                      getTurnAnimationPositions(disk, start, target)}
        );
    target->putDiskOnTop(disk);
}
///
/// \brief HanoiGame::getTurnAnimationPositions
/// \param disk: disk to be animated
/// \param start: rod from which the disk is taken away
/// \param target: rod to which the disk will be moved
/// Gets the points that the disks should pass in the animation
/// \return queue of points that the disks should pass in the animation
///
QQueue<QPointF> HanoiGame::getTurnAnimationPositions(Disk* disk, Rod* start, Rod* target)
{
    QQueue<QPointF> targetPositions;

    targetPositions.enqueue(getAnimationPositionAboveRod(disk, start));
    targetPositions.enqueue(getAnimationPositionAboveRod(disk, target));
    targetPositions.enqueue(getAnimationPositionOnRod(disk, target));

    return targetPositions;
}
///
/// \brief HanoiGame::getAnimationPositionAboveRod
/// \param disk: disk for which the point is calculated
/// \param rod: rod with which the point is calculated
/// Calculates the point above the rod relative to the disk-size
/// \return point above the rod
///
QPointF HanoiGame::getAnimationPositionAboveRod(Disk* disk, Rod* rod)
{
    QRectF diskRectangle = disk->getRectangle()->rect();
    QRectF rodRectangle = rod->getRectangle()->rect();

    return QPointF(rodRectangle.x() - (diskRectangle.width() - rodRectangle.width()) / 2, ANIMATION_HEIGHT);
}
///
/// \brief HanoiGame::getAnimationPositionAboveRod
/// \param disk: disk for which the point is calculated
/// \param rod: rod with which the point is calculated
/// Calculates the point on the rod relative to the disk-size and amount of Disks
/// \return point on the rod
///
QPointF HanoiGame::getAnimationPositionOnRod(Disk* disk, Rod* rod)
{
    QRectF diskRectangle = disk->getRectangle()->rect();
    QRectF rodRectangle = rod->getRectangle()->rect();

    return QPointF(
        rodRectangle.x() - (diskRectangle.width() - rodRectangle.width()) / 2,
        rodRectangle.y() - (diskRectangle.height() - rodRectangle.height()) - rod->numberOfDisks() * DISK_HEIGHT
        );
}
///
/// \brief HanoiGame::updateScene
/// Updates gamescene based on timer
///
void HanoiGame::updateScene()
{
    if (!isGameFinished())
    {
        animateMovement(turns.head());
        if (isEndOfTurn())
        {
            startNextTurn();
        }
    }
}
///
/// \brief HanoiGame::animateMovement
/// \param turn: turn to be animated
/// Gets disk and current animation-targetposition and moves the disk
/// based on distance to the targetposition and totalFramesPerAnimation
/// while remainingFrames acts as decrement variable for checks
///
void HanoiGame::animateMovement(AnimationTurn& turn)
{
    QGraphicsRectItem* diskRectangle = turn.disk->getRectangle();
    QPointF targetPos = turn.targetPositions.head();

    if (remainingFrames == totalFramesPerAnimation)
    {//initalize Animation
        animationOffset = (targetPos - diskRectangle->pos())
                          / totalFramesPerAnimation;
    }

    if (remainingFrames > 1)
    {//animate
        diskRectangle->setPos(diskRectangle->pos() + animationOffset);
        remainingFrames--;
    }
    else
    {//finish Animation
        diskRectangle->setPos(targetPos);
        turn.targetPositions.dequeue();
        remainingFrames = totalFramesPerAnimation;
    }
}
///
/// \brief HanoiGame::startNextTurn
/// Checks if game is finished and updates gamestate and turn number based on that
///
void HanoiGame::startNextTurn()
{
    turns.dequeue();
    if (!isGameFinished())
    {
        turn++;
        notifyObserversMoves();
    }
    else
    {
        timer->stop();
        currentState = GameState::Finished;
        notifyObserversStates();
    }
}
///
/// \brief HanoiGame::isEndOfTurn
/// \returns whether or not there are targetPositions left for the current turn
///
bool HanoiGame::isEndOfTurn()
{
    return turns.head().targetPositions.isEmpty();
}
///
/// \brief HanoiGame::isGameFinished
/// \returns whether or not there are turns left
///
bool HanoiGame::isGameFinished()
{
    return turns.isEmpty();
}
///
/// \brief HanoiGame::getCurrentDiskAmount
/// \returns the amount of disks
///
int HanoiGame::getCurrentDiskAmount()
{
    return amountOfDisks;
}
///
/// \brief HanoiGame::getTurnsPerSecond
/// \returns amount of turns animated per Second
///
float HanoiGame::getTurnsPerSecond()
{
    return turnsPerSecond;
}
///
/// \brief HanoiGame::start
/// Starts the timer for the animation and updates gamestate and turn number
///
void HanoiGame::start()
{
    timer->start(UPDATE_TIME_MS);
    turn = 1;
    currentState = GameState::Playing;
    notifyObserversMoves();
    notifyObserversStates();
}
///
/// \brief HanoiGame::pause
/// Pauses or starts the timer for the animation based on gamestate and updates gamestate
///
void HanoiGame::pause()
{
    if (currentState == GameState::Playing)
    {
        timer->stop();
        currentState = GameState::Paused;
    }
    else if (currentState == GameState::Paused)
    {
        timer->start(UPDATE_TIME_MS);
        currentState = GameState::Playing;
    }
    notifyObserversStates();
}
///
/// \brief HanoiGame::registerObserver
/// Registers new observer to listen to gamestate and turn number
///
void HanoiGame::registerObserver(Observer* observer)
{
    observers.append(observer);
    notifyObserversStates();
    notifyObserversMoves();
}
///
/// \brief HanoiGame::removeObserver
/// Remove observer from list
///
void HanoiGame::removeObserver(Observer* observer)
{
    observers.removeOne(observer);
}
///
/// \brief HanoiGame::notifyObserversStates
/// Calls the updateState function of every observer with the current gameState
///
void HanoiGame::notifyObserversStates()
{
    for (const auto &observer : observers)
    {
        observer->updateState(currentState);
    }
}
///
/// \brief HanoiGame::notifyObserversMoves
/// Calls the updateMoves function of every observer with the current turn number
///
void HanoiGame::notifyObserversMoves()
{
    for (const auto &observer : observers)
    {
        observer->updateMoves(turn);
    }
}
