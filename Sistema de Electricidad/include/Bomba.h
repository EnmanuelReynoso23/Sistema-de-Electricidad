#ifndef BOMBA_H
#define BOMBA_H

#include "Equipo.h"

/**
 * @brief Clase abstracta Bomba - Hereda de Equipo
 *
 * Clase intermedia en la jerarquía de equipos que representa
 * las características comunes de todos los tipos de bombas.
 * Implementa herencia multinivel: Equipo -> Bomba -> {Centrífuga, Émbolos}
 */
class Bomba : public Equipo {
protected:
    double ps;  // Presión de succión en unidades de presión
    double pd;  // Presión de descarga en unidades de presión
    double f;   // Flujo volumétrico en unidades de caudal

public:
    /**
     * @brief Constructor de la clase Bomba
     * @param inv Número de inventario de la bomba
     * @param c Costo de la bomba
     * @param ps Presión de succión
     * @param pd Presión de descarga
     * @param f Flujo volumétrico
     */
    Bomba(std::string inv, double c, double ps, double pd, double f);
    
    /**
     * @brief Destructor virtual de la clase Bomba
     */
    virtual ~Bomba();
    
    // Métodos de acceso para las características específicas de bombas
    double getPs() const;  // Obtiene la presión de succión
    double getPd() const;  // Obtiene la presión de descarga
    double getF() const;   // Obtiene el flujo volumétrico
    
    /**
     * @brief Sobrescribe mostrarInfo() para incluir datos específicos de bombas
     * Implementa polimorfismo - comportamiento específico para bombas
     */
    void mostrarInfo() const override;
    
    // NOTA: Los métodos consumo() y tipo() siguen siendo virtuales puros
    // y deben ser implementados por las clases derivadas (Centrífuga, Émbolos)
};

#endif // BOMBA_H
