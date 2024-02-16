/**
 * Ejercicio 39
 * Author: FNS
 * Descripción: Desarrollar un procedimiento tal que dada una hora (HHMMSS) y un tiempo
 *              también en formato HHMMSS devuelva la nueva hora que surge de sumar el tiempo a la hora
 *              inicial, considere también si cambió el día. 
*/

#include<iostream>

using namespace std;

// Prototipo

void sumarHorarios(char inicial[],char adicional[]);

// Implementación

void sumarHorarios(char inicial[],char adicional[]){
    int hh_inicial,mm_inicial,ss_inicial;
    int hh_adicional,mm_adicional,ss_adicional;

    hh_inicial = (inicial[0]-'0') * 10 + (inicial[1] - '0');
    mm_inicial = (inicial[2]-'0') * 10 + (inicial[3] - '0');
    ss_inicial = (inicial[4]-'0') * 10 + (inicial[5] - '0');
    
    hh_adicional = (adicional[0]-'0') * 10 + (adicional[1] - '0');
    mm_adicional = (adicional[2]-'0') * 10 + (adicional[3] - '0');
    ss_adicional = (adicional[4]-'0') * 10 + (adicional[5] - '0');

    ss_adicional = ss_inicial + ss_adicional;
    mm_adicional = mm_inicial + mm_adicional;
    hh_adicional = hh_adicional + hh_inicial;

    if(ss_adicional > 59){
        ss_adicional = ss_adicional - 60;
        mm_adicional++;
    }
    if(mm_adicional > 59){
        mm_adicional = mm_adicional - 60;
        hh_adicional++;
    }
    if(hh_adicional > 23){
        hh_adicional = hh_adicional - 24;
    }

    if(hh_adicional < 10){
        adicional[0] = '0';
        adicional[1] = char(hh_adicional + '0');
    }
    else{
        adicional[0] = char( '0' + (hh_adicional/10));
        adicional[1] = char( '0' + (hh_adicional%10) );
    }
    if(mm_adicional < 10){
        adicional[2] = '0';
        adicional[3] = char(mm_adicional + '0');
    }
    else{
        adicional[2] = char( '0' + (mm_adicional/10));
        adicional[3] = char( '0' + (mm_adicional%10) );
    }
    if(ss_adicional < 10){
        adicional[4] = '0';
        adicional[5] = char(ss_adicional + '0');
    }
    else{
        adicional[4] = char( '0' + (ss_adicional/10));
        adicional[5] = char( '0' + (ss_adicional%10) );
    }
        
    cout << "La hora resultando es: " << adicional[0] << adicional[1] << ":";
    cout << adicional[2] << adicional[3] << ":" << adicional[4] << adicional[5] << endl;
}


int main(){

    char inicial[7];
    char adicional[7];

    cout << "--------- Carga de hora inicial ---------" << endl; 
    cout << "Indique horas en (HH): ";
    cin >> inicial[0];
    cin >> inicial[1];
    cout << "Indique minutos en (MM): ";
    cin >> inicial[2];
    cin >> inicial[3];
    cout << "Indique segundos en (SS): ";
    cin >> inicial[4];
    cin >> inicial[5];
    inicial[6]='\0';
    
    cout << "--------- Carga de hora adicional ---------" << endl; 
    cout << "Indique horas en (HH): ";
    cin >> adicional[0];
    cin >> adicional[1];
    cout << "Indique minutos en (MM): ";
    cin >> adicional[2];
    cin >> adicional[3];
    cout << "Indique segundos en (SS): ";
    cin >> adicional[4];
    cin >> adicional[5];
    adicional[6]='\0';

    sumarHorarios(inicial,adicional);

    return 0;
}