#include "escena.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    escena w;
    w.show();
    return a.exec();
}
