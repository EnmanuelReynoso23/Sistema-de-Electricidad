#include "Trabajador.h"
#include <iostream>

// Constructor: inicializa los atributos del trabajador
Trabajador::Trabajador(std::string n, std::string c, int a, std::string g)
    : nombre(n), carne(c), anios(a), grupo(g) {}

// Destructor virtual para permitir herencia correcta
Trabajador::~Trabajador() {}

// Métodos de acceso (getters) - Principio de encapsulamiento
std::string Trabajador::getNombre() const {
    return nombre;
}

std::string Trabajador::getCarne() const {
    return carne;
}

int Trabajador::getAnios() const {
    return anios;
}

std::string Trabajador::getGrupo() const {
    return grupo;
}

// Método para cambiar grupo
void Trabajador::setGrupo(const std::string& nuevoGrupo) {
    grupo = nuevoGrupo;
}

// Muestra información básica del trabajador
void Trabajador::mostrarInfo() const {
    std::cout << "Nombre: " << nombre << ", CI: " << carne
              << ", Años: " << anios << ", Grupo: " << grupo << std::endl;
}
