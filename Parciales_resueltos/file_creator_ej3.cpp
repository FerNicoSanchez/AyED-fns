// En este cpp creamos el archivo que luego vamos a leer para el ejercicio 50.

#include<iostream>
#include<stdio.h>

using namespace std;

struct Producto{
    int id;
    int cant;
    char tipo;
};


int main(){

    FILE * arch_agosto = fopen("BurgerFastAgosto.dat" , "ab+");
    FILE * arch_sept = fopen("BurgerFastSeptiembre.dat" , "ab+");
    int menu = 1;
    Producto reg_producto;
    if(arch_agosto != nullptr){
        cout << endl << "------------ Inicio de carga de productos agosto -------------------" << endl;
        while(menu != 0){
            cout << endl << "Ingrese código del producto (presione 0 si desea salir): ";
            cin >> reg_producto.id;
            if(reg_producto.id == 0) { menu = 0; continue; }
            cout << endl << "Ingrese cantidad en deposito : ";
            cin >> reg_producto.cant;
            cout << endl << "Ingrese tipo de producto : ";
            cin >> reg_producto.tipo;
            fwrite(&reg_producto,sizeof(struct Producto),1,arch_agosto);
        }
    }
    else{
        cout << "Error al abrir el archivo." << endl;
    }
    fclose(arch_agosto);
    menu = -1;
    if(arch_sept != nullptr){
        cout << endl << "------------ Inicio de carga de productos septiembre -------------------" << endl;
        while(menu != 0){
            cout << endl << "Ingrese código del producto (presione 0 si desea salir): ";
            cin >> reg_producto.id;
            if(reg_producto.id == 0) { menu = 0; continue; }
            cout << endl << "Ingrese cantidad en deposito : ";
            cin >> reg_producto.cant;
            cout << endl << "Ingrese tipo de producto : ";
            cin >> reg_producto.tipo;
            fwrite(&reg_producto,sizeof(struct Producto),1,arch_sept);
        }
    }
    else{
        cout << "Error al abrir el archivo." << endl;
    }
    fclose(arch_sept);
    return 0;
}