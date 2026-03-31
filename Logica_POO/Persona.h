#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

class Persona {
private:
    string* nombre;
    string* dni;
    int* edad;

public:
    Persona(string nombre, string dni, int edad);
    Persona(const Persona& otra);
    Persona& operator=(const Persona& otra);
    ~Persona();

    string getNombre() const;
    string getDni() const;
    int getEdad() const;
    bool esMayorDeEdad() const;

    void setNombre(string nombre);
    void setDni(string dni);
    void setEdad(int edad);
    void mostrarInfo() const;
};

#endif