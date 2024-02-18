/**
 * Ejercicios de repaso 2º Parcial 2023
 * Author: FNS
 * Descripción: Consignas en parcial1_2023.pdf 
*/

#include<iostream>

using namespace std;

struct Nodo{
    int info;
    Nodo * sgte;
};

struct Producto{
    int id;
    int cant;
    char tipo;
};

struct Pan{
    int id;
    int cant;
};

//Prototipos

void push(Nodo*&pila,int valor);
int pop(Nodo*&pila);
void agregar(Nodo*&cfte,Nodo*&cfin,int valor);
int suprimir(Nodo*&cfte,Nodo*&cfin);
void unionVectores(int A[],int B[], int C[]);
void agregarPrimero(Nodo *&Lista,int valor);
int eliminarPrimero(Nodo *&Lista);
void insertarOrdenado(Nodo*&,int);
void mostrarLista(Nodo*);
Nodo * buscar(Nodo * Lista, int valor);
void liberar(Nodo*&lista);
void unionColas(Nodo*&cfteA,Nodo*&cfinA,Nodo*&cfteB,Nodo*&cfinB,Nodo*&cfteC,Nodo*&cfinC);
void unionPilas(Nodo *&pilaA,Nodo*&pilaB,Nodo*&pilaC);
void unionListas(Nodo * listaA,Nodo * ListaB, Nodo*&ListaC);
Nodo * intersecListas(Nodo * lista1, Nodo * lista2);
Nodo * intersecPilaLista(Nodo *lista,Nodo*&pila);
void consolidarBurgerFast(FILE * arch1,FILE * arch2);
void filtrarPan(FILE * arch1, FILE * arch2);

//Implementación de funciones

void push(Nodo*&pila,int valor){
    Nodo*nuevo = new Nodo();    //Pedimos memoria.
    nuevo->info = valor;      //Cargamos int.
    nuevo->sgte = pila;         //Conectamos la pila al nuevo dato.
    pila = nuevo;               //La pila comienza con este nuevo dato.
}

int pop(Nodo*&pila){
    Nodo * aux = pila;          //Pedimos memoria.
    int ret = pila->info;     //Guardamos los int del nodo a eliminar.
    pila=pila->sgte;            //Avanzamos el puntero de la pila.
    delete(aux);                //Eliminamos el nodo.
    return ret;                 //Devolvemos el valor del nodo eliminado.
}

void agregar(Nodo*&cfte,Nodo*&cfin,int valor){
    Nodo* nuevo = new Nodo();   //Pedimos memoria.
    nuevo->info = valor;      //Cargamos int.
    nuevo->sgte = NULL;         //Inicializamos puntero.(siempre queda a Null ya que siempre será el último dato de la cola)
    if(cfte == NULL){           //Si la cola esta vacia el puntero al frente sera el nuevo dato ingresado.
        cfte=nuevo;
    }
    else{                       //Si la cola tenia int:
        cfin->sgte=nuevo;       //El puntero sgte del último dato siempre debe apuntar a NULL.
    }
    cfin = nuevo;               //El puntero al final apunta al nuevo dato ingresado.
}//Fin función agregar.

int suprimir(Nodo * & cfte, Nodo * & cfin){
    int ret = cfte->info;  //Guardamos los int del primer nodo.
    Nodo* aux = cfte;       //Inicializamos nodo auxiliar cargado con el nodo del primer dato.
    cfte=cfte->sgte;        //Aumentamos a lo que apunta el inicio de la cola.
    if(cfte==NULL){         //Si es Nulo significa que estaba vacia o bien era el último dato.
        cfin = NULL;        //En ambos casos el final debe apuntar a NULL,
    }
    delete(aux);            //Liberamos la memoria.
    return ret;             //Retornamos el dato eliminado.
}//Fin función suprimir.

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

void insertarOrdenado(Nodo*&lista,int valor){
    Nodo*nuevo= new Nodo();
    nuevo->info = valor;
    nuevo->sgte = NULL;

    Nodo*aux=lista;
    Nodo*ant=NULL;

    while(aux!=NULL && nuevo->info > aux->info ){
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

void mostrarLista(Nodo*lista){
    Nodo * aux = lista;
    if(aux==NULL){
        cout << "No hay datos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << "El valor es : " << aux->info << endl;
        aux = aux->sgte;
    }
}

Nodo * buscar(Nodo * Lista, int valor){
    Nodo * aux=Lista;
    while( aux!=NULL && aux->info != valor){
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

void unionVectores(int A[],int B[],int C[]){        //Ejercicio 1
    int i;
    for( i = 0 ; i<10 ; i++){
        C[i] = A[i];
    }
    for (int b = 0; b < 10 ; b++ , i++){
        C[i] = B[b];
    }
}

void unionColas(Nodo*&cfteA,Nodo*&cfinA,Nodo*&cfteB,Nodo*&cfinB,Nodo*&cfteC,Nodo*&cfinC){   //Ej 2 a)
    int aux;
    while(cfteA != NULL){
        aux = suprimir(cfteA,cfinA);
        agregar(cfteC,cfinC,aux);
    }
    while(cfteB != NULL){
        aux = suprimir(cfteB,cfinB);
        agregar(cfteC,cfinC,aux);
    }
}

void unionPilas(Nodo *&pilaA,Nodo*&pilaB,Nodo*&pilaC){  //Ej 2 b)
    int aux;
    while(pilaA!=NULL){
        aux = pop(pilaA);
        push(pilaC,aux);
    }
    while(pilaB!=NULL){
        aux = pop(pilaB);
        push(pilaC,aux);
    }
}

void unionListas(Nodo * listaA,Nodo * ListaB, Nodo*&ListaC){    //Ej 2 c)
    while(listaA != NULL){
        agregarPrimero(ListaC,listaA->info);
        listaA = listaA->sgte;
    }
    while(ListaB != NULL){
        agregarPrimero(ListaC,ListaB->info);
        ListaB = ListaB->sgte;
    }
}

Nodo * intersecListas(Nodo * lista1, Nodo * lista2){ //Ej 2 d)
    Nodo * nuevo = NULL;
    Nodo * aux = lista2;

    while(lista1 != NULL){
        if(lista1->info == aux->info){
            insertarOrdenado(nuevo,lista1->info);
            aux = lista2;
            lista1 = lista1->sgte;
        }
        else{
            aux = aux->sgte;
        }
        if(aux == NULL){
            aux = lista2;
            lista1 = lista1->sgte;
        }
    }

    return nuevo;
}

Nodo * intersecPilaLista(Nodo *lista,Nodo*&pila){   //Ej 2 e)
    Nodo * nuevo = NULL;
    Nodo * aux = lista;
    int aux_pila = pop(pila);
    while(pila != NULL){
        if(aux->info == aux_pila){
            insertarOrdenado(nuevo,aux_pila);
            aux_pila = pop(pila);
            aux = lista;
        }
        else{
            aux = aux->sgte;
        }
        if(aux == NULL){
            aux_pila = pop(pila);
            aux = lista;
        }
    }
    while(aux!=NULL){
        if(aux_pila == aux->info){
            insertarOrdenado(nuevo,aux_pila);
            aux = NULL;
        }
        else{
            aux = aux->sgte;
        }
    }
    return nuevo;
}

void consolidarBurgerFast(FILE * arch1,FILE * arch2){   //EJ 3 a)
    FILE * consolidado = fopen("BurgerFast.dat","wb");
    Producto reg_prod;
    if( consolidado != nullptr ){
        fread(&reg_prod,sizeof(struct Producto),1,arch1);
        while(!(feof(arch1))){
            fwrite(&reg_prod,sizeof(struct Producto),1,consolidado);
            fread(&reg_prod,sizeof(struct Producto),1,arch1);
        }
        fread(&reg_prod,sizeof(struct Producto),1,arch2);
        while(!(feof(arch2))){
            fwrite(&reg_prod,sizeof(struct Producto),1,consolidado);
            fread(&reg_prod,sizeof(struct Producto),1,arch2);
        }
    }
    else{
        cout << "Error al crear consolidado." << endl;
    }
    fclose(consolidado);
}

void filtrarPan(FILE * arch1, FILE * arch2){    //Ej 3 b)

    FILE * arch_panes = fopen("Pan.dat","wb");
    Pan reg_pan;
    Producto reg_prod;
    if ( arch_panes != nullptr ){
        fread(&reg_prod,sizeof(struct Producto),1,arch1);
        while( !feof(arch1)){
            if(reg_prod.tipo == 'P'){
                reg_pan.id = reg_prod.id;
                reg_pan.cant = reg_prod.cant;
                fwrite(&reg_pan,sizeof(struct Pan),1,arch_panes);
            }
            fread(&reg_prod,sizeof(struct Producto),1,arch1);
        }
        fread(&reg_prod,sizeof(struct Producto),1,arch2);
        while( !feof(arch2)){
            if(reg_prod.tipo == 'P'){
                reg_pan.id = reg_prod.id;
                reg_pan.cant = reg_prod.cant;
                fwrite(&reg_pan,sizeof(struct Pan),1,arch_panes);
            }
            fread(&reg_prod,sizeof(struct Producto),1,arch2);
        }
    }
    else{
        cout << "Problemas al crear archivo Pan.dat" << endl;
    }
    fclose(arch_panes);
}

//Prueba de funciones

int main(){
    // Ejercicio 1
    int A[10];
    int B[10];
    int C[20];

    for(int i = 0 ; i<10 ; i++){
        A[i] = i*10;
    }
    for(int i = 0 ; i<10 ; i++){
        B[i] = 7;
    }
    unionVectores(A,B,C);

    for( int i = 0; i<20 ; i++){
        cout << i+1 <<"º dato: " << C[i] << endl; 
    }
    //Fin ejercicio 1
    FILE * arch_agosto = fopen("BurgerFastAgosto.dat","rb");
    FILE * arch_sept = fopen("BurgerFastSeptiembre.dat","rb");
    Producto aux;
    consolidarBurgerFast(arch_agosto,arch_sept);
    FILE * consolidado = fopen("BurgerFast.dat","rb");

    fread(&aux,sizeof(struct Producto),1,consolidado);
    while(!feof(consolidado)){
        cout << endl << "ID: " << aux.id << endl;
        cout << "Cant: " << aux.cant << endl;
        cout << "Tipo: " << aux.tipo << endl;
        fread(&aux,sizeof(struct Producto),1,consolidado);
    }
    fclose(arch_agosto);
    fclose(arch_sept);
    fclose(consolidado);

    cout << endl << "-------------------------------" << endl;

    FILE * arch_agosto2 = fopen("BurgerFastAgosto.dat","rb");
    FILE * arch_sept2 = fopen("BurgerFastSeptiembre.dat","rb");
    Pan reg_pan;

    filtrarPan(arch_agosto2,arch_sept2);
    FILE * arch_pan = fopen("Pan.dat","rb");

    fread(&reg_pan,sizeof(struct Pan),1,arch_pan);
    while(!feof(arch_pan)){
        cout << endl << "ID: " << reg_pan.id << endl;
        cout << "Cant: " << reg_pan.cant << endl;
        fread(&reg_pan,sizeof(struct Pan),1,arch_pan);
    }
    fclose(arch_agosto2);
    fclose(arch_sept2);
    fclose(arch_pan);

    return 0;
}