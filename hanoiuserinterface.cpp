#include "hanoiuserinterface.h"
#include "ui_hanoiuserinterface.h"

///
/// \brief HanoiUserInterface::HanoiUserInterface
/// \param parent: the parent widget
///
HanoiUserInterface::HanoiUserInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HanoiUserInterface)
    , statusbarBlinkOn(false)
{
    ui->setupUi(this);
    // QTimer to implement a blinking bar
    blinkTimer = new QTimer(this);

    // initialize a new game of towers of hanoi
    createNewGame(5, 1);

    // get the current disk amount of the game scene
    QString diskAmount = QString::number(gameScene->getCurrentDiskAmount());
    // update the label
    ui->lblDiskAmount->setText(diskAmount);

    // set the default window icon to a custom png
    this->setWindowIcon(QIcon(":/icons/favicon.png"));

    // connect the ui element with a slot method for the choosen signal
    connect(ui->btnSettings,            // open settings
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_showSettings()));
    connect(ui->btnExit,                // close the main window
            SIGNAL(clicked(bool)),
            this,
            SLOT(close()));
    connect(ui->actionExit,             // close the main window
            SIGNAL(triggered(bool)),
            this,
            SLOT(close()));
    connect(ui->actionAbout,            // open about dialog
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_triggeredAbout()));
    connect(ui->actionHelp,             // open about dialog
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_triggeredHelp()));
    connect(ui->btnStart,               // starts the game
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_triggeredStart()));
    connect(ui->actionStart,            // starts the game
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_triggeredStart()));
    connect(ui->actionPause,            // pause the game
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_triggeredPause()));
    connect(ui->btnPause,               // pause the game
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_triggeredPause()));
    connect(ui->btnNew,                 // reinit the game
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_triggeredNew()));
    connect(ui->actionNew,              // reinit the game
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_triggeredNew()));
    connect(this->blinkTimer,           // connect blink timer with slot method
            SIGNAL(timeout()),
            this,
            SLOT(on_toggleStatusBarBackground()));
}
///
/// \brief HanoiUserInterface::~HanoiUserInterface
/// Deallocate the memory
///
HanoiUserInterface::~HanoiUserInterface()
{
    delete ui;
    delete gameScene;
    delete blinkTimer;
}
///
/// \brief HanoiUserInterface::updateState: Updates the game state in status bar and the button visibility
/// \param newState: the next game state
///
void HanoiUserInterface::updateState(GameState newState)
{
    // handle visibility of the buttons and update statusbar
    switch (newState)
    {
        case GameState::Ready:
        {
            ui->btnPause->setText("Pause");
            ui->actionPause->setText("Pause");
            ui->btnPause->setEnabled(false);
            ui->actionPause->setEnabled(false);
            ui->btnNew->setEnabled(false);
            ui->actionNew->setEnabled(false);
            ui->btnStart->setEnabled(true);
            ui->actionStart->setEnabled(true);
            ui->statusbar->showMessage("Spielstatus: Bereit");
            break;
        }
        case GameState::Playing:
        {
            ui->btnPause->setText("Pause");
            ui->actionPause->setText("Pause");
            ui->btnPause->setEnabled(true);
            ui->actionPause->setEnabled(true);
            ui->btnNew->setEnabled(true);
            ui->actionNew->setEnabled(true);
            ui->btnStart->setEnabled(false);
            ui->actionStart->setEnabled(false);
            ui->statusbar->showMessage("Spielstatus: Wird ausgeführt");
            break;
        }
        case GameState::Paused:
        {
            ui->btnPause->setText("Fortsetzen");
            ui->actionPause->setText("Fortsetzen");
            blinkTimer->start(500);
            ui->statusbar->showMessage("Spielstatus: Pausiert");
            break;
        }
        case GameState::Finished:
        {
            ui->btnPause->setEnabled(false);
            ui->actionPause->setEnabled(false);
            ui->statusbar->showMessage("Spielstatus: Abgeschlossen");
            break;
        }
        default:
        {
            break;
        }
    }

    // activate blinking in the status bar
    if (newState != GameState::Paused && blinkTimer->isActive())
    {
        blinkTimer->stop();
        if(statusbarBlinkOn)
        {
            on_toggleStatusBarBackground();
        }
    }
    else if (newState == GameState::Paused && !blinkTimer->isActive())
    {
        blinkTimer->start(500);
    }
}
///
/// \brief HanoiUserInterface::on_toggleStatusBarBackground: Toggles the background color of the status bar
///
void HanoiUserInterface::on_toggleStatusBarBackground()
{
    QString currentStyle = ui->statusbar->styleSheet();

    // stylesheet injection
    QString blinkOff = "background-color: #FFF;";
    QString blinkOn = "background-color: #DFF704;";

    // change the color of the status bar after the count down of the timer
    if (statusbarBlinkOn)
    {
        currentStyle.replace(blinkOn, blinkOff);
    }
    else
    {
        currentStyle.replace(blinkOff, blinkOn);
    }
    statusbarBlinkOn = !statusbarBlinkOn;

    // change the stylesheet of the status bar to selected one
    ui->statusbar->setStyleSheet(currentStyle);
}
///
/// \brief HanoiUserInterface::updateMoves: updates the move details in the top bar
/// \param turns: the new turn amount to calculate the progress
///
void HanoiUserInterface::updateMoves(int turns)
{
    // create details string
    QString movesDetails = QString::number(turns)
        + " / " + QString::number(pow(2, gameScene->getCurrentDiskAmount())-1);

    // update the label
    ui->lblMoveAmount->setText(movesDetails);
}
///
/// \brief HanoiUserInterface::createNewGame: Reinitializes the game
/// \param amountOfDisks: number of disks for the new game
/// \param turnsPerSecond: turns per second for the new game
///
void HanoiUserInterface::createNewGame(int amountOfDisks, float turnsPerSecond)
{
    // new game scene
    gameScene = new HanoiGame(amountOfDisks, turnsPerSecond);
    // register observer
    gameScene->registerObserver(this);
    // set game scene
    ui->graphicsView->setScene(gameScene);
}
///
/// \brief HanoiUserInterface::on_triggeredNew: slot method to react to button new pressed
///
void HanoiUserInterface::on_triggeredNew()
{
    // gets the data from game scene
    int amountOfDisks = gameScene->getCurrentDiskAmount();
    float turnsPerSecond = gameScene->getTurnsPerSecond();
    // removes old game scene
    delete gameScene;
    // reinits new game scene
    createNewGame(amountOfDisks, turnsPerSecond);
}
///
/// \brief HanoiUserInterface::on_triggeredStart: slot method to react to button start pressed
///
void HanoiUserInterface::on_triggeredStart()
{
    // trigger game scene to start
    gameScene->start();
}
///
/// \brief HanoiUserInterface::on_triggeredPause: slot method to react to button pause pressed
///
void HanoiUserInterface::on_triggeredPause()
{
    // trigger game scene to pause
    gameScene->pause();
}
///
/// \brief HanoiUserInterface::on_showSettings: opens a dialog for the game settings
///
void HanoiUserInterface::on_showSettings()
{
    // create dialog instance
    DlgSettings dialog(this,
                       gameScene->getCurrentDiskAmount(),
                       gameScene->getTurnsPerSecond());
    // if dialog accepted()
    if (dialog.exec())
    {
        // remove game scene
        delete gameScene;
        // load game scene with new data
        createNewGame(dialog.getDiskAmount(), dialog.getAnimationSpeed());
        // update the label of disk amount
        ui->lblDiskAmount->setText(QString::number(gameScene->getCurrentDiskAmount()));
    }
}
///
/// \brief HanoiUserInterface::on_triggeredHelp: opens a dialog for key combinations as help
///
void HanoiUserInterface::on_triggeredHelp()
{
    QString keyCombinations = "<br/><br/>" \
        "<p><strong>Strg + N</strong> - Neues Spiel/Spiel zurücksetzen</p>" \
        "<p><strong>Strg + P</strong> - Spiel pausieren/fortsetzen</p>" \
        "<p><strong>Strg + S</strong> - Spiel starten/Automatisches Lösungsverfahren triggern</p>" \
        "<p><strong>Strg + H</strong> - Übersicht der Tastenkombinationen</p>" \
        "<p><strong>Strg + U</strong> - Informationen über das Spiel</p>" \
        "<p><strong>Strg + B</strong> - Programm beenden</p>" \
        "<br/><br/>";

    // default message box
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Hilfe");
    // rich text for html attributes
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(keyCombinations);
    // add ok button
    msgBox.addButton(QMessageBox::Ok);
    msgBox.exec();
}
///
/// \brief HanoiUserInterface::on_triggeredAbout: opens a dialog with information about how to play the game
///
void HanoiUserInterface::on_triggeredAbout()
{
    QString info = "<br/><br/><p><strong>Die Türme von Hanoi</strong> zählen zu den klassischen " \
        "mathematischen Puzzle-Spielen und basieren auf einem Set an Scheiben " \
        "und drei Stäben. Hierbei werden die Scheiben auf den Stäben gestapelt, " \
        "wobei sich die größte Scheibe immer an der untersten Stelle befindet.</p>" \
        "<h3>Ziel des Spiels</h3>" \
        "<p>Das Ziel des Spiels besteht darin, die Scheiben " \
        "vom linken Stab aus auf den rechten Stab zu verschieben, während man sich an " \
        "die drei Hauptspielregeln hält, welche das Spiel einschränken.</p>" \
        "<h3>Spielregeln</h3>" \
        "<p><strong>1.</strong> Alle Scheiben müssen vom linken Stab auf den rechten Stab verschoben werden." \
        "<br/><strong>2.</strong> Es darf immer nur eine Scheibe gleichzeitig bewegt werden." \
        "<br/><strong>3.</strong> Eine größere Scheibe darf niemals auf einer kleineren Scheibe platziert werden.</p>" \
        "<h3>Spielanleitung</h3>" \
        "<p>Zu Beginn des Spiels sind alle Scheiben auf dem linken Stab in aufsteigender Reihenfolge " \
        "gestapelt, wobei die größte Scheibe unten und die Kleinste oben liegt. Der " \
        "Spieler muss nun die Scheiben vom linken Ausgangsstab auf den Zielstab " \
        "verschieben. " \
        "<br/><br/>Der Prozess des Umstapelns erfordert das systematische Verschieben der Scheiben " \
        "zwischen den Stäben. Dabei muss der Spieler den mittleren Hilfsstab verwenden, " \
        "um die Scheiben zu bewegen, ohne die Regeln zu brechen.<br/><br/>Die Herausforderung des " \
        "Spiels besteht darin, die Scheiben mit der geringsten Anzahl von Zügen zu verschieben. " \
        "<br/><br/>Das Spiel fordert strategisches Denken und Planung, da es verschiedene Lösungen für das " \
        "Rätsel gibt, wobei jede Bewegung sorgfältig überlegt sein muss, um das Ziel zu erreichen. " \
        "<br/><br/><strong>Die Türme von Hanoi</strong> sind nicht nur ein unterhaltsames Spiel, sondern auch ein " \
        "faszinierendes mathematisches Problem, das auf den Prinzipien von Rekursion und " \
        "verschiedener Muster basiert. Hierbei gibt es auch Spielvarianten mit unterschiedlicher Anzahl von Scheiben, " \
        "wodurch die Schwierigkeit erhöht wird.<br/><br/>Das Spiel ist eine großartige Möglichkeit, " \
        "logisches Denken und Problemlösungsfähigkeiten zu entwickeln und kann gleichzeitig " \
        "eine fesselnde Herausforderung für Spieler jeglicher Altersgruppen sein.</p><br/><br/>";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Über Türme von Hanoi");
    // rich text for html attributes
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(info);
    // add ok button
    msgBox.addButton(QMessageBox::Ok);
    msgBox.exec();
}
