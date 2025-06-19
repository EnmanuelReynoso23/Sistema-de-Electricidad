#include "Embolo.h"
#include <iostream>
#include <iomanip>

// Constructor: llama al constructor de Bomba e inicializa atributos específicos
Embolo::Embolo(std::string inv, double c, double ps, double pd, double f, double l, double d)
    : Bomba(inv, c, ps, pd, f), l(l), d(d) {}

Embolo::~Embolo() {}

// Getters para atributos específicos de émbolo
double Embolo::getL() const {
    return l;
}

double Embolo::getD() const {
    return d;
}

// Implementa el cálculo de consumo específico para émbolos
double Embolo::consumo() const {
    // Fórmula del problema: 0.38(ps + pd) + 2.3f (más simple que centrífuga)
    return 0.38 * (ps + pd) + 2.3 * f;
}

// Identifica el tipo de equipo para polimorfismo
std::string Embolo::tipo() const {
    return "Bomba de Émbolos";
}

// Muestra información completa incluyendo datos específicos
void Embolo::mostrarInfo() const {
    Bomba::mostrarInfo(); // Llama al método de la clase padre
    std::cout << "  Largo: " << std::fixed << std::setprecision(2) << l
              << ", Diámetro: " << std::fixed << std::setprecision(2) << d << std::endl;
}
