#include "menujuego.h"
#include "ui_menujuego.h"

extern vector<string> datos;
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

void MenuJuego::on_botonCargarPartida_clicked()
{
    if(datos.size() == 2){
        QMessageBox msgBox;
        msgBox.setText("Este usuario no tiene partidas jugadas");
        msgBox.exec();
        return;
    }

    Juego *juego = new Juego;
    this->close();
    juego->show();
}

void MenuJuego::on_botonVolver_clicked()
{
    MenuInicio *w = new MenuInicio();
    this->close();
    w->show();
}

void MenuJuego::on_botonNuevPartida_clicked()
{
    ofstream archivo(ruta + usu.toStdString() + ".txt"); //La idea es volver a sobreescribir los datos

    if(archivo.is_open()){
        archivo << usu.toStdString() << "\n" << pass.toStdString() << "\n" << "0\n" << "100\n" << "1";
        archivo.close();

        if(datos.size() != 2){
            datos[2] = "0";
            datos[3] = "100";
            datos[4] = "1";
        }

        datos.push_back("0");
        datos.push_back("100");
        datos.push_back("1");

        Juego *juego = new Juego();
        this->close();
        juego->show();
    }
}

