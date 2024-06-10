#include "Orbital.h"
#include <QGraphicsScene>
#include <QList>
#include <cmath>
#include "enemigo.h"

Orbital::Orbital(Personaje *personaje, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), personaje(personaje), angulo(0), radio(100)
{
    QPixmap pixmap(":/Imagenes/videoJuego/rata.png");
    QPixmap scaled = pixmap.scaled(60, 60, Qt::KeepAspectRatio);
    setPixmap(scaled);
    setPos(personaje->x() + radio, personaje->y());

    // Crear un temporizador para mover el objeto orbital
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Orbital::mover);
    timer->start(10);
}

QTimer *Orbital::getTimer()
{
    return timer;
}

void Orbital::mover() {
    int cantImpactos = 1;

    // Calcular la nueva posición en base a la orbita
    angulo += 0.05; // Ajusta la velocidad de rotación segn sea necesario
    if (angulo >= 360) angulo -= 360;

    float x = personaje->x() + radio * std::cos(angulo);
    float y = personaje->y() + radio * std::sin(angulo);
    setPos(x + 20, y + 60); //posicion cambiada a mano

    // Verificar colisiones con enemigos
    QList<QGraphicsItem *> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
        if (enemigo){
            if(cantImpactos == 2){
                cantImpactos = 1;
                enemigo->recibirImpacto(); // esta funcion maneje la logica de recibir daño
            }else{
                cantImpactos++;
            }
        }
    }
}
