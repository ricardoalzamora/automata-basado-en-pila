#include <iostream>
#include <stdlib.h>
#include "grafo.h"


//Código ASCII 157 = "Ø", reemplaza a "λ", para no extraer nada de la pila 
//Código ASCCI 156 = "£", empleado para no leer ningún caracter

Grafo g = Grafo();

bool agregarVertice(){
    int esAceptado;
    string nombreEstado;
    do{
        cout<<"Ingrese el nombre del nodo: ";
        cin>>nombreEstado;
        cout<<"Ingrese 0 si no sera aceptado, 1 para ser aceptado: ";
        cin>>esAceptado;
        if(esAceptado != 0 && esAceptado != 1){
            system("clear");
            cout<<"Intente de nuevo."<<endl;
        }else{
            return g.agregarVertice(new Vertice(nombreEstado, esAceptado));
        }
    }while(esAceptado != 0 && esAceptado != 1);
}

bool agregarRelacion(){
    string estadoPartida, estadoLlegada;
    cout<<"Ingrese el nombre del nodo de partida: ";
    cin>>estadoPartida;
    cout<<"Ingrese el nombre del nodo de llegada: ";
    cin>>estadoLlegada;

    return g.relacionar(estadoPartida, estadoLlegada);
}

bool agregarRegla(){    
    string estadoPartida, estadoLlegada, ingresarPila;
    int numeroReglas, decision;
    char caracterLectura, caracterExtraerPila;

    cout<<"Ingrese el nombre del nodo de partida: ";
    cin>>estadoPartida;
    cout<<"Ingrese el nombre del nodo de llegada: ";
    cin>>estadoLlegada;
    cout<<"Numero de reglas: ";
    cin>>numeroReglas;
    
    for(int i = 0; i < numeroReglas; i++){
        do{
            system("clear");
            cout<<endl<<"1.SI"<<endl<<"0.NO"<<endl;
            cout<<"Se leera primer caracter?: ";
            cin>>decision;
            if(decision == 1){
                cout<<"Caracter de lectura: ";
                cin>>caracterLectura;
            }else{
                if(decision == 0){
                    caracterLectura = 156;
                }else{
                    cout<<"Intente de nuevo!";
                    decision = 3;
                    continue;
                }
            }

            cout<<"Se sacara de la pila?: ";
            cin>>decision;
            if(decision == 1){
                cout<<"Caracter a sacar: ";
                cin>>caracterExtraerPila;
            }else{
                if(decision == 0){
                    caracterExtraerPila = 157;
                }else{
                    cout<<"Intente de nuevo!";
                    decision = 3;
                    continue;
                }
            }

            cout<<"Se ingresara a la pila?: ";
            cin>>decision;
            if(decision == 1){
                cout<<"Ingresa la cadena que se ingresara a la pila: ";
                cin>>ingresarPila;
            }else{
                if(decision == 0){
                    ingresarPila = "λ";
                }else{
                    cout<<"Intente de nuevo!";
                    decision = 3;
                    continue;
                }
            }
        }while(decision == 3);
        
    }
}

main(){

    int opcion;
    do{
        system("clear");
        cout<<(char)157;
        cout<<"\t\tMenu."<<endl<<"1.Agregar Nodo."<<endl<<"2.Relacionar."<<endl<<"3.Mostrar Nodos."<<endl<<"4.Mostrar Relaciones."
        <<endl<<"5.Salir."<<endl<<"Opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:{
                system("clear");
                if(!agregarVertice()){
                    cout<<"Ya esta el vertice!";
                    cin.get();
                    cin.get();
                }                             
                break;
            }
            case 2:{
                system("clear");
                if(!agregarRelacion()){
                    cout<<"No se puede realizar la operacion, intentalo de nuevo!";
                    cin.get();
                    cin.get();
                }                
                break;
            }
            case 3:{
                system("clear");
                g.imprimirVertices();
                cin.get();
                cin.get();
                break;
            }
            case 4:{
                system("clear");
                g.imprimirVerticesWAdy();
                cin.get();
                cin.get();
                break;
            }
        }
    }while(opcion != 5);
}