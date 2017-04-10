///////////////////////////////////////////
/// Creado por: Erick Quesada Fonseca   ///
/// Fecha: 03/03/2016                   ///
/// Descripción:                        ///
///     Esta es la clase encargada de   ///
///     crear las opciones para poder   ///
///     seleccionar las cartas en el    ///
///     juego y colocarlas el la matriz ///
///////////////////////////////////////////

#ifndef SELECCIONCARTA_H
#define SELECCIONCARTA_H
#include "Carta.h"
#include "Mazo.h"
#include "CamposMatriz.h"
#include <QGraphicsTextItem>
class SeleccionCarta{

public:
    SeleccionCarta();
    Mazo *mazo;
    CamposMatris *camp1;
    CamposMatris *camp2;
};

#endif // SELECCIONCARTA_H
