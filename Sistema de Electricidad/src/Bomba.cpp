#include "Bomba.h"
#include <iostream>
#include <iomanip>

Bomba::Bomba(std::string inv, double c, double ps, double pd, double f)
    : Equipo(inv, c), ps(ps), pd(pd), f(f) {}

Bomba::~Bomba() {}

double Bomba::getPs() const {
    return ps;
}

double Bomba::getPd() const {
    return pd;
}

double Bomba::getF() const {
    return f;
}

void Bomba::mostrarInfo() const {
    Equipo::mostrarInfo();
    std::cout << "  Ps: " << std::fixed << std::setprecision(2) << ps 
              << ", Pd: " << std::fixed << std::setprecision(2) << pd
              << ", Flujo: " << std::fixed << std::setprecision(2) << f << std::endl;
}
