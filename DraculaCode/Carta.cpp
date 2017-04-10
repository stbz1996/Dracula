
#include "Game.h"
extern Game *game;

/// constructor y su sobrecarga ///
Carta::Carta(QString ruCartas, QString rutaNaipe, QChar color,
             QChar simbolo, int valor)
{
    /// llena atributos ///
    this->esMovible = true;
    this->valor = valor;
    this->simbolo = simbolo ;
    this->color = color;
    this->rutaFrente = rutaNaipe;
    this->rutaAtras = ruCartas;
    setPixmap(QPixmap(rutaAtras));
}

/// crea una carta inmovible ///
Carta::Carta(QString x)
{
    setPixmap(QPixmap(x));
}

/// control de imagenes de la carta ///
void Carta::cambiaImagen() {setPixmap(QPixmap(rutaFrente));}

void Carta::cambiaAtras()
{
    setPixmap(QPixmap(this->rutaAtras));
}


/// control al toque del mouse ///
void Carta::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(getIsPlaced() == false) {game->pickUpCard(this);}
    else {game->placeCard(this);}
}

/// métodos set's ///
void Carta::setIsPlaced(bool x) {isPlaced = x;}

void Carta::setEsMovible(bool estado) {esMovible = estado;}

/// métodos gets ///
bool Carta::getIsPlaced()   {return isPlaced;}
bool Carta::getEsMovible()  {return esMovible;}
int Carta::getCordx()       {return this->x();}
int Carta::getCordy()       {return this->y();}
int Carta::getValor()       {return this->valor;}
QChar Carta::getColor()     {return this->color;}
QChar Carta::getSimbolo()   {return this->simbolo;}


// envía la carta a la POS inicial //
void Carta::goToPosInicialYa(){
    this->setPos(this->posInicialx, this->posInicialy);
}


// guarda la POS inicial para usarla en el undo //
void Carta::setPosInicialYa(int x, int y){
    posInicialx = x;
    posInicialy = y;
}

