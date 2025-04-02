#ifndef PROXY2_H
#define PROXY2_H

#include "ConexionJugador.h"
#include <string>

using namespace std;

class Proxy {
public:
    Proxy(ConexionJugador** conexion);
    void enviarMensaje(string msg);

private:
    ConexionJugador** _conexiones;
    Proxy(const Proxy&);
};

#endif
