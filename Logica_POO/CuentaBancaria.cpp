#include "CuentaBancaria.h"
#include <iostream>
#include <iomanip>

using namespace std;

CuentaBancaria::CuentaBancaria(string num, string codigoCci, Persona* persona, double saldoInicial) {
    numeroCuenta = new string(num);
    cci = new string(codigoCci);
    saldo = new double(saldoInicial);
    titular = new Persona(*persona);
}

CuentaBancaria::~CuentaBancaria() {
    delete numeroCuenta;
    delete cci;
    delete saldo;
    delete titular;
}

string CuentaBancaria::getNumeroCuenta() const { return *numeroCuenta; }
string CuentaBancaria::getCCI() const { return *cci; }
double CuentaBancaria::getSaldo() const { return *saldo; }
Persona* CuentaBancaria::getTitular() const { return titular; }

void CuentaBancaria::depositar(double monto) {
    if (monto > 0) {
        *saldo += monto;
        cout << "   [+] Deposito de $" << fixed << setprecision(2) << monto << " en cuenta " << *numeroCuenta << " exitoso." << endl;
    }
}

void CuentaBancaria::mostrarDetalles() const {
    cout << "Cuenta: " << *numeroCuenta << " | CCI: " << *cci << endl;
    cout << "   Saldo: $" << fixed << setprecision(2) << *saldo;
}

CuentaAhorros::CuentaAhorros(string num, string codigoCci, Persona* t, double tasa)
    : CuentaBancaria(num, codigoCci, t, 0.0) {
    tasaInteres = new double(tasa);
}

CuentaAhorros::~CuentaAhorros() {
    delete tasaInteres;
}

bool CuentaAhorros::retirar(double monto) {
    if (monto > 0 && *saldo >= monto) {
        *saldo -= monto;
        cout << "   [-] Retiro de $" << fixed << setprecision(2) << monto << " exitoso (Ahorros)." << endl;
        return true;
    }
    cout << "   [!] Fondos insuficientes en Cuenta de Ahorros " << *numeroCuenta << "." << endl;
    return false;
}

void CuentaAhorros::mostrarDetalles() const {
    cout << "[Ahorros] ";
    CuentaBancaria::mostrarDetalles();
    cout << endl;
}

CuentaCorriente::CuentaCorriente(string num, string codigoCci, Persona* t, double sobregiro)
    : CuentaBancaria(num, codigoCci, t, 0.0) {
    limiteSobregiro = new double(sobregiro);
    sobregiroUsado = new double(0.0);
}

CuentaCorriente::~CuentaCorriente() {
    delete limiteSobregiro;
    delete sobregiroUsado;
}

void CuentaCorriente::depositar(double monto) {
    if (monto <= 0) return;

    if (*sobregiroUsado > 0) {
        if (monto >= *sobregiroUsado) {
            double sobrante = monto - *sobregiroUsado;
            cout << "   [+] Deposito de $" << fixed << setprecision(2) << monto << ". Se pago deuda de sobregiro ($" << *sobregiroUsado << ")." << endl;
            *sobregiroUsado = 0;
            *saldo += sobrante;
            cout << "   [+] El sobrante ($" << sobrante << ") se agrego al saldo." << endl;
        } else {
            *sobregiroUsado -= monto;
            cout << "   [+] Deposito de $" << fixed << setprecision(2) << monto << " destinado a pagar sobregiro. Deuda restante: $" << *sobregiroUsado << "." << endl;
        }
    } else {
        CuentaBancaria::depositar(monto);
    }
}

bool CuentaCorriente::retirar(double monto) {
    if (monto <= 0) return false;

    if (*saldo >= monto) {
        *saldo -= monto;
        cout << "   [-] Retiro de $" << fixed << setprecision(2) << monto << " exitoso (Corriente)." << endl;
        return true;
    } else {
        double falta = monto - *saldo;
        double sobregiroDisponible = *limiteSobregiro - *sobregiroUsado;

        if (sobregiroDisponible >= falta) {
            *sobregiroUsado += falta;
            *saldo = 0;
            cout << "   [-] Retiro de $" << fixed << setprecision(2) << monto << " exitoso. Se uso $" << falta << " de sobregiro." << endl;
            return true;
        } else {
            cout << "   [!] Fondos insuficientes y limite de sobregiro excedido." << endl;
            return false;
        }
    }
}

void CuentaCorriente::mostrarDetalles() const {
    cout << "[Corriente] ";
    CuentaBancaria::mostrarDetalles();
    cout << endl << "   Limite Sobregiro: $" << fixed << setprecision(2) << *limiteSobregiro
         << " | Sobregiro Usado (Deuda): $" << *sobregiroUsado << endl;
}