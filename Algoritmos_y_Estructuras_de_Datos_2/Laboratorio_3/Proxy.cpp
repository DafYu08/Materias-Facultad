#include "Proxy.h"

Proxy::Proxy(ConexionJugador* conexion) : _conexiones(conexion) {}

void Proxy::enviarMensaje(string msg) {
  _conexiones->enviarMensaje(msg);
}
