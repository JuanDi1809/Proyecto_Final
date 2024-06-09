#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class MenuPausa;
}

class MenuPausa : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPausa(QWidget *parent = nullptr);
    ~MenuPausa();
    QLabel *w;

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
