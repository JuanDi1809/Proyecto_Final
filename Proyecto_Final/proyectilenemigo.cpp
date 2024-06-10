#include "ProyectilEnemigo.h"
#include "personaje.h"
#include <QGraphicsScene>
#include <QList>
#include <cmath>

ProyectilEnemigo::ProyectilEnemigo(QPointF posInicial, QPointF posobj, QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(){

    this->posInicial = posInicial;
    setPos(posInicial); //establecemos la posicion con enemigo

    //calculamos velocidad inicial que tendrá el proyectil
    QPointF delta = posobj - posInicial;
    //float distancia = std::sqrt(delta.x() * delta.x() + delta.y() + delta.y());
    float velInicial = 40.0; //si ajustamos esta velocidad cambia el proyectil
    float angulo = std::atan2(delta.y(), delta.x());

    //luego seteamos el atributo velocidad
    velocidad.setX(velInicial * std::cos(angulo));
    velocidad.setY(velInicial * std::sin(angulo));

    //gravedad y tiempo
    gravedad = 9.8; //modificado para la caida de los proy
    tiempo = 0;

    QPixmap pixmap(":/Imagenes/videoJuego/fire.png");
    QPixmap scaled = pixmap.scaled(50, 50);
    setPixmap(scaled);

    //slot
    tiempoProy = new QTimer(this);
    connect(tiempoProy, &QTimer::timeout, this, &ProyectilEnemigo::mover);
    tiempoProy->start(10);
}

QTimer *ProyectilEnemigo::getTimer()
{
    return tiempoProy;
}

void ProyectilEnemigo::mover(){
    tiempo += 0.12; //actualizamos el tiempo para el seguimiento de l movimiento

    //calculamos y establecemos la nueva posicion constantemente
    float dirx = velocidad.x() * tiempo;
    //float diry = velocidad.y() * tiempo;
    float diry = (velocidad.y() * tiempo) + (0.5 * gravedad * tiempo * tiempo);

    setPos(posInicial.x() + dirx, posInicial.y() + diry);

    //verificar colision con personaje y luego emitir señal de que
    //le hizo daño
    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Personaje *personaje = dynamic_cast<Personaje*>(item);
        if (personaje) {
            personaje->reducirVida(2); // Ajusta la cantidad de daño según sea necesario
            emit personajeGolpeado();

            // Eliminar el proyectil después del impacto
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    //eliminar proyectil de la escena luego de choque
    if (pos().y() > scene()->height() || pos().x() < 0 || pos().x() > scene()->width()) {
        scene()->removeItem(this);
        delete this;
    }
}
