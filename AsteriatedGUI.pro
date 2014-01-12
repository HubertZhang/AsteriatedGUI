#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T00:42:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AsteriatedGUI
TEMPLATE = app

INCLUDEPATH += . players network dialog background card button

SOURCES += main.cpp\
    window.cpp \
    background/starbg.cpp \
    paintstruct.cpp \
    messagesource.cpp \
    button/picbutton.cpp \
    dialog/choosecharacter.cpp \
    background/paintcolor.cpp \
    card/cardList.cpp \
    card/card.cpp \
    dialog/askdialog.cpp \
    cardandskill.cpp \
    button/cardbutton.cpp \
    card/cardattack.cpp \
    dialog/framelabel.cpp \
    dialog/newdialog.cpp \
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
    background/winanime.cpp

HEADERS  += \
    window.h \
    background/starbg.h \
    paintstruct.h \
    messagesource.h \
    button/picbutton.h \
    dialog/choosecharacter.h \
    background/paintcolor.h \
    card/cardList.h \
    card/card.h \
    dialog/askdialog.h \
    cardandskill.h \
    button/cardbutton.h \
    card/cardattack.h \
    dialog/framelabel.h \
    dialog/newdialog.h \
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
    background/winanime.h

RESOURCES += \
    resource/Image.qrc

OTHER_FILES += \
    InformtionX.txt \
    InformationNew.txt
