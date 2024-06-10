#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include "juego.h"

class Enemigo : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemigo(int nivel, Personaje *objetivo); //se le pasa el objetivo a seguir
    void recibirImpacto();

    //para las texturas de los enemigos
    void setTexturas(int nivelActual);

    //Getter par el timer del enemigo
    QTimer* getTimer();
    //Geeter para el timer de generacion de proyectiles Enenmigos
    QTimer *getTimerProy();


signals:
    void eliminado();
private slots:
    void moverEnemigo();
    void disparaProyectil();

private:
    //miembros de la clase los cuales contienen los punteros de lo que usaremos en los metodos
    Personaje *objetivo;
    QTimer *tiempo;
    QTimer *tiempoDisparo;
    QPixmap generico;
    QPixmap enemigo2;


    //nivel enemigo
    int cuentaImpact;
    int nivelActual;
};

#endif // ENEMIGO_H
