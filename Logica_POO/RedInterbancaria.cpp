#include "RedInterbancaria.h"
#include <iostream>
#include <iomanip>

using namespace std;

RedInterbancaria::RedInterbancaria() {
    bancosAfiliados = new vector<Banco*>();
}

RedInterbancaria::~RedInterbancaria() {
    delete bancosAfiliados;
}

void RedInterbancaria::afiliarBanco(Banco* banco) {
    bancosAfiliados->push_back(banco);
}

void RedInterbancaria::transferirPorCCI(string cciOrigen, string cciDestino, double monto) {
    cout << endl << ">>> INICIANDO TRANSFERENCIA INTERBANCARIA ($" << fixed << setprecision(2) << monto << ") >>>" << endl;
    cout << "Origen: " << cciOrigen << " | Destino: " << cciDestino << endl;

    CuentaBancaria* cuentaOrigen = nullptr;
    CuentaBancaria* cuentaDestino = nullptr;

    for (Banco* b : *bancosAfiliados) {
        if (cuentaOrigen == nullptr) {
            cuentaOrigen = b->buscarCuentaPorCCI(cciOrigen);
        }
        if (cuentaDestino == nullptr) {
            cuentaDestino = b->buscarCuentaPorCCI(cciDestino);
        }
        if (cuentaOrigen != nullptr && cuentaDestino != nullptr) {
            break;
        }
    }

    if (cuentaOrigen == nullptr) {
        cout << "[!] Error de enrutamiento: La cuenta de origen no existe en la red." << endl;
        return; 
    }
    if (cuentaDestino == nullptr) {
        cout << "[!] Error de enrutamiento: La cuenta de destino no existe en la red." << endl;
        return; 
    }

    if (cciOrigen == cciDestino) {
        cout << "[!] Error: No se puede transferir a la misma cuenta." << endl;
        return;
    }

    if (cuentaOrigen->retirar(monto)) {
        cuentaDestino->depositar(monto);
        cout << ">>> TRANSFERENCIA INTERBANCARIA EXITOSA <<<" << endl;
    } else {
        cout << ">>> TRANSFERENCIA FALLIDA (Fondos insuficientes en la cuenta origen) <<<" << endl;
    }
}