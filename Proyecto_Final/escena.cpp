#include "escena.h"
#include "ui_escena.h"

escena::escena(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::escena)
    , menuInicial(new MenuInicial())
    , menuJuego(new MenuJuego())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(menuInicial->getEscena());

    connect(menuInicial, &MenuInicial::cambiarEscena, this, &escena::escenaMenuJuego);
    connect(menuJuego, &MenuJuego::cambiarEscena, this, &escena::escenMenuInicial);
}

escena::~escena()
{
    delete ui;
}

void escena::escenaMenuJuego()
{
    ui->graphicsView->setScene(menuJuego->getEscena());
}

void escena::escenMenuInicial()
{
    ui->graphicsView->setScene(menuInicial->getEscena());
}

