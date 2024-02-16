// En este cpp creamos el archivo que luego vamos a leer para el ejercicio 32.

#include<iostream>
#include<stdio.h>

using namespace std;

struct Vuelo{
    int id_vuelo;
    char destino;
    int cant_asientos;
};

struct Pasajero{
    int id_vuelo;
    int pasaporte;
    int monto;
};

int main(){

    FILE * archivo_vuelos = fopen("vuelos.dat","wb");
    FILE * archivo_pasajeros = fopen("pasajeros.dat","wb");
    Vuelo reg_vuelo;
    Pasajero reg_pasajero;
    int menu = 1;
    cout << endl << "------Inicio de carga de datos de vuelos--------" << endl;
    while(menu != 0){
        cout << endl << "Ingrese número de vuelo: ";
        cin >> reg_vuelo.id_vuelo;
        cout << "Ingrese destino: ";
        cin >> reg_vuelo.destino;
        cout << "Ingrese cantidad de asientos: ";
        cin >> reg_vuelo.cant_asientos;
        fwrite(&reg_vuelo,sizeof(struct Vuelo),1,archivo_vuelos);
        cout << "Dato cargado, ingrese 0 para salir o cualquier número para continuar: ";
        cin >> menu;
    }
    cout << endl << "------Inicio de carga de datos de pasajeros--------" << endl;
    menu = 1;
    while(menu != 0){
        cout << endl << "Ingrese número de vuelo: ";
        cin >> reg_pasajero.id_vuelo;
        cout << "Ingrese monto: ";
        cin >> reg_pasajero.monto;
        cout << "Ingrese número de pasaporte o 0 para salir: ";
        cin >> reg_pasajero.pasaporte;
        fwrite(&reg_pasajero,sizeof(struct Pasajero),1,archivo_pasajeros);
        menu = reg_pasajero.pasaporte ;
    }
    fclose(archivo_vuelos);
    fclose(archivo_pasajeros);
    return 0;
}