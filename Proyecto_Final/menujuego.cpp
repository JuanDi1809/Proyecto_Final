#include "menujuego.h"

MenuJuego::MenuJuego() : QObject(), escenaMenuJuego(new QGraphicsScene(this)) {
    decorarEscena();
    configurarEscena();
}

MenuJuego::~MenuJuego()
{
    delete escenaMenuJuego;
}

QGraphicsScene *MenuJuego::getEscena()
{
    return escenaMenuJuego;
}

void MenuJuego::decorarEscena()
{
    //Creando el fondo de la escena y ajustandolo a la escena
    QPixmap fondoMenuJuego("C:/Users/jtoro/OneDrive/Escritorio/Imagenes juego/BosqueTenebroso.jpg");
    QPixmap escalandoFondo = fondoMenuJuego.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //Cmabiando el fondo de la escena menu
    escenaMenuJuego->setBackgroundBrush(escalandoFondo);
}

void MenuJuego::configurarEscena(){
    escenaMenuJuego->setSceneRect(0, 0, 800, 600);

    // Crear un widget contenedor
    QWidget *contenedor = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(contenedor);

    //Creando un item de separador
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);


    // Crear los botones
    QPushButton *botonNuevaPartida = new QPushButton("NUEVA PARTIDA");
    botonNuevaPartida->setStyleSheet("QPushButton {"
                                    "background-color: gray ;"  // Color de fondo
                                    "color: black;"              // Color del texto
                                    "border-radius: 20px;"       // Esquinas redondeadas
                                    "padding: 10px;"             // Relleno
                                    "font-size: 20px;"           // Tamaño de fuente
                                    "font-style: Ghotic;"        //Estilo de fuente
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: white;" // Color de fondo al presionar el botón
                                    "}");


    QPushButton *botonCargarPartida = new QPushButton("CARGAR PARTIDA");
    botonCargarPartida->setStyleSheet("QPushButton {"
                                 "background-color: gray;"  // Color de fondo
                                 "color: black;"              // Color del texto
                                 "border-radius: 20px;"       // Esquinas redondeadas
                                 "padding: 10px;"             // Relleno
                                 "font-size: 20px;"           // Tamaño de fuente
                                 "font-style: Ghotic"        //Estilo de fuente
                                 "}"
                                 "QPushButton:pressed {"
                                 "background-color: white;" // Color de fondo al presionar el botón
                                 "}");

    QPushButton *botonVolver = new QPushButton("VOLVER");
    botonVolver->setStyleSheet("QPushButton {"
                                 "background-color: gray;"  // Color de fondo
                                 "color: black;"              // Color del texto
                                 "padding: 10px;"             // Relleno
                                 "font-size: 20px;"           // Tamaño de fuente
                                 "font-style: Ghotic"        //Estilo de fuente
                                 "}"
                                 "QPushButton:pressed {"
                                 "background-color: white;" // Color de fondo al presionar el botón
                                 "}");

    layout->addWidget(botonNuevaPartida);
    layout->addWidget(botonCargarPartida);
    layout->addSpacerItem(spacer);
    layout->addWidget(botonVolver);

    //Establecer el fondo del conetenedor
    contenedor->setAttribute(Qt::WA_TranslucentBackground);
    contenedor->setStyleSheet("background: transparent;");

    // Crear un QGraphicsProxyWidget y agregar el contenedor a la escena
    QGraphicsProxyWidget *proxy = escenaMenuJuego->addWidget(contenedor);

    QRectF sceneRect = escenaMenuJuego->sceneRect();
    QSizeF buttonSize = proxy->size();

    // Calcular la posición para centrar el botón en la escena
    qreal x = (sceneRect.width() - buttonSize.width()) / 2;
    qreal y = (sceneRect.height() - buttonSize.height()) / 2;


    // Establecer la posición del widget en la escena
    proxy->setPos(x, y);

    // Conectar el botón d
    connect(botonVolver, &QPushButton::clicked, this, &MenuJuego::on_botonVolver_clicked);
}

void MenuJuego::on_botonVolver_clicked() {
    emit cambiarEscena();
}
