#ifndef BALAS_H
#define BALAS_H
#include <QGraphicsPixmapItem> //incluir la libreria QgraphicsPixmapItem.
#include "enemigo.h" //incluir la libreria enemigo
#include "puntaje.h" //incluir la libreria puntaje

//clase balas

class balas: public QObject, public QGraphicsPixmapItem //heredar las librerias
{
    Q_OBJECT //agregar un Q_OBJECT
public:
    balas(QGraphicsItem *parent = 0); //crear las balas    

public slots:
    void move(); //funcion mover las balas
};

#endif // BALAS_H
