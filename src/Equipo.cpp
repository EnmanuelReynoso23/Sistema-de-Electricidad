#include "Equipo.h"
#include <iostream>
#include <iomanip>

Equipo::Equipo(std::string inv, double c)
    : inventario(inv), costo(c) {}

Equipo::~Equipo() {}

std::string Equipo::getInventario() const {
    return inventario;
}

double Equipo::getCosto() const {
    return costo;
}

void Equipo::mostrarInfo() const {
    std::cout << "Inventario: " << inventario 
              << ", Costo: $" << std::fixed << std::setprecision(2) << costo
              << ", Consumo: " << std::fixed << std::setprecision(2) << consumo() << " kWh" 
              << ", Tipo: " << tipo() << std::endl;
}
