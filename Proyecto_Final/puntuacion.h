#ifndef PUNTUACION_H
#define PUNTUACION_H

#include <QGraphicsTextItem>

class Puntuacion : public QGraphicsTextItem{
public:
    Puntuacion(QGraphicsItem *parent = nullptr);
    void aumentarPuntuacion();
    int getPuntuacion();
private:
    int puntuacion;

};
#endif // PUNTUACION_H
