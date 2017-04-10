#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T11:51:47
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proyecto
TEMPLATE = app


SOURCES += main.cpp\
        Boton.cpp \
    CamposMatriz.cpp \
    Carta.cpp \
    Game.cpp \
    Jugador.cpp \
    Matriz.cpp \
    Mazo.cpp \
    SeleccionCarta.cpp

HEADERS  += Boton.h \
    Carta.h \
    Game.h \
    Jugador.h \
    Matriz.h \
    Mazo.h \
    SeleccionCarta.h \
    CamposMatriz.h \
    Stack.h \
    Node.h

RESOURCES += \
    archivos.qrc
