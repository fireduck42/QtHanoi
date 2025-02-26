#include "dlgsettings.h"
#include "ui_dlgsettings.h"

///
/// \brief DlgSettings::DlgSettings
/// \param parent: the parent widget
/// \param diskAmount: amount of start disks
/// \param speed: movement per second
///
DlgSettings::DlgSettings(QWidget *parent,
                         int diskAmount,
                         float speed)
    : QDialog(parent)
    , ui(new Ui::DlgSettings)
    , diskAmount(diskAmount)
    , animationSpeed(speed)
{
    ui->setupUi(this);
    ui->lblDisks->setText(QString::number(this->diskAmount));
    ui->lblAnimation->setText(QString::number(animationSpeed));

    // connect the ui element with a slot method for the choosen signal
    connect(ui->btnIncreaseDisks,           // more disks
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_increaseDisks()));
    connect(ui->btnDecreaseDisks,           // less disks
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_decreaseDisks()));
    connect(ui->btnIncreaseAnimation,       // more speed
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_increaseSpeed()));
    connect(ui->btnDecreaseAnimation,       // less speed
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_decreaseSpeed()));
}
///
/// \brief DlgSettings::~DlgSettings
/// Deallocate ui from memory
///
DlgSettings::~DlgSettings()
{
    delete ui;
}
///
/// \brief DlgSettings::getDiskAmount
/// \return the current amount of disks
///
int DlgSettings::getDiskAmount()
{
    return diskAmount;
}
///
/// \brief DlgSettings::getAnimationSpeed
/// \return the current speed per seconds
///
float DlgSettings::getAnimationSpeed()
{
    return animationSpeed;
}
///
/// \brief DlgSettings::on_increaseDisks
/// Increase the disk amount by one to a maximum of 9
///
void DlgSettings::on_increaseDisks()
{
    if (diskAmount < 9)
    {
        diskAmount++;
    }
    // update the label
    ui->lblDisks->setText(QString::number(diskAmount));
}
///
/// \brief DlgSettings::on_decreaseDisks
/// Decrease the disk amount by one to a minimum of 1
///
void DlgSettings::on_decreaseDisks()
{
    if (diskAmount > 1)
    {
        diskAmount--;
    }
    // update the label
    ui->lblDisks->setText(QString::number(diskAmount));
}
///
/// \brief DlgSettings::on_increaseSpeed
/// Increase speed by 1.0f or 0.5f for odd steps to a maximum of 5.0f
///
void DlgSettings::on_increaseSpeed()
{
    if (animationSpeed == 0.5f)
    {
        animationSpeed += 0.5f;
    }
    else if(animationSpeed < 5.0f)
    {
        animationSpeed += 1.0f;
    }
    // update the label
    ui->lblAnimation->setText(QString::number(animationSpeed));
}
///
/// \brief DlgSettings::on_decreaseSpeed
/// Decrease speed by 1.0f or 0.5f for odd steps to a minimum of 1.0f
///
void DlgSettings::on_decreaseSpeed()
{
    if (animationSpeed == 1.0f)
    {
        animationSpeed -= 0.5f;
    }
    else if(animationSpeed > 0.5f)
    {
        animationSpeed -= 1.0f;
    }
    // update the label
    ui->lblAnimation->setText(QString::number(animationSpeed));
}
