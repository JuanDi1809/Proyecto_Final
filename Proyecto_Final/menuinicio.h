#ifndef MENUINICIO_H
#define MENUINICIO_H

#include "menu.h"
#include <vector>

using namespace std;


namespace Ui {
class MenuInicio;
}

class MenuInicio : public Menu
{
    Q_OBJECT

public:
    MenuInicio(QWidget *parent=nullptr);
    ~MenuInicio();

private slots:
    void on_botonIngresar_clicked();
    void on_botonRegistrar_clicked();
    void on_botonMostar_clicked();
    void on_botonSalir_clicked();

private:
    Ui::MenuInicio *ui;
    bool validPassword = true;
    int parametroComando;
};

#include "menujuego.h"

#endif // MENUINICIO_H
