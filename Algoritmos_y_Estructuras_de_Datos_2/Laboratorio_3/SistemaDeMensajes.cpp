#include "SistemaDeMensajes.h"

SistemaDeMensajes::SistemaDeMensajes(): _conexiones(), _proxys(){
    for (int i = 0; i < 4; ++i) {
        _conexiones[i] = nullptr;
        _proxys[i] = nullptr;
    }
}

SistemaDeMensajes::~SistemaDeMensajes(){
    for (int i = 0; i < 4; ++i) {
        delete _conexiones[i];
        delete _proxys[i];
    }
}

void SistemaDeMensajes::registrarJugador(int id, string ip){
    if(registrado(id) == true) {
        *_conexiones[id] = ConexionJugador(ip);
    } else {
        _conexiones[id] = new ConexionJugador(ip);
    }
}
void SistemaDeMensajes::enviarMensaje(int id, string mensaje){
    if(registrado(id) == true) {
        (*_conexiones[id]).enviarMensaje(mensaje);

    }
}
bool SistemaDeMensajes::registrado(int id) const{
    return (_conexiones[id] != nullptr);
}
string SistemaDeMensajes::ipJugador(int id) const {
    if (registrado(id) == true) {
        return (*_conexiones[id]).ip();
    }
}
void SistemaDeMensajes::desregistrarJugador(int id){
    delete _conexiones[id];
    _conexiones[id] = nullptr;
}

Proxy* SistemaDeMensajes::obtenerProxy(int id){
    if(_proxys[id] == nullptr) {
        _proxys[id] = new Proxy(&_conexiones[id]);
    }
    return _proxys[id];
}

