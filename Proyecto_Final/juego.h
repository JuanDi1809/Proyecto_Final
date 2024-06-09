#ifndef JUEGO_H
#define JUEGO_H

#include "personaje.h"
#include "enemigo.h"
#include "seleccionarma.h"
#include "menupausa.h"
#include "proyectil.h"
#include <QVBoxLayout>
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
#include <QGraphicsProxyWidget>
#include <vector>
#include <string>
#include <QDebug>

using namespace std;


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

    //background
    void setBack(int nivel);
    void cargarEstado(); //Permtira cargar el juego con el nivel de juego, la vida y la puntuacion en donde quedo el usuario
    void pararTimers();
private slots:
    void crearEnemigo();
    void actualizarVida(int nuevaVida);
    void actualizarPuntuacion(int nuevaPts);
    void mostrarImagenMuerte();

    //subida de nivel (cambio de escena
    void mostrarSeleccionArma();
    void iniciarNivel();

    void reanudarTimers(int);

private:
    Ui::Juego *ui;
    QGraphicsScene * escena;
    Personaje * personaje;
    SeleccionArma *seleccionarma;
    QTimer *tiempo;
    QTimer *enemigoTiempo;
    QGraphicsTextItem *vidaTexto;
    QGraphicsTextItem *nivelJuego;
    QGraphicsTextItem *ptsJugador;
    MenuPausa *pausa = new MenuPausa;
    int parametroComando;

    //imagen muerte
    QGraphicsPixmapItem *muerte;
    QPixmap *imagen;

    //datos para definir dificultad
    //int nivel;
    int puntuacionObjetivo;
    QGraphicsTextItem *mensajeNivel;


    //metodos encapsulados
    void actualizarNivel(int tiempo);
    void limpiarNivel();
    void eliminarItem(QGraphicsPixmapItem*);
};

#endif // JUEGO_H
