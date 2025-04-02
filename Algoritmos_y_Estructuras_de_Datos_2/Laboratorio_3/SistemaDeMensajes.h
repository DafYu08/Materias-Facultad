#ifndef SISTEMADEMENSAJES_H
#define SISTEMADEMENSAJES_H

#include "ConexionJugador.h"
#include <string>
#include <vector>

#if EJ == 4 || EJ == 5
#include "Proxy.h"
#elif EJ == 6
#include "Proxy2.h"
#endif

using namespace std;

class SistemaDeMensajes {
  public:
    //Observadores
    bool registrado(int id) const;
    string ipJugador(int id) const;

    //Generadores
    SistemaDeMensajes();
    ~SistemaDeMensajes();
    void registrarJugador(int id, string ip);
    void desregistrarJugador(int id);
    void enviarMensaje(int id, string mensaje);

    //Otras operaciones
    Proxy* obtenerProxy(int id);

  private:
    ConexionJugador* _conexiones[4];
    Proxy* _proxys[4];

};

#endif
