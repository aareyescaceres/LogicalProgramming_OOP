
#ifndef LOGICAPROGRAMACION_FECHA_H
#define LOGICAPROGRAMACION_FECHA_H

struct Fecha {
    int* mes;
    int* anio;

    Fecha(int m, int a);
    Fecha(const Fecha& otra);
    Fecha& operator=(const Fecha& otra);
    ~Fecha();

    bool esIgual(const Fecha& otra) const;
};

#endif //LOGICAPROGRAMACION_FECHA_H