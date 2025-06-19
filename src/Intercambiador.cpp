#include "Intercambiador.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Intercambiador::Intercambiador(std::string inv, double c, double a, double ptc, double d)
    : Equipo(inv, c), a(a), ptc(ptc), d(d) {}

Intercambiador::~Intercambiador() {}

double Intercambiador::getA() const {
    return a;
}

double Intercambiador::getPtc() const {
    return ptc;
}

double Intercambiador::getD() const {
    return d;
}

double Intercambiador::consumo() const {
    // Fórmula: 0.25ptc + ln(d)
    return 0.25 * ptc + log(d);
}

std::string Intercambiador::tipo() const {
    return "Intercambiador de Calor";
}

void Intercambiador::mostrarInfo() const {
    Equipo::mostrarInfo();
    std::cout << "  Área: " << std::fixed << std::setprecision(2) << a 
              << ", Presión tubo central: " << std::fixed << std::setprecision(2) << ptc
              << ", Diámetro: " << std::fixed << std::setprecision(2) << d << std::endl;
}
