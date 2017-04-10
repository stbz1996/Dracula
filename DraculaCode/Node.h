////////////////////////////////////////////
/// Creado por: Jorge González Rodríguez ///
/// Fecha: 03/03/2016                    ///
/// Descripción:                         ///
///     Esta es la clase encargada de    ///
///     crear nodos como punteros que    ///
///     van a ser usados en el Stack     ///
///     del juego                        ///
////////////////////////////////////////////

#ifndef NODO_H
#define NODO_H
#include "Carta.h"
#include <iostream>
#include <QString>


using namespace std;
template<typename E>

class Nodo{
public:
    E element;
    Nodo<E>*next;

    Nodo(E pElement, Nodo<E>*pNext = NULL){
        element = pElement;
        next = pNext;
    }
    Nodo(Nodo<E>*pNext = NULL){
        next = pNext;
    }
};


#endif // NODO_H
