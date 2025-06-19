#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Trabajador.h"

/**
 * @brief Clase Director - Hereda de Trabajador
 *
 * Representa al director de la industria, quien tiene responsabilidades
 * adicionales como generar informes mensuales de consumo eléctrico.
 * Implementa el principio de herencia "ES UN" - Director ES UN Trabajador.
 */
class Director : public Trabajador {
private:
    std::string beeper;        // Número del beeper del director
    std::string fechaInicio;   // Fecha de inicio en el cargo de director

public:
    /**
     * @brief Constructor de la clase Director
     * @param n Nombre del director
     * @param c Número de carné de identidad
     * @param a Años trabajando en la industria
     * @param b Número del beeper
     * @param f Fecha de inicio en el cargo
     */
    Director(std::string n, std::string c, int a, std::string b, std::string f);
    
    /**
     * @brief Destructor virtual de la clase Director
     */
    virtual ~Director();
    
    // Métodos de acceso específicos del director
    std::string getBeeper() const;       // Obtiene el número del beeper
    std::string getFechaInicio() const;  // Obtiene la fecha de inicio en el cargo
    
    /**
     * @brief Sobrescribe el método mostrarInfo() de la clase base
     * Implementa polimorfismo - comportamiento específico para Director
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Genera un informe mensual de consumo eléctrico
     * Funcionalidad específica del director para cumplir con sus responsabilidades
     * @param mes Mes del informe (1-12)
     * @param plan Plan de consumo asignado para el mes
     * @param real Consumo real registrado
     * @param min Consumo mínimo del año hasta la fecha
     * @param max Consumo máximo del año hasta la fecha
     */
    void renderInforme(int mes, double plan, double real, double min, double max) const;
};

#endif // DIRECTOR_H
