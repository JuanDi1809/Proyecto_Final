#ifndef PROYECTILENEMIGO_H
#define PROYECTILENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

class ProyectilEnemigo : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    ProyectilEnemigo(QPointF posIinicial, QPointF posobj, QObject * parent = nullptr);

    QTimer *getTimer();
public slots:
    void mover();
signals: //sera tratado como una señal para detectar impaco con personaje y que este reciba daño
    void personajeGolpeado();
private:
    QPointF velocidad;
    float gravedad;
    float tiempo;
    QPointF posInicial;
    QTimer *tiempoProy;

};

#endif // PROYECTILENEMIGO_H
