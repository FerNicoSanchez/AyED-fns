/**
 * Ejercicios de repaso 2º Parcial 2023
 * Author: FNS
 * Descripción: Consignas en parcial1_2023.pdf 
*/

#include<iostream>

using namespace std;

#define max_ciudades 20

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

struct Pre_viaje{
    int id;
    int reservas;
    int visitantes;
};

struct Reserva{
    int id;
    int visitantes;
};

struct Nodo4{
    Reserva info;
    Nodo4 * sgte;
};

//Prototipos

void push(Nodo*&pila,int valor);
int pop(Nodo*&pila);
void agregar(Nodo*&cfte,Nodo*&cfin,int valor);
int suprimir(Nodo*&cfte,Nodo*&cfin);
void unionVectores(int A[],int B[], int C[]);
void agregarPrimero(Nodo *&Lista,int valor);
void agregarReserva(Nodo4 *&Lista,Reserva valor);
int eliminarPrimero(Nodo *&Lista);
void insertarOrdenado(Nodo*&,int);
void mostrarLista(Nodo*);
Nodo * buscar(Nodo * Lista, int valor);
void liberar(Nodo*&lista);
void liberar4(Nodo4*&lista);
void unionColas(Nodo*&cfteA,Nodo*&cfinA,Nodo*&cfteB,Nodo*&cfinB,Nodo*&cfteC,Nodo*&cfinC);
void unionPilas(Nodo *&pilaA,Nodo*&pilaB,Nodo*&pilaC);
void unionListas(Nodo * listaA,Nodo * ListaB, Nodo*&ListaC);
Nodo * intersecListas(Nodo * lista1, Nodo * lista2);
Nodo * intersecPilaLista(Nodo *lista,Nodo*&pila);
void consolidarBurgerFast(FILE * arch1,FILE * arch2);
void filtrarPan(FILE * arch1, FILE * arch2);
void inicializar(Pre_viaje vec[], int cant_pos, int valor_inicial);
void mostrar(Pre_viaje vec[], int len);
void insertar(Pre_viaje vec[], int &len, Pre_viaje valor, int pos);
void actualizarReservas(Pre_viaje vec[],int &len, Nodo4 * lista);

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

void liberar4(Nodo4*&lista){
    Nodo4*aux=NULL;
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

void agregarReserva(Nodo4 *&Lista,Reserva valor){
    Nodo4 * nuevo = new Nodo4();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void inicializar(Pre_viaje vec[], int cant_pos, int valor_inicial){
    for( int i=0 ; i<cant_pos ; i++){   //Recorremos todo el vector completo.
        vec[i].id = valor_inicial;           //A cada posición le asignamos el valor indicado.
        vec[i].reservas = valor_inicial;
        vec[i].visitantes = valor_inicial;
    }
}

void mostrar(Pre_viaje vec[], int len){
    cout << "*******Mostrando valores del vector**********" << endl;
    for( int i = 0 ; i<len ; i++ ){         //Recorremos el vector hasta la cantidad de datos cargados.
        cout << i+1 << "º Dato: " << endl;
        cout << "Código de ciudad: " << vec[i].id << endl;    //Imprimimos en orden todos los datos junto a su indice sumado 1.
        cout << "Cantidad de reservas: " << vec[i].reservas << endl;
        cout << "Código de visitantes: " << vec[i].visitantes << endl;
    }
    cout << "*********************************************" << endl;
}

void insertar(Pre_viaje vec[], int &len, Pre_viaje valor, int pos){ //Inserta un dato en una posicion especifica.
    for(int i=len; i>pos ; i--){
        vec[i] = vec[i-1];
    }
    vec[pos] = valor;
    len++;
}

void actualizarReservas(Pre_viaje vec[],int &len, Nodo4 * lista){   //EJ 4
    while(lista != NULL){
        for(int i=0 ; i<len ; i++){
            if(lista->info.id == vec[i].id){
                vec[i].visitantes += lista->info.visitantes;
                vec[i].reservas++;
            }
        }
        lista = lista->sgte;
    }
}

//NOTA: EL EJERCICIO 5 ES EXACTAMENTE LO MISMO QUE EL 4 SOLO QUE CAMBIAMOS DE NOMBRE LOS DATOS.
//Prueba de funciones

int main(){
    
    Pre_viaje ciudad[max_ciudades];
    Nodo4 * lista = NULL;
    Reserva reg_reserva;

    ciudad[0].id = 1;
    ciudad[0].reservas = 0;
    ciudad[0].visitantes = 0;

    ciudad[1].id = 2;
    ciudad[1].reservas = 5;
    ciudad[1].visitantes = 25;

    ciudad[2].id = 3;
    ciudad[2].reservas = 1;
    ciudad[2].visitantes = 7;

    ciudad[3].id = 4;
    ciudad[3].reservas = 14;
    ciudad[3].visitantes = 100;

    ciudad[4].id = 5;
    ciudad[4].reservas = 30;
    ciudad[4].visitantes = 55;

    ciudad[5].id = 6;
    ciudad[5].reservas = 0;
    ciudad[5].visitantes = 0;

    int len = 6;

    for(int i=0; i<5;i++){
        cout << endl << "Ingrese cod de ciudad: ";
        cin >> reg_reserva.id;
        cout << "Ingrese cant visitantes: ";
        cin >> reg_reserva.visitantes;
        agregarReserva(lista,reg_reserva);
    }

    actualizarReservas(ciudad,len,lista);

    mostrar(ciudad,len);

    liberar4(lista);

    return 0;
}