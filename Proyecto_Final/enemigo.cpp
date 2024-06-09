#include "enemigo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>

Enemigo::Enemigo(int nivel, Personaje *objetivo) : QGraphicsPixmapItem(), objetivo(objetivo){
    //en el constructor se paso la inicializacion del miembro objetivo
    //generacion de posicion aleatoria
    int aleatX = QRandomGenerator::global()->bounded(800 + 200);
    int aleatY = QRandomGenerator::global()->bounded(600 + 200);
    setPos(aleatX, aleatY);

    //establecer dificultad de enemigo
    cuentaImpact = 1;
    if(nivel == 1) nivelActual = 1;
    if(nivel == 2) nivelActual = 2;
    if(nivel == 3) nivelActual = 3;

    //para las texturas
    setTexturas(nivelActual);

    //para el manejo de impactos

    //uso de slots para el movimiento del enemigo
    tiempo = new QTimer(this);
    connect(tiempo, &QTimer::timeout, this, &Enemigo::moverEnemigo);
    tiempo->start(25); //modificar este tiempo cambia la velocidad

}
void Enemigo::moverEnemigo(){
    //if(!objetivo) return;
    //si objetivo es un puntero nulo evita la ejecucion de las lineas
    //de abajo, esto se verificó con chatgpt al presentar errores con personaje

    //posicion del personaje
    qreal objetivoX = objetivo->x();
    qreal objetivoY = objetivo->y();

    //calculamos la direccion hacia el objetivo
    qreal direccionX = objetivoX - x();
    qreal direccionY = objetivoY - y();
    qreal distancia = std::sqrt(objetivoX * objetivoX + objetivoY * objetivoY); //pitagoras

    //normalizamos el vetor de direcion para luego determinar como se debe mover el enemigo
    if(distancia != 0){
        qreal velocidad = 4.0;
        qreal movimientoX = (direccionX / distancia) * velocidad;
        qreal movimientoY = (direccionY / distancia) * velocidad;
        setPos(x() + movimientoX, y() + movimientoY);
    }
}

void Enemigo::recibirImpacto(){
    if(cuentaImpact == nivelActual){
        cuentaImpact = 1;
        emit eliminado(); //es una señal que va junto con la señal de cambio puntuacion
        scene()->removeItem(this);
        delete this;
    }else{
        cuentaImpact++;
    }
}

void Enemigo::setTexturas(int nivel){
    if(nivel == 1){
        generico.load(":/Imagenes/videoJuego/enemigo.png");
        QPixmap scaled_generico = generico.scaled(70, 70);
        setPixmap(scaled_generico);
    }else if(nivel == 2){
        generico.load(":/Imagenes/videoJuego/enemigo2.png");
        QPixmap scaled_enemigo = generico.scaled(70, 70);
        setPixmap(scaled_enemigo);
    }else if(nivel == 3){
        generico.load(":/Imagenes/videoJuego/enemigo2.png");
        QPixmap scaled_enemigo = generico.scaled(70, 70);
        setPixmap(scaled_enemigo);
    }
}

QTimer *Enemigo::getTimer()
{
    return tiempo;
}

