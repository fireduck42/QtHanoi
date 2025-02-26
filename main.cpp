#include <QApplication>
#include "hanoiuserinterface.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HanoiUserInterface window;
    window.showMaximized();

    return app.exec();
}

