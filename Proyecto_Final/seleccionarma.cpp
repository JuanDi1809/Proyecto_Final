#include "SeleccionArma.h"
#include "ui_seleccionarma.h"

SeleccionArma::SeleccionArma(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::SeleccionArma)
{
    ui->setupUi(this);

    this->resize(400,400);

    w = new QLabel(this);
    QPixmap fondoLogrado(":/Imagenes/videoJuego/FondoPausa.jpg");
    w->setPixmap(fondoLogrado);
    //w->setScaledContents(true); //Ajusta el tamaño de la imagen con el QLabel
    w->lower(); //Pasa la imagen al fondo

   // pushButton = new QPushButton("Iniciar Nivel", this);
    //QVBoxLayout *layout = new QVBoxLayout(this);
    //layout->addWidget(pushButton);

    //connect(pushButton, &QPushButton::clicked, this, &SeleccionArma::botonPresionado);
}


void SeleccionArma::on_botonPresionado_clicked()
{
    emit iniciarNivel();
}

