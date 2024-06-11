#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent): QWidget(parent)
{
    w = new QLabel(this);
}

Menu::~Menu(){}
