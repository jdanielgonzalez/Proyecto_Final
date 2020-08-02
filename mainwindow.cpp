#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //escena
    escena = new QGraphicsScene; //crear la escena del juego
    ui->graphicsView->setScene(escena); //agregar el graphicsView
    escena->setSceneRect(0,0,1000,698); //darle un tamaño a la escena

    //vidas
    vidas = new salud(); //crear variable de las vidas
    vidas->setPos(70,20); //dar posicion a las vidas

    //puntos
    puntos = new puntaje; //crear variable puntaje
    puntos->setPos(140,20); //dar posicion al puntaje

    //texto en pantalla
    escogerpartida = new puntaje;
    escogerpartida->setPos(353,20);

    //probabilidad
    probabilidad = new porcentaje(); //crear variable de la probabilidad

    //cuerpo principal
    chillin = new Cuerpo(10,600,50,40); //creo chillin

//    moncha = new Cuerpo(900,600,50,50);
//    escena->addItem(moncha);

    //jeringa
    pastilla = new Cuerpo(950,600,50,40); //creo pastilla
    pastilla->setcolumna_fila(0,280); //dar posicion a pastilla

    //entorno
    piso = new Cuerpo(500,650,1000,50); //creo el piso
    muroderecho = new Cuerpo(1025,350,50,800); //creo el muro derecho
    muroizquierdo = new Cuerpo(-25,350,50,800); //creo el muro izquierdo

    //timers
    timerenemigo = new QTimer; //creo el Qtimer
    timerenemigo2 = new QTimer; //creo el Qtimer
    timerenemigo3 = new QTimer; //creo el Qtimer

    //sprite vidas
    Sprite_vidas = new Cuerpo(50,40,50,50); //crear Spritevidas
    Sprite_vidas->setImagen(1); //actualizar el spirte

    //lodo
    lodo1 = new Cuerpo(75,600,150,40); //crear lodo1
    lodo1->setImagen(2); //seleccionar imagen

    lodo2 = new Cuerpo(500,600,150,40); //crear lodo2
    lodo2->setImagen(2); //seleccionar imagen

    lodo3 = new Cuerpo(940,600,150,40); //crear lodo3
    lodo3->setImagen(2); //seleccionar imagen

    //audio
    musica = new QMediaPlayer; //creo musica del menu
    musica->setMedia(QUrl("qrc:/musica/musica_menu.mp3")); // le doy la cancion correspondiente

    fuego = new QMediaPlayer;
    fuego->setMedia(QUrl("qrc:/musica/musica_fuego.mp3"));

    corte = new QMediaPlayer;
    corte->setMedia(QUrl("qrc:/musica/musica_triturado.mp3"));

    //gif
    quemado = new QMovie(":/gif/quemado.gif"); //darle el gif al QMovie
    ui->Quemado->setMovie(quemado); //darle al label el QMovie

    triturado = new QMovie(":/gif/triturado.gif");
    ui->Triturado->setMovie(triturado);

    portal = new QMovie(":/gif/portal.gif");
    ui->Portal->setMovie(portal);

    //lineedit
    ui->lineEdit_clave->setEchoMode(QLineEdit::Password); //esconder texto en el lineEdit

    menu(); //mostrar el menu
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mover_enemigo()
{
    for(int i=0; i<enemigos.size();i++) //ciclo que lee toda la lista de enemigos
    {
        /* enemmigo 1 y 2 son las bolas que rebotan
         * enemigo 3 y 4 las bolas con movimiento MCU
         * enemigo 5 con el movimiento MAS*/

        //qDebug() <<"velocidad: "<<enemigos.at(i)->getVel();
        //qDebug() <<"velocidadx: "<<enemigos.at(i)->getVelx();
        if(enemigos.at(i)->getVel()>70){enemigos.at(i)->setVel(70);} //condicion para que no supere cierta velocidad
        if(enemigos.at(i)->getVelx()<20){enemigos.at(i)->setVelx(20);} //condicion para que no rebote con una velocidad menor

        //mover a la derecha
        if(enemigos.at(i)->getDir()==1) //condicion para preguntar por la direcion
        {

            if(enemigos.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                enemigos.at(i)->setColumnas_fila(0,0);//actulizar el sprite
            }
            if(enemigos.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativo
            {
                enemigos.at(i)->setColumnas_fila(0,84);// actualiza el sprite
            }
            enemigos.at(i)->actualizarposicion_derecha(); //actualiza la posicion
            enemigos.at(i)->actualizarvelocidad(); //actualiza la velocidad
            enemigos.at(i)->setX(enemigos.at(i)->getPosx()); //setea la posicion en x
            enemigos.at(i)->setY(-enemigos.at(i)->getPosy());//setea la posicion en y
        }

        //mover a la izquierda
        if(enemigos.at(i)->getDir()==2) //condicion para preguntar la direccion
        {
            if(enemigos.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                enemigos.at(i)->setColumnas_fila(80,0); //actualiza el sprite
            }
            if(enemigos.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativa
            {
                enemigos.at(i)->setColumnas_fila(80,84); //actualizar el sprite
            }
            enemigos.at(i)->actualizarposicion_izquierda(); //actualiza la posicion
            enemigos.at(i)->actualizarvelocidad(); //actualiza la velocidad
            enemigos.at(i)->setX(enemigos.at(i)->getPosx()); //setea la posicion en x
            enemigos.at(i)->setY(-enemigos.at(i)->getPosy());//setea la posicion en y
        }

        //rebote con el piso
        if(enemigos.at(i)->collidesWithItem(piso)) //condicion para preguntar si colisiono con el piso
        {
            enemigos.at(i)->rebotepiso(); //aplicar rebote
        }
        //rebote con el muro derecho
        if (enemigos.at(i)->collidesWithItem(muroderecho)) //condicion que pregunta si colisiono con el muro derecho
        {
            enemigos.at(i)->setDir(2); //actualizar la direccion de movimiento
        }
        //rebote con el muro izquierdo
        if (enemigos.at(i)->collidesWithItem(muroizquierdo)) //condicion que pregunta si colisiono con el muro izquierdo
        {
            enemigos.at(i)->setDir(1);//actualizar la direccion de movimiento
        }

        if(i==2) //condicion que pregunta si es el tercer enemigo
        {
            enemigos.at(i)->MCU(250,300,150,1,0); //darle movimiento circular uniforme
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        if(i==3) //condicion que pregunta si es el cuarto enemigo
        {
            enemigos.at(i)->MCU(750,300,150,-1,-3.1416); //darle el omvimiento circular uniforme
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        if(i==4) //condicion que pregunta si es el quinto enemigo
        {
            enemigos.at(i)->MAS(500,170,180,1,1); //darle movmiento armonico simple
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        choque(enemigos.at(i)); //funcion que detecta el choque y actualiza las vidas
        actualizar_puntaje(0); //funcion que detecta que el diparo haya acertado a un enemigo y actualiza el puntaje
    }
    if(puntos->getPuntaje()==50)
    {
        nivel2();
    }
    //qDebug()<<"enemigos: "<<c;
    //qDebug()<<"corriendo timer1";
}

void MainWindow::mover_enemigo2()
{
    for(int i=0; i<enemigos.size();i++) //ciclo que lee toda la lista de enemigos
    {
        /* enemmigo 1 y 2 son las bolas que rebotan
         * enemigo 3 y 4 las bolas con movimiento MCU
         * enemigo 5 con el movimiento MAS*/

        //qDebug() <<"velocidad: "<<enemigos.at(i)->getVel();
        //qDebug() <<"velocidadx: "<<enemigos.at(i)->getVelx();
        if(enemigos.at(i)->getVel()>60){enemigos.at(i)->setVel(60);} //condicion para que no supere cierta velocidad
        if(enemigos.at(i)->getVelx()<30){enemigos.at(i)->setVelx(30);} //condicion para que no rebote con una velocidad menor

        //mover a la derecha
        if(enemigos.at(i)->getDir()==1) //condicion para preguntar por la direcion
        {

            if(enemigos.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                enemigos.at(i)->setColumnas_fila(0,0);//actulizar el sprite
            }
            if(enemigos.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativo
            {
                enemigos.at(i)->setColumnas_fila(0,84);// actualiza el sprite
            }
            enemigos.at(i)->actualizarposicion_derecha(); //actualiza la posicion
            enemigos.at(i)->actualizarvelocidad(); //actualiza la velocidad
            enemigos.at(i)->setX(enemigos.at(i)->getPosx()); //setea la posicion en x
            enemigos.at(i)->setY(-enemigos.at(i)->getPosy());//setea la posicion en y
        }

        //mover a la izquierda
        if(enemigos.at(i)->getDir()==2) //condicion para preguntar la direccion
        {
            if(enemigos.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                enemigos.at(i)->setColumnas_fila(80,0); //actualiza el sprite
            }
            if(enemigos.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativa
            {
                enemigos.at(i)->setColumnas_fila(80,84); //actualizar el sprite
            }
            enemigos.at(i)->actualizarposicion_izquierda(); //actualiza la posicion
            enemigos.at(i)->actualizarvelocidad(); //actualiza la velocidad
            enemigos.at(i)->setX(enemigos.at(i)->getPosx()); //setea la posicion en x
            enemigos.at(i)->setY(-enemigos.at(i)->getPosy());//setea la posicion en y
        }

        //rebote con el piso
        if(enemigos.at(i)->collidesWithItem(piso)) //condicion para preguntar si colisiono con el piso
        {
            enemigos.at(i)->rebotepiso(); //aplicar rebote
        }
        //rebote con el muro derecho
        if (enemigos.at(i)->collidesWithItem(muroderecho)) //condicion que pregunta si colisiono con el muro derecho
        {
            enemigos.at(i)->setDir(2); //actualizar la direccion de movimiento
        }
        //rebote con el muro izquierdo
        if (enemigos.at(i)->collidesWithItem(muroizquierdo)) //condicion que pregunta si colisiono con el muro izquierdo
        {
            enemigos.at(i)->setDir(1);//actualizar la direccion de movimiento
        }

        if(i==2) //condicion que pregunta si es el tercer enemigo
        {
            enemigos.at(i)->MCU(300,450,150,-1.5,0); //darle movimiento circular uniforme
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        if(i==3) //condicion que pregunta si es el cuarto enemigo
        {
            enemigos.at(i)->MCU(700,450,150,-1.5,-3.1416); //darle el omvimiento circular uniforme
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        if(i==4) //condicion que pregunta si es el quinto enemigo
        {
            enemigos.at(i)->MAS(500,350,180,1,2); //darle movmiento armonico simple
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        choque(enemigos.at(i)); //funcion que detecta el choque y actualiza las vidas
        actualizar_puntaje(50); //funcion que detecta que el diparo haya acertado a un enemigo y actualiza el puntaje
    }

    if(puntos->getPuntaje()==100)
    {
        nivel3();
    }
    //qDebug()<<"corriendo timer1";

}

void MainWindow::mover_enemigo3()
{
    if(puntos->getPuntaje()==170)
    {
        gano();
    }
    //qDebug()<<"tamaño lista;"<<enemigos.size();
    for(int i=0; i<enemigos.size();i++) //ciclo que lee toda la lista de enemigos
    {
        /* enemmigo 1 y 2 son las bolas que rebotan
         * enemigo 3 y 4 las bolas con movimiento MCU
         * enemigo 5 con el movimiento MAS*/

        //qDebug() <<"velocidad: "<<enemigos.at(i)->getVel();
        //qDebug() <<"velocidadx: "<<enemigos.at(i)->getVelx();
        if(enemigos.at(i)->getVel()>90){enemigos.at(i)->setVel(90);} //condicion para que no supere cierta velocidad
        if(enemigos.at(i)->getVelx()<30){enemigos.at(i)->setVelx(30);} //condicion para que no rebote con una velocidad menor

        //mover a la derecha
        if(enemigos.at(i)->getDir()==1) //condicion para preguntar por la direcion
        {

            if(enemigos.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                enemigos.at(i)->setColumnas_fila(0,0);//actulizar el sprite
            }
            if(enemigos.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativo
            {
                enemigos.at(i)->setColumnas_fila(0,84);// actualiza el sprite
            }
            enemigos.at(i)->actualizarposicion_derecha(); //actualiza la posicion
            enemigos.at(i)->actualizarvelocidad(); //actualiza la velocidad
            enemigos.at(i)->setX(enemigos.at(i)->getPosx()); //setea la posicion en x
            enemigos.at(i)->setY(-enemigos.at(i)->getPosy());//setea la posicion en y
        }

        //mover a la izquierda
        if(enemigos.at(i)->getDir()==2) //condicion para preguntar la direccion
        {
            if(enemigos.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                enemigos.at(i)->setColumnas_fila(80,0); //actualiza el sprite
            }
            if(enemigos.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativa
            {
                enemigos.at(i)->setColumnas_fila(80,84); //actualizar el sprite
            }
            enemigos.at(i)->actualizarposicion_izquierda(); //actualiza la posicion
            enemigos.at(i)->actualizarvelocidad(); //actualiza la velocidad
            enemigos.at(i)->setX(enemigos.at(i)->getPosx()); //setea la posicion en x
            enemigos.at(i)->setY(-enemigos.at(i)->getPosy());//setea la posicion en y
        }

        //rebote con el piso
        if(enemigos.at(i)->collidesWithItem(piso)) //condicion para preguntar si colisiono con el piso
        {
            if(i!=5)
            {
                enemigos.at(i)->rebotepiso(); //aplicar rebote
            }
        }
        //rebote con el muro derecho
        if (enemigos.at(i)->collidesWithItem(muroderecho)) //condicion que pregunta si colisiono con el muro derecho
        {
            enemigos.at(i)->setDir(2); //actualizar la direccion de movimiento
        }
        //rebote con el muro izquierdo
        if (enemigos.at(i)->collidesWithItem(muroizquierdo)) //condicion que pregunta si colisiono con el muro izquierdo
        {
            enemigos.at(i)->setDir(1);//actualizar la direccion de movimiento
        }

        if(i==2) //condicion que pregunta si es el tercer enemigo
        {
            enemigos.at(i)->MCU(300,400,200,-1.5,0); //darle movimiento circular uniforme
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        if(i==3) //condicion que pregunta si es el cuarto enemigo
        {
            enemigos.at(i)->MCU(700,400,200,-1.5,-3.1416); //darle el omvimiento circular uniforme
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        if(i==4) //condicion que pregunta si es el quinto enemigo
        {
            enemigos.at(i)->MAS(500,350,240,1,2); //darle movmiento armonico simple
            enemigos.at(i)->rotar(2); //rotar imagen
        }

        if(i==5) //condicion que pregunta si es el sexto enemigo
        {
            enemigos.at(i)->MAS(250,850,700,0.8,3);
        }

        if(i==6) //condicion que pregunta si es el sexto enemigo
        {
            enemigos.at(i)->MAS(750,850,700,0.8,3);
        }

        choque(enemigos.at(i)); //funcion que detecta el choque y actualiza las vidas
        actualizar_puntaje(100); //funcion que detecta que el diparo haya acertado a un enemigo y actualiza el puntaje
    }
}

void MainWindow::menu()
{
    juego=false; //no se puede jugar
    musica->play(); //reproducir cancion menu
    musica->setVolume(30);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/imagenes/fondo_menu.jpg")); //selecionar fondo
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida2->hide();//esconder boton
    ui->boton_partida3->hide();//esconder boton
    ui->boton_regresar->hide();//esconder boton
    ui->lineEdit1->hide();//esconder boton
    ui->lineEdit2->hide();//esconder boton
    ui->lineEdit3->hide();//esconder boton
    ui->boton_guardarpartida1->hide();//esconder boton
    ui->boton_guardarpartida2->hide();//esconder boton
    ui->boton_guardarpartida3->hide();//esconder boton
    ui->guardar->hide(); //esconder boton
    ui->pausar->hide();//esconder boton
    ui->label_clave->hide(); //esconder boton
    ui->label_usuario->hide(); //esconder boton
    ui->lineEdit_clave->hide(); //esconder boton
    ui->lineEdit_usuario->hide(); //esconder boton
    ui->label_inicio_de_sesion->hide(); //esconder boton
    ui->boton_ingresar->hide(); //esconder boton
    ui->boton_cancelar->hide(); //esconder boton
    ui->boton_eliminar->hide(); //esconder boton
    ui->boton_volveralmenu->hide();
}

void MainWindow::nivel1()
{
    juego = true; //se puede jugar
    musica->stop();
    musica->setMedia(QUrl("qrc:/musica/musica_nivel1.mp3")); //le doy la cancion correspondiente
    ui->graphicsView->setBackgroundBrush(QPixmap(":/imagenes/fondo_nivel1.jpg"));
    ui->pausar->show(); //mostrar boton
    puntos->setPuntaje(0);
    chillin->setVelocidad(10);
    if(partida==0)
    {
        ui->guardar->hide(); //esonder boton
    }
    if(partida!=0)
    {
        ui->guardar->show(); //mostrar boton
    }
    timerenemigo->stop(); //parar el timer del nivel 2
    timerenemigo2->stop();
    timerenemigo3->stop();
    chillin->setPosx(10); //actualizar posicion
    portal->start();

    srand(time(NULL)); // iniciar el time para la variable aleatoria

    lodo1->hide(); //esconder lodo1
    lodo2->hide(); //esconder lodo2
    lodo3->hide(); //esconder lodo3

    //agregar personaje principal
    escena->addItem(chillin); //agregar la chillin

    escena->addItem(pastilla); //agregar pastillas
    pastilla->show();

    Sprite_vidas->setcolumna_fila(0,0); //actualizar columnas y filas
    escena->addItem(Sprite_vidas); //añadir spritevidas a escena

    //enemigo 1
    bola1 = new enemigo(25,-400,81,82,20,0); //creo enemigo 1
    bola1->setImagen(1); //selecionar imagen
    bola1->setScale(0.8);//cambiar tamaño
    enemigos.push_back(bola1); //agrego enemigo 1 a la lista de enemigos
    escena->addItem(enemigos.at(0)); //añado enemigo 1 a la escena

    //enemigo 2
    bola2 = new enemigo(975,-400,81,82,20,180); //creo enemigo 2
    bola2->setImagen(1); //seleccionar la imagen
    bola2->setScale(0.8); //cambiar tamaño
    enemigos.push_back(bola2); //agrego enemigo 2 a la lista de enemigos
    escena->addItem(enemigos.at(1)); //añado enemigo 2 a la escena

    //enemigo 3
    bola3 = new enemigo(500,-350,260,260); //creo enemigo 3
    bola3->setImagen(2); //selecionar imagen
    bola3->setScale(0.4); //cambiar tamaño
    enemigos.push_back(bola3); //agrego enemigo 3 a la lista de enemigos
    escena->addItem(enemigos.at(2)); //añado enemigo 3 a la escena

    //enemigo 4
    bola4 = new enemigo(750,-350,260,260); //creo enemigo 4
    bola4->setImagen(2); //sleecionar imagen
    bola4->setScale(0.4); //cambiar tamaño
    enemigos.push_back(bola4); //agrego enemigo 4 a la lista de enemigos
    escena->addItem(enemigos.at(3)); //añado enemigo 4 a la escena

    //enemigo 5
    bola5 = new enemigo(500,-170,260,260); //creo enemigo 5
    bola5->setImagen(2); //seleccionar imagen
    bola5->setScale(0.4); //cambiar tamaño
    enemigos.push_back(bola5); //agrego enemigo 4 a la lista de enemigos
    escena->addItem(enemigos.at(4)); //añado enemigo 4 a la escena

    //piso
    //escena->addItem(piso); //agregar piso

    //muro derecho
    //escena->addItem(muroderecho); //agregar muro derecho

    //muro izquierdo
    //escena->addItem(muroizquierdo); //agregar muro izquierdo

    //salud
    escena->addItem(vidas); //añadir las vidas a la escena

    //puntaje
    escena->addItem(puntos); //añadir el puntaje a la escena

    //probabilidad
    probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); // dar posicion, siempre al lado de el personaje principal
    escena->addItem(probabilidad); //añadir probabilidad a la escena

    //timer para los enemigos
    connect(timerenemigo,SIGNAL(timeout()),this,SLOT(mover_enemigo())); //conecto el timer al movimiento del enemigo
    //timerenemigo->start(10); //iniciar timer
}

void MainWindow::nivel2()
{
    ui->pausar->setStyleSheet("border-image:url(:/imagenes/pausa.png);");
    qDebug()<<"error aqui 1";

    musica->stop();
    musica->setMedia(QUrl("qrc:/musica/musica_nivel2.mp3"));
    juego = true; //activar la jugabilidad
    ui->graphicsView->setBackgroundBrush(QPixmap(":/imagenes/fondo_nivel2.jpg"));
    ui->guardar->show(); //mostrar boton
    puntos->setPuntaje(50);

    if(partida==0)
    {
        ui->guardar->hide(); //esonder boton
    }
    if(partida!=0)
    {
        ui->guardar->show(); //mostrar boton
    }
    timerenemigo->stop(); //parar el timer del nivel 2
    timerenemigo2->stop();
    timerenemigo3->stop();

    srand(time(NULL)); // iniciar el time para la variable aleatoria

    enemigos.clear(); //vacias lista de enemigos

    if(!chillin->isActive()) //condicion que pregunta si el cuerpo ya esta en escena
    {
        escena->addItem(chillin); //agregar la chillin
    }
    chillin->setPosx(10); //actualizar posicion
    portal->start();

    if(!Sprite_vidas->isActive()) //condicion que pregunta si el sprite vidas ya esta en escena
    {
        escena->addItem(Sprite_vidas);
        Sprite_vidas->setcolumna_fila(0,0);
    }

    if(!vidas->isActive()) //condicion que pregunta si vidas ya esta en escena
    {
        escena->addItem(vidas);
    }

    if(!puntos->isActive()) //condicion que pregunta si los puntos ya estan en escena
    {
        escena->addItem(puntos);
    }


    pastilla->show();

    if(!probabilidad->isActive())
    {
        escena->addItem(probabilidad);
    }
    probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); // dar posicion, siempre al lado de el personaje principal

    //enemigo 6
    bola6 = new enemigo(25,-450,81,82,30,0); //creo enemigo 1
    bola6->setImagen(1); //selecionar imagen
    bola6->setScale(0.8);//cambiar tamaño
    enemigos.push_back(bola6); //agrego enemigo 1 a la lista de enemigos
    escena->addItem(enemigos.at(0)); //añado enemigo 1 a la escena

    //enemigo 7
    bola7 = new enemigo(975,-450,81,82,30,180); //creo enemigo 6
    bola7->setImagen(1); //seleccionar la imagen
    bola7->setScale(0.8); //cambiar tamaño
    enemigos.push_back(bola7); //agrego enemigo 6 a la lista de enemigos
    escena->addItem(enemigos.at(1)); //añado enemigo 6 a la escena

    //enemigo 8
    bola8 = new enemigo(250,-450,260,260); //creo enemigo 3
    bola8->setImagen(2); //selecionar imagen
    bola8->setScale(0.3); //cambiar tamaño
    enemigos.push_back(bola8); //agrego enemigo 3 a la lista de enemigos
    escena->addItem(enemigos.at(2)); //añado enemigo 3 a la escena

    //enemigo 9
    bola9 = new enemigo(750,-450,260,260); //creo enemigo 4
    bola9->setImagen(2); //sleecionar imagen
    bola9->setScale(0.3); //cambiar tamaño
    enemigos.push_back(bola9); //agrego enemigo 4 a la lista de enemigos
    escena->addItem(enemigos.at(3)); //añado enemigo 4 a la escena

    //enemigo 10
    bola10 = new enemigo(500,-170,260,260); //creo enemigo 5
    bola10->setImagen(2); //seleccionar imagen
    bola10->setScale(0.6); //cambiar tamaño
    enemigos.push_back(bola10); //agrego enemigo 4 a la lista de enemigos
    escena->addItem(enemigos.at(4)); //añado enemigo 4 a la escena

    lodo1->show();
    lodo2->show();
    lodo3->show();

    connect(timerenemigo2,SIGNAL(timeout()),this,SLOT(mover_enemigo2())); //conecto el timer al movimiento del enemigo

    actualizar_puntaje(50); //funcion que detecta que el diparo haya acertado a un enemigo y actualiza el puntaje

}

void MainWindow::nivel3()
{
    ui->pausar->setStyleSheet("border-image:url(:/imagenes/pausa.png);");
    timerenemigo2->stop();
    juego = true;

    chillin->setVelocidad(10);
    musica->stop();
    musica->setMedia(QUrl("qrc:/musica/musica_nivel3.mp3"));

    lodo1->hide(); //esconder lodo1
    lodo2->hide(); //esconder lodo2
    lodo3->hide(); //esconder lodo3

    ui->graphicsView->setBackgroundBrush(QPixmap(":/imagenes/fondo_nivel3.jpg"));
    ui->guardar->show(); //mostrar boton

    puntos->setPuntaje(100);

    if(partida==0)
    {
        ui->guardar->hide(); //esonder boton
    }
    if(partida!=0)
    {
        ui->guardar->show(); //mostrar boton
    }
    timerenemigo->stop(); //parar el timer del nivel 2
    timerenemigo2->stop();
    timerenemigo3->stop();
    srand(time(NULL)); // iniciar el time para la variable aleatoria

    enemigos.clear(); //vaciar lista de enemigos

    if(!chillin->isActive()) //condicion que pregunta si el cuerpo principal ya esta en escena
    {
        escena->addItem(chillin); //agregar la chillin
    }
    chillin->setPosx(10); //actualizar posicion
    portal->start();

    if(!Sprite_vidas->isActive()) //condicion que pregunta si Sprite vidas ya esta en escena
    {
        escena->addItem(Sprite_vidas);
        Sprite_vidas->setcolumna_fila(0,0);
    }

    if(!vidas->isActive()) //condicion que pregunta si vida ya esta en escena
    {
        escena->addItem(vidas);
    }

    if(!puntos->isActive()) //condicion que pregunta si puntos ya esta en escena
    {
        escena->addItem(puntos);
    }

    pastilla->show();

    if(!probabilidad->isActive())
    {
        escena->addItem(probabilidad);
    }

    //enemigo 11
    bola11 = new enemigo(25,-200,81,82,30,0); //creo enemigo 11
    bola11->setImagen(4); //selecionar imagen
    bola11->setScale(0.6);//cambiar tamaño
    enemigos.push_back(bola11); //agrego enemigo 11 a la lista de enemigos
    escena->addItem(enemigos.at(0)); //añado enemigo 11 a la escena

    //enemigo 12
    bola12 = new enemigo(975,-200,81,82,30,180); //creo enemigo 12
    bola12->setImagen(4); //seleccionar la imagen
    bola12->setScale(0.6); //cambiar tamaño
    enemigos.push_back(bola12); //agrego enemigo 12 a la lista de enemigos
    escena->addItem(enemigos.at(1)); //añado enemigo 12 a la escena

    //enemigo 13
    bola13 = new enemigo(500,-350,260,260); //creo enemigo 13
    bola13->setImagen(3); //selecionar imagen
    bola13->setScale(0.2); //cambiar tamaño
    enemigos.push_back(bola13); //agrego enemigo 13 a la lista de enemigos
    escena->addItem(enemigos.at(2)); //añado enemigo 13 a la escena

    //enemigo 14
    bola14 = new enemigo(750,-350,260,260); //creo enemigo 14
    bola14->setImagen(3); //sleecionar imagen
    bola14->setScale(0.2); //cambiar tamaño
    enemigos.push_back(bola14); //agrego enemigo 14 a la lista de enemigos
    escena->addItem(enemigos.at(3)); //añado enemigo 14 a la escena

    //enemigo 15
    bola15 = new enemigo(500,-170,260,260); //creo enemigo 15
    bola15->setImagen(3); //seleccionar imagen
    bola15->setScale(0.2); //cambiar tamaño
    enemigos.push_back(bola15); //agrego enemigo 4 a la lista de enemigos
    escena->addItem(enemigos.at(4)); //añado enemigo 4 a la escena

    //enemigo 16
    bola16 = new enemigo(250,-170,260,260); //creo enemigo 16
    bola16->setImagen(5); //seleccionar imagen
    bola16->setScale(0.2); //cambiar tamaño
    enemigos.push_back(bola16); //agrego enemigo 16 a la lista de enemigos
    escena->addItem(enemigos.at(5)); //añado enemigo 16 a la escena

    //enemigo 17
    bola17 = new enemigo(750,-170,260,260); //creo enemigo 17
    bola17->setImagen(5); //seleccionar imagen
    bola17->setScale(0.2); //cambiar tamaño
    enemigos.push_back(bola17); //agrego enemigo 17 a la lista de enemigos
    escena->addItem(enemigos.at(6)); //añado enemigo 17 a la escena

    probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); // dar posicion, siempre al lado de el personaje principal

    connect(timerenemigo3,SIGNAL(timeout()),this,SLOT(mover_enemigo3())); //conecto el timer al movimiento del enemigo

    actualizar_puntaje(100); //funcion que detecta que el diparo haya acertado a un enemigo y actualiza el puntaje

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(juego) //condicion que pregunta si se puede jugar o no
    {
        //tecla D
        bool D=((event->key()==Qt::Key_D && timerenemigo->isActive()) || (event->key()==Qt::Key_D && timerenemigo2->isActive()) || ((event->key()==Qt::Key_D && timerenemigo3->isActive())));
        if(D) //condicion que pregunta si la tecla es la D y el timerEnemigos esta activo
        {
            if(chillin->getPosx()<970) //condicion que pregunta si el personaje principal esta dentro de la pantalla visible
            {
                if(lodo1->isVisible()&&lodo2->isVisible()&&lodo3->isVisible()) //condicion que pregunta si el lodo es visible
                {
                    if(chillin->collidesWithItem(lodo1) || chillin->collidesWithItem(lodo2) || chillin->collidesWithItem(lodo3)) //condicion que pregunta si esta chocando con algun lodo
                    {
                        chillin->setVelocidad(5); //actualizar velocidad

                    }
                    if(!chillin->collidesWithItem(lodo1) && !chillin->collidesWithItem(lodo2) && !chillin->collidesWithItem(lodo3))
                    {
                        chillin->setVelocidad(10); //actualizar velocidad
                    }
                }
                chillin->mover_derecha(); //mover hacia la derecha
                probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); // dar posicion, siempre al lado de el personaje principal
            }
        }

        //tecla A
        bool A=((event->key()==Qt::Key_A && timerenemigo->isActive()) || (event->key()==Qt::Key_A && timerenemigo2->isActive()) || (event->key()==Qt::Key_A && timerenemigo3->isActive()));
        if(A) //condicion que pregunta si la tecla es la A y el timerEnemigos esta activo
        {
            if(chillin->getPosx()>25) //condicion que pregunta si el personaje principal esta dentro de la pantalla visible
            {
                if(lodo1->isVisible()&&lodo2->isVisible()&&lodo3->isVisible())
                {
                    if(chillin->collidesWithItem(lodo1) || chillin->collidesWithItem(lodo2) || chillin->collidesWithItem(lodo3))
                    {
                        chillin->setVelocidad(5);
                    }
                    if(!chillin->collidesWithItem(lodo1) && !chillin->collidesWithItem(lodo2) && !chillin->collidesWithItem(lodo3))
                    {
                        chillin->setVelocidad(10);
                    }
                }

                chillin->mover_izquierda();//mover hacia la izquierda
                probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); // dar posicion, siempre al lado de el personaje principal
            }
        }

        //tecla W
        bool W=((event->key()==Qt::Key_W && timerenemigo->isActive()) || (event->key()==Qt::Key_W && timerenemigo2->isActive()) ||(event->key()==Qt::Key_W && timerenemigo3->isActive()));
        if(W) //condicion que pregunta si la tecla es la espacio y el timerEnemigos esta activo
        {
            chillin->Disparo(); //actualizar sprite
            balas * bala = new balas(); //crear variable bala
            bala->setPos(chillin->getPosx()-5,chillin->getPosy()-50); //darle la posicion del personaje principal
            bala->setScale(0.6); //cambiar tamaño
            escena->addItem(bala); //añadir bala a la escena
            disparo_bien_o_mal(); //revisar si el disparo salio bien o mal
        }

        if(event->key()==Qt::Key_Space) //condicion que pregunta si la tecla que se oprimio fue shift
        {
            //qDebug()<<puntos->getPuntaje();
            if(puntos->getPuntaje()<50)
            {
                timerenemigo->start(10); //iniciar juego
                musica->play(); //reproducir cancion nivel1
                ui->pausar->setFocus(); //foco en el boton pausa
            }
            if(puntos->getPuntaje()>=50&&puntos->getPuntaje()<100)
            {
                timerenemigo2->start(10); //iniciar nivel2
                musica->play(); //reproducir cancion nivel2
                ui->pausar->setFocus(); //foco boton pausa
            }
            if(puntos->getPuntaje()>=100)
            {
                timerenemigo3->start(10); //iniciar nivel3
                musica->play();
                ui->pausar->setFocus();// foco boton pausa
            }
        }
    }
}

void MainWindow::choque(enemigo* bola)
{
    if(chillin->collidesWithItem(bola)&&bola->isVisible()) //condicion que pregunta si hubo colision con una bola amistosa
    {

        vidas->disminuir_salud(); //disminuye las vidas
        if(vidas->getVidas()==2) //condicion que pregunta si las vidas son diferentes de 0
        {
            corte->play();
            triturado->start(); //reproducir gif
            chillin->setPosx(10); //resetea la posicion de la chillin
            portal->start();
            Sprite_vidas->setcolumna_fila(50,0); //actualizar sprite
            probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); //da la posision de la probabilidad siempre al lado de el personaje principal
        }
        if(vidas->getVidas()==1) //condicion que pregunta si las vidas son diferentes de 0
        {
            corte->play();
            triturado->start();
            chillin->setPosx(10); //resetea la posicion de la chillin
            portal->start();
            Sprite_vidas->setcolumna_fila(0,50); //actualziar sprite
            probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); //da la posision de la probabilidad siempre al lado de el personaje principal
        }

        if(vidas->getVidas()==0) //condicion que pregunta si las vidas son iguales a 0
        {
            corte->play();
            game_over(); //terminar juego
        }
    }

    if(pastilla->collidesWithItem(chillin)&&pastilla->isVisible())
    {
        probabilidad->setTope(100);
        pastilla->hide();
    }
}

void MainWindow::actualizar_puntaje(int p)
{
    for(int i=0;i<enemigos.size();i++) //ciclo que recorre la lista de los enemigos
    {
        if(!enemigos.at(i)->isVisible()) //condicion que pregunta si el enemigo no es visible
        {
            p=p+10; //suma 10 a la variable ps
        }
    }
    puntos->aumentar_puntaje(p); //da el valor de p a los puntos
}

void MainWindow::disparo_bien_o_mal()
{
    probabilidad->calcular_numaleatorio(); //calculo el numero aleatorio
    probabilidad->actualizar_Probabilidad(); //actualizo en pantalla el valor de la probabilidad que tiene el jugador de que el disparo le salga bien
    if(probabilidad->disparo_mal()) //condicion que pregunta si el disparo salio bien
    {
        vidas->disminuir_salud(); //disminuye las vidas

        if(vidas->getVidas()==2) //condicion que pregunta si las vidas son diferentes de 0
        {
            fuego->play();
            quemado->start(); //reproducir
            chillin->setPosx(10); //resetea la posicion de la chillin
            portal->start();
            Sprite_vidas->setcolumna_fila(50,0); //actualizar sprite
            probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); //da la posision de la probabilidad siempre al lado de el personaje principal
        }
        if(vidas->getVidas()==1) //condicion que pregunta si las vidas son diferentes de 0
        {
            fuego->play(); //reproducir cancion
            quemado->start(); //reproduir gif
            chillin->setPosx(10); //resetea la posicion de la chillin
            portal->start();
            Sprite_vidas->setcolumna_fila(0,50); //actualizar sprite
            probabilidad->setPos(chillin->getPosx()+25,chillin->getPosy()-50); //da la posision de la probabilidad siempre al lado de el personaje principal
        }

        if(vidas->getVidas()==0) //condicion que pregunta si las vidas son iguales a 0
        {
            fuego->play(); //reproducir cancion
            game_over(); //terminar juego
        }
    }
}

void MainWindow::game_over()
{
    juego=false; //no hay jugabilidad
    musica->stop();
    escena->removeItem(chillin); //elimina el personaje principal
    for(int i=0;i<enemigos.size();i++) //ciclo que recorre toda la lista de enemigos
    {
        if(enemigos.at(i)->isVisible()) //condicion que pregunta si un enemigo es visible
        {
            escena->removeItem(enemigos.at(i)); //remueve los enemigos visibles
        }
    }
    escena->removeItem(puntos); //remueve el puntaje
    escena->removeItem(probabilidad); //remueve la probabilidad
    escena->removeItem(vidas); //remueve las vidas
    escena->removeItem(Sprite_vidas);
    escena->removeItem(pastilla);
    ui->pausar->hide(); //esconder boton
    timerenemigo->stop(); //parar timer de enemigos
    timerenemigo2->stop(); //parar timer de enemigos2
    timerenemigo3->stop(); //parar timer de enemigos3
    ui->guardar->hide(); //esconder boton
    ui->boton_volveralmenu->show();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/imagenes/gameover.jpg"));
}

void MainWindow::borrar_todos_botones()
{
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida2->hide();//esconder boton
    ui->boton_partida3->hide();//esconder boton
    ui->boton_regresar->hide();//esconder boton
    ui->boton_nuevapartida->hide();//esconder boton
    ui->boton_cargarpartida->hide();//esconder boton
    ui->pausar->hide();//esconder boton
    ui->lineEdit1->hide();//esconder boton
    ui->lineEdit2->hide();//esconder boton
    ui->lineEdit3->hide();//esconder boton
    ui->guardar->hide(); //esconder boton
    ui->lineEdit_clave->hide(); //esconder boton
    ui->lineEdit_usuario->hide(); //esconder boton
    ui->label_clave->hide(); //esconder boton
    ui->label_usuario->hide(); //esconder boton
    ui->label_inicio_de_sesion->hide(); //esconder boton
    ui->boton_ingresar->hide(); //esconder boton
    ui->boton_cancelar->hide(); //esconder boton
    ui->boton_eliminar->hide(); //esconder boton
}

void MainWindow::escribir_partidasguardadas(QString texto,int p_)
{
    ui->lineEdit1->show(); //mostrar boton
    ui->lineEdit2->show();//mostrar boton
    ui->lineEdit3->show();//mostrar boton

    QFile archivo(texto); //leer el archivo
    if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }
    QTextStream in(&archivo); //crear un flujo de lectura
    texto=in.readAll(); //leer todo el archivo
    QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de String y agregarle los valores, cada valor viene dado separado de una coma
    archivo.close(); //cerrar archivo
    int nivel=0; //iniciar variable nivel
    name.clear();
    pass.clear();
    for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
    {
        if(i==0){vidas->setVidas(lista_archivo.at(0).toInt());} //dar el valor de vidas
        if(i==1){probabilidad->setTope(lista_archivo.at(1).toInt());} //dar el valor de probabilidad
        if(i==2){nivel=lista_archivo.at(2).toInt();} //dar el valor del nivel
        if(i==3){name.append(lista_archivo.at(i));} //guardar el nombre
        if(i==4){pass.append(lista_archivo.at(i));} //guardar la contraseña
    }

    if(name=="vacio")
    {
        if(pass=="vacio")
        {
            if(p_==1)
            {
                ui->lineEdit1->setText("<VACIO>"); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit1->setDisabled(true); //desabilitar escritura
                ui->lineEdit1->setFont(QFont("Gill Sans Ultra Bold Condensed",10)); //cambiar formto a la letra
            }

            if(p_==2)
            {
                ui->lineEdit2->setText("<VACIO>"); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit2->setDisabled(true); //desabilitar escritura
                ui->lineEdit2->setFont(QFont("Gill Sans Ultra Bold Condensed",10)); //cambiar formto a la letra
            }
            if(p_==3)
            {
                ui->lineEdit3->setText("<VACIO>"); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit3->setDisabled(true); //desabilitar escritura
                ui->lineEdit3->setFont(QFont("Gill Sans Ultra Bold Condensed",10)); //cambiar formto a la letra
            }
        }
    }

    if(name!="vacio")
    {
        if(pass!="vacio")
        {
            QString Texto1="Nivel: "; //crear variable string y añadir Nivel
            Texto1.append(lista_archivo.at(2)); //agregar el nivel
            Texto1.append(" Vidas: "); //agreagr Vidas:
            Texto1.append(lista_archivo.at(0)); //agregar vidas
            Texto1.append(" PROB :"); //agregar PROB;
            Texto1.append(lista_archivo.at(1)); //agregrar puntos
            Texto1.append("%"); //agregar %


            if(p_==1) //condicion que pregunta si la partida abierta fue la 1
            {
                ui->lineEdit1->setText(Texto1); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit1->setDisabled(true); //desabilitar escritura
                ui->lineEdit1->setFont(QFont("Gill Sans Ultra Bold Condensed",10)); //cambiar formto a la letra
            }
            if(p_==2) //condicion que pregunta si la partida abierta fue la 2
            {
                ui->lineEdit2->setText(Texto1); //escribir el texto completo de la partida 2 guardada
                ui->lineEdit2->setDisabled(true); //desabilitar escritura
                ui->lineEdit2->setFont(QFont("Gill Sans Ultra Bold Condensed",10)); //cambiar formto a la letra
            }
            if(p_==3) //condicion que pregunta si la partida abierta fue la 3
            {
                ui->lineEdit3->setText(Texto1); //escribir el texto completo de la partida 3 guardada
                ui->lineEdit3->setDisabled(true); //desabilitar escritura
                ui->lineEdit3->setFont(QFont("Gill Sans Ultra Bold Condensed",10)); //cambiar formto a la letra
            }
        }
    }

}

int MainWindow::leer_partidarguardadas(QString texto)
{
    QFile archivo(texto); //leer el archivo
    if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }
    QTextStream in(&archivo); //crear un flujo de lectura
    texto=in.readAll(); //leer todo el archivo
    QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
    archivo.close(); //cerrar el archivo
    int nivel=0; //iniciari variable nivel
    for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
    {
        if(i==0){vidas->setVidas(lista_archivo.at(0).toInt());} //dar el valor de vidas
        if(i==1){probabilidad->setTope(lista_archivo.at(1).toInt());} //dar el valor de probabilidad
        if(i==2){nivel=lista_archivo.at(2).toInt();} //dar el valor del nivel
    }

    return nivel; //regresar el nivel
}

bool MainWindow::revisar_usuario_clave(QString texto)
{
    QFile archivo(texto); //leer el archivo
    if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }
    QTextStream in(&archivo); //crear un flujo de lectura
    texto=in.readAll(); //leer todo el archivo
    QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
    archivo.close(); //cerrar el archivo

    name.clear();
    pass.clear();

    for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
    {
        if(i==3) //condicion que pregunta si es el nombre de usuario
        {
            name.append(lista_archivo.at(i));//guardar usuario en variable
        }
        if(i==4) //condicion que pregunta si es la clave
        {
            pass.append(lista_archivo.at(i));//guardar clave en variable
        }
    }

    QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
    QString clave=NULL; //variable que me guarda la clave ingresada
    usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
    clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit

    if(clave==pass) //condicion que pregunta si la clave ingresada es igual a la guardada
    {
        if(usuario==name)//condicion que pregunta si el usuario ingresado es igual al guardado
        {
            return true; //regresa true
        }

        return false; //regresa false
    }
    else
    {
        return false; //regresa false
    }
}

void MainWindow::gano()
{
    timerenemigo3->stop(); //parar timer enemigos 3
    juego=false; //no hay jugabilidad
    musica->stop();
    escena->removeItem(chillin); //elimina el personaje principal
    for(int i=0;i<enemigos.size();i++) //ciclo que recorre toda la lista de enemigos
    {
        if(enemigos.at(i)->isVisible()) //condicion que pregunta si un enemigo es visible
        {
            escena->removeItem(enemigos.at(i)); //remueve los enemigos visibles
        }
    }
    escena->removeItem(puntos); //remueve el puntaje
    escena->removeItem(probabilidad); //remueve la probabilidad
    escena->removeItem(vidas); //remueve las vidas
    escena->removeItem(Sprite_vidas); //remueve el sprite vidas
    pastilla->hide(); //esconder la pastilla
    ui->guardar->hide(); //esconder boton
    ui->pausar->hide(); //esconder boton
    ui->boton_volveralmenu->show();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/imagenes/well_done.jpg"));
}

void MainWindow::on_boton_nuevapartida_clicked()
{
    musica->stop(); //para cancion menu
    chillin->setPosx(10);
    vidas->setVidas(3); //dar 3 vidas
    probabilidad->setTope(100); //dar un 100% de probabilidad
    puntos->setPuntaje(0); //dar un puntaje de 0
    borrar_todos_botones(); // borrar todos los botones
    ui->pausar->show(); //mostrar boton pausa
    partida=0;
    nivel1(); // ir a funcion nivel1
}

void MainWindow::on_boton_cargarpartida_clicked()
{
    ui->boton_cargarpartida->hide(); //esconde boton cargar partida
    ui->boton_nuevapartida->hide(); //esconde boton nueeva partida
    ui->boton_partida1->show(); //muestra boton partida1
    ui->boton_partida2->show(); //muestra boton partida2
    ui->boton_partida3->show(); //muestra boton partida3
    ui->boton_regresar->show(); //muestra boton regresar
    escribir_partidasguardadas("D:/partidas/partida1.txt",1); //escribe en pantalla los datos guardados de la partida 1
    escribir_partidasguardadas("D:/partidas/partida2.txt",2); //escribe en pantalla los datos guardados de la partida 2
    escribir_partidasguardadas("D:/partidas/partida3.txt",3); //escribe en pantalla los datos guardados de la partida 3
}

void MainWindow::on_boton_regresar_clicked()
{
    ui->boton_nuevapartida->show(); //mostrar boton nueva partida
    ui->boton_cargarpartida->show(); //mostar boton cargar partida
    ui->lineEdit_usuario->setText("");
    ui->lineEdit_clave->setText("");
    menu(); //ir a funcion menu
}

void MainWindow::on_boton_partida1_clicked()
{
    partida=1; //partida 1
    ui->boton_partida2->hide(); //esconder boton
    ui->boton_partida3->hide(); //esconder boton
    ui->lineEdit2->hide(); //esconder boton
    ui->lineEdit3->hide(); //esconder boton
    ui->lineEdit_clave->show(); //mostrar boton
    ui->lineEdit_usuario->show(); //mostrar boton
    ui->label_clave->show(); //mostrar boton
    ui->label_usuario->show(); //mostrar boton
    ui->label_inicio_de_sesion->show(); //mostrar boton
    ui->boton_ingresar->show(); //mostrar boton
    ui->boton_cancelar->show(); //mostrar boton
    ui->boton_eliminar->show(); //mostrar boton
}

void MainWindow::on_boton_partida2_clicked()
{
    partida = 2; //partida 2
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida3->hide(); //esconder boton
    ui->lineEdit1->hide(); //esconder boton
    ui->lineEdit3->hide(); //esconder boton
    ui->lineEdit_clave->show(); //mostrar boton
    ui->lineEdit_usuario->show(); //mostrar boton
    ui->label_clave->show(); //mostrar boton
    ui->label_usuario->show(); //mostrar boton
    ui->label_inicio_de_sesion->show(); //mostrar boton
    ui->boton_ingresar->show(); //mostrar boton
    ui->boton_cancelar->show(); //mostrar boton
    ui->boton_eliminar->show(); //mostrar boton
}

void MainWindow::on_boton_partida3_clicked()
{
    partida = 3; //partida 3
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida2->hide(); //esconder boton
    ui->lineEdit1->hide(); //esconder boton
    ui->lineEdit2->hide(); //esconder boton
    ui->lineEdit_clave->show(); //mostrar boton
    ui->lineEdit_usuario->show(); //mostrar boton
    ui->label_clave->show(); //mostrar boton
    ui->label_usuario->show(); //mostrar boton
    ui->label_inicio_de_sesion->show(); //mostrar boton
    ui->boton_ingresar->show(); //mostrar boton
    ui->boton_cancelar->show(); //mostrar boton
    ui->boton_eliminar->show(); //mostrar boton
}

void MainWindow::on_pausar_clicked()
{
    if(puntos->getPuntaje()<50)
    {
        if(timerenemigo->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerenemigo->stop(); //parar el timer
            musica->pause(); //pausar cancion
            juego = false; //para jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/imagenes/play.png);");
            ui->boton_volveralmenu->show();
        }

        else if(!timerenemigo->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerenemigo->start(10); //iniciar el timer
            musica->play(); //reproducir
            juego = true; //habilitar la jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/imagenes/pausa.png);");
            ui->boton_volveralmenu->hide();
        }
    }

    if(puntos->getPuntaje()>=50&&puntos->getPuntaje()<100)
    {
        if(timerenemigo2->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerenemigo2->stop(); //parar el timer
            musica->pause(); //pasuar cancion
            juego = false; //para jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/imagenes/play.png);");
            ui->boton_volveralmenu->show();
        }

        else if(!timerenemigo2->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerenemigo2->start(10); //iniciar el timer
            musica->play(); //reproducir cancion
            juego = true; //habilitar la jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/imagenes/pausa.png);");
            ui->boton_volveralmenu->hide();
        }
    }

    if(puntos->getPuntaje()>=100)
    {
        if(timerenemigo3->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerenemigo3->stop(); //parar el timer
            musica->pause();
            juego = false; //para jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/imagenes/play.png);");
            ui->boton_volveralmenu->show();
        }

        else if(!timerenemigo3->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerenemigo3->start(10); //iniciar el timer
            musica->play();
            juego = true; //habilitar la jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/imagenes/pausa.png);");
            ui->boton_volveralmenu->hide();
        }
    }

}

void MainWindow::on_guardar_clicked()
{
    timerenemigo->stop(); //parar timer
    timerenemigo2->stop(); //parar timer
    timerenemigo3->stop(); //parar timer
//    escena->addItem(escogerpartida);
//    escogerpartida->texto("Donde desea guardar partida?");
//    ui->boton_guardarpartida1->show(); //mostrar boton
//    ui->boton_guardarpartida2->show(); //mostrar boton
//    ui->boton_guardarpartida3->show(); //mostrar boton

    if(partida==1) //condicion que pregunta si la partida es la 1
    {
        int nivel=0; //variable que me controla el nivel
        if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
        {
            nivel=1; //nivel 1
        }
        if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
        {
            nivel=2; //nivel 2
        }
        if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
        {
            nivel=3; //nivel 3
        }

        QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
        QString p=QString::number(probabilidad->getTope()); //convertir la probabilidad a string
        QString n=QString::number(nivel); //convertir el nivel a string
        QString texto; //variable string
        texto.append(v); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append(p); //agregar probabilidad
        texto.append(","); //agregar coma
        texto.append(n); //agregar nivel
        texto.append(","); //agregar coma
        texto.append(name); //agregar usuario
        texto.append(","); //agregar coma
        texto.append(pass); //agregar contraseña

        QFile archivo("D:/partidas/partida1.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
        ui->pausar->setFocus(); //dar el focus a el boton pausa
    }

    if(partida==2) //condicion que pregunta si la partida es la 2
    {
        int nivel=0; //variable que me controla el nivel
        if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
        {
            nivel=1; //nivel 1
        }
        if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
        {
            nivel=2; //nivel 2
        }
        if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
        {
            nivel=3; //nivel 3
        }

        QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
        QString p=QString::number(probabilidad->getTope()); //convertir la probabilidad a string
        QString n=QString::number(nivel); //convertir el nivel a string
        QString texto; //variable string
        texto.append(v); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append(p); //agregar probabilidad
        texto.append(","); //agregar coma
        texto.append(n); //agregar nivel
        texto.append(","); //agregar coma
        texto.append(name); //agregar usuario
        texto.append(","); //agregar coma
        texto.append(pass); //agregar contraseña

        QFile archivo("D:/partidas/partida2.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
        ui->pausar->setFocus(); //dar el focus a el boton pausa
    }

    if(partida==3) //condicion que pregunta si la partida es la 3
    {
        int nivel=0; //variable que me controla el nivel
        if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
        {
            nivel=1; //nivel 1
        }
        if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
        {
            nivel=2; //nivel 2
        }
        if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
        {
            nivel=3; //nivel 3
        }

        QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
        QString p=QString::number(probabilidad->getTope()); //convertir la probabilidad a string
        QString n=QString::number(nivel); //convertir el nivel a string
        QString texto; //variable string
        texto.append(v); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append(p); //agregar probabilidad
        texto.append(","); //agregar coma
        texto.append(n); //agregar nivel
        texto.append(","); //agregar coma
        texto.append(name); //agregar usuario
        texto.append(","); //agregar coma
        texto.append(pass); //agregar contraseña

        QFile archivo("D:/partidas/partida3.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
        ui->pausar->setFocus(); //dar el focus a el boton pausa
    }
}

void MainWindow::on_boton_guardarpartida1_clicked()
{
    int nivel=0; //variable que me controla el nivel
    if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
    {
        nivel=1; //nivel 1
    }
    if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
    {
        nivel=2; //nivel 2
    }
    if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
    {
        nivel=3; //nivel 3
    }

    QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
    QString p=QString::number(probabilidad->getTope()); //convertir la probabilidad a string
    QString n=QString::number(nivel); //convertir el nivel a string
    QString texto; //variable string
    texto.append(v); //agregar las vidas
    texto.append(","); //agregar coma
    texto.append(p); //agregar probabilidad
    texto.append(","); //agregar coma
    texto.append(n); //agregar nivel

    QFile archivo("D:/partidas/partida1.txt"); //leer el archivo
    if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }

    QTextStream out(&archivo); //flujo de escritura
    out<<texto; //escribir sobre el archivo
    archivo.flush(); //cerrar procesos sobre archivo
    archivo.close(); //cerrar archivo

    ui->boton_guardarpartida1->hide(); //esconder boton
    ui->boton_guardarpartida2->hide(); //esconder boton
    ui->boton_guardarpartida3->hide(); //esconder boton
    escogerpartida->hide(); //esconder texto
    QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
    ui->pausar->setFocus(); //dar el focus a el boton pausa
}

void MainWindow::on_boton_guardarpartida2_clicked()
{
    int nivel=0; //variable que me controla el nivel
    if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
    {
        nivel=1; //nivel 1
    }
    if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
    {
        nivel=2; //nivel 2
    }
    if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
    {
        nivel=3; //nivel 3
    }

    QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
    QString p=QString::number(probabilidad->getTope()); //convertir la probabilidad a string
    QString n=QString::number(nivel); //convertir el nivel a string
    QString texto; //variable string
    texto.append(v); //agregar las vidas
    texto.append(","); //agregar coma
    texto.append(p); //agregar probabilidad
    texto.append(","); //agregar coma
    texto.append(n); //agregar nivel

    QFile archivo("D:/partidas/partida2.txt"); //leer el archivo
    if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }

    QTextStream out(&archivo); //flujo de escritura
    out<<texto; //escribir sobre el archivo
    archivo.flush(); //cerrar procesos sobre archivo
    archivo.close(); //cerrar archivo

    ui->boton_guardarpartida1->hide(); //esconder boton
    ui->boton_guardarpartida2->hide(); //esconder boton
    ui->boton_guardarpartida3->hide(); //esconder boton
    escogerpartida->hide(); //esconder texto
    QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
    ui->pausar->setFocus(); //dar el focus a el boton pausa
}

void MainWindow::on_boton_guardarpartida3_clicked()
{
    int nivel=0; //variable que me controla el nivel
    if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
    {
        nivel=1; //nivel 1
    }
    if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
    {
        nivel=2; //nivel 2
    }
    if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
    {
        nivel=3; //nivel 3
    }

    QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
    QString p=QString::number(probabilidad->getTope()); //convertir la probabilidad a string
    QString n=QString::number(nivel); //convertir el nivel a string
    QString texto; //variable string
    texto.append(v); //agregar las vidas
    texto.append(","); //agregar coma
    texto.append(p); //agregar probabilidad
    texto.append(","); //agregar coma
    texto.append(n); //agregar nivel

    QFile archivo("D:/partidas/partida3.txt"); //leer el archivo
    if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }

    QTextStream out(&archivo); //flujo de escritura
    out<<texto; //escribir sobre el archivo
    archivo.flush(); //cerrar procesos sobre archivo
    archivo.close(); //cerrar archivo

    ui->boton_guardarpartida1->hide(); //esconder boton
    ui->boton_guardarpartida2->hide(); //esconder boton
    ui->boton_guardarpartida3->hide(); //esconder boton
    escogerpartida->hide(); //esconder texto
    QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
    ui->pausar->setFocus(); //dar el focus a el boton pausa
}

void MainWindow::on_boton_ingresar_clicked()
{
    if(partida==1) //condicion que pregunta si se selecciono la partida1
    {
        QString direccion="D:/partidas/partida1.txt";
        QString texto;
        QFile archivo(direccion); //leer el archivo
        if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }
        QTextStream in(&archivo); //crear un flujo de lectura
        texto=in.readAll(); //leer todo el archivo
        QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
        archivo.flush();
        archivo.close(); //cerrar el archivo

        name.clear();
        pass.clear();

        for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
        {
            if(i==3) //condicion que pregunta si es el nombre de usuario
            {
                name.append(lista_archivo.at(i));//guardar usuario en variable
            }
            if(i==4) //condicion que pregunta si es la clave
            {
                pass.append(lista_archivo.at(i));//guardar clave en variable
            }
        }

        if(name=="vacio")
        {
            QString usuario; //variable que me guarda el nombre de usuario ingresado
            QString clave; //variable que me guarda la clave ingresada
            usuario.clear();
            clave.clear();
            usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
            clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
            QString Texto1; //variable string
            Texto1.append("3"); //agregar las vidas
            Texto1.append(","); //agregar coma
            Texto1.append("100"); //agregar probabilidad
            Texto1.append(","); //agregar coma
            Texto1.append("1"); //agregar nivel
            Texto1.append(","); //agregar coma
            Texto1.append(usuario); //agregar usuario
            Texto1.append(","); //agregar coma
            Texto1.append(clave); //agregar contraseña

            QFile archivo(direccion); //leer el archivo
            if(!archivo.open(QFile::WriteOnly | QFile::Text)) //condicion que pregunta si no lo pudo abrir
            {
                QMessageBox::warning(this,"UUYYYY :V","NO ABRE EL ARCHIVO PARA ESCRIBIR"); //mensaje que dice que no se pudo leer
            }
            QTextStream out(&archivo); //flujo de escritura
            out<<Texto1; //escribir sobre el archivo
            archivo.flush(); //cerrar procesos sobre archivo
            archivo.close(); //cerrar archivo
            QMessageBox::information(this,"Crear usuario","usuario creado exitosamente");
        }

        if(revisar_usuario_clave(direccion)) //condicion que pregunta si se ingreso correctamente la clave y el usuario
        {
            if(leer_partidarguardadas(direccion)==1) //pregunta si el nivel es 1
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel1(); //ir a funcion nivel1
            }
            if(leer_partidarguardadas(direccion)==2) //condicion que pregunta si el nivel es 2
            {
                borrar_todos_botones(); //borrar botones
                ui->pausar->show(); //mostrar boton pausa
                nivel2(); // ir a funcion nivel2
            }
            if(leer_partidarguardadas(direccion)==3) //condicion que pregunta si el nivel es 3
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel3(); //ir a funcion nivel 3
            }
        }
        if(!revisar_usuario_clave(direccion))
        {
            QMessageBox::information(this,"incorrecto","clave o usuario equivocado");
        }
    }

    if(partida==2) //condicion que pregunta si se selecciono la partida1
    {
        QString direccion="D:/partidas/partida2.txt";
        QString texto;
        QFile archivo(direccion); //leer el archivo
        if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }
        QTextStream in(&archivo); //crear un flujo de lectura
        texto=in.readAll(); //leer todo el archivo
        QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
        archivo.flush();
        archivo.close(); //cerrar el archivo

        name.clear();
        pass.clear();

        for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
        {
            if(i==3) //condicion que pregunta si es el nombre de usuario
            {
                name.append(lista_archivo.at(i));//guardar usuario en variable
            }
            if(i==4) //condicion que pregunta si es la clave
            {
                pass.append(lista_archivo.at(i));//guardar clave en variable
            }
        }

        if(name=="vacio")
        {
            QString usuario; //variable que me guarda el nombre de usuario ingresado
            QString clave; //variable que me guarda la clave ingresada
            usuario.clear();
            clave.clear();
            usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
            clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
            QString Texto1; //variable string
            Texto1.append("3"); //agregar las vidas
            Texto1.append(","); //agregar coma
            Texto1.append("100"); //agregar probabilidad
            Texto1.append(","); //agregar coma
            Texto1.append("1"); //agregar nivel
            Texto1.append(","); //agregar coma
            Texto1.append(usuario); //agregar usuario
            Texto1.append(","); //agregar coma
            Texto1.append(clave); //agregar contraseña

            QFile archivo(direccion); //leer el archivo
            if(!archivo.open(QFile::WriteOnly | QFile::Text)) //condicion que pregunta si no lo pudo abrir
            {
                QMessageBox::warning(this,"UUYYYY :V","NO ABRE EL ARCHIVO PARA ESCRIBIR"); //mensaje que dice que no se pudo leer
            }
            QTextStream out(&archivo); //flujo de escritura
            out<<Texto1; //escribir sobre el archivo
            archivo.flush(); //cerrar procesos sobre archivo
            archivo.close(); //cerrar archivo
            QMessageBox::information(this,"Crear usuario","usuario creado exitosamente");
        }

        if(revisar_usuario_clave(direccion)) //condicion que pregunta si se ingreso correctamente la clave y el usuario
        {
            if(leer_partidarguardadas(direccion)==1) //pregunta si el nivel es 1
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel1(); //ir a funcion nivel1
            }
            if(leer_partidarguardadas(direccion)==2) //condicion que pregunta si el nivel es 2
            {
                borrar_todos_botones(); //borrar botones
                ui->pausar->show(); //mostrar boton pausa
                nivel2(); // ir a funcion nivel2
            }
            if(leer_partidarguardadas(direccion)==3) //condicion que pregunta si el nivel es 3
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel3(); //ir a funcion nivel 3
            }
        }
        if(!revisar_usuario_clave(direccion))
        {
            QMessageBox::information(this,"incorrecto","clave o usuario equivocado");
        }
    }

    if(partida==3) //condicion que pregunta si se selecciono la partida1
    {
        QString direccion="D:/partidas/partida3.txt";
        QString texto;
        QFile archivo(direccion); //leer el archivo
        if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }
        QTextStream in(&archivo); //crear un flujo de lectura
        texto=in.readAll(); //leer todo el archivo
        QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
        archivo.flush();
        archivo.close(); //cerrar el archivo

        name.clear();
        pass.clear();

        for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
        {
            if(i==3) //condicion que pregunta si es el nombre de usuario
            {
                name.append(lista_archivo.at(i));//guardar usuario en variable
            }
            if(i==4) //condicion que pregunta si es la clave
            {
                pass.append(lista_archivo.at(i));//guardar clave en variable
            }
        }

        if(name=="vacio")
        {
            QString usuario; //variable que me guarda el nombre de usuario ingresado
            QString clave; //variable que me guarda la clave ingresada
            usuario.clear();
            clave.clear();
            usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
            clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
            QString Texto1; //variable string
            Texto1.append("3"); //agregar las vidas
            Texto1.append(","); //agregar coma
            Texto1.append("100"); //agregar probabilidad
            Texto1.append(","); //agregar coma
            Texto1.append("1"); //agregar nivel
            Texto1.append(","); //agregar coma
            Texto1.append(usuario); //agregar usuario
            Texto1.append(","); //agregar coma
            Texto1.append(clave); //agregar contraseña

            QFile archivo(direccion); //leer el archivo
            if(!archivo.open(QFile::WriteOnly | QFile::Text)) //condicion que pregunta si no lo pudo abrir
            {
                QMessageBox::warning(this,"UUYYYY :V","NO ABRE EL ARCHIVO PARA ESCRIBIR"); //mensaje que dice que no se pudo leer
            }
            QTextStream out(&archivo); //flujo de escritura
            out<<Texto1; //escribir sobre el archivo
            archivo.flush(); //cerrar procesos sobre archivo
            archivo.close(); //cerrar archivo
            QMessageBox::information(this,"Crear usuario","usuario creado exitosamente");
        }

        if(revisar_usuario_clave(direccion)) //condicion que pregunta si se ingreso correctamente la clave y el usuario
        {
            if(leer_partidarguardadas(direccion)==1) //pregunta si el nivel es 1
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel1(); //ir a funcion nivel1
            }
            if(leer_partidarguardadas(direccion)==2) //condicion que pregunta si el nivel es 2
            {
                borrar_todos_botones(); //borrar botones
                ui->pausar->show(); //mostrar boton pausa
                nivel2(); // ir a funcion nivel2
            }
            if(leer_partidarguardadas(direccion)==3) //condicion que pregunta si el nivel es 3
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel3(); //ir a funcion nivel 3
            }
        }
        if(!revisar_usuario_clave(direccion))
        {
            QMessageBox::information(this,"incorrecto","clave o usuario equivocado");
        }
    }

    ui->lineEdit_usuario->setText("");
    ui->lineEdit_clave->setText("");
}

void MainWindow::on_boton_cancelar_clicked()
{
    ui->label_clave->hide(); //esconder boton
    ui->label_usuario->hide(); //esconder boton
    ui->lineEdit_clave->hide(); //esconder boton
    ui->lineEdit_usuario->hide(); //esconder boton
    ui->label_inicio_de_sesion->hide(); //esconder boton
    ui->boton_ingresar->hide(); //esconder boton
    ui->boton_cancelar->hide(); //esconder boton
    ui->boton_eliminar->hide(); //esoncer boton
    if(partida==1) //condicion que pregunta si se habia seleccionado la partida 1
    {
        ui->lineEdit2->show(); //mostrar boton
        ui->lineEdit3->show(); //mostrar boton
        ui->boton_partida2->show(); //mostrar boton
        ui->boton_partida3->show(); //mostrar boton
    }
    if(partida==2) //condicion que pregunta si se habia seleccionado la partida 2
    {
        ui->lineEdit1->show(); //mostrar boton
        ui->lineEdit3->show(); //mostrar boton
        ui->boton_partida1->show(); //mostrar boton
        ui->boton_partida3->show(); //mostrar boton
    }
    if(partida==3) //condicion que pregunta si se habia seleccionado la partida 3
    {
        ui->lineEdit2->show(); //mostrar boton
        ui->lineEdit1->show(); //mostrar boton
        ui->boton_partida2->show(); //mostrar boton
        ui->boton_partida1->show(); //mostrar boton
    }

    ui->lineEdit_usuario->setText("");
    ui->lineEdit_clave->setText("");
}

void MainWindow::on_boton_eliminar_clicked()
{
    if(partida==1)
    {
        QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
        QString clave=NULL; //variable que me guarda la clave ingresada
        usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
        clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
        QString texto; //variable string
        texto.append("3"); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append("100"); //agregar probabilidad
        texto.append(","); //agregar coma
        texto.append("1"); //agregar nivel
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar usuario
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar contraseña

        QFile archivo("D:/partidas/partida1.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Borrar usuario","usuario borrado exitosamente");
    }

    if(partida==2)
    {
        QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
        QString clave=NULL; //variable que me guarda la clave ingresada
        usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
        clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
        QString texto; //variable string
        texto.append("3"); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append("100"); //agregar probabilidad
        texto.append(","); //agregar coma
        texto.append("1"); //agregar nivel
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar usuario
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar contraseña

        QFile archivo("D:/partidas/partida2.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Borrar usuario","usuario borrado exitosamente");
    }

    if(partida==3)
    {
        QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
        QString clave=NULL; //variable que me guarda la clave ingresada
        usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
        clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
        QString texto; //variable string
        texto.append("3"); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append("100"); //agregar probabilidad
        texto.append(","); //agregar coma
        texto.append("1"); //agregar nivel
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar usuario
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar contraseña

        QFile archivo("D:/partidas/partida3.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Borrar usuario","usuario borrado exitosamente");
    }

    ui->boton_regresar->click();

}

void MainWindow::on_boton_volveralmenu_clicked()
{
    escena->removeItem(chillin); //elimina el personaje principal
    for(int i=0;i<enemigos.size();i++) //ciclo que recorre toda la lista de enemigos
    {
        if(enemigos.at(i)->isVisible()) //condicion que pregunta si un enemigo es visible
        {
            escena->removeItem(enemigos.at(i)); //remueve los enemigos visibles
        }
    }
    escena->removeItem(puntos); //remueve el puntaje
    escena->removeItem(probabilidad); //remueve la probabilidad
    escena->removeItem(vidas); //remueve las vidas
    escena->removeItem(Sprite_vidas); //remueve el sprite vidas
    pastilla->hide(); //esconder la pastilla
    ui->boton_nuevapartida->show(); //mostrar boton nueva partida
    ui->boton_cargarpartida->show(); //mostar boton cargar partida

    timerenemigo->stop();
    timerenemigo2->stop();
    timerenemigo3->stop();
    delete timerenemigo;
    delete timerenemigo2;
    delete timerenemigo3;
    timerenemigo = new QTimer;
    timerenemigo2 = new QTimer;
    timerenemigo3 = new QTimer;
    partida=0;
    enemigos.clear();
    musica->setMedia(QUrl("qrc:/musica/musica_menu.mp3"));
    menu(); //ir a funcion menu
}
