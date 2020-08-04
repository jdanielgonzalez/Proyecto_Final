#ifndef PORCENTAJE_H
#define PORCENTAJE_H
#include <QGraphicsTextItem> //incluir la libreria QGraphicsTextItem
#include <QFont> //incluir la libreria Qfont
#include<stdlib.h> //incluir la libreria stdlib
#include <time.h> //incluir la libreria time

class porcentaje: public QGraphicsTextItem
{
    int Porcentaje=101; //porcentaje sobre el que se calculara la probabilidad
    int num; //variable que recibira el numero aleatorio
    int tope; //variable tope que disminuira con cada disparo
public:
    porcentaje(); //constructor
    void actualizar_Probabilidad(); //funcion que actualiza la probabilidad de que el disparo salga bien
    int calcular_numaleatorio(); // funcion que calcula y retorna un numero aleatorio
    int getTope(); //funcion que devuelve el tope
    bool disparo_mal(); //funcion que regista si un disparo salio mal y retorna un verdadero en cuyo caso
    void setTope(int t_); //funcion que actualiza el tope
};

#endif // PORCENTAJE_H
