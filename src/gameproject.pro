QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buff.cpp \
    buff_damageup.cpp \
    cell.cpp \
    enemy.cpp \
    enemy_archer.cpp \
    enemy_bat.cpp \
    enemy_damageupper.cpp \
    enemy_dragon.cpp \
    enemy_sphere.cpp \
    enemy_thief.cpp \
    friendly.cpp \
    friendly_archer.cpp \
    friendly_axe.cpp \
    friendly_bomber.cpp \
    friendly_guard.cpp \
    friendly_guardmother.cpp \
    friendly_littleguard.cpp \
    friendly_sphere.cpp \
    friendly_thorn.cpp \
    game.cpp \
    gamemap.cpp \
    gameobject.cpp \
    gameoverdlg.cpp \
    loc.cpp \
    main.cpp \
    mainWindow.cpp \
    player.cpp \
    route.cpp

HEADERS += \
    buff.h \
    buff_damageup.h \
    buff_types.h \
    cell.h \
    enemy.h \
    enemy_archer.h \
    enemy_bat.h \
    enemy_damageupper.h \
    enemy_dragon.h \
    enemy_sphere.h \
    enemy_thief.h \
    enemy_types.h \
    friendly.h \
    friendly_archer.h \
    friendly_axe.h \
    friendly_bomber.h \
    friendly_guard.h \
    friendly_guardmother.h \
    friendly_littleguard.h \
    friendly_sphere.h \
    friendly_thorn.h \
    friendly_types.h \
    game.h \
    gamemap.h \
    gameobject.h \
    gameoverdlg.h \
    loc.h \
    mainWindow.h \
    player.h \
    route.h

FORMS += \
 gameoverdlg.ui \
 mainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
