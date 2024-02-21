/**
 * Tipo de ejercicio.
 * Author: FNS
 * Descripción: 
*/

#include<iostream>

using namespace std;

//--------Estructuras--------------



//--------Prototipos---------------



//---Implementación de funciones---



//-----Prueba de funciones----

int main(){
    int menu = -1;

    while( menu != 0){
        cout << "Ingrese el número de ejercicio que desea activar o 0 para salir: ";
        cin >> menu;
        if(menu == 0)   { continue; }

        switch (menu)
        {
        case 1:
            {
                cout << endl << "Ejercicio 1 " << endl;
            }
            break;
        case 2:
            {
                cout << endl << "Ejercicio 2" << endl;

            }
            break;
        case 3:
            {
                cout << endl << "Ejercicio 3" << endl;

            }
            break;
        case 4:
            {   
                cout << endl << "Ejercicio 4" << endl;

            }
            break;
        case 5:
            {
                cout << endl << "Ejercicio 5" << endl;

            }
            break;
        
        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
