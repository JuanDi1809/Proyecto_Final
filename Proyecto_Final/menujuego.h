#ifndef MENUJUEGO_H
#define MENUJUEGO_H

#include "menu.h"
#include "menuinicio.h"
#include "juego.h"
#include <QDebug>

using namespace std;

namespace Ui {
class MenuJuego;
}

class MenuJuego : public Menu
{
    Q_OBJECT

public:
    explicit MenuJuego(QWidget *parent = nullptr);
    ~MenuJuego();

private slots:
    void on_botonCargarPartida_clicked();
    void on_botonVolver_clicked();
    void on_botonNuevPartida_clicked();

private:
    Ui::MenuJuego *ui;
    int parametroComando;
};

#endif // MENUJUEGO_H
