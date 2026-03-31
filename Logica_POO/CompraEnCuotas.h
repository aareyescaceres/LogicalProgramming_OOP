
#ifndef LOGICAPROGRAMACION_COMPRAENCUOTAS_H
#define LOGICAPROGRAMACION_COMPRAENCUOTAS_H

#include <string>

using namespace std;

struct CompraEnCuotas {
    string* descripcion;
    double* montoTotal;
    int* cuotasTotales;
    int* cuotasPagadas;
    double* montoPorCuota;

    CompraEnCuotas(string desc, double monto, int cuotas);
    CompraEnCuotas(const CompraEnCuotas& otra);
    CompraEnCuotas& operator=(const CompraEnCuotas& otra);
    ~CompraEnCuotas();
};

#endif //LOGICAPROGRAMACION_COMPRAENCUOTAS_H