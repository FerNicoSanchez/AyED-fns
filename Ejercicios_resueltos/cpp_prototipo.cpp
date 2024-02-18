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
                
            }
            break;
        case 2:
            {

            }
            break;
        case 3:
            {

            }
            break;
        case 4:
            {

            }
            break;
        case 5:
            {

            }
            break;
        
        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
