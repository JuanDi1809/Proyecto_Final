#include "guardado.h"
#include <iostream>
#include <string>
#include <fstream>
#include <QDebug>

using namespace std;

Guardado::Guardado() {
    string rutaArchivo = "C:\\Users\\jtoro\\OneDrive\\Imágenes\\Documentos\\Proyecto\\Proyecto_Final\\Partidas\\Usuarios";

    ifstream archivo(rutaArchivo);

    if(archivo.is_open()){
        string linea;
        string usuario;

        while(getline(archivo, linea)){
            size_t pos = linea.find(':');
            usuario = linea.substr(0, pos);
            linea = linea.erase(0, pos+1);

            //Extraer contraseña y gurdarlo
            pos = linea.find(',');
            usuarios[usuario].push_back(linea.substr(0,pos));
            linea = linea.erase(0, pos+1);

            //Extraer nivel y guardarlo
            pos = linea.find(',');
            usuarios[usuario].push_back(linea.substr(0,pos));
            linea = linea.erase(0, pos+1);

            //Extrael puntaje y guardarlo
            pos = linea.find(',');
            usuarios[usuario].push_back(linea.substr(0,pos));
            linea = linea.erase(0, pos+1);

            //Extraer vida y guardarlo
            pos = linea.find('\n');
            usuarios[usuario].push_back(linea.substr(0,pos));
            linea = linea.erase(0, pos+1);

        }
    }


}

bool Guardado::registro(string usuario, string password)
{
    for (auto &iterador : usuarios){
        if (iterador.first == usuario)
            return true;
    }
}
