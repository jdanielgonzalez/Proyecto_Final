#ifndef CUERPO_H
#define CUERPO_H
#include <QGraphicsItem> //libreria de item grafico
#include <QPainter> //libreria para pintar

using namespace std;


class Cuerpo: public QGraphicsItem //heredar las funciones de QgraphicsItem.
{
    double posx; //posicion en x del cuerpo.
    double posy; //posicion en y del cuerpo.
    double ancho; //ancho del cuerpo.
    double largo; //largo del cuerpo.
    int velocidad=10; //velocidad de movimiento del personaje principal.

public:
    Cuerpo(); //constructor del cuerpo por defecto

    Cuerpo(double x, double y, double ancho_, double largo_); //sobre carga del constructor.
    double getPosx(); //funcion para obtener la posicion en x del cuerpo.
    double getPosy(); //funcion para obtener la posicion en y del cuerpo.
    void setPosx(double x); //darle una posicion al cuerpo en x.
    void setPosy(double y); //darle una posicion al cuerpo en y.

    QRectF boundingRect() const; //dibujar un cuerpo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //pintar el cuerpo

    void mover_derecha(); //funcion de mover a la derecha
    void mover_izquierda(); //funcion de mover a la izquierda
};

#endif // CUERPO_H
