#include "menuinicio.h"
#include "ui_menuinicio.h"

QString usu, pass;
vector<string> datos;

MenuInicio::MenuInicio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuInicio)
{
    ui->setupUi(this);

    this->resize(854, 480); //Ajusta el tamaño de la ventana

    w = new QLabel(this);
    QPixmap fondoInicial(":/Imagenes/videoJuego/FondoInicial.jpg");
    w->setPixmap(fondoInicial);
    w->setScaledContents(true); //Ajusta el tamaño de la imagen con el QLabel
    w->lower(); //Pasa la imagen al fondo

    //Alineo los cursores de los QLineEdit
    ui->Password->setAlignment(Qt::AlignCenter);
    ui->Usuario->setAlignment(Qt::AlignCenter);

    //Oculta la contraseña
    ui->Password->setEchoMode(QLineEdit::Password);

}

MenuInicio::~MenuInicio()
{
    delete ui;
    delete w;
}

void MenuInicio::on_botonIngresar_clicked()
{

    usu = ui->Usuario->text();
    pass = ui->Password->text();

    if(usu == "" || pass == ""){
        QMessageBox msgBox;
        msgBox.setText("Faltan datos por ingresar");
        msgBox.exec();
        return;
    }

    ifstream archivo(ruta + usu.toStdString() + ".txt");
    if(!archivo.is_open()){
        QMessageBox msgBox;
        msgBox.setText("Contraseña o usuario incorrecto.");
        msgBox.exec();

        return; //Evita que siga con el ciclo de ejecucion
    }
    else{
        string dato;
        while (getline(archivo,dato)) {
            datos.push_back(dato);
        }

        archivo.close();

        if(pass.toStdString() == datos[1] && usu.toStdString() == datos[0] ){
            this->setVisible(false);


            MenuJuego *menu = new MenuJuego();
            menu->show();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Contraseña o usuario incorrecto.");
            msgBox.exec(); //Bloque la ejecucion hasta que el usuario interactue con el

            return;
        }
    }

}

void MenuInicio::on_botonRegistrar_clicked()
{

    usu = ui->Usuario->text();
    pass = ui->Password->text();

    if(usu == "" || pass == ""){
        QMessageBox msgBox;
        msgBox.setText("Faltan datos por ingresar");
        msgBox.exec();

        return;
    }
    else{
         ifstream archivo(ruta + usu.toStdString() + ".txt");

        if(archivo.is_open()){
             QMessageBox msgBox;
             msgBox.setText("Este usuario ya existe.");
             msgBox.exec();

             return;
         }
        else{
            ofstream archivo(ruta + usu.toStdString() + ".txt");
            //Se guardan el nombre de usuario y la contraseña
            archivo << usu.toStdString()<<"\n" << pass.toStdString() << "\n";
            archivo.close();

            //Ventana emergente que notifica que el registro fue exitoso
            QMessageBox msgBox;
            msgBox.setText("Registrado correctamente.");
            msgBox.exec();

            ui->Usuario->clear();
            ui->Password->clear();
        }
    }

}

void MenuInicio::on_botonMostar_clicked()
{
    if(validPassword){
        ui->Password->setEchoMode(QLineEdit::Normal);
        validPassword = false;
    }
    else{
        ui->Password->setEchoMode((QLineEdit::Password));
        validPassword = true;
    }
}

