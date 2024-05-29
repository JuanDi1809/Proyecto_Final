#ifndef ESCENA_H
#define ESCENA_H

#include <QMainWindow>
#include <QDebug>
#include "menuinicial.h"
#include "menujuego.h"

namespace Ui {
class escena;
}

class escena : public QMainWindow
{
    Q_OBJECT

public:
    explicit escena(QWidget *parent = nullptr);
    ~escena();
private slots:
    void escenaMenuJuego();
    void escenMenuInicial();

private:
    Ui::escena *ui;
    MenuInicial *menuInicial;
    MenuJuego *menuJuego;
};

#endif // ESCENA_H
