/**
 * Parcial integrador 2023 
 * Author: FNS
 * Descripción: Ver archivo parcial7.jpeg
*/

#include<iostream>

using namespace std;

#define cant_prov 3
#define cant_cab 5

//--------Estructuras--------------

struct Cabania{     //No se puede usar la enie putabida
    int id;
    int reservas;
    int cant_huespedes;
    int monto;
};

struct Reservas{
    int id;
    char beneficio;
    int cant_huespedes;
    int monto;
};

struct NodoR{
    Reservas info;
    NodoR * sgte;
};

struct Nodo{
    int info;
    Nodo * sgte;
};

struct Viaje{
    int id;
    char tipo;
    int precio;
};

struct NodoV{
    Viaje info;
    NodoV * sgte;
};

struct Votos{
    int prov;
    char partido;
    int votos;
};

//--------Prototipos---------------

void push(Nodo*&pila,int persona);
int pop(Nodo*&pila);

void agregar(Nodo*&cfte,Nodo*&cfin,int persona);
int suprimir(Nodo*&cfte,Nodo*&cfin);

void insertar(int vec[], int &len, int valor, int pos);
void insertarOrdenadoVec(int vec[], int &len, int valor);
int buscar(Cabania vec[], int len , int valor);

void liberar(Nodo * &Lista);
void insertarOrdenado(Nodo *&Lista,int valor);
void agregarPrimero(Nodo *&Lista,int valor);
void mostrar(Nodo *lista);

void insertarOrdenadoV(NodoV*&lista,Viaje valor);
void liberarV(NodoV*&lista);
void mostrarV(NodoV *lista);

void insertarOrdenadoR(NodoR*&lista,Reservas valor);
void liberarR(NodoR*&lista);

void crearArchivo();

float promEstudiante(float nota1, int nota2, int nota3);

void GenerarVectorOrdenado(int * puntero_a_vec,int &len);

Nodo * unionColas(Nodo * &cfteA, Nodo * &cfinA, Nodo * &cfteB, Nodo * &cfinB);

void intersecColaLista(Nodo * &cfte, Nodo * &cfin, Nodo * lista1, Nodo *&lista_fin);

int votosXpartido(Votos vec[], int len, char partido);

void promPartidoB(Votos vec[],int len);

void maxVotos(Votos vec[],int len);

void actualizarReservas(Cabania vec[], int len, NodoR * lista);

void OrdenarArchivo();

void insertarOrdenadoPrecioViaje(NodoV*&lista,Viaje valor);

void OrdenarArchivoPorIDyPrecios();

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

void insertarOrdenadoV(NodoV*&lista,Viaje valor){
    NodoV*nuevo= new NodoV();
    nuevo->info = valor;
    nuevo->sgte = NULL;

    NodoV*aux=lista;
    NodoV*ant=NULL;

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

void insertarOrdenadoR(NodoR*&lista,Reservas valor){
    NodoR*nuevo= new NodoR();
    nuevo->info = valor;
    nuevo->sgte = NULL;

    NodoR*aux=lista;
    NodoR*ant=NULL;

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

void liberarV(NodoV*&lista){
    NodoV*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

void liberarR(NodoR*&lista){
    NodoR*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

void mostrarV(NodoV *lista){
    NodoV * aux = lista;
    if(aux==NULL){
        cout << "No hay datos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << endl << "El código de Viaje : " << aux->info.id << endl;
        cout << "Tipo de reserva : " << aux->info.tipo << endl;
        cout << "Precio : " << aux->info.precio << endl;
        aux = aux->sgte;
    }
}

void mostrar(Nodo *lista){
    Nodo * aux = lista;
    if(aux==NULL){
        cout << "No hay datos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << "El valor es : " << aux->info << endl;
        aux = aux->sgte;
    }
}

void insertar(int vec[], int &len, int valor, int pos){ //Inserta un dato en una posicion especifica.
    for(int i=len; i>pos ; i--){
        vec[i] = vec[i-1];
    }
    vec[pos] = valor;
    len++;
}

void insertarOrdenadoVec(int vec[], int &len, int valor){  //Inserta un dato segun el orden ascendente.
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

int buscar(Cabania vec[], int len , int valor){     //Busca un dato y devuelve el indice donde lo encontro.
    int i=0;
    while( i<len && vec[i].id != valor){
        i++;
    }
    if(i==len){
        return -1;
    }
    else{
        return i;
    }
}

void crearArchivo(){
    FILE * archivo_prod = fopen("Viajes2024.dat","wb");
    Viaje reg_prod;
    reg_prod.id = -1;
    cout << endl << "---- Iniciamos carga de archivo Viajes2024.dat ----" << endl;
    while(reg_prod.id != 0){

        cout << endl << "Ingrese código de Viaje o 0 para salir: ";
        cin >> reg_prod.id;
        if(reg_prod.id == 0) { continue; }
        cout << "Ingrese tipo de Viaje ( P - E - S ): ";
        cin >> reg_prod.tipo;
        cout << "Precio del Viaje: ";
        cin >> reg_prod.precio;

        fwrite(&reg_prod,sizeof(struct Viaje),1,archivo_prod);
    }
    cout << endl;
    fclose(archivo_prod);
}

float promEstudiante(float nota1, int nota2, int nota3){          //Ej 1 a)
    float promedio = (nota1 + nota2 + nota3) / 3;
    return promedio;
}

void GenerarVectorOrdenado(int vec[],int &len){                   //Ej 1 b)
    int aux = -1;
    while(aux != 0){
        cout << endl << "Ingrese valor o 0 para terminar: ";
        cin >> aux;
        if (aux == 0) { continue ; }
        insertarOrdenadoVec(vec,len,aux);
    }
}

Nodo * unionColas(Nodo * &cfteA, Nodo * &cfinA, Nodo * &cfteB, Nodo * &cfinB){          //Ej 2 a)
    Nodo * lista = NULL;
    while ( cfteA != NULL){
        insertarOrdenado(lista,suprimir(cfteA,cfinA));
    }
    while ( cfteB != NULL){
        insertarOrdenado(lista,suprimir(cfteB,cfinB));
    }
    return lista;
}

void intersecColaLista(Nodo * &cfte, Nodo * &cfin, Nodo * lista1, Nodo *&lista_fin){    //Ej 2 b)
    Nodo * aux = NULL;
    int dato_cola;
    while( cfte != NULL){
        aux = lista1;
        dato_cola = suprimir(cfte,cfin);
        while( aux != NULL){
            if( aux->info == dato_cola){
                agregarPrimero(lista_fin,dato_cola);
                aux = NULL;
            }
            else{
                aux = aux->sgte;
            }
        }
    }
    
}

int votosXpartido(Votos vec[], int len, char partido){              //Ej 3 a)
    int total_votos = 0;
    for( int i = 0; i<len ; i++){
        if( vec[i].partido == partido ){
            total_votos += vec[i].votos; 
        }
    }
    return total_votos;
}

void promPartidoB(Votos vec[],int len){                             //Ej 3 b)
    float provincias = 23;
    float promedio = votosXpartido(vec,len,'B') / provincias;
    cout << endl << "El promedio de votos por provincia para el partido B es de: " << promedio << endl;
}

void maxVotos(Votos vec[],int len){                                 //Ej 3 c)
    int max = 0;
    int i_max = 0;
    for (int i = 0; i<len ; i++){
        if( vec[i].votos > max){
            max = vec[i].votos;
            i_max = i;
        }
    }
    cout << endl << "La provincia " << vec[i_max].prov << " del partido " << vec[i_max].partido;
    cout << " con " << vec[i_max].votos << " votos fue la que mayor votos recibio." << endl;
}
//Nota: Para la resolución del ejercicio 3 se debe desarrollar el main mostrando el llamado a las funciones.

void actualizarReservas(Cabania vec[], int len, NodoR * lista){     //Ej 4
    int indice;
    while ( lista != NULL ){
        if( lista->info.beneficio == 'S'){
            indice = buscar(vec,len,lista->info.id);
            if( indice >= 0){
                vec[indice].reservas++;
                vec[indice].cant_huespedes += lista->info.cant_huespedes;
                vec[indice].monto += lista->info.monto;
            }
        }
        lista = lista->sgte;
    }
}

void insertarOrdenadoPrecioViaje(NodoV*&lista,Viaje valor){         //Auxiliar para ej 5b
    NodoV *nuevo = new NodoV();
    nuevo->info = valor;
    nuevo->sgte = NULL;
    NodoV*aux = lista;
    NodoV*ant = NULL;

    while( aux != NULL && aux->info.precio > nuevo->info.precio ){
        ant = aux;
        aux = aux->sgte;
    }
    if( ant == NULL){
        lista = nuevo;
    }
    else{
        ant->sgte = nuevo;
    }
    nuevo->sgte = aux;
}

void OrdenarArchivoPorIDyPrecios(){                                         //Ej 5 a) y b)
    FILE * archivo_lectura = fopen("Viajes2024.dat","rb");
    NodoV * lista = NULL;
    NodoV * listaB = NULL;
    Viaje reg_viaje;
    fread(&reg_viaje,sizeof(struct Viaje),1,archivo_lectura);
    while(!feof(archivo_lectura)){
        insertarOrdenadoV(lista,reg_viaje);
        if(reg_viaje.precio > 2500 && ( reg_viaje.tipo == 'P' || reg_viaje.tipo == 'E' )){
            insertarOrdenadoPrecioViaje(listaB,reg_viaje);
        }
        fread(&reg_viaje,sizeof(struct Viaje),1,archivo_lectura);
    }
    fclose(archivo_lectura);
    cout << endl << "------ Lista ordenada de viajes por id -------" << endl;
    mostrarV(lista);
    FILE * archivo_escritura = fopen("Viajes2024.dat","wb");
    NodoV * aux = lista;
    while( aux != NULL){
        fwrite(&aux->info,sizeof(struct Viaje),1,archivo_escritura);
        aux = aux->sgte;
    }
    fclose(archivo_escritura);
    liberarV(lista);
    cout << endl << "--- Lista ordenada por precios ---" << endl;
    mostrarV(listaB);
    liberarV(listaB);
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
                cout << endl << "Ejercicio 1 a)" << endl;
                float menu2 = -1;
                int nota2,nota3;
                while(menu2 != 0){
                    cout << endl << "Ingrese nota 1 o 0 para terminar: ";
                    cin >> menu2;
                    if(menu2 == 0) { continue; }
                    cout << endl << "Ingrese nota 2: ";
                    cin >> nota2;
                    cout << endl << "Ingrese nota 3: ";
                    cin >> nota3;
                    cout << endl << "El promedio es : " << promEstudiante(menu2,nota2,nota3) << endl;
                }
                cout << endl << "Ejercicio 1 b)" << endl;
                int vec[10];
                int len = 0;
                GenerarVectorOrdenado(vec,len);
                cout << endl << "----- Mostramos vector resultante ----- " << endl;
                for(int i = 0; i<len ; i++){
                    cout << endl << i+1 << "º Dato: " << vec[i] << endl;
                }

            }
            break;
        case 2:
            {
                cout << endl << "Ejercicio 2 a)" << endl;
                Nodo * cfteA = NULL;
                Nodo * cfinA = NULL;
                Nodo * cfteB = NULL;
                Nodo * cfinB = NULL;
                Nodo * lista = NULL;
                int menu2 = -1;

                cout << "----Iniciamos carga de cola 1-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregar(cfteA,cfinA,menu2);
                }
                cout << "----Iniciamos carga de cola 2-----" << endl;
                menu2 = -1;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregar(cfteB,cfinB,menu2);
                }
                lista = unionColas(cfteA,cfinA,cfteB,cfinB);
                cout << endl << "Lista resultante:" << endl;
                mostrar(lista);

                cout << endl << "Ejercicio 2 b)" << endl;
                menu2 = -1;
                Nodo * cfte = NULL;
                Nodo * cfin = NULL;
                Nodo * lista_fin = NULL;
                cout << "----Iniciamos carga de cola 3-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregar(cfte,cfin,menu2);
                }
                cout << endl << "Interseccion de cola 3 con lista resultante:" << endl;
                intersecColaLista(cfte,cfin,lista,lista_fin);
                mostrar(lista_fin);
                liberar(lista);
                liberar(lista_fin);
            }
            break;
        case 3:
            {
                cout << endl << "Ejercicio 3" << endl;
                Votos vec[cant_prov*2];
                int len = 0;

                vec[0].prov = 1;
                vec[0].partido = 'A';
                vec[0].votos = 0;
                len++;

                vec[1].prov = 1;
                vec[1].partido = 'B';
                vec[1].votos = 10;
                len++;

                vec[2].prov = 2;
                vec[2].partido = 'A';
                vec[2].votos = 500;
                len++;

                vec[3].prov = 2;
                vec[3].partido = 'B';
                vec[3].votos = 70;
                len++;

                vec[4].prov = 3;
                vec[4].partido = 'A';
                vec[4].votos = 180;
                len++;

                vec[5].prov = 3;
                vec[5].partido = 'B';
                vec[5].votos = 2500;
                len++;

                cout << endl << "La cantidad de votos totales del partido A es: " << votosXpartido(vec,len,'A');
                promPartidoB(vec,len);
                maxVotos(vec,len);
            }
            break;
        case 4:
            {   
                cout << endl << "Ejercicio 4" << endl;
                Cabania vec[cant_cab];
                NodoR * lista = NULL;
                Reservas reg_aux;
                int menu2 = -1;
                int len = 0;

                vec[0].id = 1;
                vec[0].reservas = 0;
                vec[0].cant_huespedes = 0;
                vec[0].monto = 0;
                len++;
                
                vec[1].id = 2;
                vec[1].reservas = 10;
                vec[1].cant_huespedes = 555;
                vec[1].monto = 10000;
                len++;
                
                vec[2].id = 3;
                vec[2].reservas = 1;
                vec[2].cant_huespedes = 1;
                vec[2].monto = 2500;
                len++;

                vec[3].id = 4;
                vec[3].reservas = 500;
                vec[3].cant_huespedes = 1000;
                vec[3].monto = 30000;
                len++;

                vec[4].id = 5;
                vec[4].reservas = 50;
                vec[4].cant_huespedes = 50;
                vec[4].monto = 5000;
                len++;

                cout << endl << "Iniciamos carga de lista de reservas" << endl;
                while(menu2 != 0){
                    cout << endl << "Ingrese código de cabaña o 0 para salir: ";
                    cin >> menu2;
                    if(menu2 == 0){ continue; }
                    else{
                        reg_aux.id = menu2;
                    }
                    cout << "Ingrese S si tiene beneficio o N si no lo tiene: ";
                    cin >> reg_aux.beneficio;
                    cout << "Ingrese cantidad de huespedes: ";
                    cin >> reg_aux.cant_huespedes;
                    cout << "Ingrese monto: ";
                    cin >> reg_aux.monto;
                    insertarOrdenadoR(lista,reg_aux);
                }
                actualizarReservas(vec,len,lista);
                cout << endl << "----- Reservas actualizadas -----" << endl;
                for(int i=0; i<len; i++){
                    cout << endl << "Código de cabaña: " << vec[i].id << endl;
                    cout << "Cantidad de reservas: " << vec[i].reservas << endl;
                    cout << "Cantidad de huespedes: " << vec[i].cant_huespedes << endl;
                    cout << "Monto total: " << vec[i].monto << endl;
                }
                liberarR(lista);

            }
            break;
        case 5:
            {
                cout << endl << "Ejercicio 5" << endl;
                crearArchivo();
                OrdenarArchivoPorIDyPrecios();
            }
            break;
        
        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
