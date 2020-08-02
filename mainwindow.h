#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene> //incluir la libreria QgraphicsScene.
#include "cuerpo.h" //incluir la clase cuerpo.
#include <QMainWindow> //incluir libreria mainWindow
#include "enemigo.h" //incluir la clase villano.
#include "balas.h" //incluir la libreria balas.
#include "salud.h" //incluir la libreria de salud.
#include "puntaje.h" //incluir la libreria de puntaje.
#include "porcentaje.h" //incluir la libreria de porcentaje
#include <QKeyEvent> //libreria para las teclas.
#include <QTimer> //lireria del timer.
#include <QDebug> //libreria de debug.
#include <QList> //libreria de Qlist.
#include <fstream> //libreria de lectura de archivos.
#include <QFile> //libreria lectura de archivos.
#include <QTextStream> //libreia flujo de texto
#include <QMessageBox> //libreria de mensajes de caja
#include <QMediaPlayer> //libreria para musica.
#include <QMovie> //libreria para gif.

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
    void mover_enemigo(); //funcion para mover enemigos en el nivel 1

    void mover_enemigo2(); //funcion para mover enemigos en el nivel 2

    void mover_enemigo3(); //funcion para mover enemigos en el nivel 3

    void on_boton_nuevapartida_clicked(); //boton nueva partida

    void on_boton_cargarpartida_clicked(); //boton cargar partida

    void on_boton_regresar_clicked(); //boton regresar

    void on_boton_partida1_clicked(); //boton partida 1

    void on_boton_partida2_clicked(); //boton partida 2

    void on_boton_partida3_clicked(); //boton partida 3

    void on_pausar_clicked(); //boton pausar

    void on_guardar_clicked();

    void on_boton_guardarpartida1_clicked();

    void on_boton_guardarpartida2_clicked();

    void on_boton_guardarpartida3_clicked();

    void on_boton_ingresar_clicked();

    void on_boton_cancelar_clicked();

    void on_boton_eliminar_clicked();

    void on_boton_volveralmenu_clicked();

private:
    Ui::MainWindow *ui;
    //escena
    QGraphicsScene *escena; //escena del videojuego

    //booleanas
    bool juego; //variable para saber si se puede jugar o no

    //timers
    QTimer *timerenemigo; //timer de los enemigos
    QTimer *timerenemigo2; //timer de los enemigos
    QTimer *timerenemigo3; //timer de los enemigos

    //cuerpos
    Cuerpo *chillin; // cuerpo principal
    Cuerpo *moncha; // cuerpo principal
    Cuerpo *pastilla; //cuerpo pastilla
    Cuerpo *Sprite_vidas; // sprite vidas
    Cuerpo *lodo1; //lodo 1
    Cuerpo *lodo2; //lodo 2
    Cuerpo *lodo3; //lodo 3

    enemigo *bola1; //enemigo bola1
    enemigo *bola2; //enemigo bola2
    enemigo *bola3; //enemigo bola3
    enemigo *bola4; //enemigo bola4
    enemigo *bola5; //enemigo bola5

    enemigo *bola6; //enemigo bola6
    enemigo *bola7; //enemigo bola7
    enemigo *bola8; //enemigo bola8
    enemigo *bola9; //enemigo bola9
    enemigo *bola10; //enemigo bola10

    enemigo *bola11; //enemigo bola11
    enemigo *bola12; //enemigo bola12
    enemigo *bola13; //enemigo bola13
    enemigo *bola14; //enemigo bola14
    enemigo *bola15; //enemigo bola15
    enemigo *bola16; //enemigo bola16
    enemigo *bola17; //enemigo bola17

    //lista
    QList<enemigo*> enemigos; //lista de enemigos

    //entorno
    Cuerpo *piso; // piso
    Cuerpo *muroderecho; //muro derecho
    Cuerpo *muroizquierdo; //muro izquierdo

    //Balas
    balas *bala; //balas

    //salud
    salud *vidas; //vidas

    //puntaje
    puntaje *puntos; //puntos

    //probabilidad
    porcentaje *probabilidad; //probabilidad

    //texto
    puntaje *escogerpartida;

    //partida
    int partida=0;
    int c=0;

    //audio
    QMediaPlayer *musica;
    QMediaPlayer *fuego;
    QMediaPlayer *corte;

    //gif
    QMovie *quemado;
    QMovie *triturado;
    QMovie *portal;

    //string
    QString name;
    QString pass;

    //pantallas
    void menu(); //funcion menu
    void nivel1(); //funcion que me muestra en pantalla el nivel 1
    void nivel2(); //funcion que me muestra en pantalla el nivel 2
    void nivel3(); //funcion que me muestra en pantalla el nivel 2

    //funciones
    void keyPressEvent(QKeyEvent * event); //funcion para las teclas
    void choque(enemigo*bola); //funcion que detecta las colisiones y resta una vida.
    void actualizar_puntaje(int p); //funcion que detecta que un disparo fue exitoso y aumenta el puntaje.
    void disparo_bien_o_mal(); //funcion que detecta si un disparo salio bien o mal.
    void game_over(); //funcion que muestra pantalla de game_over
    void borrar_todos_botones(); //funcion que borra todos los botones
    void escribir_partidasguardadas(QString texto, int p_); //funcion que me permite leer los datos guardados y mostrarlos en pantalla
    int leer_partidarguardadas(QString texto); //funcion que me permite leer los archivos de partidas y tomar esos valores
    bool revisar_usuario_clave(QString texto);
    void gano(); //funcion que muestra pantalla de ganar
};
#endif // MAINWINDOW_H

