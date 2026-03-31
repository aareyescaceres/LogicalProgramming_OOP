#include "AppBancaria.h"
#include <iostream>

using namespace std;

AppBancaria::AppBancaria(Persona* usr, Banco* banco) : usuarioLogueado(usr), bancoConectado(banco) {
    cout << endl << "=========================================" << endl;
    cout << ">>> APP BANCARIA: " << bancoConectado->getNombre() << " <<<" << endl;
    cout << "Hola, " << usuarioLogueado->getNombre() << "." << endl;
    cout << "=========================================" << endl;
}

void AppBancaria::mostrarResumen() const {
    cout << endl << "--- TUS PRODUCTOS ---" << endl;
    vector<CuentaBancaria*> misCuentas = bancoConectado->obtenerCuentasCliente(usuarioLogueado->getDni());
    vector<Tarjeta*> misTarjetas = bancoConectado->obtenerTarjetasCliente(usuarioLogueado->getDni());

    cout << "CUENTAS (" << misCuentas.size() << "):" << endl;
    for (CuentaBancaria* cuenta : misCuentas) { cuenta->mostrarDetalles(); }
}

void AppBancaria::comprar(string numTarjeta, double monto, int cuotas, string desc, Fecha vtoIngresado, int cvvIngresado) {
    cout << endl << "[App: Compra online - '" << desc << "']" << endl;
    vector<Tarjeta*> misTarjetas = bancoConectado->obtenerTarjetasCliente(usuarioLogueado->getDni());

    for (Tarjeta* tarjeta : misTarjetas) {
        if(tarjeta->getNumeroTarjeta() == numTarjeta) {
            if (tarjeta->validarDatos(numTarjeta, vtoIngresado, cvvIngresado)) {
                tarjeta->procesarPago(monto, desc, cuotas);
            } else {
                cout << "   [!] ERROR: Datos de tarjeta incorrectos." << endl;
            }
            return;
        }
    }
    cout << "   [!] Tarjeta no encontrada." << endl;
}

