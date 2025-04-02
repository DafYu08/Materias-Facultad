#include <iostream>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
            // ene, feb, mar, abr, may, jun
            31, 28, 31, 30, 31, 30,
            // jul, ago, sep, oct, nov, dic
            31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

using Mes = int;
using Dia = int;

class Fecha{
public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    void incrementar_dia();
#if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
#endif
private:
    int mes_;
    int dia_;
};


Fecha::Fecha(int mes, int dia): mes_(mes), dia_(dia){};

int Fecha::mes(){
    return mes_;
}

int Fecha::dia(){
    return dia_;
}
#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia() and
                    this ->mes() == o.mes();
    return igual_dia;
}
#endif

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/"<< f.mes();
    return os;
}
void Fecha::incrementar_dia(){
    if(dias_en_mes(mes_) == dia_){
        dia_ = 1;
        mes_++;
    } else{
        dia_++;
    }
};

class Horario{
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator<(Horario h);
private:
    uint hora_;
    uint min_;
};

Horario::Horario(uint hora, uint min): hora_(hora), min_(min){}

uint Horario::hora(){
    return hora_;
}
uint Horario::min(){
    return min_;
}
/*
bool Horario::operator==(Horario h) {
    bool igual_hora = this->hora() == h.hora() and
                     this ->min() == h.min();
    return igual_hora;
}
*/
ostream& operator<<(ostream& os, Horario h) {
    os << h.hora() << ":"<< h.min();
    return os;}

bool Horario::operator<(Horario h) {
    bool res = true;
    if(h.hora() < hora()){
        res = false;
    } else if (hora() == h.hora()){
        if(h.min() < min()){
            res = false;
        }
    }

    return res;
}

using rec = string;
class Recordatorio{
public:
    Recordatorio(Fecha f, Horario h, string r);
    string mensajito();
    Fecha f();
    Horario h();
    bool operator<(Recordatorio r);
private:
    string rec_;
    Horario h_;
    Fecha f_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, string mensajito): rec_(mensajito), h_(h),f_(f){}

Fecha Recordatorio:: f(){
    return f_;
}
Horario Recordatorio:: h(){
    return h_;
}
rec Recordatorio::mensajito() {
    return rec_;
}
ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.mensajito() << " @ "<< r.f() << " " << r.h();
    return os;}

bool Recordatorio::operator<(Recordatorio r){
    bool res = true;
    if( r.h() < h_){
        res = false;
    }
    return res;
}

#include <list>
// Ejercicio 14
class Agenda {
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();
private:
    Fecha fecha_;
    list<Recordatorio> recordatorios_;
};

Agenda::Agenda(Fecha fecha_inicial): fecha_(fecha_inicial){}

void Agenda:: incrementar_dia() {
    fecha_.incrementar_dia();
}

void Agenda:: agregar_recordatorio(Recordatorio r){
    recordatorios_.push_back(r);
}

list<Recordatorio> Agenda::recordatorios_de_hoy(){
    list<Recordatorio> listuch;
    for (Recordatorio r: recordatorios_) {
        if (r.f() == fecha_){
            listuch.push_back(r);
        }
    }
    listuch.sort();
    return listuch;
}


Fecha Agenda::hoy(){
    return fecha_;
}

ostream& operator<<(ostream& os, Agenda a) {
    os << a.hoy() << endl << "=====" << endl;
    for(Recordatorio r : a.recordatorios_de_hoy()){
        os << r << endl;
    }
    return os;
}
