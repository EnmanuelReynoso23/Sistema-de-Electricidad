#ifndef CENTRIFUGA_H
#define CENTRIFUGA_H

#include "Bomba.h"

// Clase Centrifuga - Bomba que usa fuerza centrífuga
class Centrifuga : public Bomba {
private:
    double der;  // diámetro del eje de rotación
    int np;      // número de paletas

public:
    // Constructor con parámetros específicos de centrífuga
    Centrifuga(std::string inv, double c, double ps, double pd, double f, double der, int np);
    virtual ~Centrifuga();
    
    // Getters para atributos específicos
    double getDer() const;
    int getNp() const;
    
    // Implementa fórmula: 0.38(ps + pd) + 2.3f + 3.4(der + np)
    double consumo() const override;
    std::string tipo() const override;
    void mostrarInfo() const override;
};

#endif // CENTRIFUGA_H
