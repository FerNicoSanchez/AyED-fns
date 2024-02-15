/**
 * Ejercicio 31
 * Author: FNS
 * Descripción: El gobierno de la Ciudad de Buenos Aires realiza una encuesta en casas de
*               familia. De cada familia conoce: domicilio, tipo de vivienda (‘C’:casa, ‘D’:departamento), y
*               cantidad de integrantes.
*               De cada integrante de la familia se conoce: inicial y apellido, edad, sexo (‘F’, ‘M’), nivel de
*               estudios alcanzados (‘N’: no posee, ‘P’: primario, ‘S’: secundario, ‘T’: terciario, ‘U’:
*               universitario), y un indicador (‘I’: incompleto, ‘C’: completo) que se refiere al ítem anterior.
*               Los datos finalizan cuando la cantidad de integrantes sea igual a cero.
*               Se pide emitir un listado con los resultados:
*                   a) los datos de los encuestados que hayan completado los estudios primarios
*                   b) el porcentaje de analfabetismo en la ciudad (se considera analfabetos a los mayores de
*                      10 años que no posean estudios)
*                   c) edad promedio de cada familia y de la ciudad
*                   d) cantidad de encuestados en cada tipo de nivel de estudios alcanzados incompletos.
*                   e) porcentaje de encuestados de sexo femenino y masculino.

*/

#include<iostream>

using namespace std;

#define max_fam 4
#define max_integrantes 10

struct familia{
    int dom;
    char tipo;
    int integrantes;
};

struct integrante{
    int dom;
    char inicial;
    int edad;
    char sexo;
    char nivel_academico;
    char estado_estudios;
};

struct Nodo{
    integrante persona;
    Nodo *sgte;
};

//-------------Prototipos----------------

void agregarPrimero(Nodo *&Lista,integrante valor);
void mostrarintegrantes(Nodo*);
void liberar(Nodo*&lista);
Nodo * primarioFinalizado(Nodo * Lista);
void analfabetismo(Nodo * Lista);
void prom_edad(Nodo *Lista);
void countEstudiosI(Nodo * Lista);
void porcentajeSexo(Nodo * Lista);

//-------------Implementación-------------

void agregarPrimero(Nodo *&Lista,integrante valor){
    Nodo * nuevo = new Nodo();
    nuevo->persona = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void mostrarintegrantes(Nodo*lista){
    Nodo * aux = lista;
    if(aux==NULL){
        cout << "No hay integrantes cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << "---------------------------------------------------------" << endl;
        cout << "inicial: " << aux->persona.inicial << endl;
        cout << "Domicilio: " << aux->persona.dom << endl;
        cout << "Edad: " << aux->persona.edad << endl;
        cout << "Sexo: " << aux->persona.sexo << endl;
        cout << "Nivel academico: " << aux->persona.nivel_academico << endl;
        cout << "Estado de últimos estudios: " << aux->persona.estado_estudios << endl;
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

Nodo * primarioFinalizado(Nodo * Lista){        //Función para punto a)
    Nodo * nuevo = NULL;
    while(Lista!=NULL){
        if(Lista->persona.nivel_academico != 'N' && !(Lista->persona.nivel_academico == 'P' && Lista->persona.estado_estudios == 'I')){
            agregarPrimero(nuevo,Lista->persona);
        }
        Lista=Lista->sgte;
    }
    return nuevo;
}

void analfabetismo(Nodo * Lista){               //Procedimiento para punto b)
    int count=0;
    float total=0;

    while(Lista!=NULL){
        if(Lista->persona.edad > 10 && Lista->persona.nivel_academico == 'N'){
            count++;
        }
        total++;
        Lista = Lista->sgte;
    }
    total = (count/total)*100;
    cout << "El porcentaje de analfabetismo es de " << total << "%" << endl;
}

void prom_edad(Nodo *Lista){                    //Procedimiento para punto c)
    int dom_ant = Lista->persona.dom;
    int count = 0;
    int count_global = 0;
    float acum_edad = 0;
    float acum_edad_global = 0; 
    float prom=0;
    while(Lista!=NULL){
        if(dom_ant != Lista->persona.dom){
            prom = acum_edad / count;
            cout << "El prom de edad del dom " << dom_ant << " es: " << prom << endl;
            count=0;
            acum_edad = 0;
        }
        count++;
        count_global++;
        acum_edad += Lista->persona.edad;
        acum_edad_global += Lista->persona.edad;
        dom_ant = Lista->persona.dom;
        Lista = Lista->sgte;
        if(Lista == NULL){
            prom = acum_edad / count;
            cout << "El prom de edad del dom " << dom_ant << " es: " << prom << endl;
        }
    }
    prom = acum_edad_global / count_global; 
    cout << "El prom de edad de la ciudad es de: " << prom << endl;
}

void countEstudiosI(Nodo * Lista){              //Procedimiento para punto d)
    int count_U = 0;
    int count_T = 0;
    int count_S = 0;
    int count_P = 0;
    while(Lista != NULL){
        if ( Lista->persona.estado_estudios == 'I' && Lista->persona.nivel_academico == 'U' ){
            count_U++;
        }
        if ( Lista->persona.estado_estudios == 'I' && Lista->persona.nivel_academico == 'T' ){
            count_T++;
        }
        if ( Lista->persona.estado_estudios == 'I' && Lista->persona.nivel_academico == 'S' ){
            count_S++;
        }
        if ( Lista->persona.estado_estudios == 'I' && Lista->persona.nivel_academico == 'P' ){
            count_P++;
        }
        Lista = Lista->sgte;
    }
    cout << "La cantidad de encuestados con la universidad incompleta es : " << count_U << endl;
    cout << "La cantidad de encuestados con el terciario incompleto es : " << count_T << endl;
    cout << "La cantidad de encuestados con la secundaria incompleta es : " << count_S << endl;
    cout << "La cantidad de encuestados con la primaria incompleta es : " << count_P << endl;
}

void porcentajeSexo(Nodo * Lista){              //Procedimiento para punto e)
    int count_M = 0;
    float count_S = 0;
    float prom = 0;
    while(Lista != NULL){
        if(Lista->persona.sexo == 'F'){
            count_S++;
        }
        else{
            count_M++;
        }
        Lista = Lista->sgte;
    }
    prom = count_S * 100 / (count_M + count_S);
    cout << "El promedio de encuestados que es del sexo femenino es del " << prom << "%" << endl;
    prom = 100 - prom;
    cout << "El promedio de encuestados que es del sexo masculino es del " << prom << "%" << endl;
}

//-------Prueba de funciones---------

int main(){

    Nodo * Lista = NULL;
    familia familias[max_fam];
    integrante integrantes[max_integrantes];

    familias[0].dom = 1;
    familias[0].integrantes = 1;
    familias[0].tipo = 'D';
    familias[1].dom = 2;
    familias[1].integrantes = 2;
    familias[1].tipo = 'D';
    familias[2].dom = 3;
    familias[2].integrantes = 3;
    familias[2].tipo = 'C';
    familias[3].dom = 4;
    familias[3].integrantes = 4;
    familias[3].tipo = 'D';

    integrantes[0].dom = 1;
    integrantes[0].inicial = 'A';
    integrantes[0].edad = 27;
    integrantes[0].sexo = 'M';
    integrantes[0].nivel_academico = 'U';
    integrantes[0].estado_estudios = 'I';
    
    integrantes[1].dom = 2;
    integrantes[1].inicial = 'B';
    integrantes[1].edad = 24;
    integrantes[1].sexo = 'M';
    integrantes[1].nivel_academico = 'T';
    integrantes[1].estado_estudios = 'C';
    
    integrantes[2].dom = 2;
    integrantes[2].inicial = 'C';
    integrantes[2].edad = 23;
    integrantes[2].sexo = 'F';
    integrantes[2].nivel_academico = 'U';
    integrantes[2].estado_estudios = 'I';
    
    integrantes[3].dom = 3;
    integrantes[3].inicial = 'D';
    integrantes[3].edad = 35;
    integrantes[3].sexo = 'F';
    integrantes[3].nivel_academico = 'S';
    integrantes[3].estado_estudios = 'I';
    
    integrantes[4].dom = 3;
    integrantes[4].inicial = 'E';
    integrantes[4].edad = 14;
    integrantes[4].sexo = 'M';
    integrantes[4].nivel_academico = 'N';
    integrantes[4].estado_estudios = 'C';
    
    integrantes[5].dom = 3;
    integrantes[5].inicial = 'F';
    integrantes[5].edad = 9;
    integrantes[5].sexo = 'F';
    integrantes[5].nivel_academico = 'P';
    integrantes[5].estado_estudios = 'I';
    
    integrantes[6].dom = 4;
    integrantes[6].inicial = 'G';
    integrantes[6].edad = 40;
    integrantes[6].sexo = 'F';
    integrantes[6].nivel_academico = 'T';
    integrantes[6].estado_estudios = 'C';
    
    integrantes[7].dom = 4;
    integrantes[7].inicial = 'H';
    integrantes[7].edad = 44;
    integrantes[7].sexo = 'M';
    integrantes[7].nivel_academico = 'T';
    integrantes[7].estado_estudios = 'I';
    
    integrantes[8].dom = 4;
    integrantes[8].inicial = 'I';
    integrantes[8].edad = 21;
    integrantes[8].sexo = 'F';
    integrantes[8].nivel_academico = 'S';
    integrantes[8].estado_estudios = 'C';
    
    integrantes[9].dom = 4;
    integrantes[9].inicial = 'J';
    integrantes[9].edad = 18;
    integrantes[9].sexo = 'F';
    integrantes[9].nivel_academico = 'U';
    integrantes[9].estado_estudios = 'I';
    

    for(int i = 0 ; i<max_integrantes ; i++){
        agregarPrimero(Lista,integrantes[i]);
    }
    // mostrarintegrantes(Lista);
    Nodo * aux = primarioFinalizado(Lista);
    mostrarintegrantes(aux);
    analfabetismo(Lista);
    prom_edad(Lista);
    countEstudiosI(Lista);
    porcentajeSexo(Lista);
    liberar(Lista);
    liberar(aux);

    return 0;
}
