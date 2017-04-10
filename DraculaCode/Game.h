/////////////////////////////////////////////////////
/// Proyecto Número 1 de Estructuras de Datos     ///
/// Juego Drácula                                 ///
/// Creadores:                                    ///
///     - Steven Alberto Bonilla Zúñiga           ///
///     - Erick Quesada Fonseca                   ///
///     - Jorge Luis González Rodríguez           ///
/////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
/// Creado por: Steven Bonilla Zúñiga                               ///
/// Fecha: 01/03/2016                                               ///
/// Clase modificada por todos los integrantes del grupo.           ///
/// Descripción:                                                    ///
///     Esta es la clase encargada de controlar todos los procesos  ///
///     y adecuarlos a los diferentes caminos que el usuario pueda  ///
///     tomar a lo largo del juego, aquí se controla desde el lugar ///
///     en donde se coloca cada carta hasta el lugar donde termina  ///
///     después de que el usuario la mueve. Absolutamente todos los ///
///     datos estan controlados aquí.                               ///
///////////////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QBrush>
#include <QDebug>
#include <time.h>
#include <QMouseEvent>
#include <QPointF>
#include <QKeyEvent>
#include <QList>
#include "Matriz.h"
#include "boton.h"
#include "Carta.h"
#include "mazo.h"
#include "jugador.h"
#include "Seleccioncarta.h"
#include "CamposMatriz.h"
#include "stdio.h"
#include "stdlib.h"
#include "Stack.h"

///////////////////////////////////////////////////////////////////////////
/// Clase encargada de conectar codigo con interfaz y ejecutar el juego ///
///////////////////////////////////////////////////////////////////////////
class Game: public QGraphicsView{
    Q_OBJECT
    public:
        // constructor
        Game();

        // metodos publicos
        void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
        void mouseMoveEvent(QMouseEvent *event);
        void placeCard(Carta * cardToReplace);
        void pintaPunctuacionesConNumeros();
        void calculoFinalDePunctuaciones();
        void pickUpCard(Carta *card);
        void creaTextoSeleccion();
        void creaEspacioMatris();
        void colocaBotonCalc();
        void colocaSeleccion();
        void verificaciones();
        void colocaBotonSig();
        void botonVerificar();
        void pintaGanador1();
        void pintaGanador2();
        void pantallaFinal();
        void creaAmbiente();
        void cambiaTurno();
        void verifbutton();
        void colocaMazo();
        void botonUndu();
        void verAtras();
        void drawGUI();
        void musica();
        void deco();
        void gato();
        void pantallaInicioBienvenida();


        // metodos que retornan
        int CalculaHorizontal(int sub);
        int CalculaVertical(int sub);
        int mayorPuntaje(QString index, int x, int y, int z);
        QString getWhosTurn();

        // metodos set's
        void setWhosTurn(QString player);

        // estructuras
        Pila<Carta*> stack;
        Carta *CartaPorRonda[15];
        Pila<CamposMatris*> stackMatris;

        // atributos y objetos publicos
        Boton *unduBoton;

        QGraphicsTextItem* whosTurnText;
        QGraphicsScene * scene;
        QPointF originalPos;
        QString rutaCartas = ":/complementos/imag/back2.png";
        matris *matriss;
        Mazo maso;
        Carta *cardToPlace;
        bool controlUndu;
        bool sele;
        bool yaVerifico;
        int cont;
        int jug;
        int index;
        QMediaPlayer * music;

    public slots:
        /// aqui va la respuesta de los boton
        void cambiaEstadoPlayer1();
        void cambiaEstadoPlayer2();
        void creaCartasSeleccion();
        void colocaPunctuaciones();
        void pideReyoReina();
        void iniciaJuego();
        void seguir();
        void pinta();
        void calc();
        void paso();
        void next();
        void undu();
        void salir();
        void IniciaAplicacion();



    private:
        SeleccionCarta *select;
        QList<Carta*> calculos;
        Boton *ver;
        Boton *iniciaAplicacion;
        Carta *lis[3][3];
        jugador *jugador1;
        jugador *jugador2;
        QString whosTurn;
        char *num[10];
        int ronda;
        int puntageJugador1;
        int puntageJugador2;
        bool verificarTime;



};

#endif // GAME_H
