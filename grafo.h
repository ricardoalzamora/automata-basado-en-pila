#include "pila.h"
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

class Grafo{
	private:
		Vertice *vertices;
		string nodoEntrada;

	public:
		Grafo(){
			vertices = NULL;
			nodoEntrada = "";
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

	bool hayNodoEntrada(){
		return !(nodoEntrada == "");
	}

	string getNodoEntrada(){
		return nodoEntrada;
	}
	
	bool marcarNodoEntrada(string nodoEntrada){
		if(this->nodoEntrada == "" && esta(nodoEntrada) != NULL){
			this->nodoEntrada = nodoEntrada;
			return true;
		}
		return false;
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

            if(verticeAuxiliar->estaRelacionado(estadoLlegada) == NULL){
				verticeAuxiliar->agregarRelacion(new Relacion(estadoLlegada));
				return true;
			}
			return false;
		}
		return false;
	}
	
	bool agregarReglas(string estadoPartida, string estadoLlegada, char caracterLectura, char caracterExtraerPila, string ingresarPila){
		Vertice *verticeAuxiliar = esta(estadoPartida);

		if(verticeAuxiliar != NULL && esta(estadoLlegada) != NULL){
			return verticeAuxiliar->agregarRegla(estadoLlegada, caracterLectura, caracterExtraerPila, ingresarPila);
		}
		return false;
	}

	bool verificarAceptaciona(string estadoActual, string lectura, Pila pila, bool esEntrada = true){
		Vertice *verticeActual = esta(estadoActual);
		Relacion *relacionesActuales = verticeActual->getListaRelaciones();

		while(relacionesActuales != NULL){
			Lista *listaReglas = relacionesActuales->getListaReglas();
			while(listaReglas != NULL){

				if(esEntrada){
					if(listaReglas->getLeeCaracter() == lectura[0]){
						for(int i = 0; i < listaReglas->getIngresaPila().length(); i++){
							pila.insertar(listaReglas->getIngresaPila()[i]);
						}
						if(lectura.length() == 1 && esta(relacionesActuales->getEstadoRelacionado())->getAceptacion() == true){
							return true;
						}
						bool aceptado = verificarAceptaciona(relacionesActuales->getEstadoRelacionado(), 
						lectura.substr(1, lectura.length()), pila, false);
						if(aceptado){
							return true;
						}

					}
				}else{
					if(!pila.pilaVacia()){
						char caracter = pila.quitar();						
						if(listaReglas->getLeeCaracter() == lectura[0] && listaReglas->getExtraePila() == caracter){
							for(int i = 0; i < listaReglas->getIngresaPila().length(); i++){
								pila.insertar(listaReglas->getIngresaPila()[i]);
							}
							if(lectura.length() == 1 && esta(relacionesActuales->getEstadoRelacionado())->getAceptacion() == true){
								return true;
							}
							bool aceptado = verificarAceptaciona(relacionesActuales->getEstadoRelacionado(), 
							lectura.substr(1, lectura.length()), pila, false);
							if(aceptado){
								return true;
							}
						}else{
							pila.insertar(caracter);
						}
					}			
				}

				listaReglas = listaReglas->getSiguienteRegla();
			}

			relacionesActuales = relacionesActuales->getSiguiente();
		}

	}

	bool imprimirReglaNodoEspecifico(string estadoPartida, string estadoLlegada){
		Vertice *verticeAuxiliar = esta(estadoPartida);
		if(verticeAuxiliar != NULL && esta(estadoLlegada)){
			verticeAuxiliar->imprimirReglas(estadoPartida, estadoLlegada);
			return true;
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