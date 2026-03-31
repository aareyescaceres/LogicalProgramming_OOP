#include "Banco.h"

using namespace std;

Banco::Banco(string nombre, string codigo) {
    this->nombre = new string(nombre);
    codigoBanco = new string(codigo);
    cuentas = new vector<CuentaBancaria*>();
    tarjetasEmitidas = new vector<Tarjeta*>();
}

Banco::~Banco() {
    for (CuentaBancaria* c : *cuentas) delete c;
    for (Tarjeta* t : *tarjetasEmitidas) delete t;
    delete cuentas;
    delete tarjetasEmitidas;
    delete nombre;
    delete codigoBanco;
}

string Banco::getNombre() const { return *nombre; }
string Banco::getCodigo() const { return *codigoBanco; }

CuentaBancaria* Banco::abrirCuentaAhorros(string num, string cci, Persona* cliente, double tasa) {
    if (!cliente->esMayorDeEdad()) return nullptr;
    CuentaBancaria* nueva = new CuentaAhorros(num, cci, cliente, tasa);
    cuentas->push_back(nueva);
    return nueva;
}

CuentaBancaria* Banco::abrirCuentaCorriente(string num, string cci, Persona* cliente, double sobregiro) {
    if (!cliente->esMayorDeEdad()) return nullptr;
    CuentaBancaria* nueva = new CuentaCorriente(num, cci, cliente, sobregiro);
    cuentas->push_back(nueva);
    return nueva;
}

TarjetaDebito* Banco::emitirTarjetaDebito(string num, Fecha vto, int cvv, CuentaBancaria* cta) {
    TarjetaDebito* nueva = new TarjetaDebito(num, vto, cvv, cta);
    tarjetasEmitidas->push_back(nueva);
    return nueva;
}

TarjetaCredito* Banco::emitirTarjetaCredito(string num, Fecha vto, int cvv, CuentaBancaria* cta, double limite) {
    TarjetaCredito* nueva = new TarjetaCredito(num, vto, cvv, cta, limite);
    tarjetasEmitidas->push_back(nueva);
    return nueva;
}

CuentaBancaria* Banco::buscarCuentaPorCCI(string cciBuscado) const {
    for (CuentaBancaria* c : *cuentas) {
        if (c->getCCI() == cciBuscado) return c;
    }
    return nullptr;
}

vector<CuentaBancaria*> Banco::obtenerCuentasCliente(string dniCliente) const {
    vector<CuentaBancaria*> result;
    for (CuentaBancaria* c : *cuentas) {
        if (c->getTitular()->getDni() == dniCliente) result.push_back(c);
    }
    return result;
}

vector<Tarjeta*> Banco::obtenerTarjetasCliente(string dniCliente) const {
    vector<Tarjeta*> result;
    for (Tarjeta* t : *tarjetasEmitidas) {
        if (t->getCuentaBancaria()->getTitular()->getDni() == dniCliente) result.push_back(t);
    }
    return result;
}