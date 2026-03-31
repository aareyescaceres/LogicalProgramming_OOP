
#ifndef LOGICAPROGRAMACION_TARJETA_H
#define LOGICAPROGRAMACION_TARJETA_H

#include <string>
#include <vector>
#include "Fecha.h"
#include "CuentaBancaria.h"
#include "CompraEnCuotas.h"

using namespace std;

class Tarjeta {
protected:
    string* numeroTarjeta;
    Fecha* fechaVencimiento;
    int* cvv;
    CuentaBancaria* cuentaAsociada;

public:
    Tarjeta(string num, Fecha vto, int cod, CuentaBancaria* cuenta);
    virtual ~Tarjeta();

    virtual void procesarPago(double monto, string descripcion, int cuotas = 1) = 0;

    CuentaBancaria* getCuentaBancaria() const;
    string getNumeroTarjeta() const;
    bool validarDatos(string num, Fecha vtoIngresada, int cod) const;
};

class TarjetaDebito : public Tarjeta {
public:
    TarjetaDebito(string num, Fecha vto, int cod, CuentaBancaria* cuenta);

    void procesarPago(double monto, string descripcion, int cuotas = 1) override;
};

class TarjetaCredito : public Tarjeta {
private:
    double* limiteCredito;
    double* deudaTotal;
    vector<CompraEnCuotas>* comprasActivas;

public:
    TarjetaCredito(string num, Fecha vto, int cod, CuentaBancaria* cuenta, double limite);
    ~TarjetaCredito() override;

    void procesarPago(double monto, string descripcion, int cuotas = 1) override;
    void facturarMes();
    void limpiarComprasPagadas();
    void adelantarPago(double monto);
};

#endif //LOGICAPROGRAMACION_TARJETA_H