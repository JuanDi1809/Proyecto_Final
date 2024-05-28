#ifndef GUARDADO_H
#define GUARDADO_H

#include <vector>
#include <map>
#include <QMessageBox>
#include <string>

using namespace std;

class Guardado
{
private:
    QMessageBox msgBox;
    string usuarioActual;
    map<string, vector<string>> usuarios;

public:
    Guardado();
    bool registro(string usuario, string password);
    bool ingreso(string usuario, string contraseña);

    void guardarDatos();
    void obtenerDatos();

};

#endif // GUARDADO_H
