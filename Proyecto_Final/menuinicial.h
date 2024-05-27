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

class MenuInicial : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *escenaMenu;
    QLineEdit *usuario;
    QLineEdit *contraseña;

signals:
    void on_botonIngresar_clicked();

private slots:
    void cambiarEscena();
    void on_botonRegistarse_clicked();


public:
    MenuInicial();
    ~MenuInicial();

    QGraphicsScene* getEscena();
    void configurarEscena();
    void decorarEscena();
};

#endif // MENUINICIAL_H
