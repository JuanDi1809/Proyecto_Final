#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include "Juego.h"

class Enemigo : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemigo(int nivel, Personaje *objetivo); //se le pasa el objetivo a seguir
    void recibirImpacto();
signals:
    void eliminado();
private slots:
    void moverEnemigo();

private:
    //miembros de la clase los cuales contienen los punteros de lo que usaremos en los metodos
    Personaje *objetivo;
    QTimer *tiempo;
    QPixmap generico;

    //nivel enemigo
    int cuentaImpact;
    int nivelActual;
};

#endif // ENEMIGO_H
