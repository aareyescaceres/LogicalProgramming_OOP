#include "CompraEnCuotas.h"

CompraEnCuotas::CompraEnCuotas(string desc, double monto, int cuotas) {
    descripcion = new string(desc);
    montoTotal = new double(monto);
    cuotasTotales = new int(cuotas);
    cuotasPagadas = new int(0);
    montoPorCuota = new double(0.0);

    if (*cuotasTotales > 0) {
        *montoPorCuota = *montoTotal / *cuotasTotales;
    } else {
        *montoPorCuota = *montoTotal;
        *cuotasTotales = 1;
    }
}

CompraEnCuotas::CompraEnCuotas(const CompraEnCuotas& otra) {
    descripcion = new string(*otra.descripcion);
    montoTotal = new double(*otra.montoTotal);
    cuotasTotales = new int(*otra.cuotasTotales);
    cuotasPagadas = new int(*otra.cuotasPagadas);
    montoPorCuota = new double(*otra.montoPorCuota);
}

CompraEnCuotas& CompraEnCuotas::operator=(const CompraEnCuotas& otra) {
    if (this == &otra) return *this;
    *descripcion = *otra.descripcion;
    *montoTotal = *otra.montoTotal;
    *cuotasTotales = *otra.cuotasTotales;
    *cuotasPagadas = *otra.cuotasPagadas;
    *montoPorCuota = *otra.montoPorCuota;
    return *this;
}

CompraEnCuotas::~CompraEnCuotas() {
    delete descripcion;
    delete montoTotal;
    delete cuotasTotales;
    delete cuotasPagadas;
    delete montoPorCuota;
}