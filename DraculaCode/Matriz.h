//////////////////////////////////////////
/// Creado por: Steven Bonilla Zúñiga  ///
/// Fecha: 02/03/2016                  ///
/// Descripción:                       ///
///     Esta es la clase encargada de  ///
///     crear la matriz de datos, en   ///
///     donde van a entrar situadas las///
///     cartas en el juego             ///
//////////////////////////////////////////

#ifndef MATRIS_H
#define MATRIS_H


#include <QList>
#include "CamposMatriz.h"



class matris{
    public:
        // constructor
        matris();

        // metodos
        void cambiaColorDeCuadro(int lugar);
        void construyeEspacios();
        void defineEstadosDeLosCuadros();

        // atributos
        QList<CamposMatris*> listaMatris;

};

#endif // MATRIS_H
