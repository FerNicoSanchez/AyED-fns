/**
 * Ejercicios de repaso 2º Parcial 2023
 * Author: FNS
 * Descripción: Consignas en parcial1_2023.pdf 
*/

#include<iostream>

using namespace std;

//Prototipos

void unionVectores(int A[],int B[], int C[]);


//Implementación de funciones

void unionVectores(int A[],int B[],int C[]){        //Ejercicio 1
    int i;
    for( i = 0 ; i<10 ; i++){
        C[i] = A[i];
    }
    for (int b = 0; b < 10 ; b++ , i++){
        C[i] = B[b];
    }
}


//Prueba de funciones

int main(){

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

    return 0;
}