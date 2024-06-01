#include "juego.h"
#include "ui_juego.h"

Juego::Juego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Juego)
    , puntuacionObjetivo(50)
{
    ui->setupUi(this);

    escena = new QGraphicsScene();
    escena->setSceneRect(0,0, 800, 900);
    escena->setBackgroundBrush(QBrush(QImage(":/Imagenes/videoJuego/back.png")));

    ui->graphicsView->setScene(escena);
    ui->graphicsView->setFixedSize(1600, 900);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //imagen muerte
    muerte = new QGraphicsPixmapItem;
    QPixmap imagen(":/Imagenes/videoJuego/muerte.png");
    QSize tamanioVentana = size();
    imagen = imagen.scaled(tamanioVentana, Qt::KeepAspectRatio);
    muerte->setPixmap(imagen);
    muerte->setPos(500,500);
    muerte->setVisible(false);
    escena->addItem(muerte);

    //creacion de elementos en escena:
    personaje = new Personaje();
    //personaje->setPixmap(normal);
    personaje->setPos(width() / 2, height() / 2); //posicion en el centro


    //establecer valores para aumentar dificultad
    establecerNivel(1);
    //añadir nuevo poder en el nivel 3...

    //creacion textos
    vidaTexto = new QGraphicsTextItem();
    nivelJuego = new QGraphicsTextItem();

    //nivel
    nivelJuego->setPlainText(QString("Nivel: %1").arg(nivelActual));
    nivelJuego->setDefaultTextColor(Qt::white);
    nivelJuego->setFont(QFont("times", 24));
    nivelJuego->setPos(742, 60);

    //vida
    vidaTexto->setPlainText(QString("Vida:%1 | ").arg(personaje->getVida()));
    vidaTexto->setDefaultTextColor(Qt::white);
    vidaTexto->setFont(QFont("times", 15, 1, true));
    vidaTexto->setPos(70, 55);

    //puntuacion
    ptsJugador = new QGraphicsTextItem();
    ptsJugador->setPlainText(QString("Eliminados: %1").arg(personaje->getPuntacion()));
    ptsJugador->setDefaultTextColor(Qt::white);
    ptsJugador->setFont(QFont("times", 15, 1, true));
    ptsJugador->setPos(160, 55);

    //mensaje puntuacion objetivo lograda
    mensajeNivel = new QGraphicsTextItem();
    mensajeNivel->setDefaultTextColor(Qt::yellow);
    mensajeNivel->setFont(QFont("Arial", 24));
    mensajeNivel->setPos(600, 400);
    mensajeNivel->setVisible(false);  // Inicialmente no visible
    escena->addItem(mensajeNivel);

    escena->addItem(ptsJugador);
    escena->addItem(nivelJuego);
    escena->addItem(vidaTexto);

    //slots para cambio de vida
    //hacemos la conexion entre la señal vidaCambiada y actualizarVida
    connect(personaje, &Personaje::vidaCambiada, this, &Juego::actualizarVida);
    connect(personaje, &Personaje::cambioPuntuacion, this, &Juego::actualizarPuntuacion);


    //player focusable
    personaje->setFlag(QGraphicsItem::ItemIsFocusable);
    personaje->setFocus();
    //añadimos al jugador en la escena
    escena->addItem(personaje);

    //añadir enemigos
    /*for(int i = 0; i < 10; i++){
        Enemigo *enemigo = new Enemigo(personaje);
        escena->addItem(enemigo);
    }*/
    tiempo = new QTimer(this);
    connect(tiempo, &QTimer::timeout, this, &Juego::crearEnemigo);
    tiempo->start(600); //cambiando este dato podemos definir dificultad

    connect(personaje, &Personaje::muerte, this, &Juego::mostrarImagenMuerte);

}

Juego::~Juego()
{
    delete ui;
}


void Juego::establecerNivel(int nivel){
    nivelActual = nivel;
}

void Juego::verificarPuntuacion(){
    if (personaje->getPuntacion() >= puntuacionObjetivo) {
        nivelActual++;
        puntuacionObjetivo *= 2;
        nivelJuego->setPlainText(QString("Nivel: %1").arg(nivelActual));

        mensajeNivel->setPlainText(QString("Has pasado al nivel %1").arg(nivelActual));
        mensajeNivel->setVisible(true);

        //temporizador para ocultar mensaje luego de 2 segundos
        QTimer::singleShot(3000, [this](){
            mensajeNivel->setVisible(false);
        });
    }
}

void Juego::actualizarPuntuacion(int nuevaPts){
    ptsJugador->setPlainText(QString("Eliminados: %1").arg(nuevaPts));
    verificarPuntuacion();
}

void Juego::actualizarVida(int nuevaVida){
    vidaTexto->setPlainText(QString("Vida:%1 | ").arg(nuevaVida));

}

void Juego::mostrarImagenMuerte(){
    muerte->setVisible(true);
    tiempo->stop();
    setFocusPolicy(Qt::NoFocus);
    //aqui irá el retorno al menu del juego
}

void Juego::crearEnemigo(){
    //generacion aleatoria de enemigo
    int randomX = rand() % 1600;
    int randomY= rand() % 900;

    //añadir enemigo a escena
    Enemigo *enemigo = new Enemigo(nivelActual, personaje);
    enemigo->setPos(randomX, randomY);
    escena->addItem(enemigo);
}
