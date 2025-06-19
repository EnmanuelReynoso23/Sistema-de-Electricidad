#ifndef EMBOLO_H
#define EMBOLO_H

#include "Bomba.h"

// Clase Embolo - Bomba de desplazamiento positivo
class Embolo : public Bomba {
private:
    double l;  // largo del émbolo
    double d;  // diámetro del émbolo

public:
    // Constructor con parámetros específicos de émbolo
    Embolo(std::string inv, double c, double ps, double pd, double f, double l, double d);
    virtual ~Embolo();
    
    // Getters para atributos específicos
    double getL() const;
    double getD() const;
    
    // Implementa fórmula: 0.38(ps + pd) + 2.3f
    double consumo() const override;
    std::string tipo() const override;
    void mostrarInfo() const override;
};

#endif // EMBOLO_H
