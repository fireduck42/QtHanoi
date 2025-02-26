QT       += core gui quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    disk.cpp \
    dlgsettings.cpp \
    hanoiGame.cpp \
    hanoiuserinterface.cpp \
    main.cpp \
    rod.cpp

HEADERS += \
    animationTurn.h \
    disk.h \
    dlgsettings.h \
    gameState.h \
    hanoiGame.h \
    hanoiuserinterface.h \
    observer.h \
    rod.h

FORMS += \
    dlgsettings.ui \
    hanoiuserinterface.ui

RESOURCES += \
    icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
