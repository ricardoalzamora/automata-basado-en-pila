#include "pila.h"

class Relacion{

	private:		
	string estadoRelacionado;
	Relacion *sig;

	public:	
	
	Relacion(){
		sig = NULL;
    }
    
    Relacion(string estadoRelacionado){
        this->estadoRelacionado =  estadoRelacionado;
		sig = NULL;
	}    

	string getEstadoRelacionado(){
		return estadoRelacionado;
    }
    
	Relacion *getSiguiente(){
		return sig;
	}

	void setSiguiente(Relacion *sig){
		this->sig = sig;
	}

};

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

		bool estaRelacionado(string estado){
        	Relacion *listaRelacionesAuxiliar = listaRelaciones;
        	while(listaRelacionesAuxiliar != NULL){
            	if(listaRelacionesAuxiliar->getEstadoRelacionado() == estado){
            	    return true;
            	}
            	listaRelacionesAuxiliar = listaRelacionesAuxiliar->getSiguiente();
        	}
        	return false;
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
            if(!estaRelacionado(relacion->getEstadoRelacionado())){
                Relacion *listaRelacionesAuxiliar = listaRelaciones;
                while(listaRelaciones->getSiguiente() != NULL){
                    listaRelaciones = listaRelaciones->getSiguiente();
				}
				listaRelaciones->setSiguiente(relacion);
                listaRelaciones = listaRelacionesAuxiliar;

            }
        }else{
            listaRelaciones = relacion;
        }
    }

	void imprimirRelacion(){
        Relacion *listaRelacionesAuxiliar = listaRelaciones;
        while(listaRelacionesAuxiliar != NULL){
            cout<<"["<<listaRelacionesAuxiliar->getEstadoRelacionado()<<"]"<<endl;
            listaRelacionesAuxiliar = listaRelacionesAuxiliar->getSiguiente();
        }
    }

};

class Grafo{
	private:
		Vertice *vertices;

	public:
		Grafo(){
			vertices = NULL;
		}

		Vertice *esta(string estado){
        	Vertice *verticeAuxiliar = vertices;
        	while(verticeAuxiliar != NULL){
            	if(verticeAuxiliar->getEstado() == estado){
            	    return verticeAuxiliar;
            	}
            	verticeAuxiliar = verticeAuxiliar->getSiguiente();
        	}
        	return NULL;
    	}
	
	bool agregarVertice(Vertice *vertice){
        if(vertices != NULL){
            if(esta(vertice->getEstado()) == NULL){
                Vertice *verticeAuxiliar = vertices;
                while(vertices->getSiguiente() != NULL){
                    vertices = vertices->getSiguiente();
				}
				vertices->setSiguiente(vertice);
                vertices = verticeAuxiliar;

            }else{
				return false;
				delete(vertice);
            }
        }else{
            vertices = vertice;
		}
		return true;
    }

	void imprimirVertices(){
        Vertice *verticeAuxiliar = vertices;
        while(verticeAuxiliar != NULL){
            cout<<"["<<verticeAuxiliar->getEstado()<<"]"<<endl;
            verticeAuxiliar = verticeAuxiliar->getSiguiente();
        }
    }

    bool relacionar(string estadoOrigen, string estadoLlegada){
        Vertice *verticeAuxiliar = esta(estadoOrigen);

        if(verticeAuxiliar != NULL && esta(estadoLlegada) != NULL){

            if(!verticeAuxiliar->estaRelacionado(estadoLlegada)){
				verticeAuxiliar->agregarRelacion(new Relacion(estadoLlegada));
				return true;
			}
			return false;
		}
		return false;
    }

        void imprimirVerticesWAdy(){
        	Vertice *verticeAuxiliar = vertices;
        	while(verticeAuxiliar != NULL){
            	cout<<"["<<verticeAuxiliar->getEstado()<<"] relacionado: "<<endl;
            	verticeAuxiliar->imprimirRelacion();
            	cout<<endl;
            	cout<<"------"<<endl;
            	verticeAuxiliar = verticeAuxiliar->getSiguiente();
        	}
    	}

};