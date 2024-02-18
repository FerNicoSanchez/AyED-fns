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

//---------Prototipos-----------

bool promo(int nota1, int nota2);
void obtenerCuatri(int mes);

void push(Nodo*&pila,int valor);
int pop(Nodo*&pila);

void agregarPrimero(Nodo *&Lista,int valor);
void insertarOrdenado(Nodo*&,int valor);
void mostrarLista(Nodo* lista);
void liberar(Nodo*&lista);

Nodo * unionListaPila(Nodo * lista, Nodo * &pila);
void interseccionOrdenadaListas(Nodo * lista1, Nodo * lista2, Nodo * &lista_nueva);

void mostrar(Mueble vec[], int len);
void insertar(Mueble vec[], int &len, Mueble valor, int pos);
void cargarMueble(Mueble vec[], int &len, int cant_pos);

void maxFabricante(Mueble vec[],int len);
void maxMueble(Mueble vec[],int len);
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
                mostrarLista(lista1);
                lista2 = unionListaPila(lista1,pila);
                cout << endl << "---La lista resultante de la union---" << endl;
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

            }
            break;
        case 5:
            {

            }
            break;
        
        default:
            cout << "Ingrese una opción válida." << endl;
            break;
        }
    }

    return 0;
}

