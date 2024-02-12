/**
 * Ejercicio 25
 * Author: FNS
 * Descripción: Dada una serie de M pares {color, número} que corresponden a los tiros de una
*               ruleta. Se pide informar:
*                       a) cuántas veces salió el número cero y el número anterior a cada cero
*                       b) cuántas veces seguidas llegó a repetirse el color negro
*                       c) cuántas veces seguidas llegó a repetirse el mismo número y cuál fue
*                       d) el mayor número de veces seguidas que salieron alternados el rojo y el negro
*                       e) el mayor número de veces seguidas que se negó la segunda docenas
*/

#include<iostream>

using namespace std;

#define max 20

struct tiros{
    char color;
    int num;
};

//------Prototipos-----------------

void mostrar(tiros vec[], int len);
void cargarVector(tiros vec[], int &len, int cant_pos);
void countCeros(tiros vec[],int len);
void countNegro(tiros vec[],int len);
void countNumeros(tiros vec[],int len);
void countAlternadosNyR(tiros vec[],int len);
void countSin2daDocena(tiros vec[],int len);
//---------------------------------

//---Implementación de funciones---

void mostrar(tiros vec[], int len){
    cout << "*******Mostrando valores del vector**********" << endl;
    for( int i = 0 ; i<len ; i++ ){                     //Recorremos el vector hasta la cantidad de datos cargados.
        cout << i+1 << "º Infracción: " << endl;
        cout << "Color: " << vec[i].color << endl;    //Imprimimos en orden todos los datos junto a su indice sumado 1.
        cout << "Número: " << vec[i].num << endl;
        cout << "----------------------------------------" << endl;
    }
    cout << "*********************************************" << endl;
}

void cargarVector(tiros vec[], int &len, int cant_pos){   //Se carga vector con valores arbitrarios.
    cout << "Iniciamos la carga masiva del vector de " << cant_pos << " posiciones." << endl;
    for(int i=0; i<cant_pos ; i++){
        if( i < 10){
            vec[i].color = 'V';
            vec[i].num = 4;
        }
        else if( i < 15){
            vec[i].color = 'N';
            vec[i].num = 22;
        }
        else{
            vec[i].color = 'R';
            vec[i].num = 30;
        }
        len++;
    }
}

void countCeros(tiros vec[],int len){           //Procedimiento para el punto a)
    int count_ceros = 0;
    int num_ant [len];
    int len_ant = 0;
    for(int i=0 ; i<len ; i++){
        if( i==0 && vec[i].num==0){
            num_ant[len_ant] = -1;
            count_ceros++;
            len_ant++;
        }
        else if( vec[i].num == 0){
            count_ceros++;
            num_ant[len_ant] = vec[i-1].num;
            len_ant++;
        }
    }
    cout << "Cantidad de ceros: " << count_ceros << endl;
    for(int i=0; i<len_ant ; i++){
        cout << "Número anterior al " << i+1 << "º cero: " << num_ant[i] << endl; 
    }
}

void countNegro(tiros vec[],int len){           //Procedimiento para el punto b)
    int count_negros = 0;
    int max_seguidos = 0;
    for(int i=0; i<len ; i++){
        if(vec[i].color == 'N'){
            count_negros++;
        }
        else{
            count_negros = 0;
        }
        if(max_seguidos < count_negros){
            max_seguidos = count_negros;
        }
    }
    cout << "El color negro llego a repetirse " << max_seguidos << " veces." << endl;
}

void countNumeros(tiros vec[],int len){         //Procedimiento para el punto c)
    int ant  = vec[0].num;
    int max_nums = 0;
    int count_aux = 0;
    int num_max = -1;
    for(int i = 1 ; i<len ; i++){
        if(ant == vec[i].num){
            count_aux++;
        }
        else{
            count_aux =0;
        }
        if(count_aux > max_nums){
            max_nums = count_aux;
            num_max = vec[i].num;
        }
        ant = vec[i].num;
    }
    if(num_max == -1){
        cout << "No hubo números repetidos de manera consecutiva." << endl;
    }
    else{
        cout << "El número que salio más veces repetido fue el " << num_max << ", unas " << max_nums+1 << " veces" << endl;
    }
}

void countAlternadosNyR(tiros vec[],int len){   //Procedimiento para el punto d)
    char ant = vec[0].color;
    int count = 0;
    int count_max = 0;
    for(int i = 1; i<len ; i++){
        if((ant == 'N' && vec[i].color == 'R') || (ant == 'R' && vec[i].color == 'N')){
            count++;
        }
        else{
            count = 0;
        }
        if(count > count_max){
            count_max = count;
        }
        ant = vec[i].color;
    }
    if(count_max == 0){
        cout << "No hubo alternación entre el rojo y el negro." << endl;
    }
    else{
        cout << "La cantidad de veces que alterno el rojo y el negro fue de " << count_max << endl;
    }
}

void countSin2daDocena(tiros vec[],int len){    //Procedimiento para el punto e)
    int count = 0;
    int max_seguidos = 0;
    for(int i=0; i<len ; i++){
        if(vec[i].num > 12 && vec[i].num < 25){
            count=0;
        }
        else{
            count++;
        }
        if(max_seguidos < count){
            max_seguidos = count;
        }
    }
    cout << "La segunda docena se negó una cantidad consecutiva de " << max_seguidos << " veces." << endl;
}

//Prueba de funciones

int main(){
    tiros vec[max];
    int len=0;
    cargarVector(vec,len,max);
    
    vec[0].color = 'N';
    vec[1].color = 'R';
    vec[2].color = 'N';
    vec[3].color = 'R';
    mostrar(vec,len);
    countCeros(vec,len);
    countNegro(vec,len);
    countNumeros(vec,len);
    countAlternadosNyR(vec,len);
    countSin2daDocena(vec,len);
    return 0;
}
