/////////////////////////////////////////
/// Creado por: Steven Bonilla Zúñiga ///
/// fecha: 01/03/2016                 ///
/// Descripción:                      ///
///     Esta es la clase encargada de ///
///     crear las instancias de las   ///
///     cartas que se van a usar en   ///
///     el juego.                     ///
/////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
class Carta:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        // constructor
        Carta(QString ruCartas, QString rutaNaipe, QChar color, QChar simbolo, int valor);
        Carta(QString x);

        // metodos
        void cambiaImagen();
        void cambiaAtras();
        void goToPosInicialYa();
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        // metodos gets
        bool getIsPlaced();
        bool getEsMovible();
        int getCordx();
        int getCordy();
        int getValor();
        QChar getColor();
        QChar getSimbolo();
        QString gatRuta();

        // metodos sets
        void setIsPlaced(bool x);
        void setEsMovible(bool estado);
        void setPosInicialYa(int x, int y);

        // atributos publicos
        QString owner;

    private:
        /// atributos ///
        int posInicialx;
        int posInicialy;
        int valor;
        bool esMovible;
        bool isPlaced;
        QString rutaAtras;
        QString rutaFrente;
        QChar simbolo;
        QChar color;
};
#endif // PLAYER_H
