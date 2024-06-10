#ifndef ORBITAL_H
#define ORBITAL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Personaje.h"

class Orbital : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Orbital(Personaje *personaje, QObject *parent = nullptr);
    //le pasamos como constructor donde pertenece

    //para obtener el timer
    QTimer* getTimer();

public slots:
    void mover(); //determina el movimiento, la misma clase lo hace

private:
    Personaje *personaje;
    QTimer *timer;
    float angulo;
    float radio;
};


#endif // ORBITAL_H
