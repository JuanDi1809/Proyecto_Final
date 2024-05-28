#include "guardado.h"
#include <iostream>
#include <string>
#include <fstream>
#include <QDebug>

using namespace std;

Guardado::Guardado() {
    string rutaArchivo = "C:/Users/jtoro/Downloads/Usuarios.txt";
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
            usuarios.insert({usuario,{linea.substr(0,pos)}});
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

    archivo.close();


}

int Guardado::registro(string usuario, string password)
{
    if(usuario == "" || password == ""){
        return 0;
    }

    for (auto &iterador : usuarios){
        if (iterador.first == usuario)
            return 1;
    }

    usuarios.insert({usuario, {password,"100","1","0"}});

    string rutaArchivo = "C:/Users/jtoro/Downloads/Usuarios.txt";
    ofstream archivo(rutaArchivo, ios::out | ios::app);

    if(archivo.is_open()){
        archivo << usuario << ":" << password << ","<< "100," << "1," << "0\n";
        return 2;
    }

    archivo.close();

}

int Guardado::ingreso(string usuario, string password)
{
    if(usuario == "" || password == ""){
        return 0;
    }

    for (auto &iterador : usuarios){
        qDebug() << iterador.first;
        if (iterador.first == usuario && iterador.second[0] == password){
            usuarioActual = usuario;
            return 1;
        }

    }

    return 2;

}
