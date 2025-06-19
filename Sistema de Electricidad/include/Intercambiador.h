#ifndef INTERCAMBIADOR_H
#define INTERCAMBIADOR_H

#include "Equipo.h"

// Clase Intercambiador - Equipo para transferencia de calor
class Intercambiador : public Equipo {
private:
    double a;    // área de transferencia
    double ptc;  // presión del tubo central
    double d;    // diámetro del intercambiador

public:
    // Constructor con parámetros específicos de intercambiador
    Intercambiador(std::string inv, double c, double a, double ptc, double d);
    virtual ~Intercambiador();
    
    // Getters para atributos específicos
    double getA() const;
    double getPtc() const;
    double getD() const;
    
    // Implementa fórmula: 0.25*ptc + ln(d)
    double consumo() const override;
    std::string tipo() const override;
    void mostrarInfo() const override;
};

#endif // INTERCAMBIADOR_H
