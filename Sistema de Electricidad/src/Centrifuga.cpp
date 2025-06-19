#include "Centrifuga.h"
#include <iostream>
#include <iomanip>

// Constructor: llama al constructor de Bomba e inicializa atributos específicos
Centrifuga::Centrifuga(std::string inv, double c, double ps, double pd, double f, double der, int np)
    : Bomba(inv, c, ps, pd, f), der(der), np(np) {}

Centrifuga::~Centrifuga() {}

// Getters para atributos específicos de centrífuga
double Centrifuga::getDer() const {
    return der;
}

int Centrifuga::getNp() const {
    return np;
}

// Implementa el cálculo de consumo específico para centrífugas
double Centrifuga::consumo() const {
    // Fórmula del problema: 0.38(ps + pd) + 2.3f + 3.4(der + np)
    return 0.38 * (ps + pd) + 2.3 * f + 3.4 * (der + np);
}

// Identifica el tipo de equipo para polimorfismo
std::string Centrifuga::tipo() const {
    return "Bomba Centrífuga";
}

// Muestra información completa incluyendo datos específicos
void Centrifuga::mostrarInfo() const {
    Bomba::mostrarInfo(); // Llama al método de la clase padre
    std::cout << "  Diámetro eje: " << std::fixed << std::setprecision(2) << der
              << ", Número de paletas: " << np << std::endl;
}
