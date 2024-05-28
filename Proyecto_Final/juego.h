#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QDebug>
#include "menujuego.h"
#include "menuinicial.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Juego;
}
QT_END_NAMESPACE

class Juego : public QMainWindow
{
    Q_OBJECT

public:
    Juego(QWidget *parent = nullptr);
    ~Juego();

private slots:
    void escenaMenuJuego();
    void escenaMenuInicial();

private:
    Ui::Juego *ui;
    MenuInicial *menuInicial;
    MenuJuego *menuJuego;

};
#endif // JUEGO_H
