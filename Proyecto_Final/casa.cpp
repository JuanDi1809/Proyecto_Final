#include "casa.h"
#include "QGraphicsScene"


Casa::Casa(int x, int y, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), cuentaImpactos(0) {
    QPixmap pixmap(":/Imagenes/videoJuego/casa.png");
    QPixmap scaledPixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio); // Cambiar 100x100 según sea necesario
    setPixmap(scaledPixmap);

    //establecemos posiciones predeterminadas
    setPos(x, y);

}

void Casa::recibirImpacto() {
    cuentaImpactos++;
    if (cuentaImpactos >= 3) {
        emit casaDestruida();
        scene()->removeItem(this);
        delete this;
    }
}
