#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <QGraphicsItem> //libreria de item grafico
#include <QPainter> //libreria para pintar
#include <math.h> //libreria matematica

using namespace std;


class enemigo: public QGraphicsItem //heredar las funciones de QgraphicsItem.
{
    double posx; //posicion en x del cuerpo.
    double posy; //posicion en y del cuerpo.
    double ancho; //ancho del cuerpo.
    double largo; //largo del cuerpo.
    double vel; //velocidad del enemigo
    double velx; //velocidad en el eje x
    double vely;  //velocidad en el eje y
    double g=9.8; //gravedad
    double delta=0.1; //timepo
    double pi=3.1416; //pi
    double angulo; //angulo
    int dir; //direccion 1 es hacia la derecha, direccion 2 es a la izquierda
    int r; //radio para el MCU
    double Rad= 0.01745329252; //radianes
    double i=0;
    double W; //velocidad angular

public:
    enemigo(); //constructor por defecto
    enemigo(double x, double y, double ancho_, double largo_, double vi, double ang_); //sobre carga de constructor
    enemigo(double x, double y, double ancho_, double largo_);

    double getPosx(); //funcion para tomar la posicion en x.
    double getPosy(); //funcion para tomar la posicion en y.

    double getVelx(); //funcion para tomar la velocidad en x.
    double getVely(); //funcion para tomar la velocidad en y.
    void setVelx(double vx_);

    void actualizarposicion_derecha(); //funcion que actualiza la posicion hacia la derecha
    void actualizarposicion_izquierda(); //funcion que actualiza la posicion hacia la izquierda
    void rebotepiso(); //funcion que simula rebote con el piso

    void setVel(double vel_); //funcion que da velocidad al enemigo
    double getVel(); //funcion obtener la velocidad.

    double getAngulo(); //funcion obtener el angulo.
    void setAngulo(double Angulo); //funcion para cambiar el angulo

    void actualizarvelocidad(); //funcion que actualizia la velocidad

    void MCU(double x, double y, int r_, double W_, double Desfase_); //movimentiento circular uniforme

    void MAS(double x, double y, int r_, double W_); //movimiento armonico simple

    void setDir(int dir_); //funcion para cambiar la direccion.
    int getDir(); //funcion para tomar la direccion.
    QRectF boundingRect() const; //funcion que dibuja
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //funcion que pinta
};

#endif // ENEMIGO_H


