
#ifndef LOGICAPROGRAMACION_REDINTERBANCARIA_H
#define LOGICAPROGRAMACION_REDINTERBANCARIA_H

#include <vector>
#include <string>
#include "Banco.h"

using namespace std;

class RedInterbancaria {
private:
    vector<Banco*>* bancosAfiliados;

public:
    RedInterbancaria();
    ~RedInterbancaria();

    void afiliarBanco(Banco* banco);
    void transferirPorCCI(string cciOrigen, string cciDestino, double monto);
};


#endif //LOGICAPROGRAMACION_REDINTERBANCARIA_H