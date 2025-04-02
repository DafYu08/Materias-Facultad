
template<class Cuadrado>
Cuadrado cuadrado(Cuadrado x){
    return x * x;
}

template<class Contenedor, class Elem>
bool contiene(Contenedor s, Elem c) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}


template<class Contenedor>
bool esPrefijo(Contenedor a, Contenedor b){
    int i = 0;
    while(i < a.size()){
        if (a[i] != b[i]){
            return false;
        }
        i++;
    }
    return true;
}

template<class Contenedor, class Elem>
Elem maximo(Contenedor c){
    Elem max = c[0];
    for (int i = 0; i < c.size(); ++i) {
        if (max < c[i]) {
            max = c[i];
        }
    }
    return max;
}

