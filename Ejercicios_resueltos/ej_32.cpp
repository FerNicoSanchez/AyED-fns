/**
 * Ejercicio 32
 * Author: FNS
 * Descripción: Una compañía aérea desea emitir un listado con los movimientos mensuales de
*               sus M vuelos al exterior. Para ello cuenta con la siguiente información. De cada vuelo
*               realizado el número de vuelo, destino, y cantidad de asientos. De cada pasajero el número de
*               pasaporte y el importe que abonó por el pasaje en dólares.
*               La información finaliza con un número de pasaporte igual a cero. Se pide emitir el siguiente
*               listado:
*                        Nro. de Vuelo 9999 Destino: xxxxxxxxxxxxxxxxx
*                        Nro. de Pasaporte          Importe en u$s
*                           99999999                    999.99
*                           99999999                    999.99
*                        Total recaudado del vuelo: 99999.99
*                        % de Asientos Libres del vuelo 999.99
*                        % de Asientos Ocupados del vuelo 999.99
*                        Total recaudado en el mes 999999.99
*                        Cantidad de veces seguidas que se dieron vuelos completos 99
*                        El número de vuelo que más recaudó 9999

*  Nota: Para poder ejecutar este codigo es necesaria la previa ejecucion del codigo "creacion_archivo_ej32.cpp"
*        Una vez ejecutado el otro codigo ya se puede utilizar sin problemas este codigo.
*/

#include<iostream>
#include<stdio.h>

using namespace std;

struct Vuelo{
    int id_vuelo;
    char destino;
    int cant_asientos;
};

struct Pasajero{
    int id_vuelo;
    int pasaporte;
    int monto;
};

struct Nodo_V{
    Vuelo info;
    Nodo_V * sgte;
};

struct Nodo_P{
    Pasajero info;
    Nodo_P * sgte;
};

//----------------Prototipos--------------------------

void agregarPasajero(Nodo_P *&Lista,Pasajero valor);
void agregarVuelo(Nodo_V *&Lista,Vuelo valor);
Nodo_V * buscarVuelo(Nodo_V * Lista, int id_vuelo);
void liberarP(Nodo_P*&lista);
void liberarV(Nodo_V*&lista);
void mostrarPasajeros(Nodo_P*Lista);
int recaudadoXvuelo(Nodo_P*Lista,int id_vuelo);
int montoMayorVuelo(Nodo_V * Lista_v,Nodo_P * Lista_p);
float porcentajeAsientosOcupados(Nodo_P*Lista,int id_vuelo,int asientosVuelo);
void imprimirPasajeros(Nodo_P * Lista, int id_vuelo);
void reporte(Nodo_V * Lista_v,Nodo_P * Lista_p);
int recaudadoXmes(Nodo_V *Lista_v,Nodo_P * Lista_p);
int vuelosCompletos(Nodo_V *Lista_v, Nodo_P * Lista_p);

//---------Implementación de funciones----------------

void agregarPasajero(Nodo_P *&Lista,Pasajero valor){
    Nodo_P * nuevo = new Nodo_P();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

void agregarVuelo(Nodo_V *&Lista,Vuelo valor){
    Nodo_V * nuevo = new Nodo_V();
    nuevo->info = valor;
    nuevo->sgte = Lista;
    Lista = nuevo;
}

Nodo_V * buscarVuelo(Nodo_V * Lista, int id_vuelo){
    Nodo_V * aux=Lista;
    while( aux!=NULL && aux->info.id_vuelo != id_vuelo){
        aux=aux->sgte;
    }
    return aux;
}

void mostrarPasajeros(Nodo_P*lista){
    Nodo_P * aux = lista;
    if(aux==NULL){
        cout << "No hay alumnos cargados en la lista." << endl;
    }
    while(aux!=NULL){
        cout << "El pasaporte : " << aux->info.pasaporte << " del vuelo: " << aux->info.id_vuelo << " de monto " << aux->info.monto << endl;
        aux = aux->sgte;
    }
}

void liberarP(Nodo_P*&lista){
    Nodo_P*aux=NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

void liberarV(Nodo_V*&lista){
    Nodo_V * aux = NULL;
    while(lista!=NULL){
        aux=lista;
        lista=lista->sgte;
        delete(aux);
    }
}

int recaudadoXvuelo(Nodo_P*Lista , int id_vuelo){
    int monto_total = 0;
    while (Lista != NULL){
        if(Lista->info.id_vuelo == id_vuelo){
            monto_total += Lista->info.monto;
        }
        Lista = Lista->sgte;
    }
    return monto_total;
}

int montoMayorVuelo(Nodo_V * Lista_v, Nodo_P * Lista_p){
    int recaudado = 0;
    int recaudado_max = 0;
    while(Lista_v!=NULL){
        recaudado = recaudadoXvuelo(Lista_p,Lista_v->info.id_vuelo);
        if(recaudado > recaudado_max){
            recaudado_max = recaudado;
        }
        Lista_v = Lista_v->sgte;
    }
    return recaudado_max;
}

float porcentajeAsientosOcupados(Nodo_P*Lista,int id_vuelo,int asientosVuelo){
    float count = 0;
    while(Lista!=NULL){
        if(Lista->info.id_vuelo == id_vuelo){
            count++;
        }
        Lista = Lista->sgte;
    }
    count = count*100/asientosVuelo;
    return count;
}

void imprimirPasajeros(Nodo_P * Lista, int id_vuelo){
    cout << endl << "Nro de Pasaporte      Importe en U$s" << endl;
    while(Lista!=NULL){
        if(Lista->info.id_vuelo == id_vuelo){
            cout << Lista->info.pasaporte << "                     " << Lista->info.monto << endl;
        }
        Lista = Lista->sgte;
    }
}

int recaudadoXmes(Nodo_V *Lista_v, Nodo_P * Lista_p){
    int acum_recaudado = 0;
    while(Lista_v!=NULL){
        acum_recaudado += recaudadoXvuelo(Lista_p,Lista_v->info.id_vuelo);
        Lista_v=Lista_v->sgte;
    }
    return acum_recaudado;
}

int vuelosCompletos(Nodo_V *Lista_v, Nodo_P * Lista_p){
    int vuelos_completos = 0;
    int max_vuelosC_seguidos = 0;
    bool dispo_ant = false;
    float dispo_asientos = 0;
    while(Lista_v!=NULL){
        dispo_asientos = porcentajeAsientosOcupados(Lista_p,Lista_v->info.id_vuelo,Lista_v->info.cant_asientos);
        if(dispo_asientos == 100){
            if(dispo_ant){
                vuelos_completos++;
            }
            dispo_ant = true;
        }
        else{
            vuelos_completos = 0;
            dispo_ant = false;
        }
        if(vuelos_completos > max_vuelosC_seguidos){
            max_vuelosC_seguidos = vuelos_completos;
        }
        Lista_v = Lista_v->sgte;
    }
    return max_vuelosC_seguidos > 0 ? max_vuelosC_seguidos+1:0;
}

void reporte(Nodo_V * Lista_v,Nodo_P * Lista_p){
    float dispo_asientos = 0;
    int recaudado = 0;
    int recaudado_total = recaudadoXmes(Lista_v,Lista_p);
    int vuelos_completos = vuelosCompletos(Lista_v,Lista_p);
    int recaudado_max = montoMayorVuelo(Lista_v,Lista_p);

    while(Lista_v != NULL){
        cout << "--------------------------------------------------" << endl;
        cout << "Nro de vuelo: " << Lista_v->info.id_vuelo << "        Destino: " << Lista_v->info.destino << endl;
        imprimirPasajeros(Lista_p,Lista_v->info.id_vuelo);
        recaudado = recaudadoXvuelo(Lista_p,Lista_v->info.id_vuelo);
        cout << "Total recaudado del vuelo: " << recaudado << endl;
        dispo_asientos = porcentajeAsientosOcupados(Lista_p,Lista_v->info.id_vuelo,Lista_v->info.cant_asientos);
        cout << "'%' de asientos libres del vuelo : " << 100-dispo_asientos << endl;
        cout << "'%' de asientos ocupados del vuelo: " << dispo_asientos << endl;
        cout << endl << "Total recaudado en el mes: " << recaudado_total << endl;
        cout << "Cantidad de veces seguidas que se dieron vuelos completos: " << vuelos_completos << endl;
        cout << "El número de vuelo que mas recaudo: " << recaudado_max << endl;
        Lista_v = Lista_v->sgte;
    }

}

//---------------------------------

int main(){
    
    FILE * archivo_vuelos = fopen("vuelos.dat","rb");
    FILE * archivo_pasajeros = fopen("pasajeros.dat","rb");
    Vuelo reg_vuelo;
    Pasajero reg_pasajero;
    Nodo_P * lista_pasajeros=NULL;
    Nodo_V * lista_vuelos=NULL;
    
    reg_vuelo.id_vuelo = 77;
    reg_vuelo.destino = 'S';
    reg_vuelo.cant_asientos = 1;
    agregarVuelo(lista_vuelos,reg_vuelo);
    reg_pasajero.id_vuelo = 77;
    reg_pasajero.monto = 320000;
    reg_pasajero.pasaporte = 77;
    agregarPasajero(lista_pasajeros,reg_pasajero);
    reg_vuelo.id_vuelo = 777;
    reg_vuelo.destino = 'Z';
    reg_vuelo.cant_asientos = 1;
    agregarVuelo(lista_vuelos,reg_vuelo);
    reg_pasajero.id_vuelo = 777;
    reg_pasajero.monto = 100;
    reg_pasajero.pasaporte = 777;
    agregarPasajero(lista_pasajeros,reg_pasajero);


    fread(&reg_vuelo,sizeof(struct Vuelo),1,archivo_vuelos);
    while ( !feof(archivo_vuelos) ){
        agregarVuelo(lista_vuelos,reg_vuelo);
        fread(&reg_vuelo,sizeof(struct Vuelo),1,archivo_vuelos);
    }

    fread(&reg_pasajero,sizeof(struct Pasajero),1,archivo_pasajeros);
    while( !feof(archivo_pasajeros)){
        agregarPasajero(lista_pasajeros,reg_pasajero);
        fread(&reg_pasajero,sizeof(struct Pasajero),1,archivo_pasajeros);
    }

    mostrarPasajeros(lista_pasajeros);
    reporte(lista_vuelos,lista_pasajeros);
    liberarP(lista_pasajeros);
    liberarV(lista_vuelos);
    fclose(archivo_vuelos);
    fclose(archivo_pasajeros);
    
    
    return 0;
}
