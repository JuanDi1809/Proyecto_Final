#include "menupausa.h"
#include "ui_menupausa.h"

MenuPausa::MenuPausa(QWidget *parent)
    : QWidget(parent)
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
    this->close();
    //aqui va a existir un emit para reanudar el timer de todo lo que este en movimiento en el mapa
}

