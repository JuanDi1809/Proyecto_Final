#ifndef GUARDADO_H
#define GUARDADO_H

#include <vector>
#include <map>
#include <string>

using namespace std;

class Guardado
{
private:
    string usuarioActual;
    map<string, vector<string>> usuarios;

public:
    Guardado();
    int registro(string usuario, string password);
    int ingreso(string usuario, string password);

    void guardarDatos();
    void obtenerDatos();

};

#endif // GUARDADO_H
