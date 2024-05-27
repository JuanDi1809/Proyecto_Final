#include "juego.h"
#include "menuinicial.h"
#include "ui_juego.h"

Juego::Juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Juego)
{
    MenuInicial *menuInicial = new MenuInicial();

    ui->setupUi(this);
    ui->graphicsView->setScene(menuInicial->getEscena());

    connect(menuInicial, &MenuInicial::on_botonIngresar_clicked, this, &Juego::escenaMenuJuego);

}

Juego::~Juego()
{
    delete ui;
}

void Juego::escenaMenuJuego()
{
    QGraphicsScene *escenaPrueba = new QGraphicsScene(this);

    QLabel *tituloRandom = new QLabel("Escena menu");

    escenaPrueba->addWidget(tituloRandom);

    ui->graphicsView->setScene(escenaPrueba);
}
