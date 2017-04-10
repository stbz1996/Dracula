#include "Mazo.h"
#include <time.h>

Mazo::Mazo()
{

    p = ":/complementos/imag/back2.png";

    creaStringCartas();
    creaMazoRandom();
}

// crea al mazo
void Mazo::creaMazoRandom()
{
    // selección para el random
    for(int i = 0; i < 54; i++){numm.append(i);}

    // Cartas para jugar
    srand(time(NULL));
    int cont = 54;

    //crea mazos random
    for (int i = 0; i < 54; i++){
        int random = rand() % cont;

        cartasInicio[i] = new Carta(p, n[numm[random]],
                c[numm[random]], s[numm[random]], v[numm[random]]);

        masso[i] = new Carta(p, n[numm[random]],
                c[numm[random]], s[numm[random]], v[numm[random]]);


        // borra el número que uso
        numm.removeAt(random);
        cont --;
    }
}

// crea los valores que se van a usar en las cartas
void Mazo::creaStringCartas()
{
    int x; int y; int z; int w; int va;
    x = 0; y = 1; va = 23;
    n[x] = ":/jockers/Baraja/jocker/joker3.png"; c[x] = 'r'; s[x] = 'd'; v[x] = va;
    n[y] = ":/jockers/Baraja/jocker/negrojocker.jpg"; c[y] = 'n'; s[y] = 'b'; v[y] = va;

    x = 2; y = 3; z = 4; w = 5; va = 7;
    n[x] = ":/corazones/Baraja/corazones/7-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/7-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/7-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/7-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 6; y = 7; z = 8; w = 9; va = 3;
    n[x] = ":/corazones/Baraja/corazones/3-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/3-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/3-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/3-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 10; y = 11; z = 12; w = 13; va = 1;
    n[x] = ":/corazones/Baraja/corazones/as-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/as-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/as-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/as-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 14; y = 15; z = 16; w = 17; va = 10;
    n[x] = ":/corazones/Baraja/corazones/10-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/10-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/10-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/10-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 18; y = 19; z = 20; w = 21; va = 0;
    n[x] = ":/corazones/Baraja/corazones/j-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/j-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/j-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/j-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 22; y = 23; z = 24; w = 25; va = 4;
    n[x] = ":/corazones/Baraja/corazones/4-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/4-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/4-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/4-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 26; y = 27; z = 28; w = 29; va = 9;
    n[x] = ":/corazones/Baraja/corazones/9-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/9-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/9-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/9-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 30; y = 31; z = 32; w = 33; va = 22;
    n[x] = ":/corazones/Baraja/corazones/k-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/k-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/k-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/k-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 34; y = 35; z = 36; w = 37; va = 2;
    n[x] = ":/corazones/Baraja/corazones/2-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/2-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/2-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/2-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 38; y = 39; z = 40; w = 41; va = 6;
    n[x] = ":/corazones/Baraja/corazones/6-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/6-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/6-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/6-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 42; y = 43; z = 44; w = 45; va = 21;
    n[x] = ":/corazones/Baraja/corazones/q-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/q-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/q-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/q-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 46; y = 47; z = 48; w = 49; va = 8;
    n[x] = ":/corazones/Baraja/corazones/8-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/8-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/8-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/8-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

    x = 50; y = 51; z = 52; w = 53; va = 5;
    n[x] = ":/corazones/Baraja/corazones/5-corazones-rojo.png"; c[x] = 'r'; s[x] = 'c'; v[x] = va;
    n[y] = ":/diamantes/Baraja/diamante/5-diamante-rojo.png";   c[y] = 'r'; s[y] = 'd'; v[y] = va;
    n[z] = ":/treboles/Baraja/trebol/5-trebol-negro.png";       c[z] = 'n'; s[z] = 't'; v[z] = va;
    n[w] = ":/bastos/Baraja/espada/5-espada-negro.png";         c[w] = 'n'; s[w] = 'b'; v[w] = va;

}

// baraja el mazo
void Mazo::baraja()
{
    for(int i = 0; i < 54; i++){numm.append(i);}

    // cartas para jugar
    srand(time(NULL));
    int cont = 54;

    //crea mazos random
    for (int i = 0; i < 54; i++){
        int random = rand() % cont;

        cartasInicio[i] = new Carta(p, n[numm[random]],
                c[numm[random]], s[numm[random]], v[numm[random]]);

        // borra el número que uso
        numm.removeAt(random);
        cont --;
    }
}


