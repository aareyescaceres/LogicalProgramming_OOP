#include "Tarjeta.h"
#include <iostream>
#include <iomanip>

using namespace std;

Tarjeta::Tarjeta(string num, Fecha vto, int cod, CuentaBancaria* cuenta) {
    numeroTarjeta = new string(num);
    fechaVencimiento = new Fecha(vto);
    cvv = new int(cod);
    cuentaAsociada = cuenta;
}

Tarjeta::~Tarjeta() {
    delete numeroTarjeta;
    delete fechaVencimiento;
    delete cvv;
}

CuentaBancaria* Tarjeta::getCuentaBancaria() const { return cuentaAsociada; }

string Tarjeta::getNumeroTarjeta() const { return *numeroTarjeta; }

bool Tarjeta::validarDatos(string num, Fecha vtoIngresada, int cod) const {
    return (*numeroTarjeta == num && fechaVencimiento->esIgual(vtoIngresada) && *cvv == cod);
}

TarjetaDebito::TarjetaDebito(string num, Fecha vto, int cod, CuentaBancaria* cuenta)
    : Tarjeta(num, vto, cod, cuenta) {}

void TarjetaDebito::procesarPago(double monto, string descripcion, int cuotas) {
    cout << "Procesando compra ('" << descripcion << "') con Debito de $" << fixed << setprecision(2) << monto << "..." << endl;
    if (cuotas > 1) {
        cout << "   [!] Advertencia: Tarjetas de debito no aceptan cuotas. Cobrando al contado." << endl;
    }
    if (!cuentaAsociada->retirar(monto)) {
        cout << "   [!] Pago rechazado." << endl;
    }
}

TarjetaCredito::TarjetaCredito(string num, Fecha vto, int cod, CuentaBancaria* cuenta, double limite)
    : Tarjeta(num, vto, cod, cuenta) {
    limiteCredito = new double(limite);
    deudaTotal = new double(0.0);
    comprasActivas = new vector<CompraEnCuotas>();
}

TarjetaCredito::~TarjetaCredito() {
    delete limiteCredito;
    delete deudaTotal;
    delete comprasActivas;
}

void TarjetaCredito::procesarPago(double monto, string descripcion, int cuotas) {
    cout << "Procesando compra de credito ('" << descripcion << "') por $" << fixed << setprecision(2) << monto << " en " << cuotas << " cuota(s)..." << endl;

    if (*deudaTotal + monto <= *limiteCredito) {
        *deudaTotal += monto;
        CompraEnCuotas nuevaCompra(descripcion, monto, cuotas);
        comprasActivas->push_back(nuevaCompra);

        cout << "   [+] Compra aprobada." << endl;
        cout << "       Deuda total actual: $" << fixed << setprecision(2) << *deudaTotal << endl;
        cout << "       Cuota mensual generada por esta compra: $" << *nuevaCompra.montoPorCuota << endl;
    } else {
        cout << "   [!] Pago rechazado. Limite de credito excedido (Disponible: $" << (*limiteCredito - *deudaTotal) << ")." << endl;
    }
}

void TarjetaCredito::facturarMes() {
    if (comprasActivas->empty()) {
        cout << endl << "--- ESTADO DE CUENTA (TARJETA CREDITO " << *numeroTarjeta << ") ---" << endl;
        cout << "No hay deudas pendientes." << endl;
        return;
    }

    double montoTotalMes = 0;
    cout << endl << "--- ESTADO DE CUENTA (TARJETA CREDITO " << *numeroTarjeta << ") ---" << endl;
    cout << "Detalle de cuotas del mes:" << endl;

    for (auto& compra : *comprasActivas) {
        if (*compra.cuotasPagadas < *compra.cuotasTotales) {
            montoTotalMes += *compra.montoPorCuota;
            (*compra.cuotasPagadas)++;
            cout << " * " << *compra.descripcion << " | Cuota " << *compra.cuotasPagadas
                 << "/" << *compra.cuotasTotales << " | Monto: $" << fixed << setprecision(2) << *compra.montoPorCuota << endl;
        }
    }

    cout << "------------------------------------------" << endl;
    cout << "TOTAL A PAGAR ESTE MES: $" << fixed << setprecision(2) << montoTotalMes << endl;

    if (montoTotalMes > 0) {
        cout << endl << "Intentando cobro automatico desde la cuenta (" << cuentaAsociada->getNumeroCuenta() << ")..." << endl;
        if(cuentaAsociada->retirar(montoTotalMes)){
            *deudaTotal -= montoTotalMes;
            cout << "   [+] Cobro exitoso. Nueva deuda total pendiente: $" << fixed << setprecision(2) << *deudaTotal << endl;
            limpiarComprasPagadas();
        } else {
            cout << "   [!] Fondos insuficientes. Tarjeta en MORA." << endl;
        }
    }
}

void TarjetaCredito::limpiarComprasPagadas() {
    vector<CompraEnCuotas> comprasRestantes;
    for (const auto& compra : *comprasActivas) {
        if (*compra.cuotasPagadas < *compra.cuotasTotales) {
            comprasRestantes.push_back(compra);
        }
    }
    *comprasActivas = comprasRestantes;
}

void TarjetaCredito::adelantarPago(double monto) {
    if (monto <= 0 || *deudaTotal == 0) return;

    cout << endl << "[Adelantando pago de Tarjeta de Credito por $" << fixed << setprecision(2) << monto << "]" << endl;
    if(cuentaAsociada->retirar(monto)){
        *deudaTotal -= monto;
        cout << "   [+] Abono exitoso. La deuda total se ha reducido a $" << fixed << setprecision(2) << *deudaTotal << endl;

        if (*deudaTotal <= 0) {
            *deudaTotal = 0;
            comprasActivas->clear();
            cout << "   [+] Ha cancelado la totalidad de la deuda." << endl;
        }
    }
}
