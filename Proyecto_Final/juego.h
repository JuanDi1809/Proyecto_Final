#ifndef JUEGO_H
#define JUEGO_H

#include "personaje.h"
#include "enemigo.h"
#include <QWidget>
#include <QVector2D>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QMessageBox>
#include <QDebug>
#include <QObject>

namespace Ui {
class Juego;
}

class Juego : public QWidget
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = nullptr);
    ~Juego();

    //setters de dificultad
    void establecerNivel(int nivel);
    int getNivelActual();
    void verificarPuntuacion();
private slots:
    void crearEnemigo();
    void actualizarVida(int nuevaVida);
    void actualizarPuntuacion(int nuevaPts);
    void mostrarImagenMuerte();

private:
    Ui::Juego *ui;
    QGraphicsScene * escena;
    Personaje * personaje;
    QTimer *tiempo;
    QGraphicsTextItem *vidaTexto;
    QGraphicsTextItem *nivelJuego;
    QGraphicsTextItem *ptsJugador;
    //imagen muerte
    QGraphicsPixmapItem *muerte;

    //datos para definir dificultad
    int nivel;
    int puntuacionObjetivo;
    QGraphicsTextItem *mensajeNivel;
    int nivelActual;
};

#endif // JUEGO_H
