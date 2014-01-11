#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T00:42:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AsteriatedGUI
TEMPLATE = app

INCLUDEPATH += . players network textgui

SOURCES += main.cpp\
    window.cpp \
    starbg.cpp \
    paintstruct.cpp \
    messagesource.cpp \
    picbutton.cpp \
    choosecharacter.cpp \
    paintcolor.cpp \
    cardList.cpp \
    card.cpp \
    askdialog.cpp \
    cardandskill.cpp \
    cardbutton.cpp \
    cardattack.cpp \
    framelabel.cpp \
    newdialog.cpp \
    network/agclient.cpp \
    network/agchatclient.cpp \
    players/swordmaster.cpp \
    players/berserker.cpp \
    players/arrowmaid.cpp \
    players/sealmaid.cpp \
    players/darkkiller.cpp \
    players/puremaid.cpp \
    players/angel.cpp \
    players/magicmaid.cpp \
    players/magicsword.cpp \
    players/purespear.cpp \
    players/elementmaster.cpp \
    players/adventurer.cpp \
    players/necromancer.cpp \
    players/arbitrationmaid.cpp \
    players/priestmaid.cpp \
    players/praymaid.cpp \
    players/kamishirasawakeine.cpp \
    players/hakureireimu.cpp \
    players/swordking.cpp \
    players/kazamiyuuka.cpp \
    players/hoshigumayugi.cpp \
    players/uuz.cpp \
    players/redwhite.cpp \
    players/butterfly.cpp \
    characterbutton.cpp

HEADERS  += \
    window.h \
    starbg.h \
    paintstruct.h \
    messagesource.h \
    picbutton.h \
    choosecharacter.h \
    paintcolor.h \
    cardList.h \
    card.h \
    askdialog.h \
    cardandskill.h \
    cardbutton.h \
    cardattack.h \
    framelabel.h \
    newdialog.h \
    network/agclient.h \
    network/agchatclient.h \
    players/swordmaster.h \
    players/berserker.h \
    players/arrowmaid.h \
    players/sealmaid.h \
    players/darkkiller.h \
    players/puremaid.h \
    players/angel.h \
    players/magicmaid.h \
    players/magicsword.h \
    players/purespear.h \
    players/elementmaster.h \
    players/adventurer.h \
    players/necromancer.h \
    players/arbitrationmaid.h \
    players/priestmaid.h \
    players/praymaid.h \
    players/kamishirasawakeine.h \
    players/hakureireimu.h \
    players/swordking.h \
    players/kazamiyuuka.h \
    players/hoshigumayugi.h \
    players/uuz.h \
    players/redwhite.h \
    players/butterfly.h \
    characterbutton.h \
    placeinfo.h

RESOURCES += \
    resource/Image.qrc

OTHER_FILES += \
    InformtionX.txt \
    InformationNew.txt
