#include "pantallafin.h"
#include "ui_pantallafin.h"
#include "menujuego.h"

PantallaFin::PantallaFin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaFin)
{
    ui->setupUi(this);
    this->resize(1600, 900);

    //establecemos imagen
    label = new QLabel(this);
    QPixmap fondo(":/Imagenes/videoJuego/fin.png");
    label->setPixmap(fondo);
    label->setScaledContents(true);
    label->setFixedSize(1600, 900);
    label->lower();
}
PantallaFin::~PantallaFin(){
    delete label;
    delete ui;
}


void PantallaFin::on_botonVolver_clicked()
{
    MenuJuego *menu = new MenuJuego();
    menu->show();
    this->close();
}

