/**
 * Recuperatorio 1º parcial.
 * Author: FNS
 * Descripción: Ver archivo parcial3_2023.jpeg
*/

#include<iostream>

using namespace std;

#define cant_prov 4
#define cant_registros 6

//--------Estructuras--------------

struct Provincia{
    int cod_prov;
    int cod_seccion;
    int total_ciudadanos;
    int votantes;
};

struct Provincia_T{
    int cod_prov;
    float total_ciudadanos;
    int votantes;
};

//--------Prototipos---------------


void crearArchivo(Provincia reg_prov_carga[],int len);

void mostrarDatosProvincia();

//---Implementación de funciones---


void crearArchivo(Provincia reg_prov_carga[],int len){
    FILE * archivo_prod = fopen("elecciones2023.dat","wb");

    fwrite(reg_prov_carga,sizeof(struct Provincia),len,archivo_prod);
    
    fclose(archivo_prod);
}

void mostrarDatosProvincia(){
    FILE * archivo_lectura = fopen("elecciones2023.dat","rb");
    Provincia reg_aux[cant_registros];
    fread(reg_aux,sizeof(struct Provincia),cant_registros,archivo_lectura);
    int len = cant_registros;
    fclose(archivo_lectura);
    Provincia_T totales[cant_prov];
    float prom_padron[cant_prov];

    for(int i_reg = 0, i_prov = 0 ; i_prov < cant_prov ; i_prov++){
        totales[i_prov].cod_prov = reg_aux[i_reg].cod_prov;
        totales[i_prov].total_ciudadanos = reg_aux[i_reg].total_ciudadanos;
        totales[i_prov].votantes = reg_aux[i_reg].votantes;
        i_reg++;
        while ( totales[i_prov].cod_prov == reg_aux[i_reg].cod_prov ){
            totales[i_prov].total_ciudadanos += reg_aux[i_reg].total_ciudadanos;
            totales[i_prov].votantes = reg_aux[i_reg].votantes;
            i_reg++;
        }
        prom_padron[i_prov] = ( totales[i_prov].votantes / totales[i_prov].total_ciudadanos ) * 100;
    }
    
    cout << endl << "---------- Resultados elecciones ----------" << endl;
    for(int i = 0 ; i < cant_prov ; i++){
        cout << endl << "Provincia: " << totales[i].cod_prov << endl;
        cout << "Total ciudadanos: " << totales[i].total_ciudadanos << endl;
        cout << "Padrón que se presento a votar: " << prom_padron[i] << " %" << endl;
    }
}

//-----Prueba de funciones----

int main(){

    Provincia reg_prov_carga[cant_registros];
    int len = 0;

    //                    Carga de datos de provincias

    reg_prov_carga[0].cod_prov = 1;
    reg_prov_carga[0].cod_seccion = 10;
    reg_prov_carga[0].total_ciudadanos = 1000;
    reg_prov_carga[0].votantes = 10;
    len++;

    reg_prov_carga[1].cod_prov = 1;
    reg_prov_carga[1].cod_seccion = 20;
    reg_prov_carga[1].total_ciudadanos = 1000;
    reg_prov_carga[1].votantes = 157;
    len++;

    reg_prov_carga[2].cod_prov = 2;
    reg_prov_carga[2].cod_seccion = 30;
    reg_prov_carga[2].total_ciudadanos = 1000;
    reg_prov_carga[2].votantes = 500;
    len++;

    reg_prov_carga[3].cod_prov = 3;
    reg_prov_carga[3].cod_seccion = 40;
    reg_prov_carga[3].total_ciudadanos = 100;
    reg_prov_carga[3].votantes = 100;
    len++;

    reg_prov_carga[4].cod_prov = 4;
    reg_prov_carga[4].cod_seccion = 50;
    reg_prov_carga[4].total_ciudadanos = 700;
    reg_prov_carga[4].votantes = 0;
    len++;

    reg_prov_carga[5].cod_prov = 4;
    reg_prov_carga[5].cod_seccion = 60;
    reg_prov_carga[5].total_ciudadanos = 700;
    reg_prov_carga[5].votantes = 500;
    len++;

    // Fin carga de datos de provincias

    crearArchivo(reg_prov_carga,len);
    mostrarDatosProvincia();

    return 0;
}