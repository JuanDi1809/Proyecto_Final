#ifndef PANTALLAFIN_H
#define PANTALLAFIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class PantallaFin;
}

class PantallaFin : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaFin(QWidget *parent = nullptr);
    ~PantallaFin();
    QLabel *label;

private slots:
    void on_botonVolver_clicked();

private:
    Ui::PantallaFin *ui;

};

#endif // PANTALLAFIN_H
