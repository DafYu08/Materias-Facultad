#include "Lista.h"
#include <cassert>

Lista::Lista() {
    _primero = nullptr;
    _ultimo = nullptr;
    _size = 0;
}

Lista::Lista(const Lista& l) : Lista() {
    *this = l;
    _size = longitud();

}

Lista::~Lista() {
    if(_primero != nullptr) {
        Nodo *pistolero = _primero;
        while (pistolero->siguiente != nullptr) {
            pistolero = pistolero->siguiente;
            delete pistolero->anterior;

        }
        _primero = nullptr;
        _ultimo = nullptr;
        delete pistolero;
        _size = 0;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    //Primero tengo que destruir los nodos de la lista que me pasan
    if(_primero != nullptr) {
        Nodo *pistolero = _primero;
        while (pistolero->siguiente != nullptr) {
            pistolero = pistolero->siguiente;
            delete pistolero->anterior;

        }
        _primero = nullptr;
        _ultimo = nullptr;
        delete pistolero;
        _size = 0;
    }
    //Ahora ya está vacía. Es el momento de copiar los elementos de aCopiar #Divertido
    for (int i = 0; i < aCopiar.longitud(); ++i) {
        agregarAtras(aCopiar.iesimo(i));
    }



    return *this;
}



void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(longitud()==0){
        _primero = nuevo;
        _ultimo = nuevo;
        nuevo ->anterior = nullptr;
        nuevo ->siguiente = nullptr;
    } else{
        nuevo ->siguiente = _primero;
        _primero->anterior = nuevo;
        _primero = nuevo;
        nuevo ->anterior = nullptr;

    }
    _size++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(longitud()==0){
        _primero = nuevo;
        _ultimo = nuevo;
        nuevo ->anterior = nullptr;
        nuevo ->siguiente = nullptr;
    } else{
        nuevo ->anterior = _ultimo;
        _ultimo->siguiente = nuevo;
        _ultimo = nuevo;
        nuevo ->siguiente = nullptr;
    }
    _size++;
}



void Lista::eliminar(Nat i) {
    Nodo* actual = _primero;
    for (int j = 0; j < i; ++j) {
        actual = actual -> siguiente;
    }
    if(actual -> anterior == nullptr){
        _primero = actual -> siguiente;
    } else{
        (actual -> anterior) -> siguiente = actual ->siguiente;
    }
    if(actual -> siguiente == nullptr){
        _ultimo = actual -> anterior;
    } else{
        (actual -> siguiente) -> anterior = actual ->anterior;
    }
    delete actual;
    _size--;
}

int Lista::longitud() const {
    return _size;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* nuevo = _primero;
    for (int j = 0; j < i; j++) {
        nuevo = nuevo-> siguiente;
    }
    return nuevo-> valor; //Desreferencia el puntero al valor y da el valor
}

int& Lista::iesimo(Nat i) {
    Nodo* nuevo = _primero;
    for (int j = 0; j < i; j++) {
        nuevo = nuevo-> siguiente;
    }
    return (nuevo-> valor); //Desreferencia el puntero al valor y da el valor
}

void Lista::mostrar(ostream& o) {
    // Completar
}
