/**
 * Ejercicio 50
 * Author: FNS
 * Desarrollar:
 *              a) Una función que reciba un número natural de 4 dígitos en formato de HHMM que
 *              corresponde a un tiempo determinado en horas y minutos, retorne ese tiempo en
 *              minutos.
 *              b) Un procedimiento que reciba el costo en pesos de un abono telefónico, la cantidad de
 *              minutos libres que incluye el abono, el cargo en pesos por minuto excedente y la
 *              cantidad de minutos utilizados por un abonado, retorne la cantidad de minutos
 *              excedidos y el monto en pesos a abonar (costo del abono más minutos excedidos por
 *              el costo de minutos excedidos) más el 21% del valor del IVA.
 * 
 *              Desarrolle un algoritmo que resuelva la siguiente situación problemática: Todos los fines de
 *              mes, una empresa de telefonía celular debe confeccionar las facturas con los consumos de
 *              todos sus abonados, que se realizan en tres turnos de trabajo: Mañana, Tarde y Noche.
 *               Para ello se ingresará por teclado la siguiente información de cada celular:
 *              - Número de celular 9 dígitos ( 0 indica cambio de turno)
 *              - Nombre del abonado 20 caracteres
 *              - Dirección del abonado 25 caracteres
 *              - Tiempo utilizado 4 dígitos en formato HHMM
 *              - Tipo de abono (carácter, A, B, C, D o E)
 *               Dependiendo del tipo de abono que se tenga, el usuario tiene cierta cantidad de minutos
 *              libres, por los cuales no abona cargo extra, pero por cada minuto que se exceda debe
 *              abonar una suma extra según la siguiente tabla:
 *              
 *              Plan                            A       B       C       D       E
 *              Costo                           $70     $55     $40     $28     $19
 *              Minutos Libres                  300     200     100     60      40
 *              Cargo por minuto excedente      $0.09   $0.15   $0.21   $0.29   $0.37
 *              
 *              Informar por cada turno de trabajo:
 *               El nombre del abonado que debe abonar la factura más costosa y el monto de ésta.
 *               El nombre y el número de celular de la persona que realizó la mayor cantidad de minutos
 *              excedentes, indicando cuántos fueron.
 *              Al final del día informar:
 *              * El monto total facturado
 *              * En que turno y en que orden dentro del turno apareció el abonado que utilizó la menor cantidad
 *              de minutos en el mes.
 *              Utilice los subprogramas a) y b).

*/

#include<iostream>
#include<stdio.h>

#define max_planes 5

using namespace std;

struct Factura{
    int cel;
    char inicial;
    char dir;
    int tiempo;
    char tipo;
    char turno;
};

struct Plan{
    char tipo;
    int costo;
    int min_libre;
    float excedente;
};

struct Nodo{
    Factura info;
    Nodo * sgte;
};


//-------------Prototipos-------------------

int buscar(Plan vec[], int len, char tipo);
void agregarPrimero(Nodo *&Lista,Factura valor);
void liberar(Nodo*&lista);
int getMin(int num);
void montoXcliente(int costo, int min_libre, float excedente, int utilizados,int &min_exceso, float &deuda);
Nodo * filtrarTurno(Nodo * lista, char turno);
void imprimirAbonados(Nodo * lista,Plan plan[],char turno);
void informeXturno(Nodo * lista,Plan plan[],char turno);
void informeFinal(Nodo * lista, Plan plan[]);


//------Implementación de funciones---------

int buscar(Plan vec[], int len , char tipo){     //Busca un dato y devuelve el indice donde lo encontro.
    int i=0;
    while( i<len && vec[i].tipo != tipo){
        i++;
    }
    if(i==len){
        return -1;
    }
    else{
        return i;
    }
}

void agregarPrimero(Nodo *&Lista,Factura valor){
    Nodo * nuevo = new Nodo();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void liberar(Nodo*&lista){
    Nodo*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

int getMin(int num){                        //Función del punto a)
    int hora_a_min = (num / 100) * 60;
    hora_a_min += (num%100);
    return hora_a_min;
}

void montoXcliente(int costo, int min_libre, float excedente, int utilizados,int &min_exceso, float &deuda){  //Procedimiento del punto b)
    min_exceso = min_libre - utilizados;
    if(min_exceso < 0) { min_exceso *= -1;}     //En el caso de ser negativo lo pasamos a positivo.
    else               { min_exceso = 0;}       //Si le sobran minutos no tiene exceso.
    deuda = costo + (min_exceso * excedente);   //Sumamos el costo y lo correspondiente al exceso de minutos.
    deuda = deuda + deuda*0.21;                 //Le agregamos el 21% de la deuda resultante.
}

Nodo * filtrarTurno(Nodo * lista, char turno){
    Nodo * nuevo = NULL;
    while(lista!=NULL){
        if(lista->info.turno == turno){
            agregarPrimero(nuevo,lista->info);
        }
        lista = lista->sgte;
    }
    return nuevo;
}

void imprimirAbonados(Nodo * lista, Plan plan[],char turno){
    Nodo * aux = filtrarTurno(lista, turno);
    int min_exceso = 0;
    int min_utilizados = 0;
    float deuda = 0;
    int i = 0;
    if(turno == 'M'){
        cout << endl << "TURNO MAÑANA" << endl;
    }
    else if(turno == 'T'){
        cout << endl << "TURNO TARDE" << endl;
    }
    else{
        cout << endl << "TURNO NOCHE" << endl;
    }
    cout << "Nombre del Abonado" << "      Dirección" << "      Minutos Libres";
    cout << "      Minutos Excedidos" << "      Monto Total a Abonar" << endl;
    while(aux != NULL){
        i = buscar(plan,max_planes,aux->info.tipo);
        min_utilizados = getMin(aux->info.tiempo);
        montoXcliente(plan[i].costo,plan[i].min_libre,plan[i].excedente,min_utilizados,min_exceso,deuda);
        cout << "       " << aux->info.inicial << "                 " << aux->info.dir << "                  ";
        cout << plan[i].min_libre <<  "                  " << min_exceso << "                       ";
        cout << "$ " << deuda << endl;
        aux = aux->sgte;
    }
}

void informeXturno(Nodo * lista,Plan plan[],char turno){
    Nodo * aux_monto = NULL;
    Nodo * aux_min = NULL;
    lista = filtrarTurno(lista,turno);
    float deuda_max = 0;
    float deuda = 0;
    int min_utilizados = 0;
    int min_excedente = 0;
    int min_excedentes_max = 0;
    int i_plan = 0;
    while(lista != NULL){
        i_plan = buscar(plan,max_planes,lista->info.tipo);
        min_utilizados = getMin(lista->info.tiempo);
        montoXcliente(plan[i_plan].costo,plan[i_plan].min_libre,plan[i_plan].excedente,min_utilizados,min_excedente,deuda);
        if(deuda > deuda_max){
            aux_monto = lista;
            deuda_max = deuda;
        }
        if(min_excedente > min_excedentes_max){
            aux_min = lista;
            min_excedentes_max = min_excedente;
        }
        lista = lista->sgte;
    }
    cout << endl << aux_monto->info.inicial;
    cout << "  es quien debe abonar la factura mas costosa correspondiente a  ";
    cout << "$ " << deuda_max << endl ;
    cout << "El abonado " << aux_min->info.inicial << " de celular: " << aux_min->info.cel;
    cout << " realizo la mayor cantidad de min excedentes, correspondientes a ";
    cout << min_excedentes_max << " minutos" << endl;
    
}

void informeFinal(Nodo * lista, Plan plan[]){
    Nodo * lista_turno = filtrarTurno(lista,'M');
    float deuda_total = 0;
    float deuda = 0;
    int exceso = 0;
    int min_utilizados = getMin(lista_turno->info.tiempo);
    int i = 0;
    int orden = 0;
    int orden_menor = 0;
    int menor_minU = min_utilizados;
    int turnos = 0;
    Nodo * aux = NULL;
    while(turnos < 3){
        i = buscar(plan,max_planes,lista_turno->info.tipo);
        min_utilizados = getMin(lista_turno->info.tiempo);
        montoXcliente(plan[i].costo,plan[i].min_libre,plan[i].excedente,min_utilizados,exceso,deuda);
        deuda_total += deuda;
        if(min_utilizados < menor_minU){
            orden_menor = orden;
            menor_minU = min_utilizados;
            aux = lista_turno;
        }
        orden++;
        lista_turno = lista_turno->sgte;
        if(lista_turno == NULL && turnos == 0){
            turnos++;
            lista_turno = filtrarTurno(lista,'T');
        }
        if(lista_turno == NULL && turnos == 1){
            turnos++;
            lista_turno = filtrarTurno(lista,'N');
        }
        if(lista_turno == NULL && turnos == 2){
            turnos++;
        }
    }
    cout << endl << "El monto total facturado es de $ " << deuda_total << endl;
    cout << "Del turno " << aux->info.turno << " de orden " << orden_menor+1;
    cout << "º tenemos al abonado que menos minutos utilizo, siendo estos  " << menor_minU << endl;
}

//--------Prueba de funciones---------------

int main(){

    FILE *archivo_facturas = fopen("facturas.dat","rb");
    Factura reg_factura;
    Nodo * lista = NULL;
    Plan plan[max_planes];

    plan[0].tipo = 'A';
    plan[0].costo = 70;
    plan[0].min_libre = 300;
    plan[0].excedente = 0.09;

    plan[1].tipo = 'B';
    plan[1].costo = 55;
    plan[1].min_libre = 200;
    plan[1].excedente = 0.15;

    plan[2].tipo = 'C';
    plan[2].costo = 40;
    plan[2].min_libre = 100;
    plan[2].excedente = 0.21;

    plan[3].tipo = 'D';
    plan[3].costo = 28;
    plan[3].min_libre = 60;
    plan[3].excedente = 0.29;

    plan[4].tipo = 'E';
    plan[4].costo = 19;
    plan[4].min_libre = 40;
    plan[4].excedente = 0.37;

    if(archivo_facturas != nullptr){
        fread(&reg_factura,sizeof(struct Factura),1,archivo_facturas);
        while(!feof(archivo_facturas)){
            agregarPrimero(lista,reg_factura);
            fread(&reg_factura,sizeof(struct Factura),1,archivo_facturas);
        }
    }
    else{
        cout << "Error al leer el archivo" << endl;
    }
    fclose(archivo_facturas);

    imprimirAbonados(lista,plan,'M');
    informeXturno(lista,plan,'M');
    imprimirAbonados(lista,plan,'T');
    informeXturno(lista,plan,'T');
    imprimirAbonados(lista,plan,'N');
    informeXturno(lista,plan,'N');
    informeFinal(lista,plan);

    liberar(lista);
    return 0;
}
