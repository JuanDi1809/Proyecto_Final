#ifndef MENU_H
#define MENU_H

#include <string>
#include <QObject>
#include <QString>
#include <fstream>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace std;

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    virtual ~Menu();
    string ruta = "C:/Users/jtoro/Downloads/";

protected:
    QLabel *w;
};

#endif // MENU_H
