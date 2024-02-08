#include<iostream>

using namespace std;

//Una pila sirve para invertir el orden de una serie de datos, solo puede agregar y sacar.
//Una cola sirve para mantener el orden de una serie de datos, solo puede agregar y sacar.

//**************Estructuras**********************************
struct Datos{
    char inicial;
    int dni;
    int edad;
};
struct Nodo{
    Datos info;
    Nodo * sgte;
};
//************************************************************

//**********Prototipo de funciones****************************

void push(Nodo*&pila,Datos persona);
Datos pop(Nodo*&pila);
void agregar(Nodo*&cfte,Nodo*&cfin,Datos persona);
Datos suprimir(Nodo*&cfte,Nodo*&cfin);

//************************************************************

//************Implementación de funciones*********************

void push(Nodo*&pila,Datos persona){
    Nodo*nuevo = new Nodo();    //Pedimos memoria.
    nuevo->info = persona;      //Cargamos datos.
    nuevo->sgte = pila;         //Conectamos la pila al nuevo dato.
    pila = nuevo;               //La pila comienza con este nuevo dato.
}

Datos pop(Nodo*&pila){
    Nodo * aux = pila;          //Pedimos memoria.
    Datos ret = pila->info;     //Guardamos los datos del nodo a eliminar.
    pila=pila->sgte;            //Avanzamos el puntero de la pila.
    delete(aux);                //Eliminamos el nodo.
    return ret;                 //Devolvemos el valor del nodo eliminado.
}

void agregar(Nodo*&cfte,Nodo*&cfin,Datos persona){
    Nodo* nuevo = new Nodo();   //Pedimos memoria.
    nuevo->info = persona;      //Cargamos datos.
    nuevo->sgte = NULL;         //Inicializamos puntero.(siempre queda a Null ya que siempre será el último dato de la cola)
    if(cfte == NULL){           //Si la cola esta vacia el puntero al frente sera el nuevo dato ingresado.
        cfte=nuevo;
    }
    else{                       //Si la cola tenia datos:
        cfin->sgte=nuevo;       //El puntero sgte del último dato siempre debe apuntar a NULL.
    }
    cfin = nuevo;               //El puntero al final apunta al nuevo dato ingresado.
}//Fin función agregar.

Datos suprimir(Nodo * & cfte, Nodo * & cfin){
    Datos ret = cfte->info;  //Guardamos los datos del primer nodo.
    Nodo* aux = cfte;       //Inicializamos nodo auxiliar cargado con el nodo del primer dato.
    cfte=cfte->sgte;        //Aumentamos a lo que apunta el inicio de la cola.
    if(cfte==NULL){         //Si es Nulo significa que estaba vacia o bien era el último dato.
        cfin = NULL;        //En ambos casos el final debe apuntar a NULL,
    }
    delete(aux);            //Liberamos la memoria.
    return ret;             //Retornamos el dato eliminado.
}//Fin función suprimir.

//************************************************************


//*************Main**********************

int main()
{
    Nodo*pila= new Nodo();
    Nodo*cfte=NULL;
    Nodo*cfin=NULL;
    Datos persona1,persona2,persona3,persona_eliminada1,persona_eliminada2;
    persona1.inicial = 'F';
    persona1.dni = 40394493;
    persona1.edad = 26;

    persona2.inicial = 'N';
    persona2.dni = 12345678;
    persona2.edad = 27;

    persona3.inicial = 'S';
    persona3.dni = 88888888;
    persona3.edad = 27;
    
    push(pila,persona1);
    push(pila,persona2);

    cout << "----------Prueba de pilas--------" << endl;
    persona_eliminada1 = pop(pila);
    cout << "Persona eliminada de la pila: " << persona_eliminada1.inicial << endl;
    persona_eliminada1 = pop(pila);
    cout << "Persona eliminada de la pila: " << persona_eliminada1.inicial << endl;

    cout << "----------Prueba de colas--------" << endl;

    agregar(cfte,cfin,persona1);
    agregar(cfte,cfin,persona1);
    agregar(cfte,cfin,persona2);
    agregar(cfte,cfin,persona3);

    persona_eliminada2 = suprimir(cfte,cfin);
    cout << "Persona eliminada de la cola: " << persona_eliminada2.inicial << endl;
    persona_eliminada2 = suprimir(cfte,cfin);
    cout << "Persona eliminada de la cola: " << persona_eliminada2.inicial << endl;
    persona_eliminada2 = suprimir(cfte,cfin);
    cout << "Persona eliminada de la cola: " << persona_eliminada2.inicial << endl;
    persona_eliminada2 = suprimir(cfte,cfin);
    cout << "Persona eliminada de la cola: " << persona_eliminada2.inicial << endl;

}