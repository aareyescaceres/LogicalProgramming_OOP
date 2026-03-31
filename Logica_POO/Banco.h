
#ifndef LOGICAPROGRAMACION_BANCO_H
#define LOGICAPROGRAMACION_BANCO_H

#include <string>
#include <vector>
#include "CuentaBancaria.h"
#include "Tarjeta.h"

using namespace std;

class Banco {
private:
    string* nombre;
    string* codigoBanco;
    vector<CuentaBancaria*>* cuentas;
    vector<Tarjeta*>* tarjetasEmitidas;

public:
    Banco(string nombre, string codigo);
    ~Banco();

    string getNombre() const;
    string getCodigo() const;

    CuentaBancaria* abrirCuentaAhorros(string num, string cci, Persona* cliente, double tasa);
    CuentaBancaria* abrirCuentaCorriente(string num, string cci, Persona* cliente, double sobregiro);

    TarjetaDebito* emitirTarjetaDebito(string num, Fecha vto, int cvv, CuentaBancaria* cta);
    TarjetaCredito* emitirTarjetaCredito(string num, Fecha vto, int cvv, CuentaBancaria* cta, double limite);

    CuentaBancaria* buscarCuentaPorCCI(string cciBuscado) const;
    vector<CuentaBancaria*> obtenerCuentasCliente(string dniCliente) const;
    vector<Tarjeta*> obtenerTarjetasCliente(string dniCliente) const;
};

#endif //LOGICAPROGRAMACION_BANCO_H