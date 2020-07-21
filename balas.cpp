#include "balas.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>
#include <QDebug>


balas::balas(QGraphicsItem* parent): QObject(), QGraphicsPixmapItem()
{
    //dibujar la bala
    setPixmap(QPixmap(":/imagenes/disparo.png")); //tamaño de las ballas

    //conectar el tiempo a la bala
    QTimer * timer= new QTimer(); //clear el QTimer
    connect(timer,SIGNAL(timeout()),this,SLOT(move())); //conectar el timer con la funcion mover de las balas
    //lo que hace es que cada 50 milisegundos la bala se mueve
    timer->start(50); //empieza cada 50 milisegundos
}

void balas::move()
{
    //mover la bala
    setPos(x(),y()-20); //le da la posicicion de la bala
    if(pos().y()<0)
    {
        delete this;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){
        if(typeid(*(colliding_items[i])) == typeid (enemigo)){

            //remove the both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            qDebug()<<"choco";
        }
    }
}
