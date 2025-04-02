#include <iostream>
#include <ostream>
using namespace std;
using uint = unsigned int;

// Ejercicio 1
class Rectangulo {
public:
    Rectangulo(uint alto, uint ancho);
    uint alto();
    uint ancho();
    float area();
    //int operator*(Rectangulo mult); PREGUNTAR SI HACE FALTA
private:
    int alto_;
    int ancho_;
};
Rectangulo::Rectangulo(uint alto, uint ancho) :
        alto_(alto), ancho_(ancho){}

uint Rectangulo::alto() {
    return alto_;
}
uint Rectangulo::ancho() {
    return ancho_;
}
float Rectangulo::area() {
    return alto_ * ancho_;
}
/*int Rectangulo::operator*(Rectangulo mult) {
    return alto_ * ancho_ == mult.alto_ * ancho_;
} PREGUNTAR SI HAY QUE AGREGAR EL MULTIPLICAR*/
const float PI = 3.14;
// Ejercicio 2
class Elipse{
    public:
        Elipse(uint a, uint b);
        uint r_a();
        uint r_b();
        float area();
    private:
        uint r_a_;
        uint r_b_;

};

Elipse::Elipse (uint a, uint b):
        r_a_(a), r_b_(b){}

uint Elipse::r_a(){
    return r_a_;
}
uint Elipse::r_b(){
    return r_b_;
}
float Elipse::area(){
    return r_a_ * r_b_ * PI;
}


// Ejercicio 3
class Cuadrado {
public:
    Cuadrado(uint lado);
    uint lado();
    float area();

private:
    Rectangulo r_;
};

Cuadrado::Cuadrado(uint lado): r_(lado, lado) {}

uint Cuadrado::lado() {
    return r_.alto();
}
float Cuadrado::area() {
    return r_.area();
}

// Ejercicio 4
class Circulo{
public:
    Circulo(float radio);
    float radio();
    float area();

private:
    float radio_;
};

Circulo::Circulo(float radio): radio_(radio){}

float Circulo::radio(){
    return radio_;
}

float Circulo::area(){
    return  radio_ * radio_ * PI;
}

// Ejercicio 5
ostream& operator<<(ostream& os, Rectangulo r) {
    os << "Rect(" << r.alto() << ", " << r.ancho() << ")";
    return os;
}

ostream& operator<<(ostream& os, Elipse e) {
    os << "Elipse(" << e.r_a() << ", " << e.r_b() << ")";
    return os;
}

// Ejercicio 6
ostream& operator<<(ostream& os, Cuadrado q) {
    os << "Cuad(" << q.lado() << ")";
    return os;
}//Agrega el cout al cuadrado

ostream& operator<<(ostream& os, Circulo c) {
    os << "Circ(" << c.radio() << ")";
    return os;
}//Agrega el cout al círculo

