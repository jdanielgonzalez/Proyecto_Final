#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene> //incluir la libreria QgraphicsScene.
#include "cuerpo.h" //incluir la clase cuerpo.
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //escena
    QGraphicsScene *escena; //escena del videojuego

    //cuerpos
    Cuerpo *nave; // cuerpo prueba
};
#endif // MAINWINDOW_H
