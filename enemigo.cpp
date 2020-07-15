#include "enemigo.h"

enemigo::enemigo()
{

}

enemigo::enemigo(double x, double y, double ancho_, double largo_, double vi, double ang_)
{
    largo=largo_; //tomar el largo
    ancho=ancho_; //tomar el ancho
    posx = x; //tomar la posicion inicial enx
    posy = y; //tomar la posicion inicial en y
    vel = vi; //tomar la velocidad inicial
    angulo=(ang_/180)*pi; //tomar el angulo inicial
    setPos(posx,-posy); //dar posicion en x y en y
    dir=1;
}

double enemigo::getPosx()
{
    return posx; //retorna la posicion en x.
}

double enemigo::getPosy()
{
    return posy; //retorna la posicion en y.
}

double enemigo::getVelx()
{
    return velx;
}

double enemigo::getVely()
{
    return vely;
}

void enemigo::setVelx(double vx_)
{
    velx=vx_;
}


void enemigo::actualizarposicion_izquierda()
{
    posx=posx-velx*delta; //x=x0+Vx*T
    posy=posy+vely*delta-(0.5*g*delta*delta); //y=y0+Vy*t-(9.8/2)*t^2
}

void enemigo::rebotepiso()
{
    velx=vel*cos(angulo); //vx=v*cos(angulo)
    vely=-vel*sin(angulo)+g*delta; //vy=v*sin(angulo)-g*T
    angulo=atan2(vely,velx); //angulo = arctan(vy/vx)
    vel=sqrt(velx*velx+vely*vely); //v=(vx^2+vy^2)^1/2
    posx=posx+velx*delta; //x=x0+Vx*T
    posy=posy+vely*delta+(0.5*g*delta*delta); //y=y0+Vy*t-(9.8/2)*t^2
}


void enemigo::setVel(double vel_)
{
    vel=vel_; //darle un valor a la velocidad
}

double enemigo::getVel()
{
    return vel;
}

double enemigo::getAngulo()
{
    return angulo*180/pi;
}

void enemigo::setAngulo(double angulo_)
{
    angulo=(angulo_/180)*pi; //darle un valor al angulo
}

void enemigo::actualizarposicion_derecha()
{
    posx=posx+velx*delta; //x=x0+Vx*T
    posy=posy+vely*delta-(0.5*g*delta*delta); //y=y0+Vy*t-(9.8/2)*t^2
}

void enemigo::actualizarvelocidad()
{
    velx=vel*cos(angulo); //vx=v*cos(angulo)
    vely=vel*sin(angulo)-g*delta; //vy=v*sin(angulo)-g*T
    angulo=atan2(vely,velx); //angulo = arctan(vy/vx)
    vel=sqrt(velx*velx+vely*vely); //v=(vx^2+vy^2)^1/2
}

void enemigo::setDir(int dir_)
{
    dir=dir_;
}

int enemigo::getDir()
{
    return dir;
}

QRectF enemigo::boundingRect() const
{
    return QRectF(-ancho/2,-largo/2,ancho,largo); //retorna un rectangulo
}

void enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect()); //dibuja una elipse
}
