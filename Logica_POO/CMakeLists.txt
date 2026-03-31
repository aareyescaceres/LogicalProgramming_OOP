cmake_minimum_required(VERSION 4.1)
project(LogicaProgramacion)

set(CMAKE_CXX_STANDARD 20)

add_executable(LogicaProgramacion main.cpp
        Persona.cpp
        CuentaBancaria.cpp
        Tarjeta.cpp
        CompraEnCuotas.cpp
        Banco.cpp
        Fecha.cpp
        RedInterbancaria.cpp
        AppBancaria.cpp
        AppBancaria.h
        Banco.h
        CompraEnCuotas.h
        CuentaBancaria.h
        Fecha.h
        Persona.h
        RedInterbancaria.h
        Tarjeta.h)
