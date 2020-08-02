#include "puntaje.h"

puntaje::puntaje(QGraphicsItem *parent)
{
    //dibujar el texto
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
    setDefaultTextColor(Qt::black); //pintar el texto
    setFont(QFont("Gill Sans Ultra Bold Condensed",18)); //fuente y tamaño
}

void puntaje::aumentar_puntaje(int p_)
{
    Puntaje=p_;
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
}

void puntaje::setPuntaje(int p_)
{
    Puntaje=p_;
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
}

int puntaje::getPuntaje()
{
    return Puntaje;
}

void puntaje::mostrar_Puntaje()
{
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
}

void puntaje::texto(QString texto)
{
    setPlainText(texto);
    setDefaultTextColor(Qt::black); //pintar el texto
    setFont(QFont("Gill Sans Ultra Bold Condensed",16)); //fuente y tamaño
}




