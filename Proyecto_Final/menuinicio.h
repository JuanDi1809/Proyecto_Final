#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <vector>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <Qstring>
#include <fstream>
#include <string>

using namespace std;


namespace Ui {
class MenuInicio;
}

class MenuInicio : public QWidget
{
    Q_OBJECT

public:
    MenuInicio(QWidget *parent = nullptr);
    ~MenuInicio();

    QLabel *w;
    string ruta = "C:/Users/jtoro/Downloads/";

private slots:
    void on_botonIngresar_clicked();
    void on_botonRegistrar_clicked();

private:
    Ui::MenuInicio *ui;
};

#include "menujuego.h"

#endif // MENUINICIO_H
