#include "Persona.h"
#include <iostream>

using namespace std;

Persona::Persona(string nombre, string dni, int edad) {
    this->nombre = new string(nombre);
    this->dni = new string(dni);
    this->edad = new int(edad);
}

Persona::Persona(const Persona& otra) {
    nombre = new string(*otra.nombre);
    dni = new string(*otra.dni);
    edad = new int(*otra.edad);
}

Persona& Persona::operator=(const Persona& otra) {
    if (this == &otra) return *this;
    *nombre = *otra.nombre;
    *dni = *otra.dni;
    *edad = *otra.edad;
    return *this;
}

Persona::~Persona() {
    delete nombre;
    delete dni;
    delete edad;
}

string Persona::getNombre() const { return *nombre; }
string Persona::getDni() const { return *dni; }
int Persona::getEdad() const { return *edad; }
bool Persona::esMayorDeEdad() const { return *edad >= 18; }

void Persona::setNombre(string nombre) { *this->nombre = nombre; }
void Persona::setDni(string dni) { *this->dni = dni; }
void Persona::setEdad(int edad) { *this->edad = edad; }

