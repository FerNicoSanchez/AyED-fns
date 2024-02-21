/**
 * Final 11/12/23 (Prof: Yamila)
 * Author: FNS
 * Descripción: Ver archivo Final1_2023.pdf
*/

#include<iostream>

using namespace std;

#define max_hoteles 50

//--------Estructuras--------------

struct Nodo {
    int info;
    Nodo * sgte;
};

struct Hotel
{
    int id;
    int reservas;
    int dias_dispo;
};

struct Reserva {
    int id;
    int dias_reservados;
};

struct NodoR{
    Reserva info;
    NodoR * sgte;
};

struct Producto
{
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

void agregarPrimero(Nodo *&Lista,int valor);
void agregarPrimeroR(NodoR *&Lista,Reserva valor);
void mostrar(Nodo * Lista);
void mostrarR(Hotel vec[],int len);
void mostrarP(NodoP * lista);
void liberar(Nodo * &Lista);
void liberarP(NodoP * &Lista);
void liberarR(NodoR * &Lista);
void insertarOrdenado(Nodo *&Lista,int valor);
void insertarOrdenadoP(NodoP *&Lista,Producto valor);





Nodo * unionPilaCola(Nodo *& pila, Nodo *& cfte, Nodo *&cfin);

void intersecListas(Nodo * lista1, Nodo * lista2, Nodo *&lista_fin);

void actualizarReservas(Hotel vec[],int len,NodoR * lista);

void ordenarStock();

void mostrarSinStock();

void mostrarPesados();

void mostrarStock();

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
    int ret = cfte->info;   //Guardamos los int del primer nodo.
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

void agregarPrimeroR(NodoR *&Lista,Reserva valor){
    NodoR * nuevo = new NodoR();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
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

void liberarR(NodoR * &Lista){
    NodoR * aux=NULL;
    while(Lista != NULL){
        aux = Lista;
        Lista = Lista->sgte;
        delete(aux);
    }
}

void liberarP(NodoP * &Lista){
    NodoP * aux=NULL;
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


void insertarOrdenadoP(NodoP *&Lista,Producto valor){
    NodoP * nuevo = new NodoP();
    nuevo->info = valor;
    nuevo->sgte = NULL;
    NodoP * aux = Lista;
    NodoP * ant = NULL;

    while(aux != NULL && aux->info.id < valor.id){
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

void mostrarP(NodoP * lista){
    while(lista != NULL){
        cout << endl << "Código de producto: " << lista->info.id << endl;
        cout << "Peso: " << lista->info.peso << endl;
        cout << "Tipo: " << lista->info.tipo << endl;
        cout << "Cantidad de stock: " << lista->info.stock << endl;
        lista=lista->sgte;
    }
}

void mostrarR(Hotel vec[],int len){
    cout << endl << "Mostrando hoteles" << endl;
    for(int i=0; i<len ; i++){
        cout << endl << "Código de hotel: " << vec[i].id << endl;
        cout << "Reservas: " << vec[i].reservas << endl;
        cout << "Cantidad de días disponibles: " << vec[i].dias_dispo << endl;
    }
}


Nodo * unionPilaCola(Nodo *& pila, Nodo *& cfte, Nodo *&cfin){          //Ej 1 a)
     Nodo * nuevo = NULL;
     int aux;
     while( pila != NULL){
        aux = pop(pila);
        insertarOrdenado(nuevo,aux);
     }
     while( cfte != NULL){
        aux = suprimir(cfte,cfin);
        insertarOrdenado(nuevo,aux);
     }
     return nuevo;
}

void intersecListas(Nodo * lista1, Nodo * lista2, Nodo *&lista_fin){    //Ej 1 b)
    //lista_fin debe estar vacia.
    //Si hay datos repetidos en lista1 y estos existen en lista2 al menos 1 vez, se repetirán en la intersección
    Nodo * aux = lista2;        //Este nodo nos ayudara a recorrer varias veces la lista 2.
    while( lista1 != NULL){     //Primero recorremos la lista 1.
        while( aux != NULL){    //Para cada dato de la lista 1 recorremos la lista 2.
            if( lista1->info == aux->info){                 //Comparamos la info de cada lista en cada iteración.
                agregarPrimero(lista_fin,lista1->info);     //En caso de ser iguales agregamos a la lista final.
                aux = NULL;                                 //Igualamos el puntero a NULL para salir del bucle.
            }
            else{
                aux = aux->sgte;                            //En el caso de coincidir la info avanzamos lista2.
            }
        }
        lista1 = lista1->sgte;  //Avanzamos lista1
        aux = lista2;           //Volvemos a conectarnos al inicio de la lista2
    }
}


void actualizarReservas(Hotel vec[],int len,NodoR * lista){         //Ej 2
    /* Algoritmo 
        -Recorrer listado de reservas.
        -Para cada reserva se le debe actualizar sus datos al hotel.
        -Para encontrar el hotel se debe recorrer todo el vector para cada reserva.
        -Una vez encontrado el hotel se debe aumentar la cantidad de reserva y disminuir su disponibilidad.
        -Una vez recorrida la lista completa termina el programa.
    */

    while( lista != NULL){
        for(int i = 0; i<len ; i++){
            if(lista->info.id == vec[i].id){
                vec[i].reservas++;
                vec[i].dias_dispo -= lista->info.dias_reservados;
                break;
            }
        }
        lista = lista->sgte;
    }

    /*Punto extra:
    Es la más eficiente ya que utilizamos la menor cantidad de recursos posibles, al conocer el tamaño max 
    del vector y la cantidad de datos cargados podemos usar sin problemas las estrategias de vectores, al no
    conocer la cantidad de reservas en la lista debemos utilizar un sistema que pueda funcionar independiente
    a ello. Se podría hacer lo mismo reemplazando la lista por una pila pero en este caso consumiriamos más
    recursos ya que para movernos por la pila debemos realizar el llamado de otra función.
    */
}


void ordenarStock(){                                                //Ej 3 a)
    FILE * arch_lectura = fopen("STOCK.dat","rb");
    NodoP * lista = NULL;
    Producto reg_prod;
    if( arch_lectura != nullptr){

        fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        while(!feof(arch_lectura)){
            insertarOrdenadoP(lista,reg_prod);
            fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        }
        fclose(arch_lectura);
        FILE * arch_escritura = fopen("STOCK.dat","wb");
        if ( arch_escritura != nullptr){
            NodoP * aux = lista;
            while( aux != NULL){
                fwrite(&aux->info,sizeof(struct Producto),1,arch_escritura);
                aux = aux->sgte;
            }
            fclose(arch_escritura);
            liberarP(lista);
        }
        else{
            cout << "Error al abrir el archivo STOCK.dat en modo escritura" << endl;
        }
    }
    else{
        cout << "Error al abrir el archivo STOCK.dat en modo lectura" << endl;
    }

}

void mostrarSinStock(){                                             //Ej 3 b) a.
    FILE * arch_lectura = fopen("STOCK.dat","rb");
    NodoP * lista = NULL;
    Producto reg_prod;
    if( arch_lectura != nullptr){
        fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        while(!feof(arch_lectura)){
            if( reg_prod.stock == 0){
                insertarOrdenadoP(lista,reg_prod);  //Sería mas óptimo usar la función agregarPrimero.
            }
            fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        }
        fclose(arch_lectura);
        mostrarP(lista);
        liberarP(lista);
    }
    else{
        cout << "Error al abrir el archivo STOCK.dat en modo escritura" << endl;
    }
}

void mostrarPesados(){                                              //Ej 3 b) b.
    FILE * arch_lectura = fopen("STOCK.dat","rb");
    NodoP * lista = NULL;
    Producto reg_prod;
    if( arch_lectura != nullptr){
        fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        while(!feof(arch_lectura)){
            if( reg_prod.peso > 100 || reg_prod.tipo == 'B'){
                insertarOrdenadoP(lista,reg_prod);  //Sería mas óptimo usar la función agregarPrimero.
            }
            fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        }
        fclose(arch_lectura);
        mostrarP(lista);
        liberarP(lista);
    }
    else{
        cout << "Error al abrir el archivo STOCK.dat en modo escritura" << endl;
    }
}

//Punto extra ejercicio 3:
/*
    Para ambos puntos podriamos utilizar vectores siempre y cuando tengamos conocimiento de la cantidad
    de productos que hay en el archivo.
    Para el punto b) podríamos utilizar pilas o colas ya que no necesitamos mantener el orden.

*/
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
        cout << "Ingrese tipo de producto ( A - B ): ";
        cin >> reg_prod.tipo;
        cout << "Ingrese cantidad de stock del producto: ";
        cin >> reg_prod.stock;

        fwrite(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    }
    cout << endl;
    fclose(archivo_prod);
}

void mostrarStock(){
    FILE * arch_lectura = fopen("STOCK.dat","rb");
    Producto reg_prod;
    if( arch_lectura != nullptr){
        cout << endl << "----------- Mostrando archivo STOCK.dat -------------" << endl;
        fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        while(!feof(arch_lectura)){
            cout << endl << "Código de producto: " << reg_prod.id << endl;
            cout << "Peso: " << reg_prod.peso << endl;
            cout << "Tipo: " << reg_prod.tipo << endl;
            cout << "Cantidad de stock: " << reg_prod.stock << endl;
            fread(&reg_prod,sizeof(struct Producto),1,arch_lectura);
        }
        fclose(arch_lectura);
    }
    else{
        cout << "Error al abrir el archivo STOCK.dat en modo lectura" << endl;
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
                cout << endl << "Ejercicio 1 a) " << endl;
                Nodo * pila = NULL;
                Nodo * cfte = NULL;
                Nodo * cfin = NULL;
                Nodo * lista = NULL;
                Nodo * lista2 = NULL;
                Nodo * lista3 = NULL;
                int menu2 = -1;
                cout << "----Iniciamos carga de pila-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    cout << "Dato cargado: " << menu2 << endl;
                    push(pila,menu2);
                }
                cout << "----Iniciamos carga de cola-----" << endl;
                menu2 = -1;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregar(cfte,cfin,menu2);
                }
                lista = unionPilaCola(pila,cfte,cfin);
                cout << endl << "Mostramos lista resultante" << endl;
                mostrar(lista);
                cout << endl << "Ejercicio 1 b) " << endl;
                cout << endl << "Con la lista del Ejercicio 1 a) buscamos intersección con la sig lista." << endl;
                cout << endl << "----- Iniciamos carga de la lista ----" << endl;
                menu2 = -1;
                while(menu2 != 0){
                    cout << endl << "Ingrese valor de la lista o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregarPrimero(lista2,menu2);
                }
                intersecListas(lista,lista2,lista3);
                cout << endl << "Mostramos lista intersección" << endl;
                mostrar(lista3);
                liberar(lista);
                liberar(lista2);
                liberar(lista3);
            }
            break;
        case 2:
            {
                cout << endl << "Ejercicio 2" << endl;
                Hotel vec[max_hoteles];
                int len = 0;
                int menu2 = -1;
                Reserva reg_reservas;
                NodoR * lista = NULL;

                cout << "La carga de los hoteles están en el código." << endl;
                vec[0].id = 1;
                vec[0].reservas = 0;
                vec[0].dias_dispo = 90;
                len++;
                
                vec[1].id = 2;
                vec[1].reservas = 10;
                vec[1].dias_dispo = 70;
                len++;
                vec[2].id = 3;
                vec[2].reservas = 40;
                vec[2].dias_dispo = 5;
                len++;

                mostrarR(vec,len);
                cout << endl << "----- Iniciamos carga de la lista ----" << endl;
                while(menu2 != 0){
                    cout << endl << "Ingrese código de hotel o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    else{
                        reg_reservas.id = menu2;
                    }
                    cout << "Ingrese cantidad de días reservados: ";
                    cin >> reg_reservas.dias_reservados;
                    agregarPrimeroR(lista,reg_reservas);
                }

                actualizarReservas(vec,len,lista);
                mostrarR(vec,len);
                liberarR(lista);


            }
            break;
        case 3:
            {
                cout << endl << "Ejercicio 3 " << endl;
                crearArchivo();
                cout << endl << "------ Archivo creado ------" << endl;
                ordenarStock();
                cout << endl << "------ Archivo Ordenado por ID------" << endl;
                mostrarStock();
                cout << endl << "------ Productos sin stock ------" << endl;
                mostrarSinStock();
                cout << endl << "------ Productos Pesados y Bebidas ------" << endl;
                mostrarPesados();
            }
            break;
        
        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
