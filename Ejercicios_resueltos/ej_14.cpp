/**
 * Ejercicio 14
 * Author: FNS
 * Descripción: Dados 50 números enteros, informar el promedio de los mayores que 100 y la
 *              suma de los menores que –10.
*/

#include<iostream>

using namespace std;

#define max 50

//Prototipo
void promPlus100_sumLowNeg10 (int vec[]);

//Implementación
void promPlus100_sumLowNeg10 (int vec[]){
    float acum_plus_100 = 0;
    int count_100 = 0;
    int sum_low_10 = 0;
    float prom = 0;
    for(int i=0; i<max ; i++){
        if(vec[i] > 100){
            acum_plus_100+= vec[i];
            count_100++;
        }
        if(vec[i] < -10){
            sum_low_10+= vec[i];
        }
    }
    if(count_100 == 0){
        cout << "No hay números mayores a 100" << endl;
    }
    else{
        prom = acum_plus_100 / count_100;
        cout << "El promedio de números mayores a 100 es: " << prom << endl;
    }
    cout << "La suma de los números menores a -10 es: " << sum_low_10 << endl;
}

//Prueba de procedimientos

int main(){
    int vec[max];
    for(int i = 0; i < max ; i++){
        if(i < 10){
            vec[i] = -3;
        }
        else{
            vec[i] = 57;
        }
    }
    vec[49]= 13;
    promPlus100_sumLowNeg10(vec);
    return 0;
}