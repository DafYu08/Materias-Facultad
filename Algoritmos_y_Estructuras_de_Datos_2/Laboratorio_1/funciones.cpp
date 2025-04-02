#include <vector>
#include <iostream>
#include "algobot.h"

using namespace std;

// Ejercicio 1

vector<int> quitar_repetidos(vector<int> s) {
    set<int> set_a;
    vector<int> res;
    for (int i = 0; i < s.size(); i++) {
        set_a.insert(s[i]);
    }
    for(int x:set_a){
        res.push_back(x);
    }
    return res;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> set_a;
    vector<int> res;
    for (int i = 0; i < s.size(); i++) {
        set_a.insert(s[i]);
    }
    for(int x:set_a){
        res.push_back(x);
    }
    return res;
}
// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    set<int> set_a;
    set<int> set_b;
    bool res = true;
    for (int i = 0; i < a.size(); i++) {
        set_a.insert(a[i]);
    }
    for (int i = 0; i < b.size(); i++) {
        set_b.insert(b[i]);
    }
    for (int x:set_a){
        if(set_b.count(x) == 0){
            res = false;
        }
    }
    for (int y:set_b){
        if(set_a.count(y) == 0){
            res = false;
        }
    }
    return res;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    set<int> set_a;
    set<int> set_b;
    bool res = true;
    for (int i = 0; i < a.size(); i++) {
        set_a.insert(a[i]);
    }
    for (int i = 0; i < b.size(); i++) {
        set_b.insert(b[i]);
    }
    for (int x:set_a){
        if(set_b.count(x) == 0){
            res = false;
        }
    }
    for (int y:set_b){
        if(set_a.count(y) == 0){
            res = false;
        }
    }
    return res;
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int,int> mapita;
    for (int num : s) {
        if(mapita.count(num) == 0){
            mapita[num] = 1;
        }else{
            mapita[num]++;
        }
    }
    return mapita;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    set<int> set_a;
    vector<int> res;
    for (int i = 0; i < s.size(); i++) {
        set_a.insert(s[i]);
    }
    for(int x:set_a){
        res.push_back(x);
    }
    return res;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> res;
    if(a.size() >= b.size()){
        for(int x : b){
            if (a.count(x) == 1){
                res.insert(x);
            };
        }
    }
    else{
        for(int x : a){
            if (b.count(x) == 1){
                res.insert(x);
            }
        }
    }
    return res;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int,set<int>> mapita;
    for (int n : s) {
            mapita[n%10].insert(n);
    }
    return mapita;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> res;
    map<char,char> mapita;
    for(pair<char,char> p: tr){
        mapita[p.first] = p.second;
    }
    for (int i = 0; i < str.size(); ++i) {
        if(mapita.count(str[i]) == 1){
            res.push_back(mapita[str[i]]);
        } else{
            res.push_back(str[i]);
        }
    }
    return res;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    bool res = false;
    set<set<LU>> libretitas;
    for(Mail m: s){
        libretitas.insert(m.libretas());
    }
    vector<LU> listaGrande;
    for (set<LU> l: libretitas) {
        for(LU k: l){
            listaGrande.push_back(k);
        }
    }
    map<LU, int> mapita;
    for (LU lu : listaGrande) {
        if(mapita.count(lu) == 0){
            mapita[lu] = 1;
        }else{
            res = true;
        }
    }
    return res;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>, Mail> res;
    set<set<LU>> grupos;
    for (Mail m : s){
        grupos.insert(m.libretas()); // creamos un conjunto con todos los grupos de la cadena de mails (grupo = cjto de LUs)
    }
    for(set<LU> grupo: grupos){
        for(Mail m: s){
            if (m.libretas() == grupo){
                if(m.adjunto()){
                    res[grupo] = m;
                }
            }
        }
    }
  return res;
}
