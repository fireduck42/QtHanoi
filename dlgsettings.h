#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DlgSettings; }
QT_END_NAMESPACE

///
/// \brief The DlgSettings class
/// Extends QMainWindow for Qt functionality
///
class DlgSettings : public QDialog
{
Q_OBJECT
public:
    explicit DlgSettings(QWidget *parent,
                         int diskAmount,
                         float speed);
    ~DlgSettings();
    int getDiskAmount();
    float getAnimationSpeed();

private:
    Ui::DlgSettings *ui;
    int diskAmount;
    float animationSpeed;

public slots:
    void on_increaseDisks();
    void on_decreaseDisks();
    void on_increaseSpeed();
    void on_decreaseSpeed();
};

#endif // DLGSETTINGS_H
