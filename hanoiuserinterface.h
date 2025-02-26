#ifndef HANOIUSERINTERFACE_H
#define HANOIUSERINTERFACE_H

#include "dlgsettings.h"
#include "gameState.h"
#include "hanoiGame.h"
#include "observer.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class HanoiUserInterface; }
QT_END_NAMESPACE

///
/// \brief The HanoiUserInterface class
/// Extends QMainWindow for Qt functionality
/// Extends Observer to update the game states
///
class HanoiUserInterface : public QMainWindow, public Observer
{
Q_OBJECT
public:
    explicit HanoiUserInterface(QWidget *parent = nullptr);
    ~HanoiUserInterface();

private:
    Ui::HanoiUserInterface *ui;
    HanoiGame *gameScene;
    QTimer* blinkTimer;
    bool statusbarBlinkOn;

    void updateState(GameState newState);
    void updateMoves(int turns);
    void createNewGame(int amountOfDisks,
                       float turnsPerSecond);

public slots:
    void on_triggeredNew();
    void on_triggeredStart();
    void on_triggeredPause();
    void on_showSettings();
    void on_triggeredHelp();
    void on_triggeredAbout();
    void on_toggleStatusBarBackground();
};

#endif // HANOIUSERINTERFACE_H
