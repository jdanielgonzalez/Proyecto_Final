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
        nave = new Cuerpo(475,600,50,50);
        escena->addItem(nave); //agregar la nave

        //agregar enemigo 1
        bola1 = new enemigo(25,-400,50,50,20,0);
        enemigos.push_back(bola1);
        escena->addItem(enemigos.at(0));
        //escena->addItem(bola1); //agregar el enemigo 1

        //agregar enemigo 2
        bola2 = new enemigo(900,-400,50,50,20,180);
        enemigos.push_back(bola2);
        escena->addItem(enemigos.at(1));

        //agregar piso
        piso = new Cuerpo(500,650,1000,50);
        escena->addItem(piso); //agregar piso

        //agrego muro derecho
        muroderecho = new Cuerpo(1025,350,50,800);
        escena->addItem(muroderecho); //agregar muro derecho

        //agrego muro izquierdo
        muroizquierdo = new Cuerpo(-25,350,50,800);
        escena->addItem(muroizquierdo); //agregar muro izquierdo

        timerenemigo = new QTimer; //timer
        connect(timerenemigo,SIGNAL(timeout()),this,SLOT(mover_enemigo())); //mover el enemigo
        timerenemigo->start(10); //iniciar timer
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mover_enemigo()
{
    for(int i=0; i<2;i++)
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
        if(enemigos.at(i)->collidesWithItem(piso))
        {
            enemigos.at(i)->rebotepiso();
        }
        //rebote con el muro derecho
        if (enemigos.at(i)->collidesWithItem(muroderecho))
        {
            enemigos.at(i)->setDir(2);
        }
        //rebote con el muro izquierdo
        if (enemigos.at(i)->collidesWithItem(muroizquierdo))
        {
            enemigos.at(i)->setDir(1);
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
}
