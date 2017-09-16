using namespace std;
typedef char TipoDato;
const int TAMPILA = 10;

class Pila{
	private:
		int cima;
		TipoDato v[TAMPILA];
	public:
		Pila(){
			cima = -1;
		}
		bool pilaVacia(){
			if(cima == -1){
				return true;
			}else{
				return false;
			}
		}
		bool pilaLlena(){
			return cima == TAMPILA-1;
		}
		void insertar(TipoDato dato){
			if(!pilaLlena()){
				cima++;
				v[cima]=dato;
			}else{
				cout<<"Overflow!";
			}
		}
		TipoDato quitar(){
			TipoDato aux;
			if(!pilaVacia()){
				aux = v[cima];
				cima--;
				return aux;
			}else{
				cout<<"Underflow";
			}
		}
		void imprimir(){
			if(!pilaVacia()){
				for(int i = cima; i >= 0; i--){
					cout<<"["<<v[i]<<"]"<<endl;
				}
			}else{
				cout<<"La pila esta vacia!";
			}
		}
		void limpiar(){
			if(pilaVacia()){
				cout<<"La pila ya estaba vacia!";
			}else{
				cima = -1;
			}
		}
		TipoDato cimaPila(){
			if(!pilaVacia())
			return v[cima];
		}
		int tamPila(){
			return TAMPILA;
		}
		int tamAct(){
			return ++cima;
		}
};

