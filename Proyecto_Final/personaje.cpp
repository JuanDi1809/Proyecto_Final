#include "personaje.h"
#include "Enemigo.h"
#include "proyectil.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>

Personaje::Personaje() : vida(100), puntuacion(0){
    ataqueImg.load(":/Imagenes/videoJuego/ataque.png");

    //slot para frecuencia de actualizacion de movimiento
    tempo = new QTimer(this);
    connect(tempo, &QTimer::timeout, this, &Personaje::actualizarPosicion);
    tempo->start(26);

    //slot para manejo de vida
    tiempoCol = new QTimer(this);
    connect(tiempoCol, &QTimer::timeout, this, &Personaje::manejoColision);
    tiempoCol->start(50); //cada 20 ms se verifica si hubo colision

    //direccion inicial de apuntado
    direccion = QPointF(0, -1); //hacia arriba

    normal.load(":/Imagenes/videoJuego/plaga.png");
    QPixmap scaled = normal.scaled(100,100);

    setPixmap(scaled);
}
void Personaje::reducirVida(int cantidad){
    vida -= cantidad;
    emit vidaCambiada(vida);
    if(vida <= 0){
        emit muerte(); //se envía la señal de que personaje murio
        scene()->removeItem(this);
        delete this;
    }
}
void Personaje::manejoColision(){
    //explicacion:
    //el tipo de datos es una lista de todos los elementos que colisionan
    //con el objeto personaje, en este caso es el creado en esta clase
    //luego se itera por todos los items colisionados y se compara
    //si el tipo dinamico item colisionado es igual al enemigo entonces es porque hubo colision
    QList<QGraphicsItem*> itemsColisionados = collidingItems();
    for(QGraphicsItem *item : itemsColisionados){
        if(typeid(*item) == typeid(Enemigo)){
            reducirVida(1);
        }
    }

}

int Personaje::getVida() const{
    return vida;
}

int Personaje::getPuntacion() const{
    return puntuacion;
}
void Personaje::aumentarPuntuacion(int cantidad){
    puntuacion += cantidad; //se sumara segun la cantidad de enemigos que elimine
    emit cambioPuntuacion(puntuacion);
}

void Personaje::setVida(){
    vida *= 2;
}

void Personaje::setVida(int _vida)
{
    vida = _vida;
}

void Personaje::setPuntuacion(int _puntuacion)
{
    puntuacion = _puntuacion;
}

void Personaje::keyPressEvent(QKeyEvent *event)
{
    //para la deteccion de la direccion a la que apunta personaje
    switch(event->key()){
    case Qt::Key_W:
        arriba = true;
        direccionActual = "W";
        break;
    case Qt::Key_S:
        abajo = true;
        direccionActual = "S";
        break;
    case Qt::Key_A:
        izquierda = true;
        direccionActual = "A";
        break;
    case Qt::Key_D:
        derecha = true;
        direccionActual = "D";
        break;
    default:
        break;
    }

    //se registra la direccion
    direccion = QPointF(derecha - izquierda, abajo - arriba);
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S || event->key() == Qt::Key_A || event->key() == Qt::Key_D) {
        QPixmap scaled_atq = ataqueImg.scaled(100,100);
        setPixmap(scaled_atq);
        disparar();
    }
    teclas.insert(event->key());
}
void Personaje::keyReleaseEvent(QKeyEvent *event){

    switch(event->key()){
    case Qt::Key_W:
        arriba = false;
        direccionActual = "W";
        break;
    case Qt::Key_S:
        abajo = false;
        direccionActual = "S";
        break;
    case Qt::Key_A:
        izquierda = false;
        direccionActual = "A";
        break;
    case Qt::Key_D:
        derecha = false;
        direccionActual = "D";
        break;
    default:
        break;
    }

    //se registra la direccion
    direccion = QPointF(derecha - izquierda, abajo - arriba);
    teclas.remove(event->key());
    //cuando se deja de presionar la tecla
    QPixmap scaled = normal.scaled(100,100);
    setPixmap(scaled);
}

QPointF Personaje::getDireccion(){
    return direccion;
}

QString Personaje::direccionApuntado(){
    return direccionActual;
}

void Personaje::disparar(){
    Proyectil *proyectil = new Proyectil(this, direccion);
    //se pasa la direccion donde apunta jugador para determinar que imagen se pone al proyectil
    proyectil->actualizarImagen(direccionActual);
    //posicion del proyectil
    proyectil->setPos(x() + pixmap().width() / 4, y() + pixmap().height() / 4);
    scene()->addItem(proyectil);
}

void Personaje::actualizarPosicion(){
    izq.load(":/Imagenes/videoJuego/izq.png");
    QPixmap scaled_izq = izq.scaled(100,90);
    abj.load(":/Imagenes/videoJuego/abajo.png");
    QPixmap scaled_abj = abj.scaled(100,90);
    arr.load(":/Imagenes/videoJuego/arr.png");
    QPixmap scaled_arr = arr.scaled(100,90);
    der.load(":/Imagenes/videoJuego/der.png");
    QPixmap scaled_der = der.scaled(100,90);


    int movimientoX = 0, movimientoY = 0;
    if (teclas.contains(Qt::Key_Left)) {
        movimientoX -= 10;
        setPixmap(scaled_izq);
    }
    if (teclas.contains(Qt::Key_Right)) {
        movimientoX += 10;
        setPixmap(scaled_der);
    }
    if (teclas.contains(Qt::Key_Up)) {
        movimientoY -= 10;
        setPixmap(scaled_arr);
    }
    if (teclas.contains(Qt::Key_Down)) {
        movimientoY += 10;
        setPixmap(scaled_abj);
    }

    //limitar bordes
    //posiciones actuales mas el desplazamiento en pixeles que tuvo
    qreal limiteX = x() + movimientoX;
    qreal limiteY = y() + movimientoY;

    //en caso de que la posicion del rect sea negativa, es decir fuera de las dimensiones de la vista
    if(limiteX < 0) limiteX = 0;
    if(limiteY < 0) limiteY = 0;

    if(limiteX + pixmap().width() > 1600) limiteX = 1600 - pixmap().width();
    if(limiteY + pixmap().height() > 900) limiteY = 900 - pixmap().height();

    // Actualiza la posición del personaje
    if (movimientoX != 0 || movimientoY != 0) {
        setPos(limiteX, limiteY);
    }
}


