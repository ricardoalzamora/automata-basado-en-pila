/*
    Author: Ricardo Rafael Alzamora Valle
*/
#include <iostream>
#include <stdlib.h>
#include "grafo.h"



//Código ASCII 157 = "Ø", reemplaza a "λ", para no extraer nada de la pila 
//Código ASCCI 156 = "£", empleado para no leer ningún caracter

Grafo g = Grafo();

bool agregarVertice(){
    int esAceptado;
    bool esAceptadoAuxiliar;
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
            if(esAceptado == 1){
                esAceptadoAuxiliar = true;
            }else{
                esAceptadoAuxiliar = false;
            }
            return g.agregarVertice(new Vertice(nombreEstado, esAceptadoAuxiliar));
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
            cout<<"1.SI"<<endl<<"0.NO"<<endl;
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
        if(!g.agregarReglas(estadoPartida, estadoLlegada, caracterLectura, caracterExtraerPila, ingresarPila)){
            return false;
        }        
    }
    return true;
}

main(){

    int opcion;
    do{
        system("clear");
        cout<<"\t\tMenu."<<endl<<"1.Agregar Nodo."<<endl<<"2.Marcar Nodo de inicio"<<endl
        <<"3.Relacionar."<<endl<<"4.Agregar Reglas."<<endl<<"5.Verificar palabra."<<endl
        <<"6.Mostrar reglas de un estado a otro."
        <<endl<<"7.Mostrar Nodos."<<endl<<"8.Mostrar Relaciones."
        <<endl<<"9.Salir."<<endl<<"Opcion: ";
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
                string nodoEntrada;
                cout<<"Ingresa el nombre del nodo o estado: ";
                cin>>nodoEntrada;
                if(!g.marcarNodoEntrada(nodoEntrada)){
                    cout<<"Ya hay un nodo de entrada o no existe el nodo indicado!";
                    cin.get();
                    cin.get();
                }
                break;
            }

            case 3:{
                system("clear");
                if(!agregarRelacion()){
                    cout<<"No se puede realizar la operacion, intentalo de nuevo!";
                    cin.get();
                    cin.get();
                }                
                break;
            }

            case 4:{
                system("clear");
                if(!agregarRegla()){
                    cout<<"No se puede agregar las reglas, verifica tus datos!";
                    cin.get();
                    cin.get();
                }
                break;
            }
            case 5:{
                system("clear");
                if(g.getNodoEntrada() == ""){
                    cout<<"No ha indicado el nodo o estado de entrada!";
                    cin.get();
                    cin.get();
                    break;
                }
                Pila pila;
                string palabra;
                cout<<"Ingresa la palabra: ";
                cin>>palabra;
                if(g.verificarAceptacion(g.getNodoEntrada(), palabra, pila)){
                    cout<<"Palabra aceptada!";
                }else{
                    cout<<"No se puede aceptar!";
                }
                cin.get();
                cin.get();
                break;
            }
            case 6:{
                system("clear");
                string estadoPartida, estadoLlegada;
                cout<<"Ingresa el estado de partida: ";
                cin>>estadoPartida;
                cout<<"Ingresa el estado de llegada: ";
                cin>>estadoLlegada;
                while(!g.imprimirReglaNodoEspecifico(estadoPartida, estadoLlegada)){
                    cout<<"Verifica los datos ingresados!";                    
                }
                cin.get();
                cin.get();
                break;
            }
            case 7:{
                system("clear");
                g.imprimirVertices();
                cin.get();
                cin.get();
                break;
            }
            case 8:{
                system("clear");
                g.imprimirVerticesWAdy();
                cin.get();
                cin.get();
                break;
            }
        }
    }while(opcion != 9);
}