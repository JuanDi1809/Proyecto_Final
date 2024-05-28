#ifndef MENUINICIAL_H
#define MENUINICIAL_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QPixmap>
#include <QLineEdit>
#include <fstream>
#include "guardado.h"

class MenuInicial : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene *escenaMenu;
    QLineEdit *usuario;
    QLineEdit *contraseña;

signals:
    void cambiarEscena();

private slots:
    void on_botonIngresar_clicked();
    void on_botonRegistarse_clicked();


public:
    //Instancio los datos
    Guardado *datos = new Guardado();

    MenuInicial(QWidget *parent=nullptr);
    ~MenuInicial();

    QGraphicsScene* getEscena();
    void configurarEscena();
    void decorarEscena();
};

#endif // MENUINICIAL_H
