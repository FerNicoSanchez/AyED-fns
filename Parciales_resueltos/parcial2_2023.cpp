/*
 * Parcial enviado por wsp.
 * Author: FNS
 * Descripción: 
Ejercicio 1 (1 punto)
a) Desarrolle una función que determine, dadas las 2 notas obtenidas, si un alumno promociona. Nota: Un alumno promociona si ambas son 8 o más.
b) Desarrolle un procedimiento que muestre, dado un mes (MM), de qué cuatrimestre del año se trata. Nota: Deberá indicar si es el “Primero”, “Segundo” o “Tercero”.
Ejercicio 2 (1 punto)
Desarrolle los siguientes Subprogramas: 
a-	Una función que retorne una lista sin orden a partir de la Unión de una pila y una lista.
b-	Un procedimiento que genere una lista ordenada a partir de la INTERSECCION de 2 listas. 
Ejercicio 3 (1.5 puntos)
Dado un vector de Stock que indica los muebles que hay en un depósito y contiene el código del fabricante, código del producto y la cantidad de unidades disponibles en depósito (Se sabe que máximo hay 200 muebles), determinar:
a-	¿Cuál es el fabricante que más unidades tiene en depósito?
b-	¿Cuál es el Mueble que más unidades tiene?
Ejercicio 4 (1.5 puntos)
Se tiene un vector de Reservas de los hoteles de la costa atlántica en las que aplicó el pre-viaje para el verano 2023, que contiene un resumen de la disponibilidad de un hotel con los siguientes campos: 
-	Código del Hotel
-	Cantidad de Reservas 
-	Cantidad de Huéspedes
Además, se cuenta con una lista ordenada que contiene las últimas reservas realizadas, cada nodo de la lista contiene:
-	Código de Hotel 
-	AplicoPre-viaje (‘S’ o ‘N’)
-	Cantidad de huéspedes.
Se pide, actualizar el vector Reservas con la información que hay en la lista. Por cada reserva en la que SI haya aplicado Pre-viaje, debe actualizar la cantidad de huéspedes en el vector, como así incrementar 1 en las reservas. Se sabe que cómo Máximo hay 100 Hoteles.
 
Ejercicio 5 (2 puntos)
Se tiene un archivo de productos PROD.DAT (sin orden)
-	Código de producto: 999999999
-	Peso: 9999 kg
-	Cantidad en stock: 999999999
Se pide:
a)	Ordenar el archivo PROD.DAT por código de Producto.
b)	Mostrar un listado de los productos que no tienen unidades en Stock y otro listado con los productos PESADOS (peso mayor a 100 kg.)
Para Aprobar se requiere 1 punto de Teoría y el 5 puntos de práctica.
*/

#include<iostream>

using namespace std;

#define max_muebles 200
#define max_hoteles 100

//--------Estructuras-----------

struct Nodo{
    int info;
    Nodo * sgte;
};

struct Mueble{
    int id_fabricante;
    int id_producto;
    int unidades;
};

struct Hotel{
    int id_hotel;
    int reservas;
    int cant_huespedes;
};

struct Reserva{
    int id_hotel;
    char pre_viaje;
    int cant_huespedes;
};

struct NodoR{
    Reserva info;
    NodoR * sgte;
};

struct Producto{
    int id_producto;
    int peso;
    int stock;
};

struct NodoP{
    Producto info;
    NodoP * sgte;
};

//---------Prototipos-----------

bool promo(int nota1, int nota2);
void obtenerCuatri(int mes);

void push(Nodo*&pila,int valor);
int pop(Nodo*&pila);

void agregarPrimero(Nodo *&Lista,int valor);
void insertarOrdenado(Nodo*&,int valor);
void mostrarLista(Nodo* lista);
void liberar(Nodo*&lista);

void agregarPrimeroR(NodoR *&Lista,Reserva valor);
void insertarOrdenadoR(NodoR*&,Reserva valor);
void mostrarListaReservas(NodoR* lista);
void liberarR(NodoR*&lista);

Nodo * unionListaPila(Nodo * lista, Nodo * &pila);
void interseccionOrdenadaListas(Nodo * lista1, Nodo * lista2, Nodo * &lista_nueva);

void mostrar(Mueble vec[], int len);
void insertar(Mueble vec[], int &len, Mueble valor, int pos);
void cargarMueble(Mueble vec[], int &len, int cant_pos);

void mostrarHoteles(Hotel vec[], int len);

void maxFabricante(Mueble vec[],int len);
void maxMueble(Mueble vec[],int len);

void actualizarReservas(Hotel vec[], int len, NodoR * reservas);

void insertarOrdenadoP(NodoP*&lista,Producto valor);
void liberarP(NodoP*&lista);

void ordenarProductos(FILE * archivo);

void crearArchivo();

void mostrarArchivoProd();

NodoP * filtrarProdSinStock();

NodoP * filtrarProdPesados();

void mostrarProductos(NodoP *lista);
//--Implementación de funciones--

bool promo(int nota1, int nota2){               //Ej 1 a)
    if( nota1 > 7 && nota2 > 7){
        return true;
    }
    else{
        return false;
    }
}

void obtenerCuatri(int mes){                    //Ej 1 b)
    cout << endl << "El cuatrimestre es el: ";
    if( mes < 5){
        cout << "Primero" << endl;
    }
    else if( mes < 9){
        cout << "Segundo" << endl;
    }
    else{
        cout << "Tercero" << endl;
    }
}

void push(Nodo*&pila,int valor){
    Nodo*nuevo = new Nodo();    //Pedimos memoria.
    nuevo->info = valor;      //Cargamos int.
    nuevo->sgte = pila;         //Conectamos la pila al nuevo dato.
    pila = nuevo;               //La pila comienza con este nuevo dato.
}

int pop(Nodo*&pila){
    Nodo * aux = pila;          //Conectamos la pila.
    int ret = pila->info;       //Guardamos los int del nodo a eliminar.
    pila=pila->sgte;            //Avanzamos el puntero de la pila.
    delete(aux);                //Eliminamos el nodo.
    return ret;                 //Devolvemos el valor del nodo eliminado.
}

void agregarPrimero(Nodo *&Lista,int valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
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
        cout << "El dato es : " << aux->info << endl;
        aux = aux->sgte;
    }
}

void liberar(Nodo*&lista){
    Nodo*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

void agregarPrimeroR(NodoR *&Lista,Reserva valor){
    NodoR * nuevo = new NodoR();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void insertarOrdenadoR(NodoR*&lista,Reserva valor){
    NodoR*nuevo= new NodoR();
    nuevo->info = valor;
    nuevo->sgte = NULL;

    NodoR*aux=lista;
    NodoR*ant=NULL;

    while(aux!=NULL && nuevo->info.id_hotel > aux->info.id_hotel ){
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

void mostrarListaReservas(NodoR*lista){
    NodoR * aux = lista;
    if(aux==NULL){
        cout << "No hay datos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << endl << "El Código del hotel es : " << aux->info.id_hotel << endl;
        cout << "Estado Pre-viaje : " << aux->info.pre_viaje << endl;
        cout << "Cantidad de huespedes : " << aux->info.cant_huespedes << endl;
        aux = aux->sgte;
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

Nodo * unionListaPila(Nodo * lista, Nodo * &pila){   //Ej 2 a)
    Nodo * nuevo = NULL;
    int dato_pila;

    while( pila != NULL){
        dato_pila = pop(pila);
        agregarPrimero(nuevo,dato_pila);
    }
    
    while( lista != NULL){
        agregarPrimero(nuevo,lista->info);
        lista = lista->sgte;
    }

    return nuevo;
}

void interseccionOrdenadaListas(Nodo * lista1, Nodo * lista2, Nodo * &lista_nueva){  //Ej 2 b)
    Nodo * aux = lista2;
    while(lista1 != NULL){
        if( lista1->info == aux->info){
            insertarOrdenado(lista_nueva,lista1->info);
            lista1 = lista1->sgte;
            aux = lista2;
        }
        else {
            aux = aux->sgte;
        }
        if( aux == NULL){
            lista1 = lista1->sgte;
            aux = lista2;
        }
    }
}

void mostrar(Mueble vec[], int len){
    cout << "*******Mostrando valores del vector**********" << endl;
    for( int i = 0 ; i<len ; i++ ){                     //Recorremos el vector hasta la cantidad de datos cargados.
        cout << i+1 << "º Dato: " << endl;    //Imprimimos en orden todos los datos junto a su indice sumado 1.
        cout << "Código de fabricante: " << vec[i].id_fabricante << endl;
        cout << "Código de producto: " << vec[i].id_producto << endl;
        cout << "Cantidad de unidades en deposito: " << vec[i].unidades << endl;
    }
    cout << "*********************************************" << endl;
}

void mostrarHoteles(Hotel vec[], int len){
    cout << "*******Mostrando valores del vector**********" << endl;
    for( int i = 0 ; i<len ; i++ ){                     //Recorremos el vector hasta la cantidad de datos cargados.
        cout << i+1 << "º Dato: " << endl;    //Imprimimos en orden todos los datos junto a su indice sumado 1.
        cout << "Código de hotel: " << vec[i].id_hotel << endl;
        cout << "Cantidad de reservas: " << vec[i].reservas << endl;
        cout << "Cantidad de huéspedes: " << vec[i].cant_huespedes << endl;
    }
    cout << "*********************************************" << endl;
}

void insertar(int vec[], int &len, int valor, int pos){ //Inserta un dato en una posicion especifica.
    for(int i=len; i>pos ; i--){
        vec[i] = vec[i-1];
    }
    vec[pos] = valor;
    len++;
}

void cargarMueble(Mueble vec[], int &len, int cant_pos){   //Se carga vector mediante el ingreso por pantalla del usuario.
    cout << "Iniciamos la carga masiva del vector de " << cant_pos << " posiciones." << endl;
    for(int i=0; i<cant_pos ; i++){
        cout << endl << "Ingrese el " << i+1 << "º dato: " << endl;
        cout << "Código de fabricante: ";
        cin >> vec[i].id_fabricante;
        cout << "Código de producto: ";
        cin >> vec[i].id_producto;
        cout << "Cantidad de unidades en depósito: ";
        cin >> vec[i].unidades;
        len++;
    }
}

void maxFabricante(Mueble vec[],int len){       //Ej 3 a)
    Mueble agrup_fabri[len];
    int max_unidades = 0;
    int max_fabri = 0;
    int len_fabri = 0;
    int j;
    for(int i=0 ; i<len ; i++){
        for(j=0 ; j<len_fabri ; j++){
            if(vec[i].id_fabricante == agrup_fabri[j].id_fabricante){
                agrup_fabri[j].unidades += vec[i].unidades;
                break;
            }
        }
        if(j==len_fabri){
            agrup_fabri[len_fabri] = vec[i];
            len_fabri++;
        }
    }
    for(j=0 ; j<len_fabri ;j++){
        if(agrup_fabri[j].unidades > max_unidades){
            max_unidades = agrup_fabri[j].unidades;
            max_fabri = agrup_fabri[j].id_fabricante;
        }
    }
    cout << endl << "El fabricante con más unidades tiene el código : ";
    cout << max_fabri << ", con " << max_unidades << " unidades en depósito." << endl;
}

void maxMueble(Mueble vec[],int len){           //Ej 3 b)
    int max_unidades = 0;
    int id_producto;
    for(int i = 0; i<len ; i++){
        if(vec[i].unidades > max_unidades){
            max_unidades = vec[i].unidades;
            id_producto = vec[i].id_producto;
        }
    }
    cout << endl << "El mueble con más unidades tiene el código: ";
    cout << id_producto << ", con " << max_unidades << " unidades." << endl;
}

void actualizarReservas(Hotel vec[],int len, NodoR * reservas){ //Ej 4
    while( reservas != NULL){
        if(reservas->info.pre_viaje == 'S'){
            for(int i=0; i<len ; i++){
                if(reservas->info.id_hotel == vec[i].id_hotel){
                    vec[i].cant_huespedes += reservas->info.cant_huespedes;
                    vec[i].reservas++;
                    break;
                }
            }
        }
        reservas = reservas->sgte;
    }
}

void insertarOrdenadoP(NodoP*&lista,Producto valor){
    NodoP*nuevo= new NodoP();
    nuevo->info = valor;
    nuevo->sgte = NULL;

    NodoP*aux=lista;
    NodoP*ant=NULL;

    while(aux!=NULL && nuevo->info.id_producto > aux->info.id_producto ){
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

void ordenarProductos(FILE * archivo_lectura){  //Ej 5 a)
    Producto reg_prod;
    NodoP * lista_prod = NULL;

    fread(&reg_prod,sizeof(struct Producto),1,archivo_lectura);
    while(!feof(archivo_lectura)){
        insertarOrdenadoP(lista_prod,reg_prod);
        fread(&reg_prod,sizeof(struct Producto),1,archivo_lectura);
    }
    fclose(archivo_lectura);
    FILE * archivo_escritura = fopen("PROD.dat","wb");
    NodoP * aux = lista_prod;
    while( aux != NULL){
        fwrite(&aux->info,sizeof(struct Producto),1,archivo_escritura);
        aux = aux->sgte;
    }
    fclose(archivo_escritura);
    liberarP(lista_prod);
}

void crearArchivo(){
    FILE * archivo_prod = fopen("PROD.dat","wb");
    Producto reg_prod;
    reg_prod.id_producto = -1;
    cout << endl << "---- Iniciamos carga de archivo PROD.dat ----" << endl;
    while(reg_prod.id_producto != 0){
        cout << endl << "Ingrese código de producto o 0 para salir: ";
        cin >> reg_prod.id_producto;
        if(reg_prod.id_producto == 0) { continue; }
        cout << "Ingrese peso del producto: ";
        cin >> reg_prod.peso;
        cout << "Ingrese cantidad de stock del producto: ";
        cin >> reg_prod.stock;

        fwrite(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    }
    cout << endl;
    fclose(archivo_prod);
}

void mostrarArchivoProd(){
    FILE * archivo_prod = fopen("PROD.dat","rb");
    Producto reg_prod;
    cout << endl << "------------- Archivo PROD.dat ----------------" << endl;
    fread(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    while(!feof(archivo_prod)){
        cout << endl << "Código del producto: " << reg_prod.id_producto << endl;
        cout << "Peso del producto: " << reg_prod.peso << endl;
        cout << "Cantidad de stock del producto: " << reg_prod.stock << endl;
        fread(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    }
    fclose(archivo_prod);
}

NodoP * filtrarProdSinStock(){                      //EJ 5 b)
    FILE * archivo_prod = fopen("PROD.dat","rb");
    Producto reg_prod;
    NodoP * lista_prod = NULL;

    fread(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    while(!feof(archivo_prod)){
        if(reg_prod.stock == 0){
            insertarOrdenadoP(lista_prod,reg_prod);
        }
        fread(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    }
    fclose(archivo_prod);
    return lista_prod;
}

NodoP * filtrarProdPesados(){                       //EJ 5 b)
    FILE * archivo_prod = fopen("PROD.dat","rb");
    Producto reg_prod;
    NodoP * lista_prod = NULL;

    fread(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    while(!feof(archivo_prod)){
        if(reg_prod.peso > 100){
            insertarOrdenadoP(lista_prod,reg_prod);
        }
        fread(&reg_prod,sizeof(struct Producto),1,archivo_prod);
    }
    fclose(archivo_prod);
    return lista_prod;
}

void mostrarProductos(NodoP *lista){
    NodoP * aux = lista;
    if(aux==NULL){
        cout << "No hay datos cargados en la lista." << endl;
    }
    cout << endl << "-------Mostrando lista de productos-------" << endl;
    while(aux!=NULL){
        cout << endl << "El código de producto : " << aux->info.id_producto << endl;
        cout << "El Peso : " << aux->info.peso << endl;
        cout << "Stock : " << aux->info.stock << endl;
        aux = aux->sgte;
    }
}


//-----Prueba de funciones----

int main(){
    int menu = -1;

    while( menu != 0){
        cout << endl << "Ingrese el número de ejercicio que desea activar o 0 para salir: ";
        cin >> menu;
        if(menu == 0)   { continue; }

        switch (menu)
        {
        case 1:
            {
                int nota1 = -1;
                int nota2;
                cout << endl << "Ejercicio 1 a)" << endl;
                while(nota1 != 0){
                    cout << endl << "Ingrese nota 1 o ingrese 0 para salir: ";
                    cin >> nota1;
                    if(nota1 == 0)  { continue; }
                    cout << "Ingrese nota 2: ";
                    cin >> nota2;
                    if(promo(nota1,nota2)){
                        cout << endl << "Promocionado!" << endl; 
                    }
                    else{
                        cout << endl << "Sin promoción." << endl;
                    }
                }
                cout << "-------------------------------------------------" << endl;
                cout << "Ejercicio 1 b)" << endl;
                int mes = -1;
                while(mes != 0){
                    cout << endl << "Ingrese el número del mes o 0 para salir: ";
                    cin >> mes;
                    if(mes==0) { continue; }
                    obtenerCuatri(mes);
                }
            }
            break;
        case 2:
            {
                Nodo * lista1 = NULL;
                Nodo * lista2 = NULL;
                Nodo * lista3 = NULL;
                Nodo * lista4 = NULL;
                Nodo * pila = NULL;
                int menu2 = -1;
                cout << endl << "Ejercicio 2 a)" << endl;
                cout << "----Iniciamos carga de pila-----" << endl;
                while(menu2 != 0){
                    cout << "Ingrese valor o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    cout << "Dato cargado: " << menu2 << endl;
                    push(pila,menu2);
                }
                cout << endl << "----- Iniciamos carga de la lista 1 ----" << endl;
                menu2 = -1;
                while(menu2 != 0){
                    cout << endl << "Ingrese valor de la lista 1 o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregarPrimero(lista1,menu2);
                }
                lista2 = unionListaPila(lista1,pila);
                cout << endl << "------ Lista resultante de la union -------" << endl << endl;
                mostrarLista(lista2);
                cout << endl << "Ejercicio 2 b)" << endl;
                menu2 = -1;
                cout << "La siguiente lista sera la cual se hará intersección con la union del ej1" << endl;
                cout << "----Iniciamos carga de la lista 3-----" << endl;
                while(menu2 != 0){
                    cout << endl << "Ingrese valor de la lista o 0 para salir: ";
                    cin >> menu2;
                    if( menu2 == 0 ) { continue; }
                    agregarPrimero(lista3,menu2);
                }
                
                interseccionOrdenadaListas(lista2,lista3,lista4);
                cout << "-------Intersección de las listas-----" << endl;
                mostrarLista(lista4);
                liberar(lista1);
                liberar(lista2);
                liberar(lista3);
                liberar(lista4);
            }
            break;
        case 3:
            {
                Mueble muebles[max_muebles];
                int len = 0;
                int cant = 0;
                cout << endl << "Ejercicio 3 a) y b)" << endl << endl;
                cout << "Ingrese la cantidad de muebles que desea cargar: ";
                cin >> cant;
                cargarMueble(muebles,len,cant);
                maxFabricante(muebles,len);
                maxMueble(muebles,len);
            }
            break;
        case 4:
            {
                cout << endl << "Ejercicio 4)" << endl;
                cout << "Para cargar la info de hoteles se debe modificar el código." << endl;
                Hotel hoteles[max_hoteles];
                int len = 0;
                int menu2 = -1;
                NodoR * reservas = NULL;
                Reserva reserva;

                hoteles[0].id_hotel = 1;
                hoteles[0].reservas = 0;
                hoteles[0].cant_huespedes = 0;
                len++;
                
                hoteles[1].id_hotel = 2;
                hoteles[1].reservas = 100;
                hoteles[1].cant_huespedes = 500;
                len++;

                hoteles[2].id_hotel = 3;
                hoteles[2].reservas = 7;
                hoteles[2].cant_huespedes = 14;
                len++;
                
                hoteles[3].id_hotel = 4;
                hoteles[3].reservas = 50;
                hoteles[3].cant_huespedes = 50;
                len++;
                
                mostrarHoteles(hoteles,len);
                cout << "----- Iniciamos carga de lista de reservas ----" << endl;
                while(menu2 != 0){
                    cout << endl << "Ingrese código de hotel o 0 para salir: ";
                    cin >> reserva.id_hotel;
                    if(reserva.id_hotel == 0){
                        menu2 = 0;
                        continue;
                    }
                    cout << "Ingrese estado de pre-viaje (S o N): ";
                    cin >> reserva.pre_viaje;
                    cout << "Ingrese cantidad de huéspedes: ";
                    cin >> reserva.cant_huespedes;
                    insertarOrdenadoR(reservas,reserva);
                }
                actualizarReservas(hoteles,len,reservas);
                mostrarHoteles(hoteles,len);
                liberarR(reservas);
            }
            break;
        case 5:
            {
                cout << endl << "Ejercicio 5 a)" << endl;
                crearArchivo();
                FILE * archivo_lectura = fopen("PROD.dat","rb"); //El archivo se cierra en la prox función.
                ordenarProductos(archivo_lectura);
                cout << endl << "Archivo ordenado." << endl;
                mostrarArchivoProd();
                cout << endl << "Ejercicio 5 b)" << endl;
                NodoP * lista_pesados = filtrarProdPesados();
                NodoP * lista_sin_stock = filtrarProdSinStock();
                cout << endl << "----------Sin stock-------------" << endl;
                mostrarProductos(lista_sin_stock);
                cout << endl << "----------Pesados-------------" << endl;
                mostrarProductos(lista_pesados);
                liberarP(lista_sin_stock);
                liberarP(lista_pesados);
            }
            break;
        
        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}
