/**
 * Parcial 2022 profe Frankel.
 * Author: FNS
 * Descripción: Ver archivo parcial4.pdf
*/

#include<iostream>

using namespace std;

//--------Estructuras--------------

struct Venta{
    int codP;
    float fact;     //Cambiamos el nombre y el tipo de dato para el ej2 pero funciona igual en ej1
};

struct Nodo{
    Venta info;
    Nodo * sgte;
};

//--------Prototipos---------------

void agregarPrimero(Nodo *&lista, Venta valor);

void mostrar(Nodo * lista);

void liberar(Nodo *&lista);

void crearArchivo();

Nodo * listaSinRepe(FILE * arch_lectura,Nodo *&lista);

void Vtas100_200(Nodo *& lista, Venta vec[],int &len);


//---Implementación de funciones---

void agregarPrimero(Nodo *&Lista,Venta valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void mostrar(Nodo * lista){
    while(lista != NULL){
        cout << endl << "Código de producto: " << lista->info.codP << endl;
        cout << "Sucursal: " << lista->info.fact << endl;
        lista = lista->sgte;
    }
}

void liberar(Nodo * &lista){
    Nodo * aux = lista;
    while( lista != NULL){
        lista = aux->sgte;
        delete(aux);
        aux = lista;
    }
}

void crearArchivo(){
    FILE * archivo_prod = fopen("fVta.dat","wb");
    Venta reg_prod;
    reg_prod.codP = -1;
    cout << endl << "---- Iniciamos carga de archivo fVta.dat ----" << endl;
    while(reg_prod.codP != 0){

        cout << endl << "Ingrese código de producto o 0 para salir: ";
        cin >> reg_prod.codP;
        if(reg_prod.codP == 0) { continue; }
        cout << "Ingrese sucursal: ";
        cin >> reg_prod.fact;

        fwrite(&reg_prod,sizeof(struct Venta),1,archivo_prod);
    }
    cout << endl;
    fclose(archivo_prod);
}

Nodo * listaSinRepe(FILE * arch_lectura,Nodo *&lista){          //Ejercicio 1
    Venta reg_aux;
    fread(&reg_aux,sizeof(struct Venta),1,arch_lectura);
    if(lista == NULL){
        Nodo * nuevo = new Nodo();
        nuevo->info = reg_aux;
        nuevo->sgte = NULL;
        lista = nuevo;
        return nuevo;
    }
    Nodo * aux = lista;
    while( aux != NULL){
        if( aux->info.codP == reg_aux.codP && aux->info.fact == reg_aux.fact){
            return aux;
        }
        if ( aux->sgte == NULL){
            Nodo * nuevo = new Nodo();
            nuevo->info = reg_aux;
            nuevo->sgte = NULL;
            aux->sgte = nuevo;
            return nuevo;
        }
        aux = aux->sgte;
    }
    return NULL;
}

void Vtas100_200(Nodo *& lista, Venta vec[],int &len){          //Ejercicio 2
    Nodo * aux = lista;
    Nodo * ant = NULL;
    while( aux != NULL){
        if( aux->info.fact >= 100 && aux->info.fact <= 200){
            vec[len].codP = aux->info.codP;
            vec[len].fact = aux->info.fact;
            len++;
            if(ant == NULL){
                lista = lista->sgte;
                delete(aux);
                aux = lista;
            }
            else{
                ant->sgte = aux->sgte;
                delete(aux);
                aux = ant->sgte;
            }
        }
        else{
            ant = aux;
            aux = aux->sgte;
        }
    }
}


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
                crearArchivo();
                Nodo * lista = NULL;
                Nodo * aux = NULL;
                int count = 0;
                FILE * arch_lectura = fopen("fVta.dat","rb");
                aux = listaSinRepe(arch_lectura,lista);
                while(!feof(arch_lectura) && count < 7){
                    if(aux->sgte != NULL){
                        cout << endl << "Dato repetido" << endl;
                        mostrar(aux);
                    }
                    else{
                        cout << endl << "Dato ingresado. (codP: " << aux->info.codP;
                        cout << " - fact: " << aux->info.fact << " )" << endl;
                        cout << endl << "Lista retornada" << endl;
                        mostrar(aux);
                    }
                    aux = listaSinRepe(arch_lectura,lista);
                    count ++;
                }
                fclose(arch_lectura);
                cout << endl << "------ Lista sin repetición -------" << endl;
                mostrar(lista);
                liberar(lista);
            }
            break;
        case 2:
            {
                cout << endl << "Ejercicio 2" << endl;
                Nodo * lista = NULL;
                Venta reg_venta;
                Venta vec[50];
                int len = 0;
                cout << endl << "----- Iniciamos carga de lista de ventas -------" << endl;
                int menu2 = -1;
                while( menu2 != 0){
                    cout << endl << "Ingrese codP o 0 para terminar: ";
                    cin >> menu2;
                    if(menu2 == 0)  { continue; }
                    else            { reg_venta.codP = menu2; }
                    cout << "Ingrese facturación: ";
                    cin >> reg_venta.fact;
                    agregarPrimero(lista,reg_venta);
                }
                cout << endl << "---- Fin de carga -----" << endl;
                Vtas100_200(lista,vec,len);
                cout << "Filtro de ventas realizado." << endl << "Lista resultante:" << endl;
                mostrar(lista);
                if( lista != NULL)  { liberar(lista); }
                cout << endl << "Vector resultante:" << endl;
                for(int i = 0 ; i<len ; i++){
                    cout << endl << " CodP: " << vec[i].codP << endl;
                    cout << "Facturación: " << vec[i].fact << endl;
                }
            }
            break;
            default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
