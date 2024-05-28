#ifndef MENUJUEGO_H
#define MENUJUEGO_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QPixmap>
#include <QLineEdit>

class MenuJuego : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *escenaMenuJuego;

signals:
    void cambiarEscena();

private slots:
    //void on_botonNuevaPartida_clicked();
    //void on_botonCargarPartida_clicked();
    void on_botonVolver_clicked();


public:
    MenuJuego();
    ~MenuJuego();

    QGraphicsScene *getEscena();
    void configurarEscena();
    void decorarEscena();
};

#endif // MENUJUEGO_H
