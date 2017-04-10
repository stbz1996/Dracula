/////////////////////////////////////////
/// Creado por: Erick Quesada Fonseca ///
/// Fecha: 02/03/2016                 ///
/// Descripción:                      ///
///     Esta es la clase encargada de ///
///     crear los espacios donde se   ///
///     van a situar las cartas en la ///
///     matriz del juego              ///
/////////////////////////////////////////

#ifndef CAMPOSMATRIS_H
#define CAMPOSMATRIS_H
#include <QGraphicsPixmapItem>
#include <QObject>
class CamposMatris: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        CamposMatris(QString imag);

        // get's
        bool getHayEspacio();
        bool getEstaPermitido();
        int getX();
        int getY();

        // set's
        void setHayEspacio(bool value);
        void setEstaPermitido(bool value);
        void setAtras(QString x);

    private:
        bool hayEspacio;
        bool estaPermitido;
        QString atras;
};
#endif // CAMPOSMATRIS_H
