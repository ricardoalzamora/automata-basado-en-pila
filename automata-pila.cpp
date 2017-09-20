#include <iostream>
#include <stdlib.h>
#include "grafo.h"

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

main(){

    int opcion;
    do{
        system("clear");
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