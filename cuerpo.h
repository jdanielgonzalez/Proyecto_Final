#ifndef CUERPO_H
#define CUERPO_H
#include <QGraphicsItem> //libreria de item grafico
#include <QPainter> //libreria para pintar
#include <QPixmap> //libreria Qpixmap
#include <QGraphicsPixmapItem> //libreria de QgraphicsPixmapItem

using namespace std;


class Cuerpo: public QGraphicsItem //heredar las funciones de QgraphicsItem.
{
    double posx; //posicion en x del cuerpo.
    double posy; //posicion en y del cuerpo.
    double ancho; //ancho del cuerpo.
    double largo; //largo del cuerpo.
    int velocidad=10; //velocidad de movimiento del personaje principal.
    QPixmap *pixmap; //variable pixap
    float filas,columnas; //variables para controlar las filas y las columnas del sprite

public:
    Cuerpo(); //constructor del cuerpo por defecto

    Cuerpo(double x, double y, double ancho_, double largo_); //sobre carga del constructor.
    double getPosx(); //funcion para obtener la posicion en x del cuerpo.
    double getPosy(); //funcion para obtener la posicion en y del cuerpo.
    void setPosx(double x); //darle una posicion al cuerpo en x.
    void setPosy(double y); //darle una posicion al cuerpo en y.
    void setVelocidad(int v_); //actualizar la velocidad.
    void setcolumna_fila(int c_, int f_); //darle valores a la columna y la fila
    void setImagen(int i); //escoger la imagen

    QRectF boundingRect() const; //dibujar un cuerpo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //pintar el cuerpo

    void mover_derecha(); //funcion de mover a la derecha
    void mover_izquierda(); //funcion de mover a la izquierda
    void Disparo(); //actualizar sprite para mostrar el disparo
};

#endif // CUERPO_H

