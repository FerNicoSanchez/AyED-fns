// En este cpp creamos el archivo que luego vamos a leer para el ejercicio 50.

#include<iostream>
#include<stdio.h>

using namespace std;

struct Factura{
    int cel;
    char inicial;
    char dir;
    int tiempo;
    char tipo;
    char turno;
};


int main(){

    FILE * archivo_facturas = fopen("facturas.dat" , "ab+");
    int menu = 1;
    Factura reg_factura;
    if(archivo_facturas != nullptr){
        cout << endl << "------------ Inicio de carga de facturas -------------------" << endl;
        while(menu != 0){
            cout << endl << "Ingrese celular (presione 0 si desea salir): ";
            cin >> reg_factura.cel;
            if(reg_factura.cel == 0) { menu = 0; continue; }
            cout << endl << "Ingrese inicial : ";
            cin >> reg_factura.inicial;
            cout << endl << "Ingrese dirección : ";
            cin >> reg_factura.dir;
            cout << endl << "Ingrese tiempo en (HHMM) : ";
            cin >> reg_factura.tiempo;
            cout << endl << "Ingrese tipo de plan : ";
            cin >> reg_factura.tipo;
            cout << endl << "Ingrese turno : ";
            cin >> reg_factura.turno;
            fwrite(&reg_factura,sizeof(struct Factura),1,archivo_facturas);
        }
    }
    else{
        cout << "Error al abrir el archivo." << endl;
    }
    fclose(archivo_facturas);
    return 0;
}