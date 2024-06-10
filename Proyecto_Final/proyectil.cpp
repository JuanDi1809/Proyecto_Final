#include "proyectil.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "Enemigo.h"
#include <QKeyEvent>


Proyectil::Proyectil(Personaje *personaje, QPointF &direccion): direccion(direccion), velocidad(5), personaje(personaje){

    //posicion inicial y tamaño

    //conectar a slot
    tiempo = new QTimer();
    connect(tiempo, SIGNAL(timeout()), this, SLOT(colisiones()));
    tiempo->start(10);
    //cada 50ms tiempo el proyectil será disparado
}

QPixmap Proyectil::getProyectil(){
    return proy;
}

QTimer *Proyectil::getTimer()
{
    return tiempo;
}

void Proyectil::colisiones(){
    QList<QGraphicsItem*> itemsColisionados = collidingItems();
    for(QGraphicsItem *item : itemsColisionados){
        if(typeid(*item) == typeid(Enemigo)){
            //usamos dynamic_cast para hacer la conversion qgi a un puntero tipo enemigo
            //esto funciona ya que solo se hace en este condicional donde item apunta a un enemigo
            Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
            if(enemigo){
                //la puntuacion se maneja en este metodo
                enemigo->recibirImpacto();
                //scene()->removeItem(this);
                personaje->aumentarPuntuacion(1); //cambiar este metodo
                delete this;
                return; //necesario para las lineas siguientes
            }
        }
    }
    //movimiento del proyectil
    setPos(x() + direccion.x() * velocidad, y() + direccion.y() * velocidad);
    //se elimina cuando este en la posicion 0 respectiva a la escena
    if(pos().y() + pixmap().height() < 0){
        scene()->removeItem(this);
        delete this; //hace referencia al mismo objeto que se le pasa a la señal en el constructor
    }
}

void Proyectil::actualizarImagen(const QString &direccion){
    //texturas de proyectil;
    proy_izq.load(":/Imagenes/videoJuego/proy.png");
    QPixmap scaled_izq = proy_izq.scaled(100,100);
    proy_der.load(":/Imagenes/videoJuego/proy_der.png");
    QPixmap scaled_der = proy_der.scaled(100,100);
    proy_abj.load(":/Imagenes/videoJuego/proy_abj.png");
    QPixmap scaled_abj = proy_abj.scaled(100,100);
    proy_arr.load(":/Imagenes/videoJuego/proy_arr.png");
    QPixmap scaled_arr = proy_arr.scaled(100,100);

    if(direccion == "W"){
        setPixmap(scaled_arr);
    }else if(direccion == "S"){
        setPixmap(scaled_abj);
    }
    else if(direccion == "D"){
        setPixmap(scaled_der);
    }
    else if(direccion == "A"){
        setPixmap(scaled_izq);
    }

}


