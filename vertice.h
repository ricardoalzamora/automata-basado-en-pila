#include "relacion.h"

class Vertice{
    
        private:
            string estado;
            bool aceptacion;
            Relacion *listaRelaciones;
            Vertice *sig;
    
        public:
    
            Vertice(string estado, bool aceptacion){
                this->estado = estado;
                this->aceptacion = aceptacion;
                listaRelaciones = NULL;
                sig = NULL;
            }
    
            string getEstado(){
                return estado;
            }
    
            bool getAceptacion(){
                return aceptacion;
            }
    
            Relacion *getListaRelaciones(){
                return listaRelaciones;
            }
    
            Vertice *getSiguiente(){
                return sig;
            }
    
            void setSiguiente(Vertice *sig){
                this->sig = sig;
            }
    
            Relacion *estaRelacionado(string estado){
                Relacion *listaRelacionesAuxiliar = listaRelaciones;
                while(listaRelacionesAuxiliar != NULL){
                    if(listaRelacionesAuxiliar->getEstadoRelacionado() == estado){
                        return listaRelacionesAuxiliar;
                    }
                    listaRelacionesAuxiliar = listaRelacionesAuxiliar->getSiguiente();
                }
                return NULL;
            }
    
            Relacion *getRelacion(string estado){
                Relacion *listaRelacionesAuxiliar = listaRelaciones;
                while(listaRelacionesAuxiliar != NULL){
                    if(listaRelacionesAuxiliar->getEstadoRelacionado() == estado){
                        return listaRelacionesAuxiliar;
                    }
                    listaRelacionesAuxiliar = listaRelacionesAuxiliar->getSiguiente();
                }
                return NULL;
            }
        
        void agregarRelacion(Relacion *relacion){
            if(listaRelaciones != NULL){
                if(estaRelacionado(relacion->getEstadoRelacionado()) == NULL){
                    relacion->setSiguiente(listaRelaciones);
                    listaRelaciones = relacion;
    
                }
            }else{
                listaRelaciones = relacion;
            }
        }
        
        bool agregarRegla(string estadoLlegada, char caracterLectura, char caracterExtraerPila, string ingresarPila){
            Relacion *relacionAuxiliar = estaRelacionado(estadoLlegada);
            if(relacionAuxiliar != NULL){
                relacionAuxiliar->agregarRegla(new Lista(caracterLectura, caracterExtraerPila, ingresarPila));
                return true;
            }else{
                false;
            }
        }
    
        void imprimirRelacion(){
            Relacion *listaRelacionesAuxiliar = listaRelaciones;
            while(listaRelacionesAuxiliar != NULL){
                cout<<"["<<listaRelacionesAuxiliar->getEstadoRelacionado()<<"]"<<endl;
                listaRelacionesAuxiliar = listaRelacionesAuxiliar->getSiguiente();
            }
        }
        
        void imprimirReglas(string estadoPartida, string estadoLlegada){
            Relacion *relacionAuxiliar = estaRelacionado(estadoLlegada);
            if(relacionAuxiliar != NULL){
                Lista *listaReglasAuxiliar = relacionAuxiliar->getListaReglas();
                while(listaReglasAuxiliar != NULL){
                    cout<<listaReglasAuxiliar->getLeeCaracter()<<"/"<<listaReglasAuxiliar->getExtraePila()<<"/"
                    <<listaReglasAuxiliar->getIngresaPila()<<endl;
                    listaReglasAuxiliar = listaReglasAuxiliar->getSiguienteRegla();
                }
                
            }
        }
    
    };