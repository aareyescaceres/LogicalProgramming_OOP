#include "Fecha.h"
#include <iostream>

using namespace std;

Fecha::Fecha(int m, int a) {
    mes = new int(m);
    anio = new int(a);
}

Fecha::Fecha(const Fecha& otra) {
    mes = new int(*otra.mes);
    anio = new int(*otra.anio);
}

Fecha& Fecha::operator=(const Fecha& otra) {
    if (this == &otra) return *this;
    *mes = *otra.mes;
    *anio = *otra.anio;
    return *this;
}

Fecha::~Fecha() {
    delete mes;
    delete anio;
}

bool Fecha::esIgual(const Fecha& otra) const {
    return (*mes == *otra.mes && *anio == *otra.anio);
}


