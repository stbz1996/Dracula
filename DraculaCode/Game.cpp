#include "Game.h"
        ///////////////////////////////////////////////////////////////////////////////
        /// Sección donde se inicia el primer turno del juego, el ambiente y las    ///
        /// demás cosas que se van a necesitar para ejecutar el juego correctamente ///
        ///////////////////////////////////////////////////////////////////////////////

        // constructor para inicializar valores necesarios en la ejecución
Game::Game(){
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/songs/piano cancion hermosa final fantasy.mp3"));
    this->musica();
    this->creaAmbiente();

    // banderas
    sele = true;
    index = 0;
    ronda = 1;
    cont = 0;
    yaVerifico = false;
    cardToPlace = NULL;
    puntageJugador1 = 0;
    puntageJugador2 = 0;
    verificarTime = true;

    // instancias
    jugador1 = new jugador();
    jugador2 = new jugador();

    this->pantallaInicioBienvenida();
    show();}


        // inicia la aplicación
void Game::pantallaInicioBienvenida(){
    /// botón para continuar con el inicio de la APP
    iniciaAplicacion = new Boton(QString("Vamos a Jugar"));
    iniciaAplicacion->setPos(600, 500);
    connect(iniciaAplicacion, SIGNAL(clicked()), this, SLOT(IniciaAplicacion()));
    scene->addItem(iniciaAplicacion);

    Carta *logo = new Carta(":/complementos/imag/logo.png");
    logo->setPos(275, 50);
    scene->addItem(logo);

    Carta *vamp = new Carta(":/deco/imag/Tribales-vampiro-2.png");
    vamp->setPos(260,230);
    scene->addItem(vamp);

    Carta *vamp2 = new Carta(":/deco/imag/Tribales-vampiro-2.png");
    vamp2->setPos(900,230);
    scene->addItem(vamp2);
}

        // inicia el juego
void Game::IniciaAplicacion(){
    scene->clear();
    this->creaTextoSeleccion();
    this->colocaSeleccion();
}

        // establece las dimensiones de la pantalla y el ambiente donde se va a
        // desarrollar el juego
void Game::creaAmbiente(){
    scene = new QGraphicsScene(); /// crea ambiente
    scene->setSceneRect(0,0,1350,700);
    setBackgroundBrush(QBrush(QImage(":/complementos/imag/fondo1.jpg")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1350,700);}

        // crea la música
void Game::musica(){
    music->stop();
    music->play();
}

        // crea los espacios y los habilita o los deshabilita de acuerdo al lugar
        // donde se encuentre y a los objetos continuos
void Game::creaEspacioMatris(){
    scene->addItem(matriss->listaMatris[0]); scene->addItem(matriss->listaMatris[1]);
    scene->addItem(matriss->listaMatris[2]); scene->addItem(matriss->listaMatris[3]);
    scene->addItem(matriss->listaMatris[4]); scene->addItem(matriss->listaMatris[5]);
    scene->addItem(matriss->listaMatris[6]); scene->addItem(matriss->listaMatris[7]);
    scene->addItem(matriss->listaMatris[8]); scene->addItem(matriss->listaMatris[9]);}



        //////////////////////////////////////////////////////////////////////////////
        /// Seccion donde se inician los componentes necesarios para usar el juego ///
        /// como las cartas, además se encarga de colocarlas en el lugar adecuado  ///
        //////////////////////////////////////////////////////////////////////////////

        // coloca el mazo de cartas repartiéndole 4 cartas a cada jugador y
        // colocando la carta del centro de la matriz
void Game::colocaMazo()
{
    /// Control de posiciones y de cartas, ya el mazo esta random, aquí
    /// se toman cartas para poder usarlas al azar.
    int x = 50; int y = 500;
    for (int i = index; i < (index + 4); i++){
        maso.masso[i]->setPos(x,y);
        maso.masso[i]->owner = "PLAYER1";
        maso.masso[i]->setPosInicialYa(x,y);
        if (this->getWhosTurn() == "PLAYER2"){maso.masso[i]->cambiaAtras();}
        else if (this->getWhosTurn() == "PLAYER1") {maso.masso[i]->cambiaImagen();};
        scene->addItem(maso.masso[i]);
        x += 77; y -= 25;}

    x = 1170; y = 500;
    for (int i = (index + 4); i < (index + 8); i++){
        maso.masso[i]->setPos(x, y);
        maso.masso[i]->owner = "PLAYER2";
        maso.masso[i]->setPosInicialYa(x,y);
        if (this->getWhosTurn() == "PLAYER1"){maso.masso[i]->cambiaAtras();}
        else if (this->getWhosTurn() == "PLAYER2"){maso.masso[i]->cambiaImagen();}
        scene->addItem(maso.masso[i]);
        x -= 77; y -= 25;}

    maso.masso[(index + 8)]->setPos(610,210);
    maso.masso[(index + 8)]->cambiaImagen();
    maso.masso[(index + 8)]->setEsMovible(false);
    lis[1][1] = maso.masso[(index + 8)];
    scene->addItem(maso.masso[(index + 8)]);
}

        // crea botón para calcular
void Game::colocaBotonCalc(){
    // crea el botón
    Boton *calc = new Boton(QString("   Calcular"));
    calc->setPos(460, 620);
    connect(calc, SIGNAL(clicked()), this, SLOT(calc()));
    scene->addItem(calc);
}

        // crea botón para pasar de ronda(deshabilitado mientras no se calcule)
void Game::colocaBotonSig(){
    Boton *siguenteRonda = new Boton(QString("   Siguente"));
    siguenteRonda->setPos(768,620);
    connect(siguenteRonda, SIGNAL(clicked()), this, SLOT(next()));
    scene->addItem(siguenteRonda);
}




        ///////////////////////////////////////////////////////////////////////////////
        /// sección donde se dan los eventos del Mouse y las respectivas respuestas ///
        ///////////////////////////////////////////////////////////////////////////////

        // controla el momento en que se hace click en una cartas
void Game::mouseMoveEvent(QMouseEvent *event){
    if(cardToPlace) {cardToPlace->setPos(event->pos());}
    QGraphicsView::mouseMoveEvent(event);
}

        // levanta la carta para poder moverla en la pantalla
void Game::pickUpCard(Carta *card){

    // verifica de quién es la carta que se va a jugar
    if(cardToPlace == NULL && card->getEsMovible() == true
        && card->owner == getWhosTurn() && cont < 2){

        cardToPlace = card;
        cardToPlace->setEsMovible(false);
        originalPos = card->pos();
        cardToPlace->setIsPlaced(true);}
}

        // cuando se suelta la carta decide a que lugar enviarla o regresarla
void Game::placeCard(Carta *cardToReplace){
    if(sele == false){
        //////////////////////////////////////////////////////////////////////////////
        /// cuando se coloca la carta se verifican los valores para que no se      ///
        /// coloquen más cartas encima y ademas en ciertos casos, habilitar     ///
        /// las funcionalidades que cada carta necesite de acuerdo a los estados   ///
        /// de las cartas continuas y sus valores espectivos                       ///
        //////////////////////////////////////////////////////////////////////////////

        // sonido al soltar la carta ///
        QMediaPlayer * music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/sounds/songs/bip.mp3"));
        music->play();

        // crea las cordenadas para ser modificadas posteriormente
        int x; int y;

        // verifica matris 0,0
        if(cardToReplace->x() > 420 && cardToReplace->x() < 515 &&
           cardToReplace->y() < 100 &&
           matriss->listaMatris[1]->getEstaPermitido() == true &&
           matriss->listaMatris[1]->getHayEspacio() == true)
        {
            lis[0][0] = cardToReplace;
            matriss->listaMatris[1]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[1]);
            x = 470; y = 40;
            cambiaTurno();
        }


        // verifica matris 0,1
        else if(cardToReplace->x() > 560 && cardToReplace->x() < 650 &&
                cardToReplace->y() < 100 &&
                matriss->listaMatris[2]->getHayEspacio()==true){
            matriss->cambiaColorDeCuadro(1);
            matriss->cambiaColorDeCuadro(3);
            lis[0][1] = cardToReplace;
            matriss->listaMatris[1]->setEstaPermitido(true);
            matriss->listaMatris[3]->setEstaPermitido(true);
            matriss->listaMatris[2]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[2]);
            x = 610; y = 40;
            cambiaTurno();}

        // verifica matris 0,2
        else if(cardToReplace->x() > 700 && cardToReplace->x() < 820 &&
                cardToReplace->y() < 100 &&
                matriss->listaMatris[3]->getEstaPermitido() == true &&
                matriss->listaMatris[3]->getHayEspacio() == true)
        {
            lis[0][2] = cardToReplace;
            matriss->listaMatris[3]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[3]);
            x = 750; y = 40;
            cambiaTurno();
        }

        // verifica matris 1,0
        else if(cardToReplace->x() > 420 && cardToReplace->x() < 515 &&
                cardToReplace->y() < 260 && cardToReplace->y() > 150 &&
                matriss->listaMatris[4]->getHayEspacio()==true)
        {
            lis[1][0] = cardToReplace;
            matriss->cambiaColorDeCuadro(1);
            matriss->cambiaColorDeCuadro(7);
            matriss->listaMatris[1]->setEstaPermitido(true);
            matriss->listaMatris[7]->setEstaPermitido(true);
            matriss->listaMatris[4]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[4]);
            x = 470; y = 210;
            cambiaTurno();
        }

        // verifica matris 1,2
        else if(cardToReplace->x() > 700 && cardToReplace->x() < 820 &&
                cardToReplace->y() < 260 && cardToReplace->y() > 150 &&
                matriss->listaMatris[6]->getHayEspacio()==true)
        {
            lis[1][2] = cardToReplace;
            matriss->cambiaColorDeCuadro(3);
            matriss->cambiaColorDeCuadro(9);
            matriss->listaMatris[3]->setEstaPermitido(true);
            matriss->listaMatris[9]->setEstaPermitido(true);
            matriss->listaMatris[6]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[6]);
            x = 750; y = 210;
            cambiaTurno();
        }


        // verifica matris 2,0
        else if(cardToReplace->x() > 420 && cardToReplace->x() < 515 &&
                cardToReplace->y() < 450 && cardToReplace->y() > 300 &&
                matriss->listaMatris[7]->getEstaPermitido() == true &&
                matriss->listaMatris[7]->getHayEspacio() == true)
        {
            lis[2][0] = cardToReplace;
            matriss->listaMatris[7]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[7]);
            x = 470; y = 380;
            cambiaTurno();
        }

        // verifica matris 2,1
        else if(cardToReplace->x() > 560 && cardToReplace->x() < 650 &&
                cardToReplace->y() < 450 && cardToReplace->y() > 300 &&
                matriss->listaMatris[8]->getHayEspacio()==true)
        {
            lis[2][1] = cardToReplace;
            matriss->cambiaColorDeCuadro(7);
            matriss->cambiaColorDeCuadro(9);
            matriss->listaMatris[7]->setEstaPermitido(true);
            matriss->listaMatris[9]->setEstaPermitido(true);
            matriss->listaMatris[8]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[8]);
            x = 610; y = 380;
            cambiaTurno();
        }

        // verifica matris 2,2
        else if(cardToReplace->x() > 700 && cardToReplace->x() < 820 &&
                cardToReplace->y() < 450 && cardToReplace->y() > 300 &&
                matriss->listaMatris[9]->getEstaPermitido() == true &&
                matriss->listaMatris[9]->getHayEspacio() == true)
        {
            lis[2][2] = cardToReplace;
            matriss->listaMatris[9]->setHayEspacio(false);
            this->stack.push(cardToReplace);
            this->stackMatris.push(this->matriss->listaMatris[9]);
            x = 750; y = 380;
            cambiaTurno();
        }

        // si no esta en ningún lugar correcto se regresa a la pos donde estaba
        else{x = originalPos.x(); y = originalPos.y();}

        // verifica si se pone o no la imagen para tomar el camino correcto
        if(x != originalPos.x() && y != originalPos.y()){
            cardToPlace->cambiaImagen();
            cardToReplace->setEsMovible(false);

            // verifica quién esta jugando y cambia de jugador
            if (getWhosTurn() == "PLAYER2"){setWhosTurn("PLAYER1");}
            else if (getWhosTurn() == "PLAYER1") {setWhosTurn("PLAYER2");}}
        else {cardToReplace->setEsMovible(true);}

        // coloca la imagen en el lugar adecuado
        cardToPlace->setPos(x, y);
        cardToPlace->setIsPlaced(false);
        cardToPlace = NULL;}


    ///////////////////////////////////////////////////////////////
    /// sección para colocar las cartas que se eligen al inicio ///
    ///////////////////////////////////////////////////////////////
    else if(sele == true){
        int x; int y;

        if(cardToReplace->x() > 750 && cardToReplace->x() < 950 &&
           cardToReplace->y() > 200 && cardToReplace->y() < 500 &&
           select->camp2->getHayEspacio() == true)
        {
            calculos.insert(1, cardToReplace);
            x = 850; y = 300;
            cardToPlace->cambiaImagen();
            cardToPlace->setIsPlaced(false);
            cont ++;
            select->camp2->setHayEspacio(false);
        }

        else if(cardToReplace->x() > 250 && cardToReplace->x() < 430 &&
           cardToReplace->y() > 200 && cardToReplace->y() < 500 &&
           select->camp1->getHayEspacio() == true)
        {
            calculos.insert(0, cardToReplace);
            x = 350; y = 300;
            cardToPlace->cambiaImagen();
            select->camp1->setHayEspacio(false);
            cardToPlace->setIsPlaced(false);
            cont ++;
        }

        else{
            cardToReplace->setPos(0,0);
            cardToReplace->hide();
        }

        cardToPlace->setPos(x, y);
        cardToPlace = NULL;

        if(cont == 2){
            verificaciones();
            }
        }

    /////////////////////////////////////////////////////////////////////////////////
    /// sección para verificar el orden en que se dan vuelta las cartas del juego ///
    ////////////////////////////////////////////////////////////////////////////////

    /// da vuelta a las cartas cuando sea necesario en cada turno
    this->verAtras();
}




        ////////////////////////////////////////////////////////////////////////////////
        /// Sección donde se ejecutan todos los cálculos necesarios para cambiar los ///
        /// estados de los objetos asociados, para dar la puntuación sin fallos de   ///
        /// cada ronda al usuario y guardarla en la matriz para ser analizada        ///
        /////////////////////////////////////////////////////////////////////////////////

        // crea las instancias de los nombre de cada número
void Game::pinta(){
    num[0] = ":/num/numbers/0.png";
    num[1] = ":/num/numbers/1.png";
    num[2] = ":/num/numbers/2.png";
    num[3] = ":/num/numbers/3.png";
    num[4] = ":/num/numbers/4.png";
    num[5] = ":/num/numbers/5.png";
    num[6] = ":/num/numbers/6.png";
    num[7] = ":/num/numbers/7.png";
    num[8] = ":/num/numbers/8.png";
    num[9] = ":/num/numbers/9.png";
}

        // calcula la puntuación de cada ronda
void Game::calc(){
    /// solo calcula si la matriz esta llena, se protege del UNDO ///
    if(matriss->listaMatris[1]->getHayEspacio() == false &&
            matriss->listaMatris[2]->getHayEspacio() == false &&
            matriss->listaMatris[3]->getHayEspacio() == false &&
            matriss->listaMatris[4]->getHayEspacio() == false &&
            matriss->listaMatris[6]->getHayEspacio() == false &&
            matriss->listaMatris[7]->getHayEspacio() == false &&
            matriss->listaMatris[8]->getHayEspacio() == false &&
            matriss->listaMatris[9]->getHayEspacio() == false){

        scene->removeItem(unduBoton);

        Carta *v1;  Carta *v2;  Carta *v3;  Carta *v4;  Carta *v5;  Carta *v6;
        Carta *v7;  Carta *v8;  Carta *v9;  Carta *v10; Carta *v11; Carta *v12;
        Carta *v13; Carta *v14; Carta *v15; Carta *v16; Carta *v17; Carta *v18;

        int horCero  = CalculaHorizontal(0); int horUno   = CalculaHorizontal(1);
        int horDos   = CalculaHorizontal(2); int verCero  = CalculaVertical(0);
        int verUno   = CalculaVertical(1); int verDos   = CalculaVertical(2);

        ////////////////////////////////////////
        // crea los números para los puntajes //
        ////////////////////////////////////////
        v1 = new Carta(num[horCero % 100 / 10]); v2 = new Carta(num[horCero % 10]);
        v13 = new Carta(num[horCero / 100]);
        v13->setPos(880, 100); v1->setPos(910,100); v2->setPos(940,100);
        scene->addItem(v13); scene->addItem(v1); scene->addItem(v2);

        v3 = new Carta(num[horUno % 100 / 10]); v4 = new Carta(num[horUno % 10]);
        v14 = new Carta(num[horUno / 100]);
        v14->setPos(880, 270); v3->setPos(910, 270); v4->setPos(940,270);
        scene->addItem(v14); scene->addItem(v3); scene->addItem(v4);

        v5 = new Carta(num[horDos % 100 / 10]); v6 = new Carta(num[horDos % 10]);
        v15 = new Carta(num[horDos / 100]);
        v15->setPos(880,440); v5->setPos(910,440); v6->setPos(940,440);
        scene->addItem(v15); scene->addItem(v5); scene->addItem(v6);

        int y = 550;
        v16 = new Carta(num[verCero / 100]); v7 = new Carta(num[verCero % 100 / 10]);
        v8 = new Carta(num[verCero % 10]);
        v16->setPos(490, y); v7->setPos(515,y); v8->setPos(540,y);
        scene->addItem(v16); scene->addItem(v7); scene->addItem(v8);

        v9 = new Carta(num[verUno % 100 / 10]); v10 = new Carta(num[verUno % 10]);
        v17 = new Carta(num[verUno / 100]);
        v17->setPos(635,y); v9->setPos(660,y); v10->setPos(685,y);
        scene->addItem(v17); scene->addItem(v9); scene->addItem(v10);

        v11 = new Carta(num[verDos % 100 / 10]); v12 = new Carta(num[verDos % 10]);
        v18 = new Carta(num[verDos / 100]);
        v18->setPos(775, y); v11->setPos(800,y); v12->setPos(825,y);
        scene->addItem(v18); scene->addItem(v11); scene->addItem(v12);


        ///////////////////////
        /// inicia calculos ///
        ///////////////////////
        int rey; int reina;

        reina = mayorPuntaje("MAYOR", CalculaHorizontal(0),CalculaHorizontal(1), CalculaHorizontal(2));
        rey = mayorPuntaje("MAYOR", CalculaVertical(0), CalculaVertical(1), CalculaVertical(2));


        if(reina == rey){
            reina = mayorPuntaje("MEDIO", CalculaHorizontal(0),CalculaHorizontal(1), CalculaHorizontal(2));
            rey = mayorPuntaje("MEDIO", CalculaVertical(0), CalculaVertical(1), CalculaVertical(2));
        }

        if(reina == rey){
            reina = mayorPuntaje("MENOR", CalculaHorizontal(0),CalculaHorizontal(1), CalculaHorizontal(2));
            rey = mayorPuntaje("MENOR", CalculaVertical(0), CalculaVertical(1), CalculaVertical(2));
        }

        if(rey > reina) {rey   += (rey-reina);}
        if(reina > rey) {reina += (reina - rey);}

        // agrega el jugador 1
        if(jugador1->getCartaPartner() == "REINA"){this->jugador1->puntagesPorRonda[ronda] = reina;}
        else if(jugador1->getCartaPartner() == "REY"){this->jugador1->puntagesPorRonda[ronda] = rey;}

        // agrega el jugador 2
        if(jugador2->getCartaPartner() == "REINA"){this->jugador2->puntagesPorRonda[ronda] = reina;}
        else if(jugador2->getCartaPartner() == "REY"){this->jugador2->puntagesPorRonda[ronda] = rey;}

        // coloca la bandera de verificado en true
        yaVerifico = true;
        }
}

        // calcula horizontal para la reina
int Game::CalculaHorizontal(int sub){
    // empezamos los calculos de puntos
    int suma = 0;

    // calculos para la reina

    // joker primer caso
    if(lis[sub][0]->getValor() == 23 || lis[sub][1]->getValor() == 23 ||
       lis[sub][2]->getValor() == 23){
         return 0;}

    // horizontal con todo
    for (int i = 0; i < 3; i++){
        if(lis[sub][i]->getValor() == 22) {suma += 0;}        // si es rey no suma
        else if(lis[sub][i]->getValor() == 21) {suma += 10;}  // si es reina suma 10
        else if(lis[sub][i]->getValor() < 20){suma += lis[sub][i]->getValor();}}

    // quintuplica
    if(lis[sub][0]->getSimbolo() == lis[sub][1]->getSimbolo() &&
       lis[sub][1]->getSimbolo() == lis[sub][2]->getSimbolo()){
         suma *= 5; return suma;}

    // triplica
    else if(lis[sub][0]->getColor() == lis[sub][1]->getColor() &&
            lis[sub][1]->getColor() == lis[sub][2]->getColor()){
        suma *= 3; return suma;}

    // duplica
    else if(lis[sub][0]->getSimbolo() == lis[sub][1]->getSimbolo() ||
            lis[sub][1]->getSimbolo() == lis[sub][2]->getSimbolo() ||
            lis[sub][0]->getSimbolo() == lis[sub][2]->getSimbolo()){
        suma *= 2; return suma;}

    return suma;
}

        // calcula vertical para el rey
int Game::CalculaVertical(int sub){
    int suma = 0;
    // cálculos para el rey

    // caso joker
    if(lis[0][sub]->getValor() == 23 || lis[1][sub]->getValor() == 23 ||
       lis[2][sub]->getValor() == 23){
         return 0;}

    // horizontal 0 con todo
    for (int i = 0; i < 3; i++){
        if(lis[i][sub]->getValor() == 21) {suma += 0;}
        else if(lis[i][sub]->getValor() == 22) {suma += 10;}
        else if(true){suma += lis[i][sub]->getValor();}
    }

    // quintuplica
    if(lis[0][sub]->getSimbolo() == lis[1][sub]->getSimbolo() &&
       lis[1][sub]->getSimbolo() == lis[2][sub]->getSimbolo()){
         suma *= 5;}

    // triplica
    else if(lis[0][sub]->getColor() == lis[1][sub]->getColor() &&
            lis[1][sub]->getColor() == lis[2][sub]->getColor()){
        suma *= 3;}

    // duplica
    else if(lis[0][sub]->getSimbolo() == lis[1][sub]->getSimbolo() ||
            lis[1][sub]->getSimbolo() == lis[2][sub]->getSimbolo() ||
            lis[0][sub]->getSimbolo() == lis[2][sub]->getSimbolo()){
        suma *= 2;}

    return suma;
}

        // saca el mayor puntaje de cada jugador en la ronda actual
int Game::mayorPuntaje(QString index, int x, int z, int y){


    if(index == "MAYOR"){
        if((x >= y) && (x >= z)){return x;}
        else if (y >= z) {return y;}
        else{return z;}}

    if (index == "MEDIO"){
        if((x >= z) && (z >= y)){return z;}
        if((y >= z) && (z >= x)){return z;}
        if((z >= x) && (x >= y)){return x;}
        if((y >= x) && (x >= z)){return x;}
        if((x >= y) && (y >= z)){return z;}
        if((z >= y) && (y >= x)){return z;}}

    else if (index == "MENOR"){
        if((x <= y) && (x <= z)){return x;}
        else if((y <= x) && (y <= z)){return y;}
        else {return x;}
    }
}

        // coloca las imágenes de los números de acuerdo a la puntuación
void Game::pintaPunctuacionesConNumeros(){
    /// Cada bloque desconpone la calificación del jugador para poder colocar
    /// los números adecuados iguales a la puntuación en pantalla.
    Carta *nu[2][6];
    int x = 0;
    int y = 0;
    QString nomb;

    y = 375; x = 300;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador1->puntagesPorRonda[1] / 100];}
        if(i == 1){nomb = num[jugador1->puntagesPorRonda[1] % 100 / 10];}
        if(i == 2){nomb = num[jugador1->puntagesPorRonda[1] % 10];}
        nu[1][i] = new Carta(nomb); nu[1][i]->setPos(x,y);
        scene->addItem(nu[1][i]); x += 40;}

    y = 315; x = 300;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador1->puntagesPorRonda[2] / 100];}
        if(i == 1){nomb = num[jugador1->puntagesPorRonda[2] % 100 / 10];}
        if(i == 2){nomb = num[jugador1->puntagesPorRonda[2] % 10];}
        nu[1][i] = new Carta(nomb); nu[1][i]->setPos(x,y);
        scene->addItem(nu[1][i]); x += 40;}

    y = 255; x = 300;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador1->puntagesPorRonda[3] / 100];}
        if(i == 1){nomb = num[jugador1->puntagesPorRonda[3] % 100 / 10];}
        if(i == 2){nomb = num[jugador1->puntagesPorRonda[3] % 10];}
        nu[1][i] = new Carta(nomb); nu[1][i]->setPos(x,y);
        scene->addItem(nu[1][i]); x += 40;}

    y = 195; x = 300;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador1->puntagesPorRonda[4] / 100];}
        if(i == 1){nomb = num[jugador1->puntagesPorRonda[4] % 100 / 10];}
        if(i == 2){nomb = num[jugador1->puntagesPorRonda[4] % 10];}
        nu[1][i] = new Carta(nomb); nu[1][i]->setPos(x,y);
        scene->addItem(nu[1][i]); x += 40;}

    y = 135; x = 300;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador1->puntagesPorRonda[5] / 100];}
        if(i == 1){nomb = num[jugador1->puntagesPorRonda[5] % 100 / 10];}
        if(i == 2){nomb = num[jugador1->puntagesPorRonda[5] % 10];}
        nu[1][i] = new Carta(nomb); nu[1][i]->setPos(x,y);
        scene->addItem(nu[1][i]); x += 40;}

    y = 70; x = 300;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador1->puntagesPorRonda[6] / 100];}
        if(i == 1){nomb = num[jugador1->puntagesPorRonda[6] % 100 / 10];}
        if(i == 2){nomb = num[jugador1->puntagesPorRonda[6] % 10];}
        nu[1][i] = new Carta(nomb); nu[1][i]->setPos(x,y);
        scene->addItem(nu[1][i]); x += 40;}

    y = 375; x = 1190;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador2->puntagesPorRonda[1] / 100];}
        if(i == 1){nomb = num[jugador2->puntagesPorRonda[1] % 100 / 10];}
        if(i == 2){nomb = num[jugador2->puntagesPorRonda[1] % 10];}
        nu[2][i] = new Carta(nomb); nu[2][i]->setPos(x,y);
        scene->addItem(nu[2][i]); x += 40;}

    y = 315; x = 1190;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador2->puntagesPorRonda[2] / 100];}
        if(i == 1){nomb = num[jugador2->puntagesPorRonda[2] % 100 / 10];}
        if(i == 2){nomb = num[jugador2->puntagesPorRonda[2] % 10];}
        nu[2][i] = new Carta(nomb); nu[2][i]->setPos(x,y);
        scene->addItem(nu[2][i]); x += 40;}

    y = 255; x = 1190;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador2->puntagesPorRonda[3] / 100];}
        if(i == 1){nomb = num[jugador2->puntagesPorRonda[3] % 100 / 10];}
        if(i == 2){nomb = num[jugador2->puntagesPorRonda[3] % 10];}
        nu[2][i] = new Carta(nomb); nu[2][i]->setPos(x,y);
        scene->addItem(nu[2][i]); x += 40;}

    y = 195; x = 1190;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador2->puntagesPorRonda[4] / 100];}
        if(i == 1){nomb = num[jugador2->puntagesPorRonda[4] % 100 / 10];}
        if(i == 2){nomb = num[jugador2->puntagesPorRonda[4] % 10];}
        nu[2][i] = new Carta(nomb); nu[2][i]->setPos(x,y);
        scene->addItem(nu[2][i]); x += 40;}

    y = 135; x = 1190;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador2->puntagesPorRonda[5] / 100];}
        if(i == 1){nomb = num[jugador2->puntagesPorRonda[5] % 100 / 10];}
        if(i == 2){nomb = num[jugador2->puntagesPorRonda[5] % 10];}
        nu[2][i] = new Carta(nomb); nu[2][i]->setPos(x,y);
        scene->addItem(nu[2][i]); x += 40;}

    y = 75; x = 1190;
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador2->puntagesPorRonda[6] / 100];}
        if(i == 1){nomb = num[jugador2->puntagesPorRonda[6] % 100 / 10];}
        if(i == 2){nomb = num[jugador2->puntagesPorRonda[6] % 10];}
        nu[2][i] = new Carta(nomb); nu[2][i]->setPos(x,y);
        scene->addItem(nu[2][i]); x += 40;}
}

        // hace los cálculos al final de juego
void Game::calculoFinalDePunctuaciones(){
    int puntosJugador1 = 0;
    int puntosJugador2 = 0;

    for (int i = 1; i < 7; i++){
        jugador1->puntagesPorRonda[0] += jugador1->puntagesPorRonda[i];
        jugador2->puntagesPorRonda[0] += jugador2->puntagesPorRonda[i];
    }
}

        // crea dibujos animados
void Game::gato(){
    Carta *c = new Carta(":/deco/Deco/vampi.png");
    c->setPos(1000,345);
    scene->addItem(c);
    c->setEsMovible(false);
}


        // boton UNDO para poder regresar acciones
void Game::botonUndu(){
    unduBoton = new Boton(QString("  Retroceder"));
    unduBoton->setPos(615,620);
    connect(unduBoton, SIGNAL(clicked()), this, SLOT(undu()));
    scene->addItem(unduBoton);
}

        // verifica hacia atrás para saber cual jugador está jugando y cuál ya jugó
        // para poder cambiar los naipes boca abajo o boca arriba
void Game::verAtras(){
    /// cuando juega el jugador 1, las cartas del jugador 2 deben estar boca abajo
    /// y de la misma forma para cuando juega el jugador 2, esta parte se encarga de
    /// controlar quién juega y cuales cartas se pueden ver.
    if(this->getWhosTurn() == "PLAYER1"){
        for(int i = index; i < (index + 4); i++){
            if(maso.masso[i]->getEsMovible() == true &&
                                this->getWhosTurn() == "PLAYER1"){
               maso.masso[i]->cambiaImagen();}

            if(maso.masso[i+4]->getEsMovible() == true){
                maso.masso[i+4]->cambiaAtras();}}}

    if(this->getWhosTurn() == "PLAYER2"){
        for(int i = (index + 4); i < (index + 8); i++){
            if(maso.masso[i]->getEsMovible() == true &&
                                this->getWhosTurn() == "PLAYER2"){
                       maso.masso[i]->cambiaImagen();}

            if(maso.masso[i-4]->getEsMovible() == true){
                       maso.masso[i-4]->cambiaAtras();}}}
}

        // acción del botón undo, encargado de regresar la acción o las acciones
        // que el usuario desea.
void Game::undu(){
    // aquí se edita el stack para sacar la POS de las cartas
    if(stack.length() > 0){
        cambiaTurno();
        Carta *atras;
        CamposMatris *campAtras;
        atras = this->stack.pop();
        atras->goToPosInicialYa();
        atras->setEsMovible(true);

        if (getWhosTurn() == "PLAYER2"){setWhosTurn("PLAYER1");}
        else if (getWhosTurn() == "PLAYER1") {setWhosTurn("PLAYER2");}

        // retorna las cartas a la pos adecuada
        this->verAtras();

        // instancias de control
        campAtras = this->stackMatris.pop();
        campAtras->setHayEspacio(true);

        ////////////////////////////////////////////////////////////////////////
        /////// bloque para volver a colocar los espacios bloqueados ///////////
        ////////////////////////////////////////////////////////////////////////
        if (campAtras->getX() == 610 && campAtras->getY() == 40){
            if(matriss->listaMatris[4]->getHayEspacio() == true){
                matriss->listaMatris[1]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[1]->setEstaPermitido(false);}
            if(matriss->listaMatris[6]->getHayEspacio() == true){
                matriss->listaMatris[3]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[3]->setEstaPermitido(false);}
        }

        else if (campAtras->getX() == 470 && campAtras->getY() == 210){
            if(matriss->listaMatris[2]->getHayEspacio() == true){
                matriss->listaMatris[1]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[1]->setEstaPermitido(false);}
            if(matriss->listaMatris[8]->getHayEspacio() == true){
                matriss->listaMatris[7]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[7]->setEstaPermitido(false);}
        }

        else if (campAtras->getX() == 750 && campAtras->getY() == 210){
            if(matriss->listaMatris[2]->getHayEspacio() == true){
                matriss->listaMatris[3]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[3]->setEstaPermitido(false);}
            if(matriss->listaMatris[8]->getHayEspacio() == true){
                matriss->listaMatris[9]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[9]->setEstaPermitido(false);}
        }

        else if (campAtras->getX() == 610 && campAtras->getY() == 380){
            if(matriss->listaMatris[4]->getHayEspacio() == true){
                matriss->listaMatris[7]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[7]->setEstaPermitido(false);}
            if(matriss->listaMatris[6]->getHayEspacio() == true){
                matriss->listaMatris[9]->setAtras(":/complementos/imag/rojo-1.png");
                matriss->listaMatris[9]->setEstaPermitido(false);}
        }
    }
}

        // controla las rondas del juego, que en total son 6 y al finalizar
        // crea una pantalla con el desglose de cada jugador y quien ganó el juego
void Game::next(){
    // llamar los datos para cada ronda jugada, debe verificar que los puntajes se guarden
    // correctamente en cada espacio de la matriz puntajes
    if(yaVerifico == true && ronda <= 7){

        // según las reglas, el que pierde la ronda empieza a jugar en la siguiente
        if(jugador1->puntagesPorRonda[ronda] > jugador2->puntagesPorRonda[ronda]){
            this->setWhosTurn("PLAYER2");}
        else if(jugador1->puntagesPorRonda[ronda] < jugador2->puntagesPorRonda[ronda]){
            this->setWhosTurn("PLAYER1");}

        ronda++;
        if(ronda == 2){this->index = 9;}
        else if(ronda == 3){this->index = 18;}
        else if(ronda == 4){this->index = 27;}
        else if(ronda == 5){this->index = 36;}
        else if(ronda == 6){this->index = 45;}

        // sabe en que ronda está
        if(ronda < 7) {this->iniciaJuego();}

        // crea la pantalla final del juego
        else {
            scene->clear();

            // decoración
            drawGUI();
            this->pintaPunctuacionesConNumeros();
            Carta *d = new Carta(":/complementos/imag/congratulations-1.png");
            d->setPos(465,50);
            scene->addItem(d);

            // calcula y pinta
            calculoFinalDePunctuaciones();
            this->pantallaFinal();
        }
    }
}



        /////////////////////////////////////////////////////////////////////////////
        /// sección en la cual se pintan los páneles de estilo y se crean los     ///
        /// textos que van a dar la información de los turnos a los jugadores     ///
        /////////////////////////////////////////////////////////////////////////////

        // llama los metodos paa crear los paneles de juego y los títulos de guía
void Game::drawGUI(){
    // dibuja el panel izquierdo
    drawPanel(30,20,400,660,Qt::red,0.50);

    // dibuja el panel derecho
    drawPanel(920,20,400,660,Qt::red,0.50);

    // coloca textos correspondientes al jugador 1
    QGraphicsTextItem* p1 = new QGraphicsTextItem("Cartas y Puntos del jugador 1: ");
    p1->setDefaultTextColor(Qt::white);
    p1->setPos(150,30);
    scene->addItem(p1);

    // coloca textos correspondientes al jugador 2
    QGraphicsTextItem* p2 = new QGraphicsTextItem("Cartas y Puntos del jugador 2: ");
    p2->setDefaultTextColor(Qt::white);
    p2->setPos(1030,20);
    scene->addItem(p2);

    // colocar el turno del jugador correspondiente
    whosTurnText = new QGraphicsTextItem();
    whosTurnText->setDefaultTextColor(Qt::white);
    whosTurnText->setPos(570,20);
    scene->addItem(whosTurnText);
    colocaPunctuaciones();/// agrega textos de puntuaciones
}

        // obtiene quien esta jugando actualmente
QString Game::getWhosTurn() {return whosTurn;}

        // cambia de jugador
void Game::setWhosTurn(QString player) {whosTurn = player;}

       // establece quien juega de primero
void Game::cambiaTurno(){
    delete(whosTurnText);
    whosTurnText = new QGraphicsTextItem();
    whosTurnText->setDefaultTextColor(Qt::white);

    if (getWhosTurn() == "PLAYER1")
        whosTurnText->setPlainText(QString("Es el turno del: Jugador 2"));
    else
        whosTurnText->setPlainText(QString("Es el turno del: Jugador 1"));

    whosTurnText->setPos(610,10);
    scene->addItem(whosTurnText);
    jug = 1;
}



        // crea la pantalla para seleccionar quien juega con el rey o con la reina
void Game::pideReyoReina(){
    // texto
    scene->clear();
    gato();

    Carta *des = new Carta(":/complementos/rondas/reyoreina.png");
    des->setEsMovible(false);
    des->setPos(440,0);
    scene->addItem(des);

    QGraphicsTextItem *tit;
    tit = new QGraphicsTextItem();
    tit->setDefaultTextColor(Qt::white);
    tit->setPlainText(QString(getWhosTurn()+" decide si juega con el REY o con la REINA"));
    tit->setPos(520,250);
    scene->addItem(tit);

    // decoración
    Carta *c = new Carta(":/corazones/Baraja/corazones/k-corazones-rojo.png");
    c->setPos(700,350);
    scene->addItem(c);
    Carta *c1 = new Carta(":/corazones/Baraja/corazones/q-corazones-rojo.png");
    c1->setPos(450,350);
    scene->addItem(c1);

    // botones
    Boton *ver = new Boton(QString("        REY"));
    ver->setPos(703, 285);
    connect(ver, SIGNAL(clicked()), this, SLOT(cambiaEstadoPlayer2()));
    scene->addItem(ver);

    Boton *ver1 = new Boton(QString("     REINA"));
    ver1->setPos(453, 285);
    connect(ver1, SIGNAL(clicked()), this, SLOT(cambiaEstadoPlayer1()));
    scene->addItem(ver1);
}

        // define cuando gana el jugador 1, al escoger la carta inicial
void Game::cambiaEstadoPlayer1(){
    if(getWhosTurn() == "PLAYER1") {
        jugador1->setCartaPartner("REINA");
        jugador2->setCartaPartner("REY");

    }
    else if(getWhosTurn() == "PLAYER2") {
        jugador2->setCartaPartner("REINA");
        jugador1->setCartaPartner("REY");
    }

    paso();
}

        // define cuando gana el jugador 2, al escoger la carta inicial
void Game::cambiaEstadoPlayer2(){
    if(getWhosTurn() == "PLAYER1") {
        jugador1->setCartaPartner("REY");
        jugador2->setCartaPartner("REINA");
    }
    else if(getWhosTurn() == "PLAYER2") {
        jugador2->setCartaPartner("REY");
        jugador1->setCartaPartner("REINA");
    }
    paso();
}

        // crea los páneles del juego
void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // dibuja un pánel en un lugar específico con las propiedades necesarias
        QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(color);
        panel->setBrush(brush);
        panel->setOpacity(opacity);
        scene->addItem(panel);}




        /////////////////////////////////////////////////////////////////////////////
        /// sección en la cual se verifica el ganador al escoger la carta inicial ///
        /// y se continua el camino informativo hasta llegar a iniciar el juego   ///
        /////////////////////////////////////////////////////////////////////////////

        // botón para verificar el ganador al inico del juego
void Game::botonVerificar(){
    // crea el boton "De Nuevo"
    Boton *ver = new Boton(QString("   De Nuevo"));
    ver->setPos(603, 230);
    maso.baraja();
    connect(ver, SIGNAL(clicked()), this, SLOT(seguir()));
    scene->addItem(ver);
}

        // verifica quien puede escoger el rey o la reina
void Game::verificaciones()
{
    // verifica todas las especificaciones con respecto al color y palo de las cartas
    // declarar el ganador al escoger la carta

    // verifica negro con negro
    if(calculos[0]->getColor() == 'n' && calculos[1]->getColor() == 'n'){
        botonVerificar();}

    // verifica rojo con negro
    if(calculos[0]->getColor() == 'r' && calculos[1]->getColor() == 'n'){
        this->pintaGanador1();
        setWhosTurn("PLAYER1");
        verifbutton();}

    // verifica negro con rojo
    if(calculos[0]->getColor() == 'n' && calculos[1]->getColor() == 'r'){
        this->pintaGanador2();
        setWhosTurn("PLAYER2");
        verifbutton();}

    // verifica rojo con rojo
    if(calculos[0]->getColor() == 'r' && calculos[1]->getColor() == 'r'){



        // verifica corazones y diamantes
        if(calculos[0]->getSimbolo() == 'c' && calculos[1]->getSimbolo() == 'd'){
            this->pintaGanador1();
            setWhosTurn("PLAYER1");
            verifbutton();}

        // verifica diamantes y corazones
        else if(calculos[0]->getSimbolo() == 'd' && calculos[1]->getSimbolo() == 'c'){
            this->pintaGanador2();
            setWhosTurn("PLAYER2");
            verifbutton();}

        // si no, verifica valores
        else{


            if((calculos[0]->getValor() == 0 && calculos[1]->getValor() < 11) ||
                    (calculos[1]->getValor() == 23)){
                this->pintaGanador1();
                setWhosTurn("PLAYER1");
                verifbutton();}

            else if((calculos[0]->getValor() < 11 || calculos[1]->getValor() == 23)
                    && (calculos[1]->getValor() == 0)){
                this->pintaGanador2();
                setWhosTurn("PLAYER2");
                verifbutton();}

            else if (calculos[0]->getValor() > calculos[1]->getValor()){
                this->pintaGanador1();
                setWhosTurn("PLAYER1");
                verifbutton();}

            else if(calculos[0]->getValor() < calculos[1]->getValor()){
                this->pintaGanador2();
                setWhosTurn("PLAYER2");
                verifbutton();}
        }
    }
}

        // coloca los elementos necesarios para que se puedan escoger el rey o la reina
void Game::colocaSeleccion(){
    // coloca el texto de la pantalla y la carta de fondo
    gato();

    Carta *coloca = new Carta(":/complementos/rondas/colocaCarta.png");
    coloca->setEsMovible(false);
    coloca->setPos(180, 30);
    scene->addItem(coloca);

    Carta *c1 = new Carta(":/complementos/imag/back2.png");
    c1->setPos(600,300);
    c1->setEsMovible(false);
    scene->addItem(c1);
    creaCartasSeleccion();
}

        // coloca el mazo de cartas al azar para escoger
void Game::creaCartasSeleccion()
{
    // crea las cartas de selección al inicio del juego
    for (int i = 0; i < 54; i++){
        maso.cartasInicio[i]->setPos(600,300);
        scene->addItem(maso.cartasInicio[i]);}
}


void Game::colocaPunctuaciones(){
    Carta *eti[13];
    eti[1] = new Carta(":/eti/rondas/1ra.png"); eti[2] = new Carta(":/eti/rondas/2da.png");
    eti[3] = new Carta(":/eti/rondas/3ra.png"); eti[4] = new Carta(":/eti/rondas/4ta.png");
    eti[5] = new Carta(":/eti/rondas/5ta.png"); eti[6] = new Carta(":/eti/rondas/6ta.png");
    eti[7] = new Carta(":/eti/rondas/1ra.png"); eti[8] = new Carta(":/eti/rondas/2da.png");
    eti[9] = new Carta(":/eti/rondas/3ra.png"); eti[10] = new Carta(":/eti/rondas/4ta.png");
    eti[11] = new Carta(":/eti/rondas/5ta.png"); eti[12] = new Carta(":/eti/rondas/6ta.png");

    controlUndu = false;
    int x = 30; int y = 340;
    for (int i = 1; i < 7; i++){
        eti[i]->setPos(x,y);
        eti[1]->setPos(20, 340);
        scene->addItem(eti[i]);
        y -= 60;}

    x = 920;  y = 340;
    for (int i = 7; i < 13; i++){
        eti[i]->setPos(x,y);
        eti[7]->setPos(910, 340);
        scene->addItem(eti[i]);
        y -= 60;}
}

        // respuesta cuando se empata la ronda, para continuar con la siguiente carta
void Game::seguir(){
    // acción del boton "de nuevo", que se ejecuta cuando las cartas son negras
    delete(calculos[0]);
    delete(calculos[1]);
    cont = 0;
    maso.baraja();
    select->camp1->setHayEspacio(true);
    select->camp2->setHayEspacio(true);

    // en caso de que sean dos negras se inicia la selección
    scene->clear();
    this->creaTextoSeleccion();
    this->colocaSeleccion();
}

        // coloca el jugador que ganó
void Game::pintaGanador1(){
    QGraphicsTextItem *tit2;
    tit2 = new QGraphicsTextItem();
    tit2->setDefaultTextColor(Qt::white);
    tit2->setPlainText(QString("GANÓ EL JUGADOR NUMERO 1"));
    tit2->setPos(590,200);
    scene->addItem(tit2);
}
void Game::pintaGanador2(){
    QGraphicsTextItem *tit2;
    tit2 = new QGraphicsTextItem();
    tit2->setDefaultTextColor(Qt::white);
    tit2->setPlainText(QString("GANÓ EL JUGADOR NUMERO 2"));
    tit2->setPos(590,200);
    scene->addItem(tit2);
}

        // termina el juego
void Game::pantallaFinal(){
    // coloca las puntuaciones finales
    int y = 600; int x = 160; QString nomb; Carta *nu[3];
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador1->puntagesPorRonda[0] / 100];}
        if(i == 1){nomb = num[jugador1->puntagesPorRonda[0] % 100 / 10];}
        if(i == 2){nomb = num[jugador1->puntagesPorRonda[0] % 10];}
        nu[i] = new Carta(nomb);
        nu[i]->setPos(x,y);
        scene->addItem(nu[i]);
        x += 40;}
    y = 600; x = 1060; Carta *nu1[3];
    for(int i = 0; i < 3; i ++){
        if(i == 0){nomb = num[jugador2->puntagesPorRonda[0] / 100];}
        if(i == 1){nomb = num[jugador2->puntagesPorRonda[0] % 100 / 10];}
        if(i == 2){nomb = num[jugador2->puntagesPorRonda[0] % 10];}
        nu1[i] = new Carta(nomb);
        nu1[i]->setPos(x,y);
        scene->addItem(nu1[i]);
        x += 40;}

    // decoración de la pantalla
    Carta *final = new Carta(":/complementos/imag/total.png");
    final->setEsMovible(false);
    final->setPos(30, 510);
    scene->addItem(final);

    Carta *final2 = new Carta(":/complementos/imag/total.png");
    final2->setEsMovible(false);
    final2->setPos(920, 510);
    scene->addItem(final2);

    Carta *final3 = new Carta(":/complementos/imag/ganador.png");
    final3->setEsMovible(false);
    final3->setPos(460, 310);
    scene->addItem(final3);

    Carta *final4 = new Carta(":/complementos/imag/es.png");
    final4->setEsMovible(false);
    final4->setPos(470, 360);
    scene->addItem(final4);


    // coloca el ganador
    Carta *win;
    if(jugador1->puntagesPorRonda[0] > jugador2->puntagesPorRonda[0]){
        win = new Carta(":/complementos/imag/win1.png");}

    else if(jugador1->puntagesPorRonda[0] < jugador2->puntagesPorRonda[0]){
        win = new Carta(":/complementos/imag/win2.png");}

    win->setPos(550,450);
    scene->addItem(win);


    Boton *ver = new Boton(QString("      Salir"));
    ver->setPos(603, 630);
    connect(ver, SIGNAL(clicked()), this, SLOT(salir()));
    scene->addItem(ver);
}

        // termina con el programa
void Game::salir(){
    scene->~QGraphicsScene();
    this->~QFrame();
}

        // botón para verificar y pasar a la siguiente pantalla del juego
void Game::verifbutton(){
    // crea el boton
    Boton *ver = new Boton(QString("   Continuar"));
    ver->setPos(603, 230);
    connect(ver, SIGNAL(clicked()), this, SLOT(pideReyoReina()));
    scene->addItem(ver);
}

        // convierte los resultados para guardar las variables de cada jugador
void Game::paso(){

    // cambia de turno al inicio(primer turno)
    if(getWhosTurn() == "PLAYER1") {setWhosTurn("PLAYER2");}
    else if(getWhosTurn() == "PLAYER2") {setWhosTurn("PLAYER1");}

    // decoración
    scene->clear();
    this->gato();

    Carta *des = new Carta(":/complementos/rondas/partnercarta.png");
    des->setEsMovible(false);
    des->setPos(190,0);
    scene->addItem(des);

    QGraphicsTextItem *tit;
    tit = new QGraphicsTextItem(); tit->setDefaultTextColor(Qt::white);
    tit->setPlainText(QString("PLAYER 1 juega con"));
    tit->setPos(430,300);
    scene->addItem(tit);
    QGraphicsTextItem *tit2;
    tit2 = new QGraphicsTextItem();
    tit2->setDefaultTextColor(Qt::white);
    tit2->setPlainText(QString("PLAYER 2 juega con"));
    tit2->setPos(790,300);
    scene->addItem(tit2);

    // guarda la selección de cada jugador en su variable correspondiente

    if(jugador1->getCartaPartner() == "REY" || jugador2->getCartaPartner() == "REINA"){
        Carta *c1 = new Carta(":/corazones/Baraja/corazones/k-corazones-rojo.png");
        c1->setPos(420,330);
        scene->addItem(c1);
        Carta *c12 = new Carta(":/corazones/Baraja/corazones/q-corazones-rojo.png");
        c12->setPos(780,330);
        scene->addItem(c12);}
    else if(jugador1->getCartaPartner() == "REINA" || jugador2->getCartaPartner() == "REY"){
        Carta *c1 = new Carta(":/corazones/Baraja/corazones/q-corazones-rojo.png");
        c1->setPos(420,330);
        scene->addItem(c1);
        Carta *c12 = new Carta(":/corazones/Baraja/corazones/k-corazones-rojo.png");
        c12->setPos(780,330);
        scene->addItem(c12);}

    // botón para iniciar
    Boton *ver = new Boton(QString("Iniciar Juego"));
    ver->setPos(615, 230);

    connect(ver, SIGNAL(clicked()), this, SLOT(iniciaJuego()));
    scene->addItem(ver);
}

        // método que inicia el juego en su totalidad
void Game::iniciaJuego(){

    // limpia y define atributos necesarios para control
    scene->clear();
    cont = 0;
    sele = false;

    // limpia el stack al iniciar cada ronda
    for(int i = stack.length(); i > 0; i--){stack.pop();}

    // inicio
    this->yaVerifico = false;
    this->matriss = new matris();
    this->creaEspacioMatris();
    this->drawGUI();
    this->colocaBotonCalc();
    this->colocaBotonSig();
    this->botonUndu();
    this->pinta();
    this->pintaPunctuacionesConNumeros();
    this->colocaMazo();
}

        // crea el texto guía para el usuario
void Game::creaTextoSeleccion(){
    // crea los espacios para colocar la carta
    select = new SeleccionCarta();
    scene->addItem(select->camp1);
    scene->addItem(select->camp2);

    // crea los textos de info.
    QGraphicsTextItem *tit;
    tit = new QGraphicsTextItem();
    tit->setDefaultTextColor(Qt::white);
    tit->setPlainText(QString("CARTA DEL JUGADOR 1"));
    tit->setPos(350,280);
    scene->addItem(tit);

    QGraphicsTextItem *tit2;
    tit2 = new QGraphicsTextItem();
    tit2->setDefaultTextColor(Qt::white);
    tit2->setPlainText(QString("CARTA DEL JUGADOR 2"));
    tit2->setPos(850,280);
    scene->addItem(tit2);
}

