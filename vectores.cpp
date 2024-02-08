#include<stdio.h>
#include<iostream>

using namespace std;
#define max 5
//------Estructuras----------------
struct alum{
    int legajo;
    int dni;
    char sexo;
};

struct Nodo{
    alum info;
    Nodo * sgte;
};

//---------------------------------

//------Prototipos-----------------

void inicializar(int vec[], int cant_pos, int valor_inicial);
void mostrar(int vec[], int len);
void cargarVector(int vec[], int &len, int cant_pos);
void insertar(int vec[], int &len, int valor, int pos);
void insertarOrdenado(int vec[], int &len, int valor);
int buscar(int vec[], int len, int valor);
void eliminar(int vec[], int &len, int pos);

//---------------------------------

//---Implementación de funciones---

void inicializar(int vec[], int cant_pos, int valor_inicial){
    for( int i=0 ; i<cant_pos ; i++){   //Recorremos todo el vector completo.
        vec[i]=valor_inicial;           //A cada posición le asignamos el valor indicado.
    }
}

void mostrar(int vec[], int len){
    cout << "*******Mostrando valores del vector**********" << endl;
    for( int i = 0 ; i<len ; i++ ){                     //Recorremos el vector hasta la cantidad de datos cargados.
        cout << i+1 << "º Dato: " << vec[i] << endl;    //Imprimimos en orden todos los datos junto a su indice sumado 1.
    }
    cout << "*********************************************" << endl;
}

void cargarVector(int vec[], int &len, int cant_pos){
    cout << "Iniciamos la carga masiva del vector de " << cant_pos << " posiciones." << endl;
    for(int i=0; i<cant_pos ; i++){
        cout << "Ingrese el " << i+1 << "º dato: ";
        cin >> vec[i];
        len++;
    }
}

void insertar(int vec[], int &len, int valor, int pos){
    for(int i=len; i>pos ; i--){
        vec[i] = vec[i-1];
    }
    vec[pos] = valor;
    len++;
}

void insertarOrdenado(int vec[], int &len, int valor){
    int i=0;
    while( i<len && vec[i]<valor){
        i++;
    }
    if(i==len){
        vec[len]= valor;
        len++;
    }
    else{
        insertar(vec,len,valor,i);
    }
}

int buscar(int vec[], int len , int valor){
    int i=0;
    while( i<len && vec[i]!=valor){
        i++;
    }
    if(i==len){
        return -1;
    }
    else{
        return i;
    }
}

void eliminar(int vec[], int &len, int pos){
    for(int i=pos; i<len-1 ; i++){
        vec[i] = vec[i+1];
    }
    len--;
}

//---------------------------------

//----Función principal------------

int main(){
    int vec[max];
    int len=0;
    int count=0;
    int menu=1;
    int indice;

    inicializar(vec,max,0);
    mostrar(vec,max);
    while( menu != 0 && count<max){
        cout << "Inserte valor o 0 para terminar:";
        cin >> menu;
        if(menu!=0){
            insertarOrdenado(vec,len,menu);
            count++;
        }
    }
    menu=1;
    cout << "------------------------------------------------------" << endl;
    while( menu!=0){
        cout << "Ingrese valor que desea buscar o 0 para terminar: ";
        cin >> menu;
        indice = buscar(vec,len,menu);
        if(indice!=-1){
            cout << "Valor encontrado en la posición " << indice << endl; 
        }
        else{
            cout << "Valor no encontrado." << endl;
        }
    }
    eliminar(vec,len,0);
    eliminar(vec,len,2);
    mostrar(vec,max);
    mostrar(vec,len);
}