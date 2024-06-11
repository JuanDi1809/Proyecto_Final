#include "menupausa.h"
#include "ui_menupausa.h"

extern int nivelActual;

MenuPausa::MenuPausa(QWidget *parent)
    : Menu(parent)
    , ui(new Ui::MenuPausa)
{
    ui->setupUi(this);

    this->resize(400, 400); //Ajusta el tamaño de la ventana

    w = new QLabel(this);
    QPixmap fondoPausa(":/Imagenes/videoJuego/FondoPausa.jpg");
    w->setPixmap(fondoPausa);
    w->setScaledContents(true); //Ajusta el tamaño de la imagen con el QLabel
    w->lower(); //Pasa la imagen al fondo
}

MenuPausa::~MenuPausa()
{
    delete ui;
}



void MenuPausa::on_botonReanudar_clicked()
{
    if(nivelActual == 1){
        emit reanudar(1000);
    }
    else if(nivelActual == 2){
        emit reanudar(600);
    }
    else{
        emit reanudar(400);
    }
    this->close();
}


void MenuPausa::on_botonCerrarSesion_clicked()
{
    MenuInicio *inicio = new MenuInicio();
    this->close();
    emit cerrar();
    inicio->show();
}


void MenuPausa::on_botonGuardar_clicked()
{
    emit guardar();
}

