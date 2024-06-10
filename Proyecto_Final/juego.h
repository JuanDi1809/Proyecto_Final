#ifndef JUEGO_H
#define JUEGO_H

#include "personaje.h"
#include "enemigo.h"
#include "seleccionarma.h"
#include "menupausa.h"
#include "proyectil.h"
#include "pantallafin.h"
#include "casa.h"
#include "orbital.h"
#include "proyectilenemigo.h"

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
#include <vector>
#include <string>
#include <QMediaPlayer>
#include <QAudioOutput>

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

    void agregarCasas();

    //Permtira cargar el juego con el nivel de juego, la vida y la puntuacion en donde quedo el usuario
    void cargarEstado();
    void pararTimers();
    void cerrarSesion();
    void guardado();
private slots:
    void crearEnemigo();
    void actualizarVida(int nuevaVida);
    void actualizarPuntuacion(int nuevaPts);
    void mostrarImagenMuerte();

    //subida de nivel (cambio de escena
    void mostrarSeleccionArma();
    void mostrarPantallaFinal();
    void iniciarNivel();

    void reanudarTimers(int);
    void on_botonAjustes_clicked();

private:
    Ui::Juego *ui;
    QGraphicsScene *escena;
    Personaje *personaje;
    SeleccionArma *seleccionarma;
    PantallaFin *pantallafinal;
    QTimer *tiempo;
    QTimer *enemigoTiempo;
    QGraphicsTextItem *vidaTexto;
    QGraphicsTextItem *nivelJuego;
    QGraphicsTextItem *ptsJugador;
    MenuPausa *pausa = new MenuPausa;

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

    //musica de fondo
    QMediaPlayer *backsound;
    QAudioOutput *audioOut;
};

#endif // JUEGO_H
