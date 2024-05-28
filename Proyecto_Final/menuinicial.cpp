#include "menuinicial.h"
#include "juego.h"
#include <QString>
#include <iostream>

using namespace std;


MenuInicial::MenuInicial() : QObject(), escenaMenu(new QGraphicsScene(this)), datos(new Guardado()) {
    decorarEscena();
    configurarEscena();
}

MenuInicial::~MenuInicial()
{
    delete escenaMenu;
    delete datos;
}

QGraphicsScene *MenuInicial::getEscena()
{
    return escenaMenu;
}

void MenuInicial::configurarEscena()
{
    //Etsbaleciendo el tamaño de la escena
    escenaMenu->setSceneRect(0,0, 800,600);

    // Crear un widget contenedor
    QWidget *contenedor = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(contenedor);

    // Crear titulo de juego
    QLabel *tituloJuego = new QLabel("PESTE NEGRA");
    QFont fuenteJuego("Ghotic", 50, QFont::Bold );

    tituloJuego->setFont(fuenteJuego);
    tituloJuego->setStyleSheet("color:white");

    //Crear titulo nombre
    QLabel *tituloNombre = new QLabel("USUARIO");

    tituloNombre->setStyleSheet(("color:white;"
                                 "font-size: 20px;"
                                 "fon-style: Ghotic"));
    tituloNombre->setAlignment(Qt::AlignCenter);

    //Crear titulo contraseña
    QLabel *tituloContraseña = new QLabel("CONTRASEÑA");

    tituloContraseña->setStyleSheet(("color:white;"
                                     "font-size: 20px;"
                                     "font-style: Ghotic"));
    tituloContraseña->setAlignment(Qt::AlignCenter);

    //Crear lineEdit para ingresar dato del nombre
    QHBoxLayout *usuarioLayout = new QHBoxLayout();
    usuario = new QLineEdit();
    usuario->setStyleSheet("background-color : gray;");
    usuario->setFixedWidth(300);
    usuario->setAlignment(Qt::AlignCenter);
    usuarioLayout->addWidget(usuario);

    //Crear lineEdit para ingresar dato de la contraseña
    QHBoxLayout *contraseñaLayout = new QHBoxLayout();
    contraseña = new QLineEdit();
    contraseña->setStyleSheet("background-color : gray;");
    contraseña->setFixedWidth(300);
    contraseña->setAlignment(Qt::AlignCenter);
    contraseña->setEchoMode(QLineEdit::Password);
    contraseñaLayout->addWidget(contraseña);



    //Creando un item de separador
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);


    // Crear un layout horizontal para los botones "REGISTRARSE" e "INGRESAR"
    QHBoxLayout *botonesLayout = new QHBoxLayout();
    QPushButton *botonRegistrarse = new QPushButton("REGISTRARSE");
    botonRegistrarse->setStyleSheet("QPushButton {"
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


    QPushButton *botonIngresar = new QPushButton("INGRESAR");
    botonIngresar->setStyleSheet("QPushButton {"
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

    //Agregando los botones
    botonesLayout->addWidget(botonRegistrarse);
    botonesLayout->addSpacerItem(spacer);
    botonesLayout->addWidget(botonIngresar);

    // Agregar widgets al layout del contenedor
    layout->addWidget(tituloJuego);
    layout->addSpacerItem(spacer);
    layout->addWidget(tituloNombre);
    layout->addLayout(usuarioLayout);
    layout->addWidget(tituloContraseña);
    layout->addLayout(contraseñaLayout);
    layout->addSpacerItem(spacer);
    layout->addLayout(botonesLayout);

    //Establecer el fondo del conetenedor
    contenedor->setAttribute(Qt::WA_TranslucentBackground);
    contenedor->setStyleSheet("background: transparent;");


    // Crear un QGraphicsProxyWidget y agregar el contenedor a la escena
    QGraphicsProxyWidget *proxy = escenaMenu->addWidget(contenedor);

    QRectF sceneRect = escenaMenu->sceneRect();
    QSizeF buttonSize = proxy->size();

    // Calcular la posición para centrar el botón en la escena
    qreal x = (sceneRect.width() - buttonSize.width()) / 2;
    qreal y = (sceneRect.height() - buttonSize.height()) / 2;


    // Establecer la posición del widget en la escena
    proxy->setPos(x, y);

    // Conectar el botón de registro a la señal personalizada
    connect(botonIngresar, &QPushButton::clicked, this, &MenuInicial::cambiarEscena);

    //Conectar con el boton de registarse
    connect(botonRegistrarse, &QPushButton::clicked, this, &MenuInicial::on_botonRegistarse_clicked);

}

void MenuInicial::decorarEscena()
{

    //Creando el fondo de la escena y ajustandolo a la escena
    QPixmap fondoMenu("C:/Users/jtoro/OneDrive/Escritorio/Imagenes juego/BosqueTenebroso.jpg");
    QPixmap escalandoFondo = fondoMenu.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //Cmabiando el fondo de la escena menu
    escenaMenu->setBackgroundBrush(escalandoFondo);

}

void MenuInicial::on_botonIngresar_clicked()
{
    emit cambiarEscena();
}

void MenuInicial::on_botonRegistarse_clicked()
{
    QString _textUsuario = usuario->text();
    string textUsuario = _textUsuario.toStdString();

    QString _textContraseña = contraseña->text();
    string password = _textContraseña.toStdString();

    qDebug() << datos->registro(textUsuario, password);

    if(datos->registro(textUsuario, password)){
        qDebug() << "El usuario ya existe";
    }
}

