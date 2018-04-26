#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T17:00:23
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FullMetalPlanet
TEMPLATE = app

QMAKE_LFLAGS += -Wl,-rpath,"'$$ORIGIN'"

include(Vue/vue.pri)
include(Moteur/moteur.pri)
include(Controleur/controleur.pri)
include(Vue/Modelisation3D/modelisation3d.pri)

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS  += \ 
    mainwindow.h \
    defineclass.h

RESOURCES += ressources.qrc

unix:!macx: LIBS += -L$$PWD/'lib/glew-2.0.0 unix/glew-2.0.0 unix/lib/' -lGLEW
macx:       LIBS += -L$$PWD/'lib/glew-2.0.0 unix/glew-2.0.0 unix/lib/' -lGLEW.2.0.0

INCLUDEPATH += $$PWD/'lib/glew-2.0.0 unix/glew-2.0.0 unix/include'
DEPENDPATH += $$PWD/'lib/glew-2.0.0 unix/glew-2.0.0 unix/include'
