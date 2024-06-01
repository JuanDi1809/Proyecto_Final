#include "puntuacion.h"

#include <QFont>

Puntuacion::Puntuacion(QGraphicsItem *parent) : QGraphicsTextItem(parent), puntuacion(0){
    //puntuacion
    setPlainText(QString("Eliminados: %1").arg(puntuacion));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 15, 1, true));
}

void Puntuacion::aumentarPuntuacion(){
    puntuacion += 5;
    setPlainText(QString("Eliminados: %1").arg(puntuacion));
}
int Puntuacion::getPuntuacion(){
    return puntuacion;
}
