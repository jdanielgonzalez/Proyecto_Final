#ifndef SALUD_H
#define SALUD_H
#include <QGraphicsTextItem>
#include <QFont>

class salud: public QGraphicsTextItem
{
    int Vidas; //cantidad de vidas
public:
    salud(); // constructor
    void disminuir_salud(); //funcion que me disminuye la salud
    int getVidas(); //funcion que retorna las vidas
    void Game_over(); //funcion escribe Game_over
    void setVidas(int v_); //funcion para actualizar las vidas
};

#endif // SALUD_H
