#include "CamposMatriz.h"

/// constructor
CamposMatris::CamposMatris(QString imag) {
    setPixmap(QPixmap(imag));
    this->hayEspacio = true;
}

/// Métodos get and set
void CamposMatris::setHayEspacio(bool value) {hayEspacio = value;}
void CamposMatris::setEstaPermitido(bool value) {estaPermitido = value;}
void CamposMatris::setAtras(QString x)
{
    setPixmap(QPixmap(x));
}
bool CamposMatris::getHayEspacio() {return hayEspacio;}
bool CamposMatris::getEstaPermitido() {return estaPermitido;}
int CamposMatris::getX()
{
    return this->pos().x();
}
int CamposMatris::getY()
{
    return this->pos().y();
}

