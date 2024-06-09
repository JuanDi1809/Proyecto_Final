#include "juego.h"
#include "ui_juego.h"

extern QString usu, pass;
extern vector<string> datos;
extern string ruta;
/*
La variable nivelActual es declarada como global para saber como parar y reanudar los timers en los cambios de
nivel y las pausas en el menu del juego
*/
int nivelActual;

Juego::Juego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Juego)
    , puntuacionObjetivo(10)
{
    ui->setupUi(this);
    this->resize(1600, 900);

    escena = new QGraphicsScene();
    escena->setSceneRect(0,0, 1600, 900);
    escena->setBackgroundBrush(QBrush(QPixmap(":/Imagenes/videoJuego/back.png")));

    //Configurando la escena
    ui->graphicsView->setScene(escena);
    ui->graphicsView->setFixedSize(1600, 900);
    ui->graphicsView->setSceneRect(0, 0, 1600, 900);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //configurando boton de ajustes
    ui->botonAjustes->setIcon(QIcon(":/Imagenes/videoJuego/IconoAjustes"));
    ui->botonAjustes->setIconSize(QSize(35, 35));

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

    //seleccion de arma
    //el evento que muestra los nuevos niveles es cuando se presiona el boton
    seleccionarma = new SeleccionArma();
    connect(seleccionarma, &SeleccionArma::iniciarNivel, this, &Juego::iniciarNivel);

    //Coneects para reanudar los timers, cerrar sesion y guardado
    connect(pausa, &MenuPausa::reanudar, this, &Juego::reanudarTimers);
    connect(pausa, &MenuPausa::cerrar, this, &Juego::cerrarSesion);
    connect(pausa, &MenuPausa::guardar, this, &Juego::guardado);

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
    QString backgroundPath;
    if(nivel == 1){
        backgroundPath = ":/Imagenes/videoJuego/back.png";
    }else if(nivel == 2){
        backgroundPath = ":/Imagenes/videoJuego/back2.png";
    }else if(nivel == 3){
        backgroundPath = ":/Imagenes/videoJuego/back3.png";
    }
    escena->setBackgroundBrush(QBrush(QImage(backgroundPath)));
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
        actualizarNivel(800);
    }
    else{
        if(nivelActual == 2){
            actualizarNivel(600);
        }
        else{
            actualizarNivel(400);
        }

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
    personaje->getTimer()->stop();
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

    enemigoTiempo->start(time);
    personaje->getTimer()->start();

}

void Juego::limpiarNivel(){

    for (auto item : escena->items()) {
        Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
        if (enemigo) {
            escena->removeItem(enemigo);
            delete enemigo;
        }
    }

    for (auto item : escena->items()){
        Proyectil *proyectil = dynamic_cast<Proyectil*>(item);
        if(proyectil){
            escena->removeItem(proyectil);
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

void Juego::reanudarTimers(int time){
    personaje->getTimer()->start(); //Reaunda el timer del personaje principal
    enemigoTiempo->start(time); //Reanuda el timer de la creacion de enemigos

    //Reaunda el timer de los enemigos en la escena
    for (auto item : escena->items()){
        Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
        if(enemigo){
            enemigo->getTimer()->start();
        }
    }

    //Reanuda el timer de los proyectiles en la escena
    for (auto item : escena->items()){
        Proyectil *proyectil = dynamic_cast<Proyectil*>(item);
        if(proyectil){
            proyectil->getTimer()->start();
        }
    }
}

void Juego::pararTimers()
{
    personaje->getTimer()->stop(); //Paro el timer del personaje principal
    enemigoTiempo->stop(); //Para el timer de la creacion de enemigos

    //Para el timer para cada enemigo en la escena
    for (auto item : escena->items()){
        Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
        if(enemigo){
            enemigo->getTimer()->stop();
        }
    }

    //Para timer para los proyectiles en la escena
    for (auto item : escena->items()){
        Proyectil *proyectil = dynamic_cast<Proyectil*>(item);
        if(proyectil){
            proyectil->getTimer()->stop();
        }
    }
}

void Juego::cerrarSesion()
{
    this->close();
}

void Juego::guardado()
{
    ofstream archivo(ruta + usu.toStdString() + ".txt"); //La idea es volver a sobreescribir los datos

    if(archivo.is_open()){
        archivo << usu.toStdString() << "\n" << pass.toStdString() << "\n" << personaje->getPuntacion() << "\n" << personaje->getVida() << "\n" << nivelActual;
        archivo.close();

        datos[2] = to_string(personaje->getPuntacion());
        datos[3] = to_string(personaje->getVida());
        datos[4] = to_string(nivelActual);

        QMessageBox msgBox;
        msgBox.setText("La partida se guardo con exito");
        msgBox.exec();
    }
}


void Juego::on_botonAjustes_clicked()
{
    pararTimers();
    pausa->show();
}

