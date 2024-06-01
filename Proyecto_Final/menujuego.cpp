#include "menujuego.h"
#include "ui_menujuego.h"

extern QString usu, pass;

MenuJuego::MenuJuego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuJuego)
{
    ui->setupUi(this);
    this->resize(854, 480);

    w = new QLabel(this);
    QPixmap fondoJuego(":/Imagenes/videoJuego/FondoInicial.jpg");
    w->setPixmap(fondoJuego);
    w->setScaledContents(true); //Ajusta el tamaño de la imagen con el QLabel
    w->lower(); //Pasa la imagen al fondo

}

MenuJuego::~MenuJuego()
{
    delete ui;
    delete w;
}

void MenuJuego::on_botonVolver_clicked()
{
    MenuInicio *w = new MenuInicio();
    this->close();
    w->show();
}

void MenuJuego::on_botonNuevPartida_clicked()
{
    qDebug() << "Hizo click";
    Juego *juego = new Juego;
    this->close();
    juego->show();
}

