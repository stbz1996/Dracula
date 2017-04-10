#include "matriz.h"
#include "Game.h"
#include <QGraphicsItem>
extern Game *game;

matris::matris(){
    construyeEspacios();
    defineEstadosDeLosCuadros();
}

void matris::defineEstadosDeLosCuadros()
{
    // primera fila
     listaMatris[1]->setEstaPermitido(false);
     listaMatris[2]->setEstaPermitido(true);
     listaMatris[3]->setEstaPermitido(false);

    // segunda fila
     listaMatris[4]->setEstaPermitido(true);
     listaMatris[6]->setEstaPermitido(true);

    // tercera fila
     listaMatris[7]->setEstaPermitido(false);
     listaMatris[8]->setEstaPermitido(true);
     listaMatris[9]->setEstaPermitido(false);
}



void matris::cambiaColorDeCuadro(int lugar)
{
    listaMatris[lugar]->setPixmap(QPixmap(":/complementos/imag/blanco.png"));
}

void matris::construyeEspacios()
{
    QString blanco = ":/complementos/imag/blanco.png";
    QString rojo = ":/complementos/imag/rojo-1.png";
    // imagen del mazo
    listaMatris.append(new CamposMatris(":/complementos/imag/mazo.png"));

    // imágenes de los espacios de la matriz
    listaMatris.append(new CamposMatris(rojo));
    listaMatris.append(new CamposMatris(blanco));
    listaMatris.append(new CamposMatris(rojo));
    listaMatris.append(new CamposMatris(blanco));
    listaMatris.append(new CamposMatris(blanco));
    listaMatris.append(new CamposMatris(blanco));
    listaMatris.append(new CamposMatris(rojo));
    listaMatris.append(new CamposMatris(blanco));
    listaMatris.append(new CamposMatris(rojo));

    listaMatris[1]->setPos(470,40);  listaMatris[2]->setPos(610,40);
    listaMatris[3]->setPos(750,40);  listaMatris[4]->setPos(470,210);
    listaMatris[5]->setPos(610,210); listaMatris[6]->setPos(750,210);
    listaMatris[7]->setPos(470,380); listaMatris[8]->setPos(610,380);
    listaMatris[9]->setPos(750,380); listaMatris[0]->setPos(595,555);

}
