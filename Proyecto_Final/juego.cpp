#include "juego.h"
#include "ui_juego.h"

extern QString usu, pass;
extern vector<string> datos;

Juego::Juego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Juego)
    , puntuacionObjetivo(100)
{
    ui->setupUi(this);

    //Añadiendo imagen de ajuste
    QIcon IconoBotonAjuste(":/Imagenes/videoJuego/IconoAjustes.png");
    ui->botonAjustes->setIcon(IconoBotonAjuste);
    ui->botonAjustes->setIconSize(QSize(35,35)); // Ajusta el tamaño del icono según sea necesario


    escena = new QGraphicsScene();
    escena->setSceneRect(0,0, 1600, 900);
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

    //creacion textos
    vidaTexto = new QGraphicsTextItem();
    nivelJuego = new QGraphicsTextItem();
    ptsJugador = new QGraphicsTextItem();

    //nivel
    nivelJuego->setDefaultTextColor(Qt::white);
    nivelJuego->setFont(QFont("times", 24));
    nivelJuego->setPos(742, 60);

    //vida
    vidaTexto->setDefaultTextColor(Qt::white);
    vidaTexto->setFont(QFont("times", 15, 1, true));
    vidaTexto->setPos(70, 55);

    //puntuacion
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

    //Personaje
    personaje = new Personaje();
    //personaje->setPixmap(normal);
    personaje->setPos(width() / 2, height() / 2); //posicion en el centro
    //player focusable
    personaje->setFlag(QGraphicsItem::ItemIsFocusable);
    personaje->setFocus();
    //añadimos al jugador en la escena
    escena->addItem(personaje);

    //slots para cambio de vida
    //hacemos la conexion entre la señal vidaCambiada y actualizarVida
    connect(personaje, &Personaje::vidaCambiada, this, &Juego::actualizarVida);
    connect(personaje, &Personaje::cambioPuntuacion, this, &Juego::actualizarPuntuacion);

    //establecer niveles
    //nivel inicial
    enemigoTiempo = new QTimer(this);
    connect(enemigoTiempo, &QTimer::timeout, this, &Juego::crearEnemigo);

    connect(personaje, &Personaje::muerte, this, &Juego::mostrarImagenMuerte);
    actualizarNivel(1000);

    //seleccion de arma
    //el evento que muestra los nuevos niveles es cuando se presiona el boton
    seleccionarma = new SeleccionArma();
    connect(seleccionarma, &SeleccionArma::iniciarNivel, this, &Juego::iniciarNivel);

    cargarEstado();

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

        //ventana para la seleccion de arma
        mostrarSeleccionArma();

    }
}

void Juego::setBack(int nivel){
    if(nivel == 1){
        escena->setSceneRect(0,0, 1600, 900);
        escena->setBackgroundBrush(QBrush(QImage(":/Imagenes/videoJuego/back.png")));
    }else if(nivel == 2){
        escena->setSceneRect(0,0, 1600, 900);
        escena->setBackgroundBrush(QBrush(QImage(":/Imagenes/videoJuego/back2.png")));
    }else if(nivel == 3){
        escena->setSceneRect(0,0, 1600, 900);
        escena->setBackgroundBrush(QBrush(QImage(":/Imagenes/videoJuego/back3.png")));
    }

}

void Juego::cargarEstado()
{
    if(datos[2] == "0" && datos[3] == "100" && datos[4] == "1"){
        QString puntuacion = QString::fromUtf8(datos[2]);
        QString vida = QString::fromUtf8(datos[3]);


        //Realizo las respectivas modificaciones para la inicializacion de la partida
        ptsJugador->setPlainText(QString("Puntaje: %1").arg(puntuacion));
        vidaTexto->setPlainText(QString("Vida:%1 | ").arg(vida));
        establecerNivel(stoi(datos[4]));
        nivelJuego->setPlainText(QString("Nivel: %1").arg(nivelActual));
        setBack(stoi(datos[4]));
        personaje->setVida(vida.toInt());
        personaje->setPuntuacion(puntuacion.toInt());
    }
    else{
        QString puntuacion = QString::fromUtf8(datos[2]);
        QString vida = QString::fromUtf8(datos[3]);

        //Realizo las respectivas modificaciones para la inicializacion de la partida
        ptsJugador->setPlainText(QString("Puntaje: %1").arg(puntuacion));
        vidaTexto->setPlainText(QString("Vida:%1 | ").arg(vida));
        establecerNivel(stoi(datos[4]));
        nivelJuego->setPlainText(QString("Nivel: %1").arg(nivelActual));
        setBack(stoi(datos[4]));
        personaje->setVida(vida.toInt());
        personaje->setPuntuacion(puntuacion.toInt());
    }
}

void Juego::actualizarPuntuacion(int nuevaPts){
    ptsJugador->setPlainText(QString("Puntaje: %1").arg(nuevaPts));
    verificarPuntuacion();
}

void Juego::actualizarVida(int nuevaVida){
    vidaTexto->setPlainText(QString("Vida:%1 | ").arg(nuevaVida));

}

void Juego::mostrarImagenMuerte(){
    muerte->setVisible(true);
    enemigoTiempo->stop();
    setFocusPolicy(Qt::NoFocus);
    //aqui irá el retorno al menu del juego
}

void Juego::mostrarSeleccionArma(){
    //con esto detenemos la generacion de enemigos
    enemigoTiempo->stop();
    limpiarNivel();

    //para actualizar la vida y mostrar la nueva
    personaje->setVida();
    personaje->setPos(width() / 2, height() / 2); //posicion en el centro
    vidaTexto->setPlainText(QString("Vida:%1 | ").arg(personaje->getVida()));

    //mostramos ventana
    seleccionarma->show();

}

void Juego::iniciarNivel(){
    if(nivelActual == 2){
        seleccionarma->hide();
        actualizarNivel(600);
        setBack(nivelActual);
    }else if(nivelActual == 3){
        seleccionarma->hide();
        actualizarNivel(400);
        setBack(nivelActual);
    }
}

void Juego::actualizarNivel(int time){
    // se define el tiempo del enemigo
    enemigoTiempo->stop();
    limpiarNivel();
    //cambio de imagenes y otros metodos....
    enemigoTiempo->start(time); //cambiando este dato podemos definir dificultad
}

void Juego::limpiarNivel(){
    for (auto item : escena->items()) {
        Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
        if (enemigo) {
            escena->removeItem(enemigo);
            delete enemigo;
        }
    }
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

void Juego::on_botonAjustes_clicked()
{
    MenuPausa *pausa = new MenuPausa;
    pausa->show();
}

