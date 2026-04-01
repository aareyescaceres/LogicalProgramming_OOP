# 🏦 Simulador de Sistema Financiero (Lógica de Programación y POO)

Este proyecto es una simulación en C++ de un ecosistema financiero básico. Fue desarrollado como un ejercicio integral para enseñar y aplicar los fundamentos de la **Lógica de Programación** y la **Programación Orientada a Objetos (POO)**. 

El sistema permite la creación de bancos, gestión de clientes, apertura de distintos tipos de cuentas bancarias (ahorros y corriente), emisión de tarjetas, y la simulación de compras en cuotas con sus respectivos ciclos de facturación.

## 🎯 Objetivos de Aprendizaje

El código fuente está diseñado para demostrar de manera práctica los siguientes conceptos computacionales:

* **Gestión Manual de Memoria (Punteros):** Creación y destrucción explícita de objetos en el *heap* utilizando `new` y `delete`. Implementación profunda de la "Regla de los Tres" (Constructor de copia, operador de asignación y destructor) en estructuras dinámicas como `CompraEnCuotas` y `Fecha`.
* **Abstracción:** Modelado de entidades del mundo real (Bancos, Personas, Cuentas) en clases C++.
* **Encapsulamiento:** Protección del estado interno de los objetos mediante modificadores de acceso (`private`, `protected`) y exposición controlada a través de métodos *getters*.
* **Herencia:** Creación de jerarquías de clases. Por ejemplo, `CuentaAhorros` y `CuentaCorriente` heredan los atributos y comportamientos base de `CuentaBancaria`.
* **Polimorfismo:** Uso de métodos virtuales (ej. `virtual bool retirar(double monto) = 0`) para permitir que las cuentas derivadas implementen sus propias reglas de negocio (como el manejo de sobregiros).

## 🗂️ Estructura del Proyecto

El proyecto está modularizado en múltiples archivos de cabecera (`.h`) y de implementación (`.cpp`):

* **`Banco.h` / `Banco.cpp`**: Entidad central que administra colecciones de cuentas y tarjetas. Gestiona la lógica para abrir cuentas y emitir tarjetas verificando reglas de negocio (ej. mayoría de edad).
* **`CuentaBancaria.h` / `CuentaBancaria.cpp`**: Contiene la clase base abstracta `CuentaBancaria` y sus implementaciones concretas `CuentaAhorros` y `CuentaCorriente`, demostrando polimorfismo en el método `retirar`.
* **`CompraEnCuotas.h` / `CompraEnCuotas.cpp`**: Estructura que maneja la lógica matemática y de estado para dividir un pago en múltiples meses.
* **`Fecha.h` / `Fecha.cpp`**: Estructura utilitaria para el manejo de meses y años, demostrando la sobrecarga del operador de asignación.
* **`Persona.h` / `Tarjeta.h`**: Representan a los clientes del banco y los medios de pago asociados a sus cuentas.
* **`AppBancaria.h` / `RedInterbancaria.h`**: Clases que orquestan las transacciones de alto nivel y la comunicación entre distintas entidades.
* **`main.cpp`**: Punto de entrada del programa. Ejecuta un script de prueba que levanta el sistema, crea usuarios, asigna cuentas/tarjetas y simula compras y cierres de mes para demostrar el funcionamiento cíclico de la lógica.

## ⚙️ Tecnologías y Requisitos

* **Entorno de Desarrollo (IDE):** Desarrollado utilizando **CLion** de JetBrains.
* **Lenguaje:** C++
* **Estándar:** C++20 (Requerido para compilar las características modernas del lenguaje).
* **Sistema de Construcción:** CMake (versión mínima 4.1).

## 🚀 Compilación y Ejecución

El proyecto fue creado y estructurado nativamente en **CLion**, por lo que la forma más directa de ejecutarlo es abriendo el directorio raíz (`CMakeLists.txt`) directamente en el IDE. CLion detectará automáticamente el sistema de construcción y configurará los perfiles de ejecución.
