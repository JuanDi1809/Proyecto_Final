#ifndef MENUJUEGO_H
#define MENUJUEGO_H

#include "menuinicio.h"

#include <QWidget>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <Qstring>
#include <fstream>
#include <string>
#include <QDebug>
#include "juego.h"

using namespace std;

namespace Ui {
class MenuJuego;
}

class MenuJuego : public QWidget
{
    Q_OBJECT

public:
    explicit MenuJuego(QWidget *parent = nullptr);
    ~MenuJuego();

    QLabel *w;
    string ruta = "C:/Users/jtoro/Downloads/";

private slots:
    void on_botonCargarPartida_clicked();
    void on_botonVolver_clicked();
    void on_botonNuevPartida_clicked();

private:
    Ui::MenuJuego *ui;
};

#endif // MENUJUEGO_H
