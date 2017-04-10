//////////////////////////////////////////
/// Creado por: Erick Quesada Fonseca  ///
/// fecha: 01/03/2016                  ///
/// Descripción:                       ///
///     Crea un molde para los botones ///
///     con las dimensiones que se     ///
///     van a usar como estandar en    ///
///     el juego.                      ///
//////////////////////////////////////////

#ifndef BOTON_H
#define BOTON_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
class Boton: public QObject, public QGraphicsRectItem{
    Q_OBJECT
    public:
        Boton(QString name);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    signals:
        void clicked();

    private:
        QGraphicsTextItem *text;

};

#endif // BOTON_H
