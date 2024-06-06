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

private slots:
    void on_botonReanudar_clicked();

private:
    Ui::MenuPausa *ui;
};

#endif // MENUPAUSA_H
