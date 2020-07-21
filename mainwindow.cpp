#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int nivel=1; //inicializacion de nivel

    escena = new QGraphicsScene; //crear la escena del juego
    ui->graphicsView->setScene(escena); //agregar el graphicsView
    escena->setSceneRect(0,0,1000,698); //darle un tamaño a la escena

    if(nivel==1) //nivel 1
    {
        //agregar personaje principal
        nave = new Cuerpo(475,600,50,50); //creo nave
        escena->addItem(nave); //agregar la nave

        //enemigo 1
        bola1 = new enemigo(25,-400,50,50,20,0); //creo enemigo 1
        enemigos.push_back(bola1); //agrego enemigo 1 a la lista de enemigos
        escena->addItem(enemigos.at(0)); //añado enemigo 1 a la escena

        //enemigo 2
        bola2 = new enemigo(975,-400,50,50,20,180); //creo enemigo 2
        enemigos.push_back(bola2); //agrego enemigo 2 a la lista de enemigos
        escena->addItem(enemigos.at(1)); //añado enemigo 2 a la escena

        //enemigo 3
        bola3 = new enemigo(500,-350,50,50); //creo enemigo 3
        enemigos.push_back(bola3); //agrego enemigo 3 a la lista de enemigos
        escena->addItem(enemigos.at(2)); //añado enemigo 3 a la escena

        //enemigo 4
        bola4 = new enemigo(750,-350,50,50); //creo enemigo 4
        enemigos.push_back(bola4); //agrego enemigo 4 a la lista de enemigos
        escena->addItem(enemigos.at(3)); //añado enemigo 4 a la escena

        //enemigo 4
        bola5 = new enemigo(500,-150,50,50); //creo enemigo 4
        enemigos.push_back(bola5); //agrego enemigo 4 a la lista de enemigos
        escena->addItem(enemigos.at(4)); //añado enemigo 4 a la escena

        //piso
        piso = new Cuerpo(500,650,1000,50); //creo el piso
        escena->addItem(piso); //agregar piso

        //muro derecho
        muroderecho = new Cuerpo(1025,350,50,800); //creo el muro derecho
        escena->addItem(muroderecho); //agregar muro derecho

        //muro izquierdo
        muroizquierdo = new Cuerpo(-25,350,50,800); //creo el muro izquierdo
        escena->addItem(muroizquierdo); //agregar muro izquierdo

        //timer para los enemigos
        timerenemigo = new QTimer; //creo el Qtimer
        connect(timerenemigo,SIGNAL(timeout()),this,SLOT(mover_enemigo())); //conecto el timer al movimiento del enemigo
        timerenemigo->start(10); //iniciar timer
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mover_enemigo()
{
    for(int i=0; i<enemigos.size();i++)
    {
        //qDebug() <<"velocidad: "<<enemigos.at(i)->getVel();
        //qDebug() <<"velocidadx: "<<enemigos.at(i)->getVelx();
        if(enemigos.at(i)->getVel()>70){enemigos.at(i)->setVel(70);} //condicion para que no supere cierta velocidad
        if(enemigos.at(i)->getVelx()<20){enemigos.at(i)->setVelx(20);} //condicion para que no rebote con una velocidad menor

        //mover a la derecha
        if(enemigos.at(i)->getDir()==1) //condicion para preguntar por la direcion
        {
            enemigos.at(i)->actualizarposicion_derecha(); //actualiza la posicion
            enemigos.at(i)->actualizarvelocidad(); //actualiza la velocidad
            enemigos.at(i)->setX(enemigos.at(i)->getPosx()); //setea la posicion en x
            enemigos.at(i)->setY(-enemigos.at(i)->getPosy());//setea la posicion en y
        }

        //mover a la izquierda
        if(enemigos.at(i)->getDir()==2) //condicion para preguntar la direccion
        {
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
            enemigos.at(i)->MCU(250,300,150,1,0);
        }

        if(i==3) //condicion que pregunta si es el tercer enemigo
        {
            enemigos.at(i)->MCU(750,300,150,1,-3.1416);
        }

        if(i==4) //condicion que pregunta si es el tercer enemigo
        {
            enemigos.at(i)->MAS(500,150,150,1);
        }
    }

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //tecla D
    if(event->key()==Qt::Key_D)
    {
        if(nave->getPosx()<970)
        {
            nave->mover_derecha(); //mover hacia la derecha
        }
    }

    //tecla A
    if(event->key()==Qt::Key_A)
    {
        if(nave->getPosx()>25)
        {
            nave->mover_izquierda();//mover hacia la izquierda
        }
    }

    if(event->key()==Qt::Key_Space)
    {
        balas * bala = new balas();
        bala->setPos(nave->getPosx(),nave->getPosy()-25);
        escena->addItem(bala);
    }
}
