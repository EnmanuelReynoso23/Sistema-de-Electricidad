#ifndef TRABAJADOR_H
#define TRABAJADOR_H

#include <string>

/**
 * @brief Clase base Trabajador
 *
 * Representa a un trabajador genérico de la industria.
 * Esta es la clase base de la jerarquía de trabajadores,
 * implementando el principio de herencia de POO.
 */
class Trabajador {
protected:
    std::string nombre;    // Nombre completo del trabajador
    std::string carne;     // Número de carné de identidad
    int anios;            // Años trabajando en la industria
    std::string grupo;     // Grupo de trabajo asignado

public:
    /**
     * @brief Constructor de la clase Trabajador
     * @param n Nombre del trabajador
     * @param c Número de carné de identidad
     * @param a Años trabajando en la industria
     * @param g Grupo de trabajo
     */
    Trabajador(std::string n, std::string c, int a, std::string g = "General");
    
    /**
     * @brief Destructor virtual para permitir herencia correcta
     */
    virtual ~Trabajador();
      // Métodos de acceso (getters) - Principio de encapsulamiento
    std::string getNombre() const;  // Obtiene el nombre del trabajador
    std::string getCarne() const;   // Obtiene el carné del trabajador
    int getAnios() const;          // Obtiene los años de experiencia
    std::string getGrupo() const;   // Obtiene el grupo de trabajo
    
    // Métodos para modificar grupo
    void setGrupo(const std::string& nuevoGrupo);  // Asigna nuevo grupo
    
    /**
     * @brief Muestra la información del trabajador
     * Método virtual para permitir polimorfismo en clases derivadas
     */
    virtual void mostrarInfo() const;
};

#endif // TRABAJADOR_H
