/**
 * Ejercicio 14
 * Author: FNS
 * Descripción: Se realiza una inspección en una fábrica de pinturas, y se detectaron 20
 *              infracciones. De cada infracción se tomó nota de los siguientes datos:
 *                      - Tipo de Infracción (1, 2, 3, ó 4)
 *                      - Motivo de la infracción
 *                      - Valor de la multa
 *                      - Gravedad de la infracción (‘L’,‘M’, ‘G’)
 *              Se pide informar al final del proceso:
 *                        Los valores totales de la multa a pagar de acuerdo al tipo de gravedad.
 *                        La leyenda “Clausurar fábrica” si la cantidad de infracciones 3 y 4 con gravedad “G”
 *                        sean mayor a 3
*/

#include<iostream>

using namespace std;

#define max 20 //Cantidad de infracciones informada en el ejercicios.

struct infraccion{
    char tipo;
    char motivo;
    int valor;
    char gravedad;
};

//------Prototipos-----------------

void inicializar(infraccion vec[], int cant_pos, infraccion inicial);
void mostrar(infraccion vec[], int len);
void cargarVector(infraccion vec[], int &len, int cant_pos);
void totalesMultas(infraccion vec[], int len);
void clausura(infraccion vec[], int len);

//---------------------------------

//---Implementación de funciones---

void inicializar(infraccion vec[], int cant_pos, infraccion inicial){
    for( int i=0 ; i<cant_pos ; i++){           //Recorremos todo el vector completo.
        vec[i].tipo     = inicial.tipo;         //A cada posición le asignamos el valor indicado.
        vec[i].motivo   = inicial.motivo;           
        vec[i].valor    = inicial.valor;           
        vec[i].gravedad = inicial.gravedad;           
    }
}

void mostrar(infraccion vec[], int len){
    cout << "*******Mostrando valores del vector**********" << endl;
    for( int i = 0 ; i<len ; i++ ){                     //Recorremos el vector hasta la cantidad de datos cargados.
        cout << i+1 << "º Infracción: " << endl;
        cout << "Tipo: " << vec[i].tipo << endl;    //Imprimimos en orden todos los datos junto a su indice sumado 1.
        cout << "Motivo: " << vec[i].motivo << endl;
        cout << "Valor: " << vec[i].valor << endl;
        cout << "Gravedad: " << vec[i].gravedad << endl;
        cout << "----------------------------------------" << endl;
    }
    cout << "*********************************************" << endl;
}

void cargarVector(infraccion vec[], int &len, int cant_pos){   //Se carga vector con valores arbitrarios.
    cout << "Iniciamos la carga masiva del vector de " << cant_pos << " posiciones." << endl;
    for(int i=0; i<cant_pos ; i++){
        if( i < 10){
            vec[i].tipo = '1';
            vec[i].motivo = 'A';
            vec[i].valor = 1000;
            vec[i].gravedad = 'L';
        }
        else if( i < 15){
            vec[i].tipo = '3';
            vec[i].motivo = 'A';
            vec[i].valor = 2000;
            vec[i].gravedad = 'G';
        }
        else{
            vec[i].tipo = '4';
            vec[i].motivo = 'B';
            vec[i].valor = 20000;
            vec[i].gravedad = 'G';
        }
        len++;
    }
}

void totalesMultas (infraccion vec[], int len){
    int acumL = 0;
    int acumM = 0;
    int acumG = 0;

    for(int i = 0; i<len ; i++){
        if( vec[i].gravedad == 'L' ){
            acumL += vec[i].valor;
        }
        if( vec[i].gravedad == 'M' ){
            acumM += vec[i].valor;
        }
        if( vec[i].gravedad == 'G' ){
            acumG += vec[i].valor;
        }
    }
    cout << "El monto total de infracciones de gravedad L es : " << acumL << endl;
    cout << "El monto total de infracciones de gravedad M es : " << acumM << endl;
    cout << "El monto total de infracciones de gravedad G es : " << acumG << endl;
}

void clausura(infraccion vec[], int len){
    int count3 = 0;
    int count4 = 0;

    for( int i=0 ; i<len ; i++ ){
        if( vec[i].tipo == '3' && vec[i].gravedad == 'G'){
            count3++;
        }
        if( vec[i].tipo == '4' && vec[i].gravedad == 'G'){
            count4++;
        }
    }
    if(count3>2){
        cout << "Clausurar fábrica 3." << endl; 
    }
    if(count4>2){
        cout << "Clausurar fábrica 4." << endl; 
    }
}

//---------------------------------

//---Prueba de funciones-----------

int main(){
    infraccion vec[max];
    int len = 0;
    infraccion inicial;
    
    inicial.tipo = '0';
    inicial.motivo = '0';
    inicial.valor = 0;
    inicial.gravedad = '0';

    inicializar(vec,max,inicial);
    cargarVector(vec,len,max);
    mostrar(vec,max);
    totalesMultas(vec,len);
    clausura(vec,len);

    return 0;
}