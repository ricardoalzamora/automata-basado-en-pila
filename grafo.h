#include "pila.h"
#include "vertice.h"

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

	bool verificarAceptacion(string estadoActual, string lectura, Pila pila, bool esEntrada = true){
		Vertice *verticeActual = esta(estadoActual);
		Relacion *relacionesActuales = verticeActual->getListaRelaciones();

		while(relacionesActuales != NULL){
			Lista *listaReglas = relacionesActuales->getListaReglas();

			while(listaReglas != NULL){

				Pila pilaAuxiliar = pila;
				char caracter, primerCaracter;
				string lecturaAuxiliar;

				if(esEntrada && listaReglas->getExtraePila() != 157){
					pilaAuxiliar.insertar(listaReglas->getExtraePila());
				}
				if(listaReglas->getExtraePila() != 157 && pilaAuxiliar.tamPila() == 0){
					continue;
				}
				if(listaReglas->getExtraePila() != 157){
					caracter = pilaAuxiliar.quitar();
				}else{
					caracter = 157;
				}

				if(lectura.length() == 1 && esta(relacionesActuales->getEstadoRelacionado())->getAceptacion()){
					return true;
				}
				if(listaReglas->getExtraePila() == caracter && (lectura[0] == listaReglas->getLeeCaracter() || listaReglas->getLeeCaracter() == 156)){
				
					if(listaReglas->getIngresaPila() != "λ"){
						for(int i = 0; i < listaReglas->getIngresaPila().length(); i++){
							pilaAuxiliar.insertar(listaReglas->getIngresaPila()[i]);
						}
					}					
					if(lectura.length() == 1 && esta(relacionesActuales->getEstadoRelacionado())->getAceptacion()){
						return true;
					}
					if(listaReglas->getLeeCaracter() == 156){
						lecturaAuxiliar = lectura;
					}else{
						lecturaAuxiliar = lectura.substr(1, lectura.length() - 1);
					}					

					bool aceptado = verificarAceptacion(relacionesActuales->getEstadoRelacionado(), 
					lecturaAuxiliar, pilaAuxiliar, false);
					if(aceptado){
						return true;
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