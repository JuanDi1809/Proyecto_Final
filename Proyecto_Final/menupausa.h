#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include "menu.h"

namespace Ui {
class MenuPausa;
}

class MenuPausa : public Menu
{
    Q_OBJECT

public:
    explicit MenuPausa(QWidget *parent = nullptr);
    ~MenuPausa();

signals:
    void reanudar(int);
    void cerrar();
    void guardar();

private slots:
    void on_botonReanudar_clicked();
    void on_botonCerrarSesion_clicked();
    void on_botonGuardar_clicked();

private:
    Ui::MenuPausa *ui;
};

#include <menuinicio.h>
#endif // MENUPAUSA_H
