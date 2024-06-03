#ifndef SELECCIONARMA_H
#define SELECCIONARMA_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SeleccionArma : public QWidget {
    Q_OBJECT
public:
    explicit SeleccionArma(QWidget *parent = nullptr);

signals:
    //este dará la señal para mostrar la nueva ventana
    void iniciarNivel();

private slots:
    //evento que envía la señal
    void botonPresionado();

private:
    QPushButton *pushButton;
};


#endif // SELECCIONARMA_H
