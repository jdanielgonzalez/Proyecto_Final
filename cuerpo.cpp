#include "cuerpo.h"

Cuerpo::Cuerpo()
{

}

Cuerpo::Cuerpo(double x, double y, double ancho_, double largo_)
{
    posx=x; //asignar la posicion en x ingresada.
    posy=y; //asignar la posicion en y ingresada.
    ancho=ancho_; //asignar el ancho del cuerpo.
    largo=largo_; //asignar el largo del cuerpo.
    setPos(posx,posy);
}

double Cuerpo::getPosx()
{
    return posx; //retornar posicion en x.
}

double Cuerpo::getPosy()
{
    return posy; //retornar posicion en y.
}

void Cuerpo::setPosx(double x)
{
    setX(x); //darle el valor x a la posicion en x
}

void Cuerpo::setPosy(double y)
{
    setY(y); //darle el valor y a la posicion en y
}

QRectF Cuerpo::boundingRect() const
{
    return QRectF(-ancho/2,-largo/2,ancho,largo); //retornar un rectangulo
}

void Cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect()); //dibujar un rectangulo
}

void Cuerpo::mover_derecha()
{
    posx=posx+velocidad; //sumarle el valor de la velocidad a la posicion en x
    setX(posx); //actualiza la posicion en x
}

void Cuerpo::mover_izquierda()
{
    posx=posx-velocidad; //restarle el valor de la velocidad a la posicion en x
    setX(posx); //actualizar la posicion en x
}
