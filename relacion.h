#include "lista.h"

class Relacion{
    
        private:		
        string estadoRelacionado;
        Lista *listaReglas;
        Relacion *sig;
    
        public:	
        
        Relacion(){
            listaReglas = NULL;
            sig = NULL;
        }
        
        Relacion(string estadoRelacionado){
            this->estadoRelacionado =  estadoRelacionado;
            listaReglas = NULL;
            sig = NULL;
        }    
    
        string getEstadoRelacionado(){
            return estadoRelacionado;
        }
        
        Lista *getListaReglas(){
            return listaReglas;
        }
        
        Relacion *getSiguiente(){
            return sig;
        }
    
        void setSiguiente(Relacion *sig){
            this->sig = sig;
        }
    
        void agregarRegla(Lista *regla){
            if(listaReglas != NULL){
                regla->setSiguienteRegla(listaReglas);
                listaReglas = regla;
            }else{
                listaReglas = regla;
            }
        }
    };