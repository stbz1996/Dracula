
#include "Boton.h"

/// Aquí se crea un molde de botón que será usado en el programa ///
Boton::Boton(QString name): QGraphicsRectItem()
{
    setRect(0,0,120,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::lightGray);
    setBrush(brush);
    text = new QGraphicsTextItem(name, this);
    text->setPos(23,14);
    setAcceptHoverEvents(true);
}

void Boton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Boton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // cambia fondo cuando entra el mouse
    QBrush b;
    b.setStyle(Qt::SolidPattern);
    b.setColor(Qt::darkGray);
    setBrush(b);
}

void Boton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // cambia fondo cuando sale el mause
    QBrush b;
    b.setStyle(Qt::SolidPattern);
    b.setColor(Qt::lightGray);
    setBrush(b);
}
