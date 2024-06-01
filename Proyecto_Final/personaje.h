#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QVector2D>

class Personaje: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT //necesario para usar slots
public:
    Personaje();
    QPointF getDireccion();
    QString direccionApuntado();    //se usará para saber la direccion del personaje

    //metodos de personaje
    void disparar();
    void reducirVida(int cantidad);
    int getVida() const;
    int getPuntacion() const;
    void aumentarPuntuacion(int cantidad);

public slots:
    void manejoColision();

signals: //de esta forma podemos comunicar cambios de estado a otras partes del programa
    //el uso de señales nos permite que los objetos se comuniquen sin tener
    //acceso el uno del otro reduciendo sus dependencias
    void muerte();
    void vidaCambiada(int nuevaVida); //esto se envierá a la clase jeugo para mostrar en pantalla la vida
    void cambioPuntuacion(int nueva);

protected:
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void actualizarPosicion();

private:
    //tiempos
    QTimer *tiempoCol;
    QTimer *tempo;

    QPointF direccion;
    QString direccionActual; //para la construccion de imagenes
    qreal velocidad;
    bool arriba = false;
    bool abajo = false;
    bool derecha = false;
    bool izquierda = false;
    QSet<int> teclas;

    int vida; //vida inicial
    int puntuacion;

    //texturas
    QPixmap normal;
    QPixmap der;
    QPixmap izq;
    QPixmap abj;
    QPixmap arr;
    QPixmap ataqueImg;


};

#endif // PERSONAJE_H
