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
    columnas =50;
    filas=40;
    setPos(posx,posy);
    pixmap = new QPixmap(":/imagenes/personaje_principal.png");
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
    posx=x;
    setX(posx); //darle el valor x a la posicion en x
}

void Cuerpo::setPosy(double y)
{
    posy=y;
    setY(posy); //darle el valor y a la posicion en y
}

void Cuerpo::setVelocidad(int v_)
{
    velocidad=v_; //dar velocidad
}

void Cuerpo::setcolumna_fila(int c_, int f_)
{
    columnas=c_; //actualizar columna
    filas=f_; //actualizar fila
    this->update(-ancho/2,-largo/2,ancho,largo); //actualiza el cuerpo
}

void Cuerpo::setImagen(int i)
{
    // actualizar la imagen
    if(i==0)
    {
        pixmap = new QPixmap(":/imagenes/personaje_principal.png");
    }
    if(i==1)
    {
        pixmap = new QPixmap(":/imagenes/sprite_vidas.png");
    }
    if(i==2)
    {
        pixmap = new QPixmap(":/imagenes/VACIO.png");
    }
    if(i==3)
    {
        pixmap = new QPixmap(":/imagenes/personaje_secundario.png");
    }
}

QRectF Cuerpo::boundingRect() const
{
    return QRectF(-ancho/2,-largo/2,ancho,largo); //retornar un rectangulo
}

void Cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-largo/2,*pixmap,columnas,filas,ancho,largo);
}

void Cuerpo::mover_derecha()
{
    columnas=0; //dejar columna 0
    filas+=40; //ir sumando 40 a la fila
    if(filas>=240) // condicion que pregunta si la fila es mayor a 240
    {
        filas=0; //hacer la fila igual a 0
    }
    this->update(-ancho/2,-largo/2,ancho,largo); //actualizar cuerpo
    posx=posx+velocidad; //sumarle el valor de la velocidad a la posicion en x
    setX(posx); //actualiza la posicion en x
}

void Cuerpo::mover_izquierda()
{
    columnas=50;
    filas+=40;
    if(filas>=240)
    {
        filas=0;
    }
    this->update(-ancho/2,-largo/2,ancho,largo);
    posx=posx-velocidad; //restarle el valor de la velocidad a la posicion en x
    setX(posx); //actualizar la posicion en x
}

void Cuerpo::Disparo()
{
    columnas=50;
    filas=240;
    this->update(-ancho/2,-largo/2,ancho,largo);
}

