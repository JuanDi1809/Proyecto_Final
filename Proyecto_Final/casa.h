#ifndef CASA_H
#define CASA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Casa : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Casa(int x, int y,QGraphicsItem *parent = nullptr); //es un objeto por si mismo
    void recibirImpacto(); //esta será la encaergada de manejra las señales que se envian

signals:
    void casaDestruida(); //esta señal determina cuando la casa se elimina de la escena

private:
    int cuentaImpactos;
};

#endif // CASA_H
