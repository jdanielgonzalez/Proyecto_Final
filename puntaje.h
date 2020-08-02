#ifndef PUNTAJE_H
#define PUNTAJE_H
#include <QGraphicsTextItem> //libreria de QgraphicsTextItem
#include <QFont> //libreria de fuentes

class puntaje: public QGraphicsTextItem
{
    int Puntaje=0; //variable que guarda el puntaje
public:
    puntaje(QGraphicsItem * parent=0); //constructor
    void aumentar_puntaje(int p_); //funcion para aumentar el puntaje
    void setPuntaje(int p_); //funcion para setear el putaje
    int getPuntaje(); //funcion para obetener el puntaje
    void mostrar_Puntaje(); //funcion para mostrar el puntaje

    void texto(QString texto);
};

#endif // PUNTAJE_H
