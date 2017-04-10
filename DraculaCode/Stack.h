/////////////////////////////////////////////
/// Creado por: Jorge González Rodríguez  ///
/// Fecha: 02/03/2016                     ///
/// Descripción:                          ///
///     Esta es la clase encargada de     ///
///     crear el Stack o la pila que será ///
///     usada para los mazos del juego    ///
/////////////////////////////////////////////

#ifndef PILA_H
#define PILA_H
#include "Node.h"
#include "Carta.h"
#include <iostream>

using namespace std;
template <typename E>

class Pila{
private:
    Nodo<E>*top;
    int size;

public:
    void Stack(){
        top = NULL;
        size = 0;}

    void clear(){
        while(top != NULL){
            Nodo<E>*temp = top;
            top = top ->next;
            delete temp;
        }
        size = 0;
    }


    void push (E pElement){
        top = new Nodo<E> (pElement,top);
        size++;
    }


    E pop(){
        E deleteElement = top -> element;
        Nodo<E>*temp = top;
        top = top->next;
        delete temp;
        size--;
        return deleteElement;
    }

    E topValue(){
        return top->element;
    }

    int length(){
        return size;
    }

};

#endif // PILA_H
