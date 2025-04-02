
template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
    _size = 0;
}

template <class T> //Esto es para talar un árbol
Conjunto<T>::~Conjunto() {
    removerTodos(_raiz);
    _size = 0;
}

template<class T>
void Conjunto<T>::removerTodos(Nodo* t) {
    if (t != nullptr) {
        removerTodos(t->izq); //corto toda la rama izquierda
        removerTodos(t->der); //corto toda la rama derecha
    }
    delete t;
}


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    if (actual != nullptr){
        int i = 0;
        while(actual -> izq != nullptr || actual -> der != nullptr) {
            if (actual->valor == clave) {
                return true;
            } else if (actual->valor > clave) {
                if (actual -> izq == nullptr){
                    return false;
                } else {
                    actual = (actual->izq);
                }
            } else {
                if (actual -> der == nullptr){
                    return false;
                } else {
                    actual = (actual-> der);
                }
            }
            i++;
        }
        if (actual-> valor == clave){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* elem = new Nodo (clave);
    int i = 0;
    while(true) {
        if (actual == nullptr){
            _raiz = elem;
            _size++;
            break;
        }
        else if (actual->valor == clave){
            break;
        } else if (actual->valor > clave && actual -> izq == nullptr){
            (actual -> izq) = elem;
            _size++;
            break;
        } else if (actual->valor > clave && actual -> izq != nullptr){
            actual = actual -> izq;
        } else if (actual->valor < clave && actual -> der == nullptr){
            (actual -> der) = elem;
            _size++;
            break;
        } else if (actual->valor < clave && actual -> izq != nullptr){
            actual = actual -> der;
        }
      i++;
    }
}



template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* inmediatoInf = nullptr;
    Nodo* anterior = nullptr;

    //Primero pregunto si clave está en el árbol:
    if(pertenece(clave)){

        //Busco el elemento que hay que borrar:
        int i= 0;
        while (actual-> valor != clave){
            if(actual->valor > clave){
                anterior = actual;
                actual = actual -> izq;
            } else if(actual->valor < clave){
                anterior = actual;
                actual = actual -> der;
            }
          i++;
        }

        //Segun la cantidad de hijos, opero de la siguiente manera
        if (actual -> izq != nullptr || actual -> der != nullptr){
            if (anterior -> izq == nullptr){
                actual -> der == nullptr;
                _size--;
            } else if (anterior -> der == nullptr){
                actual -> izq == nullptr;
                _size--;
            }
        }
        else if (actual -> izq != nullptr){
            anterior -> der = actual -> der;
            _size--;
        }
        else if (actual -> der != nullptr){
            anterior -> izq = actual -> izq;
            _size--;
        }
        else{

            //Busco el inmediato inferior
            inmediatoInf = actual -> izq;
            while (inmediatoInf -> der != nullptr){
                inmediatoInf = inmediatoInf -> der;
            }

            //Borro el inmediato inferior;
            int maximoLocal = inmediatoInf -> valor;
                remover(maximoLocal);

            //Cambio el valor del actual por el del inmediato inferior
            actual -> valor = inmediatoInf -> valor;
            _size--;

        }
    }

}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* anterior = nullptr;
    T ultimoPasoDerecha;

    //Busco la clave en el arbol
    while(actual !=nullptr && actual ->valor != clave ){//Mientras la raiz no sea la clave
        anterior= actual;
        if(actual ->valor > clave){ //Está en la rama izquierda
            ultimoPasoDerecha = actual -> valor;
            actual = actual ->izq;
        }else{ //Está en la rama derecha
            actual =actual ->der;
        }
    }

    //Ahora actual es igual a la clave
    if (actual -> der == nullptr){
        return ultimoPasoDerecha;
    } else {

    }


}

template <class T>
const T& Conjunto<T>::minimo() const {
    assert(false);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    assert(false);
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _size;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

