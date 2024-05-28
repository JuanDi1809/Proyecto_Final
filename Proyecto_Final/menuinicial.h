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

class MenuInicial : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *escenaMenu;
    QLineEdit *usuario;
    QLineEdit *contraseña;
    Guardado *datos;

signals:
    void cambiarEscena();

private slots:
    void on_botonIngresar_clicked();
    void on_botonRegistarse_clicked();


public:
    MenuInicial();
    ~MenuInicial();

    QGraphicsScene* getEscena();
    void configurarEscena();
    void decorarEscena();
};

#endif // MENUINICIAL_H
