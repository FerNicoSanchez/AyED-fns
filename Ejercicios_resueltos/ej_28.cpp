/**
 * Ejercicio 28
 * Author: FNS
 * Descripción: Dada una serie de caracteres que conforman una oración, donde cada palabra está
 *              separada de la siguiente por un carácter blanco y la oración finaliza con un punto. Se pide
 *              informar:
 *                          a) cantidad de veces que apareció cada vocal
 *                          b) cantidad de palabras que contiene la oración
 *                          c) cantidad de letras que posee la palabra más larga.
*/

#include<iostream>

using namespace std;

#define max1 17
#define max2 15

//------Prototipos-----------------

void inicializar(char vec[], int cant_pos, char valor_inicial);
void mostrar(char vec[], int len);
void cargarVector(char vec[], int &len, int cant_pos);
void countVocales(char vec[],int len);
void countPalabras(char vec [],int len);
void countLetras(char vec[],int len);
//---------------------------------

//---Implementación de funciones---

void inicializar(char vec[], int cant_pos, char valor_inicial){
    for( int i=0 ; i<cant_pos ; i++){   //Recorremos todo el vector completo.
        vec[i]=valor_inicial;           //A cada posición le asignamos el valor indicado.
    }
}

void mostrar(char vec[], int len){
    cout << "*******Mostrando valores del vector**********" << endl;
    for( int i = 0 ; i<len ; i++ ){                     //Recorremos el vector hasta la cantidad de datos cargados.
        cout << vec[i];    //Imprimimos en orden todos los datos junto a su indice sumado 1.
    }
    cout << endl << "*********************************************" << endl;
}

void cargarVector(char vec[], int &len, int cant_pos){   //Se carga vector mediante el ingreso por pantalla del usuario.
    cout << "Iniciamos la carga masiva del vector de " << cant_pos << " posiciones." << endl;
    for(int i=0; i<cant_pos ; i++){
        cout << "Ingrese el " << i+1 << "º dato: ";
        cin >> vec[i];
        if(vec[i]=='_'){
            vec[i]=' ';
        }
        len++;
    }
}

void countVocales(char vec[],int len){      //Procedimiento para punto a)
    int count_a = 0;
    int count_e = 0;
    int count_i = 0;
    int count_o = 0;
    int count_u = 0;
    for(int i=0 ; i<len ; i++){
        if(vec[i]=='a' || vec[i]=='A' ){
            count_a++;
        }
        if(vec[i]=='e'|| vec[i]=='E' ){ 
            count_e++;
        }
        if(vec[i]=='i' || vec[i]=='I'){ 
            count_i++;
        }
        if(vec[i]=='o'|| vec[i]=='O'){
            count_o++;
        }
        if(vec[i]=='u'|| vec[i]=='U'){
            count_u++;
        }
    }
    cout << "Cantidad de veces que aparece 'a': " << count_a << endl;
    cout << "Cantidad de veces que aparece 'e': " << count_e << endl;
    cout << "Cantidad de veces que aparece 'i': " << count_i << endl;
    cout << "Cantidad de veces que aparece 'o': " << count_o << endl;
    cout << "Cantidad de veces que aparece 'u': " << count_u << endl;
}

void countPalabras(char vec [],int len){    //Procedimiento para punto b)
    int count_espacios = 1;
    for(int i=0; i<len ; i++){
        if(vec[i]==' '){
            count_espacios++;
        }
    }
    cout << "La cantidad de palabras es de: " << count_espacios << endl;
}

void countLetras(char vec[],int len){       //Procedimiento para punto c)
    int count = 0;
    int maxL = 0;
    for(int i =0; i<len ; i++){
        if(vec[i] != ' ' && vec[i] != '.'){
            count++;
        }
        else{
            count = 0;
        }
        if(maxL < count){
            maxL = count;
        }
    }
    cout << "La cantidad de letras que tiene la palabra mas larga es de : " << maxL << endl;
}

//---------------------------------

//Prueba de funciones

int main(){

    char vec1[max1];
    char vec2[max2];
    int len2=0;
    inicializar(vec1,max1,'C');
    vec1[0] = 'H';
    vec1[1] = 'O';
    vec1[2] = 'L';
    vec1[3] = 'A';
    vec1[4] = ' ';
    vec1[5] = 'C';
    vec1[6] = 'O';
    vec1[7] = 'M';
    vec1[8] = 'O';
    vec1[9] = ' ';
    vec1[10] = 'E';
    vec1[11] = 'S';
    vec1[12] = 'T';
    vec1[13] = 'A';
    vec1[14] = 'S';
    vec1[15] = '?';
    vec1[16] = '.';
    cargarVector(vec2,len2,max2);
    mostrar(vec1,max1);
    countVocales(vec1,max1);
    countPalabras(vec1,max1);
    countLetras(vec1,max1);
    mostrar(vec2,len2);
    countVocales(vec2,len2);
    countPalabras(vec2,len2);
    countLetras(vec2,len2);
    
    return 0;
}
