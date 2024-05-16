#-------------------------------------------------
#
# Project created by QtCreator 2024-05-03T19:11:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        startmenu.cpp \
    gamewindow.cpp \
    myobject.cpp \
    gamewindow.cpp \
    main.cpp \
    mycharacter.cpp \
    mymonster.cpp \
    myobject.cpp \
    myproperty.cpp \
    myscene.cpp \
    startmenu.cpp \
    gamewindow.cpp \
    main.cpp \
    myblock.cpp \
    mycharacter.cpp \
    mymonster.cpp \
    myobject.cpp \
    myproperty.cpp \
    startmenu.cpp \
    levelselectmenu.cpp

HEADERS += \
        startmenu.h \
    gamewindow.h \
    myobject.h \
    gamewindow.h \
    mycharacter.h \
    mymonster.h \
    myobject.h \
    myproperty.h \
    myscene.h \
    startmenu.h \
    gamewindow.h \
    myblock.h \
    mycharacter.h \
    mymonster.h \
    myobject.h \
    myproperty.h \
    startmenu.h \
    levelselectmenu.h

FORMS += \
        startmenu.ui \
    gamewindow.ui \
    gamewindow.ui \
    startmenu.ui \
    gamewindow.ui \
    startmenu.ui \
    levelselectmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    resource.qrc \
    resource.qrc

SUBDIRS += \
    demo.pro

DISTFILES += \
    demo.pro.user
