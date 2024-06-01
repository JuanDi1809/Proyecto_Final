#include "menuinicio.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuInicio w;
    w.show();


    return a.exec();
}
