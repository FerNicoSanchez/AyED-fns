#include<iostream>

using namespace std;
struct Nodo{
    int info;
    Nodo*sgte;
};
void agregarPrimero(Nodo *&Lista,int valor);
int eliminarPrimero(Nodo *&Lista);
void mostrar(Nodo * Lista);
void liberar(Nodo * &Lista);
void insertarOrdenado(Nodo *&Lista,int valor);

int main(){
    Nodo * Lista = NULL;
    
    agregarPrimero(Lista,777);
    agregarPrimero(Lista,999);
    agregarPrimero(Lista,888);
    agregarPrimero(Lista,999);
    agregarPrimero(Lista,777);
    insertarOrdenado(Lista,1);
    insertarOrdenado(Lista,779);

    mostrar(Lista);
    liberar(Lista);
    return 0;
}

void agregarPrimero(Nodo *&Lista,int valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

int eliminarPrimero(Nodo *&Lista){
    int ret = Lista->info;
    Nodo * aux = Lista;
    Lista = Lista->sgte;
    delete(aux);
    return ret;
}

void mostrar(Nodo * Lista){
    Nodo * aux = Lista;
    while(aux != NULL){
        cout << "El dato es: " << aux->info << endl;
        aux=aux->sgte;
    }
}

void liberar(Nodo * &Lista){
    Nodo * aux=NULL;
    while(Lista != NULL){
        aux = Lista;
        Lista = Lista->sgte;
        delete(aux);
    }
}

void insertarOrdenado(Nodo *&Lista,int valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = NULL;
    Nodo * aux = Lista;
    Nodo * ant = NULL;

    while(aux != NULL && aux->info < valor){
        ant = aux;
        aux = aux->sgte;
    }

    if(ant==NULL){
        Lista = nuevo;
    }
    else{
        ant->sgte = nuevo;
    }
    nuevo->sgte = aux;
}
