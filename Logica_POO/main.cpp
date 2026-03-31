#include <iostream>
#include "RedInterbancaria.h"
#include "Banco.h"
#include "Persona.h"
#include "CuentaBancaria.h"
#include "Tarjeta.h"
#include "AppBancaria.h"

using namespace std;

int main() {
    cout << "=== SIMULADOR DE SISTEMA FINANCIERO ===" << endl;

    RedInterbancaria redNacional;
    Banco miBanco("Banco Universitario", "001");
    redNacional.afiliarBanco(&miBanco);

    Persona estudiante("Carlos Silva", "12345678", 22);

    CuentaBancaria* ctaCarlos = miBanco.abrirCuentaCorriente("CC-111", "001-CC111", &estudiante, 500.0);

    TarjetaCredito* tcCarlos = miBanco.emitirTarjetaCredito("CRE-9999", Fecha(12, 28), 123, ctaCarlos, 5000.0);

    AppBancaria app(&estudiante, &miBanco);

    app.comprar("CRE-9999", 1200.0, 6, "Laptop ASUS", Fecha(12, 28), 123);
    app.comprar("CRE-9999", 600.0, 3, "Matricula", Fecha(12, 28), 123);
    app.comprar("CRE-9999", 80.0, 1, "Cena", Fecha(12, 28), 123);

    app.mostrarResumen();

    cout << endl << "*** LLEGA EL FIN DEL PRIMER MES ***" << endl;
    tcCarlos->facturarMes();

    app.mostrarResumen();

    cout << endl << "*** LLEGA EL FIN DEL SEGUNDO MES ***" << endl;
    tcCarlos->facturarMes();

    app.mostrarResumen();

    return 0;
}
