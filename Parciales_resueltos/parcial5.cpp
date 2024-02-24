/**
 * 2º Parcial 2022 Profe Frankel
 * Author: FNS
 * Descripción: Ver archivo parcial5.pdf
*/

#include<iostream>

using namespace std;

//--------Estructuras--------------

struct Tprod{
    int codP;
    float PU;
};

struct Nodo{
    Tprod info;
    Nodo * sgte;
};

struct NodoV{
    float Fact;
    NodoV * sgte;
};

struct tProd{
    int codP;
    int categ;
    NodoV * LVta;
};


//--------Prototipos---------------

void agregarPrimero(Nodo *&Lista,Tprod valor);

void agregarPrimero2(NodoV *&Lista,float valor);

void agregarUltimo(Nodo *&lista, Tprod valor);

void mostrar(Nodo * lista);

void liberar(Nodo *&lista);

void liberarV(NodoV *&lista);

void crearArchivo(Nodo *&lista);

void leerArchivo();


void actualizarPrecio(FILE * fProd, Nodo *&LP, int codP);

void ImprMenorFactdeCateg(tProd Vprod[],int len,int categ);

//---Implementación de funciones---

void agregarPrimero(Nodo *&Lista,Tprod valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void agregarPrimero2(NodoV *&Lista,float valor){
    NodoV * nuevo = new NodoV();
    nuevo->Fact = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void liberarV(NodoV *&lista){
    NodoV * aux = NULL;
    while(lista != NULL){
        aux = lista;
        lista = lista->sgte;
        delete(aux);
    }
}



void agregarUltimo(Nodo *&lista, Tprod valor){
    Nodo * aux = lista;
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = NULL;
    if( lista == NULL){
        lista = nuevo;
    }
    else{
        while( aux->sgte != NULL){
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
    }
}


void mostrar(Nodo * lista){
    while( lista != NULL){
        cout << endl << "Código de producto: " << lista->info.codP << endl;
        cout << "Precio unitario: " << lista->info.PU << endl;
        lista = lista->sgte;
    }
}

void liberar(Nodo *&lista){
    Nodo * aux = lista;
    while(lista != NULL){
        aux = lista;
        lista = lista->sgte;
        delete(aux);
    }
}

void crearArchivo(Nodo *&lista){
    FILE * archivo_prod = fopen("fProd.dat","wb");
    Tprod reg_prod;
    reg_prod.codP = -1;
    cout << endl << "---- Iniciamos carga de fProd.dat ----" << endl;
    while(reg_prod.codP != 0){
        cout << endl << "Ingrese código de Tprod o 0 para salir: ";
        cin >> reg_prod.codP;
        if(reg_prod.codP == 0) { continue; }
        cout << "Precio unitario: ";
        cin >> reg_prod.PU;
        fwrite(&reg_prod,sizeof(struct Tprod),1,archivo_prod);
        agregarUltimo(lista,reg_prod);
    }
    cout << endl;
    fclose(archivo_prod);
}

void leerArchivo(){
    FILE * archivo_prod = fopen("fProd.dat","rb");
    Tprod reg_prod;
    cout << endl << "---- Archivo fProd.dat ----" << endl;
    fread(&reg_prod,sizeof(struct Tprod),1,archivo_prod);
    while(!feof(archivo_prod)){
        cout << endl << "Código de producto: " << reg_prod.codP << endl;
        cout << "Precio unitario: " << reg_prod.PU << endl;
        fread(&reg_prod,sizeof(struct Tprod),1,archivo_prod);
    }
    cout << "----------------------------" << endl;
    fclose(archivo_prod);
}


void actualizarPrecio(FILE * fProd, Nodo *&LP, int codP){       //Ejercicio 1
    Nodo * aux = LP;
    while ( aux != NULL){
        if( aux->info.codP == codP){
            aux->info.PU += (aux->info.PU/10);
        }
        fwrite(&aux->info,sizeof(struct  Tprod),1,fProd);
        aux = aux->sgte;
    }
}

void ImprMenorFactdeCateg(tProd Vprod[],int len,int categ){
    for(int i = 0 ; i<len ; i++){
        if(Vprod[i].categ == categ){
            cout << "CodP:" << Vprod[i].codP << "           Vta de menor Facturación:";
            cout << Vprod[i].LVta->Fact << endl;
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
                Nodo * lista = NULL;
                crearArchivo(lista);
                FILE * arch_escritura = fopen("fProd.dat","wb");
                actualizarPrecio(arch_escritura,lista,1);
                cout << endl << "Precios actualizados." << endl;
                fclose(arch_escritura);
                leerArchivo();
                cout << endl << " ----------- Lista resultante ---------" << endl;
                mostrar(lista);
                liberar(lista);
            }
            break;
        case 2:
            {
                cout << endl << "Ejercicio 2" << endl;
                tProd vec[50];
                int len = 0;
                int categ;

                vec[0].codP = 1;
                vec[0].categ = 1;
                vec[0].LVta = NULL;
                agregarPrimero2(vec[0].LVta,1000);
                agregarPrimero2(vec[0].LVta,100);
                len++;

                vec[1].codP = 2;
                vec[1].categ = 2;
                vec[1].LVta = NULL;
                agregarPrimero2(vec[1].LVta,200);
                agregarPrimero2(vec[1].LVta,77);
                len++;

                vec[2].codP = 3;
                vec[2].categ = 3;
                vec[2].LVta = NULL;
                agregarPrimero2(vec[2].LVta,10);
                agregarPrimero2(vec[2].LVta,7);
                len++;

                vec[3].codP = 4;
                vec[3].categ = 1;
                vec[3].LVta = NULL;
                agregarPrimero2(vec[3].LVta,1000);
                agregarPrimero2(vec[3].LVta,123);
                len++;

                vec[4].codP = 7;
                vec[4].categ = 1;
                vec[4].LVta = NULL;
                agregarPrimero2(vec[4].LVta,7);
                agregarPrimero2(vec[4].LVta,1);
                len++;


                cout << endl << "Ingrese categoria:";
                cin >> categ;
                ImprMenorFactdeCateg(vec,len,categ);
                liberarV(vec[0].LVta);
                liberarV(vec[1].LVta);
                liberarV(vec[2].LVta);
                liberarV(vec[3].LVta);
                liberarV(vec[4].LVta);
            }
            break;

        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
