#include "juego.h"
#include "menujuego.h"
#include "menuinicial.h"
#include "ui_juego.h"

Juego::Juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Juego)
    , menuInicial(new MenuInicial())
    , menuJuego(new MenuJuego())
{

    ui->setupUi(this);
    ui->graphicsView->setScene(menuInicial->getEscena());

    connect(menuInicial, &MenuInicial::cambiarEscena, this, &Juego::escenaMenuJuego);
    connect(menuJuego, &MenuJuego::cambiarEscena, this, &Juego::escenaMenuInicial);

}

Juego::~Juego()
{
    delete ui;
}

void Juego::escenaMenuJuego()
{
    ui->graphicsView->setScene(menuJuego->getEscena());
}

void Juego::escenaMenuInicial()
{
    ui->graphicsView->setScene(menuInicial->getEscena());
}
