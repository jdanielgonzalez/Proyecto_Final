#include "porcentaje.h"

porcentaje::porcentaje()
{
    //dibujar el texto
    setPlainText(QString::number(tope)+QString("%")); //escribir el texto
    setDefaultTextColor(Qt::gray); //pintar el texto
    setFont(QFont("EMPORO",14)); //fuente y tamaño
}

void porcentaje::actualizar_Probabilidad()
{
    setPlainText(QString::number(tope)+QString("%")); //actualizar la probabilidad
}

int porcentaje::calcular_numaleatorio()
{
    tope--;
    num =rand() % Porcentaje; //calcular el numero aleatorio entre 0 y 100
    return num; //retornar el numero aleatorio
}

int porcentaje::getTope()
{
    return tope; //retnornar el tope
}

bool porcentaje::disparo_mal()
{
    if(num>tope) //condicion que pregunta si el numero aleatorio es mayor que el tope
    {
        return true; //retornar verdad
    }
    else //otro caso
        return false; //retorna falso
}

void porcentaje::setTope(int t_)
{
    tope=t_;
    setPlainText(QString::number(tope)+QString("%")); //actualizar la probabilidad
}
