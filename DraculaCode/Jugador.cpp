#include "jugador.h"

jugador::jugador()
{
    puntagesPorRonda[0] = 0;
    puntagesPorRonda[1] = 0;
    puntagesPorRonda[2] = 0;
    puntagesPorRonda[3] = 0;
    puntagesPorRonda[4] = 0;
    puntagesPorRonda[5] = 0;
    puntagesPorRonda[6] = 0;

}

QString jugador::getCartaPartner() const
{
    return cartaPartner;
}

void jugador::setCartaPartner(const QString &value)
{
    cartaPartner = value;
}

int jugador::getPuntuacionDeRonda(int x)
{
    return this->puntagesPorRonda[x];
}

