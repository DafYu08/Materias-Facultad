#ifndef PROXY_H
#define PROXY_H

#include "ConexionJugador.h"
#include <string>
#include <vector>
using namespace std;

class Proxy {
public:
    Proxy(ConexionJugador* conexion);
    void enviarMensaje(string msg);
    Proxy* obtenerProxy(int id);

private:
    ConexionJugador* _conexiones;
    // No puedo copiarlo
    Proxy(const Proxy&);
};

#endif
