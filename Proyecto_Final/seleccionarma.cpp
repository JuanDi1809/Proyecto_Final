#include "SeleccionArma.h"

SeleccionArma::SeleccionArma(QWidget *parent) : QWidget(parent) {
    pushButton = new QPushButton("Iniciar Nivel", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(pushButton);

    setFixedSize(400, 300);
    connect(pushButton, &QPushButton::clicked, this, &SeleccionArma::botonPresionado);
}

void SeleccionArma::botonPresionado() {
    emit iniciarNivel();
}
