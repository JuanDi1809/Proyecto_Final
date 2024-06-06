#ifndef PROYECTIL_H
#define PROYECTIL_H
#include <QVector2D>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "Personaje.h"

class Proyectil: public QObject, public QGraphicsPixmapItem{
    //macro
    Q_OBJECT
public:
    Proyectil(Personaje *personaje, QPointF &direccion); //constructor, se establece la direccion que tomará el proyectil
    //uso de señales y slots
    QPixmap getProyectil();

    QTimer* getTimer();

public slots: //es una funcion que puede ser asigana a una señal
    void colisiones();
    void actualizarImagen(const QString &direccion);

private:
    QPointF direccion;
    qreal velocidad;
    Personaje *personaje;
    QTimer *tiempo;

    //texturas proyectil
    QPixmap proy;
    QPixmap proy_der;
    QPixmap proy_izq;
    QPixmap proy_abj;
    QPixmap proy_arr;
};


#endif // PROYECTIL_H
