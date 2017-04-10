//////////////////////////////////////////
/// Creado por: Steven Bonilla Zúñiga  ///
/// fecha: 01/03/2016                  ///
/// Descripción:                       ///
///     Esta es la clase encargada de  ///
///     crear dos mazos con los cuales ///
///     se van a seleccionar las cartas///
///     para repartirlas y para        ///
///     seleccionarlas                 ///
//////////////////////////////////////////

#ifndef MAZO_H
#define MAZO_H
#include "Carta.h"
#include <QList>
#include "Stack.h"
class Mazo{
    public:
        Mazo();
        void creaMazoRandom();
        void creaStringCartas();
        void baraja();

        // formacion de cartas, maquina de cartas.
        QString n[54];
        char c[54];
        char s[54];
        int v[54];
        QString p;

        // mazo en ordenado
        QList<int> numm;

        // mazo para dejar TODO el deck, RANDOM
        Carta *cartas[54];

        // mazo para seleccion de inicio
        Carta *cartasInicio[54];

        // mazo para sacar en colocamazo
        Carta *masso[54];
};

#endif // MAZO_H
