#include <vector>
#include "algobot.h"

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    set<int> conj;
    vector<int> result;
    for(int i = 0; i < s.size(); i++) {
        if(conj.count(s[i]) != 1){
            result.push_back(s[i]);
        }
        conj.insert(s[i]);
    }
    return result;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> conj;
    vector<int> result;
    for(int i = 0; i < s.size(); i++) {
        if(conj.count(s[i]) != 1){
            result.push_back(s[i]);
        }
        conj.insert(s[i]);
    }
    return result;
}

bool estan_todos(vector<int> a, vector<int> b) {
    bool result = true;
    set<int> bolsa;
    for (int n : a) {
        bolsa.insert(n);
    }
    for (int n : b){
        if (bolsa.count(n) != 1){
            result = false;
        }
    }
    return result;
}


// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    return estan_todos(a,b)&& estan_todos(b,a);
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    return estan_todos(a,b)&& estan_todos(b,a);
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int,int> dicc;
    for (int n : s){
        if (dicc.count(n) == 0){
            dicc[n] = 1;
        } else {dicc[n]++;}
    }
    return dicc;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    map<int,int> mapa = contar_apariciones(s);
    vector<int> result;
    for (pair<int,int> p : mapa){
        if(p.second == 1){
            result.push_back(p.first);
        }
    }
    return result;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> result;
    for(int e : a){
        if(b.count(e) == 1){
            result.insert(e);
        }
    }
    return result;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int, set<int>> result;
    set<int> vacio;
    for (int e : s){
        if(result.count(e % 10) == 0){
            result[e % 10] = vacio;
        }
        result[e % 10].insert(e);
    }
    return result;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    map<char,char> dicc;
    vector<char> result;
    for (pair<char,char> p : tr){
        dicc[p.first] = p.second;
    }
    for (char c : str){
        if(dicc.count(c) == 1){
            result.push_back(dicc[c]);
        } else {result.push_back(c);}
    }
    return result;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    bool result = false;
    set<set<LU>> grupos;
    set<LU> lus;
    for (Mail m : s){
        grupos.insert(m.libretas());
    }
    for (set<LU> grupo : grupos){
        for(LU l : grupo){
            if(lus.count(l) == 1){
                result = true;
            } else {lus.insert(l);}
        }
    }
    return result;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
  return map<set<LU>, Mail>();
}
