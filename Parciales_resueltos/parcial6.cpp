/**
 * 2º Parcial, profe Yamila
 * Author: FNS
 * Descripción: Ver archivo parcial6.jpeg
*/

#include<iostream>

using namespace std;

#define cant_cursos 5

//--------Estructuras--------------

struct Curso{
    int id;
    int cant;
    int monto;
};

struct Matricula{
    int id;
    int monto;
};

struct NodoM{
    Matricula info;
    NodoM * sgte;
};

struct Nodo{
    int info;
    Nodo * sgte;
};

struct Producto{
    int id;
    int peso;
    char tipo;
    int stock;
};

struct NodoP{
    Producto info;
    NodoP * sgte;
};

//--------Prototipos---------------

void push(Nodo*&pila,int persona);
int pop(Nodo*&pila);

void agregar(Nodo*&cfte,Nodo*&cfin,int persona);
int suprimir(Nodo*&cfte,Nodo*&cfin);

void liberar(Nodo * &Lista);
void insertarOrdenado(Nodo *&Lista,int valor);
void agregarPrimero(Nodo *&Lista,int valor);
void mostrar(Nodo *lista);

void insertarOrdenadoP(NodoP*&lista,Producto valor);
void liberarP(NodoP*&lista);
void mostrarP(NodoP *lista);

void insertarOrdenadoM(NodoM*&lista,Matricula valor);
void liberarM(NodoM*&lista);

Nodo * unionPilasCola(Nodo *&pilaA, Nodo*&pilaB , Nodo *&cfte, Nodo *&cfin);

void intersecPilaLista(Nodo *&pila, Nodo * lista, Nodo *&lista_fin);

void actualizarMatriculas(Curso vec[], int len, NodoM * lista);

void ordenarStock();

void mostrarSinStock();

void crearArchivo();

//---Implementación de funciones---

void push(Nodo*&pila,int persona){
    Nodo*nuevo = new Nodo();    //Pedimos memoria.
    nuevo->info = persona;      //Cargamos int.
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

void agregar(Nodo*&cfte,Nodo*&cfin,int persona){
    Nodo* nuevo = new Nodo();   //Pedimos memoria.
    nuevo->info = persona;      //Cargamos int.
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

void agregarPrimero(Nodo *&Lista,int valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void insertarOrdenadoP(NodoP*&lista,Producto valor){
    NodoP*nuevo= new NodoP();
    nuevo->info = valor;
    nuevo->sgte = NULL;

    NodoP*aux=lista;
    NodoP*ant=NULL;

    while(aux!=NULL && nuevo->info.id > aux->info.id ){
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

void insertarOrdenadoM(NodoM*&lista,Matricula valor){
    NodoM*nuevo= new NodoM();
    nuevo->info = valor;
    nuevo->sgte = NULL;

    NodoM*aux=lista;
    NodoM*ant=NULL;

    while(aux!=NULL && nuevo->info.id > aux->info.id ){
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

void liberarP(NodoP*&lista){
    NodoP*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

void liberarM(NodoM*&lista){
    NodoM*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

void mostrarP(NodoP *lista){
    NodoP * aux = lista;
    if(aux==NULL){
        cout << "No hay datos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << endl << "El código de producto : " << aux->info.id << endl;
        cout << "El Peso : " << aux->info.peso << endl;
        cout << "Stock : " << aux->info.stock << endl;
        aux = aux->sgte;
    }
}

void mostrar(Nodo *lista){
    Nodo * aux = lista;
    if(aux==NULL){
        cout << "No hay datos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << "El valore es : " << aux->info << endl;
        aux = aux->sgte;
    }
}

Nodo * unionPilasCola(Nodo *&pilaA, Nodo*&pilaB , Nodo *&cfte, Nodo *&cfin){    //Ej 1 a)
    Nodo * lista = NULL;
    while( pilaA != NULL) {
        insertarOrdenado(lista,pop(pilaA));
    }
    while( pilaB != NULL){
        insertarOrdenado(lista,pop(pilaB));
    }
    while( cfte != NULL){
        insertarOrdenado(lista,suprimir(cfte,cfin));
    }
    return lista;
}

void intersecPilaLista(Nodo *&pila, Nodo * lista, Nodo *&lista_fin){            //Ej 1 b)
    Nodo * aux= lista;
    int dato_pila;
    while ( pila != NULL){
        dato_pila = pop(pila);
        while(aux != NULL){
            if( dato_pila == aux->info){
                agregarPrimero(lista_fin,dato_pila);
                aux = NULL;
            }
            else{
                aux = aux->sgte;
            }
        }
        aux = lista;
    }
}

void actualizarMatriculas(Curso vec[], int len, NodoM * lista){                 //Ej 2
    NodoM * aux = NULL;
    for(int i = 0; i<len ; i++){
        aux = lista;
        while( aux != NULL){
            if( vec[i].id == aux->info.id){
                vec[i].cant++;
                vec[i].monto += aux->info.monto;
            }
            aux = aux->sgte;
        }
    }
}

void ordenarStock(){                                                            //Ej 3 a)
    FILE * arch_lectura = fopen("STOCK.dat","rb");
    NodoP * lista = NULL;
    Producto reg_prod;
    fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
    while( !feof(arch_lectura) ){
        insertarOrdenadoP(lista,reg_prod);
        fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
    }
    fclose(arch_lectura);
    FILE * arch_escritura = fopen("STOCK.dat","wb");
    NodoP * aux = lista;
    while( aux != NULL){
        fwrite(&aux->info,sizeof(struct Producto),1,arch_escritura);
        aux = aux->sgte;
    }
    fclose(arch_escritura);
    liberarP(lista);
}

void mostrarSinStock(){                                                         //Ej 3 b)
    FILE * arch_lectura = fopen("STOCK.dat","rb");
    NodoP * lista_sin_stock = NULL;
    NodoP * lista_pesados_no_perecederos = NULL;
    Producto reg_prod;
    fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
    while( !feof(arch_lectura) ){
        if(reg_prod.stock == 0){
            insertarOrdenadoP(lista_sin_stock,reg_prod);
        }
        if(reg_prod.tipo == 'N' || reg_prod.peso > 100){
            insertarOrdenadoP(lista_pesados_no_perecederos,reg_prod);
        }
        fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
    }
    fclose(arch_lectura);
    cout << endl << "----- Productos sin stock -----" << endl;
    mostrarP(lista_sin_stock);
    liberarP(lista_sin_stock);
    cout << endl << "----- Productos pesados y no perecederos -----" << endl;
    mostrarP(lista_pesados_no_perecederos);
    liberarP(lista_pesados_no_perecederos);
}

void crearArchivo(){
    FILE * archivo_prod = fopen("STOCK.dat","wb");
    Producto reg_prod;
    reg_prod.id = -1;
    cout << endl << "---- Iniciamos carga de archivo STOCK.dat ----" << endl;
    while(reg_prod.id != 0){

        cout << endl << "Ingrese código de producto o 0 para salir: ";
        cin >> reg_prod.id;
        if(reg_prod.id == 0) { continue; }
        cout << "Ingrese peso del producto: ";
        cin >> reg_prod.peso;
        cout << "Ingrese tipo de producto ( P - N ): ";
        cin >> reg_prod.tipo;
        cout << "Ingrese cantidad de stock del producto: ";
        cin >> reg_prod.stock;

        fwrite(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    }
    cout << endl;
    fclose(archivo_prod);
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
                int menu2 = -1;
                Nodo * pila1 = NULL;
                Nodo * pila2 = NULL;
                Nodo * cfte = NULL;
                Nodo * cfin = NULL;
                Nodo * lista = NULL;


                cout << "----Iniciamos carga de pila 1-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    cout << "Dato cargado: " << menu2 << endl;
                    push(pila1,menu2);
                }
                menu2 = -1;
                cout << "----Iniciamos carga de pila 2-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    cout << "Dato cargado: " << menu2 << endl;
                    push(pila2,menu2);
                }
                menu2 = -1;
                cout << "----Iniciamos carga de cola-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregar(cfte,cfin,menu2);
                }
                lista = unionPilasCola(pila1,pila2,cfte,cfin);
                cout << endl << "Lista resultante" << endl;
                mostrar(lista);

                Nodo * pila3 = NULL;
                Nodo * lista2 = NULL;
                menu2 = -1;
                cout << "----Iniciamos carga de pila 3-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    cout << "Dato cargado: " << menu2 << endl;
                    push(pila3,menu2);
                }
                intersecPilaLista(pila3,lista,lista2);
                cout << endl << "Lista intersección" << endl;
                mostrar(lista2);
                liberar(lista);
                liberar(lista2);
            }
            break;
        case 2:
            {
                cout << endl << "Ejercicio 2" << endl;
                Curso matriculas[cant_cursos];
                int len = 0;
                NodoM * reservas = NULL;

                matriculas[0].id = 1;
                matriculas[0].cant = 10;
                matriculas[0].monto = 100;
                len++;
                
                matriculas[1].id = 2;
                matriculas[1].cant = 20;
                matriculas[1].monto = 200;
                len++;

                matriculas[2].id = 3;
                matriculas[2].cant = 1;
                matriculas[2].monto = 100;
                len++;

                matriculas[3].id = 4;
                matriculas[3].cant = 10;
                matriculas[3].monto = 100;
                len++;

                matriculas[4].id = 5;
                matriculas[4].cant = 0;
                matriculas[4].monto = 0;
                len++;

                cout << endl << "Inicio de carga de lista de rerservas" << endl;
                int menu2 = -1;
                Matricula reg_matricula;
                while(menu2 != 0){
                    cout << endl << "Ingrese id curso: ";
                    cin >> menu2;
                    if(menu2 == 0) { continue; }
                    else           { reg_matricula.id = menu2; }
                    cout << "Ingrese monto: ";
                    cin >> reg_matricula.monto;
                    insertarOrdenadoM(reservas,reg_matricula);
                }
                actualizarMatriculas(matriculas,cant_cursos,reservas);
                cout << endl << "------- Cursos actualizados --------" << endl;
                for(int i=0;i<cant_cursos;i++){
                    cout << endl << "Curso: " << matriculas[i].id << endl;
                    cout << "Cantidad de alumnos: " << matriculas[i].cant << endl;
                    cout << "Monto facturado: " << matriculas[i].monto << endl;
                }
                liberarM(reservas);
            }
            break;
        case 3:
            {
                cout << endl << "Ejercicio 3" << endl;
                crearArchivo();
                ordenarStock();
                mostrarSinStock();
            }
            break;
        
        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
