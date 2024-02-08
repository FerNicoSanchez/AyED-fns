#include<stdio.h>
#include<iostream>

using namespace std;

struct alum{
    int legajo;
    int dni;
    char sexo;
};

struct Nodo{
    alum info;
    Nodo * sgte;
};
void agregarPrimero(Nodo *&Lista,alum valor);
alum eliminarPrimero(Nodo *&Lista);
void insertarOrdenado(Nodo*&,alum);
void mostrarAlumnos(Nodo*);
Nodo * buscar(Nodo * Lista, alum valor);
void liberar(Nodo*&lista);


int main(){
    Nodo * lista=NULL;
    Nodo * aux= NULL;
    alum alumno1,alumno2,alumno3,alumno4;
    alumno1.dni = 40394493;
    alumno1.legajo = 2;
    alumno1.sexo = 'M';

    alumno2.dni = 1111;
    alumno2.legajo = 1;
    alumno2.sexo = 'F';
    
    alumno3.dni = 2222;
    alumno3.legajo = 3;
    alumno3.sexo = 'M';

    alumno4.dni = 224522;
    alumno4.legajo = 4;
    alumno4.sexo = 'M';

    insertarOrdenado(lista,alumno2);
    insertarOrdenado(lista,alumno1);
    insertarOrdenado(lista,alumno3);
    insertarOrdenado(lista,alumno4);
    mostrarAlumnos(lista);

    aux = buscar(lista,alumno2);
    if(aux==NULL){
        cout << "Alumno no encontrado." << endl;
    }
    else{
        cout << "El legajo : " << aux->info.legajo << " del DNI: " << aux->info.dni << " de sexo " << aux->info.sexo << endl;
    }
    liberar(lista);

    return 0;
}

void agregarPrimero(Nodo *&Lista,alum valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

alum eliminarPrimero(Nodo *&Lista){
    alum ret = Lista->info;
    Nodo * aux = Lista;
    Lista = Lista->sgte;
    delete(aux);
    return ret;
}

void insertarOrdenado(Nodo*&lista,alum alumno){
    Nodo*nuevo= new Nodo();
    nuevo->info.dni = alumno.dni;
    nuevo->info.legajo = alumno.legajo;
    nuevo->info.sexo = alumno.sexo;
    nuevo->sgte = NULL;

    Nodo*aux=lista;
    Nodo*ant=NULL;

    while(aux!=NULL && nuevo->info.legajo > aux->info.legajo ){
        ant=aux;
        aux=aux->sgte;
    }
    if(ant==NULL){
        lista=nuevo;
    }
    else{
        ant->sgte = nuevo;
    }
    nuevo->sgte = aux;
}

void mostrarAlumnos(Nodo*lista){
    Nodo * aux = lista;
    if(aux==NULL){
        cout << "No hay alumnos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << "El legajo : " << aux->info.legajo << " del DNI: " << aux->info.dni << " de sexo " << aux->info.sexo << endl;
        aux = aux->sgte;
    }
}

Nodo * buscar(Nodo * Lista, alum valor){
    Nodo * aux=Lista;
    while( aux!=NULL && aux->info.legajo != valor.legajo){
        aux=aux->sgte;
    }
    return aux;
}

void liberar(Nodo*&lista){
    Nodo*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}


