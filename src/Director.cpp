#include "Director.h"
#include <iostream>
#include <iomanip>

Director::Director(std::string n, std::string c, int a, std::string b, std::string f)
    : Trabajador(n, c, a, "Directivo"), beeper(b), fechaInicio(f) {}

Director::~Director() {}

std::string Director::getBeeper() const {
    return beeper;
}

std::string Director::getFechaInicio() const {
    return fechaInicio;
}

void Director::mostrarInfo() const {
    Trabajador::mostrarInfo();
    std::cout << "Beeper: " << beeper << ", Inicio en cargo: " << fechaInicio << std::endl;
}

void Director::renderInforme(int mes, double plan, double real, double min, double max) const {
    std::string nombresMeses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                                 "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    
    std::cout << "\n=== INFORME MENSUAL DE CONSUMO ELÉCTRICO: " << nombresMeses[mes-1] << " ===" << std::endl;
    std::cout << "Director: " << nombre << " (CI: " << carne << ")" << std::endl;
    std::cout << "Plan asignado: " << std::fixed << std::setprecision(2) << plan << " kWh" << std::endl;
    std::cout << "Consumo real: " << std::fixed << std::setprecision(2) << real << " kWh" << std::endl;
    
    std::string estado = (real > plan) ? "SOBREPASADO" : "CUMPLIDO";
    double porcentaje = (real / plan) * 100;
    
    std::cout << "Estado: " << estado << " (" << std::fixed << std::setprecision(1) << porcentaje << "%)" << std::endl;
    std::cout << "Mínimo anual hasta la fecha: " << std::fixed << std::setprecision(2) << min << " kWh" << std::endl;
    std::cout << "Máximo anual hasta la fecha: " << std::fixed << std::setprecision(2) << max << " kWh" << std::endl;
    std::cout << "=================================================================" << std::endl;
}
