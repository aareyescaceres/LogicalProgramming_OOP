
#ifndef LOGICAPROGRAMACION_CUENTABANCARIA_H
#define LOGICAPROGRAMACION_CUENTABANCARIA_H

#include <string>
#include "Persona.h"

using namespace std;

class CuentaBancaria {
protected:
    string* numeroCuenta;
    string* cci;
    double* saldo;
    Persona* titular;

public:
    CuentaBancaria(string num, string codigoCci, Persona* persona, double saldoInicial = 0.0);
    virtual ~CuentaBancaria();

    string getNumeroCuenta() const;
    string getCCI() const;
    double getSaldo() const;
    Persona* getTitular() const;

    virtual void depositar(double monto);
    virtual bool retirar(double monto) = 0;
    virtual void mostrarDetalles() const;
};

class CuentaAhorros : public CuentaBancaria {
private:
    double* tasaInteres;

public:
    CuentaAhorros(string num, string codigoCci, Persona* t, double tasa);
    ~CuentaAhorros() override;

    bool retirar(double monto) override;
    void mostrarDetalles() const override;
};

class CuentaCorriente : public CuentaBancaria {
private:
    double* limiteSobregiro;
    double* sobregiroUsado;

public:
    CuentaCorriente(string num, string codigoCci, Persona* t, double sobregiro);
    ~CuentaCorriente() override;

    void depositar(double monto) override;
    bool retirar(double monto) override;
    void mostrarDetalles() const override;
};

#endif //LOGICAPROGRAMACION_CUENTABANCARIA_H