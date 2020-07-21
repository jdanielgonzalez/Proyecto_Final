#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene> //incluir la libreria QgraphicsScene.
#include "cuerpo.h" //incluir la clase cuerpo.
#include <QMainWindow>
#include "enemigo.h" //incluir la clase villano.
#include "balas.h" //incluir la libreria balas.d
#include <QKeyEvent> //libreria para las teclas.
#include <QTimer> //lireria del timer.
#include <QDebug> //libreria de debug.
#include <QList> //libreria de Qlist.

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mover_enemigo();

private:
    Ui::MainWindow *ui;
    //escena
    QGraphicsScene *escena; //escena del videojuego

    //timers
    QTimer *timerenemigo;

    //cuerpos
    Cuerpo *nave; // cuerpo prueba
    enemigo *bola1; //enemigo bola1
    enemigo *bola2; //enemigo bola2
    enemigo *bola3; //enemigo bola3
    enemigo *bola4; //enemigo bola4
    enemigo *bola5; //enemigo bola5

    //lista
    QList<enemigo*> enemigos; //lista de enemigos

    //entorno
    Cuerpo *piso;
    Cuerpo *muroderecho;
    Cuerpo *muroizquierdo;

    //Balas
    balas *bala;

    //funciones
    void keyPressEvent(QKeyEvent * event); //funcion para las teclas

};
#endif // MAINWINDOW_H
