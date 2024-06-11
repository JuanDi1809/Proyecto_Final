#ifndef SELECCIONARMA_H
#define SELECCIONARMA_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class SeleccionArma;
}

class SeleccionArma : public QWidget {
    Q_OBJECT
public:
    explicit SeleccionArma(QWidget *parent = nullptr);

signals:
    //este dará la señal para mostrar la nueva ventana
    void iniciarNivel();


private slots:
    void on_botonPresionado_clicked();

private:
    Ui::SeleccionArma *ui;
    QPushButton *pushButton;
    QLabel *w;
};


#endif // SELECCIONARMA_H
