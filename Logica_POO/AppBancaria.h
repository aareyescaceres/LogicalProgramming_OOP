
#ifndef LOGICAPROGRAMACION_APPBANCARIA_H
#define LOGICAPROGRAMACION_APPBANCARIA_H

#include <string>
#include "Persona.h"
#include "Banco.h"
#include "Tarjeta.h"

using namespace std;

class AppBancaria {
private:
    Persona* usuarioLogueado;
    Banco* bancoConectado;

public:
    AppBancaria(Persona* usr, Banco* banco);

    void mostrarResumen() const;
    void comprar(string numTarjeta, double monto, int cuotas, string desc, Fecha vtoIngresado, int cvvIngresado);
};


#endif //LOGICAPROGRAMACION_APPBANCARIA_H