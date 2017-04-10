////////////////////////////////////////////
/// Creado por: Jorge González Rodríguez ///
/// Fecha: 02/03/2016                    ///
/// Descripción:                         ///
///     Esta es la clase encargada de    ///
///     crear los dos jugadores que van  ///
///     a interactual en el juego        ///
////////////////////////////////////////////

#ifndef JUGADOR_H
#define JUGADOR_H
#include <QString>

class jugador{
    public:
        jugador();
        QString getCartaPartner() const;
        void setCartaPartner(const QString &value);
        int puntagesPorRonda[7];
        int getPuntuacionDeRonda(int x);


    private:
        QString cartaPartner;

};


#endif // JUGADOR_H
