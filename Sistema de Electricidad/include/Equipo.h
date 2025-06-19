#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>

/**
 * @brief Clase abstracta Equipo
 *
 * Clase base abstracta para todos los equipos de la industria.
 * Define la interfaz común que deben implementar todos los tipos de equipos.
 * Implementa el principio de abstracción de POO mediante métodos virtuales puros.
 */
class Equipo {
protected:
    std::string inventario;  // Número de inventario del equipo
    double costo;           // Costo del equipo en unidades monetarias

public:
    /**
     * @brief Constructor de la clase base Equipo
     * @param inv Número de inventario del equipo
     * @param c Costo del equipo
     */
    Equipo(std::string inv, double c);
    
    /**
     * @brief Destructor virtual para permitir herencia correcta
     * Esencial para el polimorfismo y gestión correcta de memoria
     */
    virtual ~Equipo();
    
    // Métodos de acceso (getters) - Principio de encapsulamiento
    std::string getInventario() const;  // Obtiene el número de inventario
    double getCosto() const;           // Obtiene el costo del equipo
    
    /**
     * @brief Calcula el consumo eléctrico del equipo
     * Método virtual puro que debe ser implementado por cada tipo específico.
     * Cada tipo de equipo tiene su propia fórmula de cálculo.
     * @return Consumo eléctrico en kWh
     */
    virtual double consumo() const = 0;
    
    /**
     * @brief Obtiene el tipo específico del equipo
     * Método virtual puro para identificación del tipo de equipo.
     * @return Cadena describiendo el tipo de equipo
     */
    virtual std::string tipo() const = 0;
    
    /**
     * @brief Muestra la información general del equipo
     * Método virtual que puede ser sobrescrito por clases derivadas
     * para mostrar información específica adicional.
     */
    virtual void mostrarInfo() const;
};

#endif // EQUIPO_H
