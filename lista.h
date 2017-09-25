
class Lista{

private:
    char leeCaracter;
    char extraePila;
    string ingresaPila;
    Lista *siguienteRegla;

public:
    Lista(){
        siguienteRegla = NULL;
    }

    Lista(char leeCaracter, char extraePila, string ingresaPila){
        this->leeCaracter = leeCaracter;
        this->extraePila = extraePila;
        this->ingresaPila = ingresaPila;
        siguienteRegla = NULL;
    }

    char getLeeCaracter(){
        return leeCaracter;
    }

    char getExtraePila(){
        return extraePila;
    }

    string getIngresaPila(){
        return ingresaPila;
    }

    Lista *getSiguienteRegla(){
        return siguienteRegla;
    }

    void setSiguienteRegla(Lista *regla){
        siguienteRegla = regla;
    }

};