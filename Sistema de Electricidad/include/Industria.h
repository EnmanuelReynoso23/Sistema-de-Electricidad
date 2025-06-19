#ifndef INDUSTRIA_H
#define INDUSTRIA_H

#include <vector>
#include <string>
#include "Trabajador.h"
#include "Director.h"
#include "Equipo.h"
#include "Centrifuga.h"
#include "Embolo.h"
#include "Intercambiador.h"
#include "InformeMensual.h"

// Clase principal que gestiona toda la industria
class Industria {
private:
    std::string nombre;                        // Nombre de la industria
    double alumbrado;                          // Consumo eléctrico del alumbrado
    Director* director;                        // Puntero al director (relación 1:1)
    std::vector<Trabajador*> trabajadores;     // Lista de trabajadores (relación 1:*)
    std::vector<Equipo*> equipos;              // Lista de equipos (relación 1:*)
    std::vector<InformeMensual> informes;      // Historial de informes mensuales

public:
    // Constructor y destructor
    Industria(std::string nombre, double alum, Director* dir);
    ~Industria();
    
    // Métodos para agregar elementos
    void agregarTrabajador(Trabajador* t);
    void agregarEquipo(Equipo* e);
    void agregarInforme(int mes, double plan, double real);
    
    // Métodos de cálculo y análisis (requisitos del proyecto)
    double consumoTotal() const;                              // Consumo total = alumbrado + equipos
    Equipo* equipoMayorConsumo() const;                      // a) Equipo con mayor consumo
    std::vector<Centrifuga*> centrifugasOrdenadas() const;   // b) Centrífugas por diámetro
    void cantidadPorTipo(int& cent, int& emb, int& interc) const; // c) Cantidad por tipo
    std::vector<Trabajador*> trabajadoresOrdenados() const;  // d) Trabajadores alfabético
    Trabajador* trabajadorMasAntiguo() const;               // e) Trabajador más antiguo
    std::vector<int> mesesSobrepasados() const;             // f) Meses sobrepasados
    
    // Métodos de visualización
    void mostrarInformes() const;
    void mostrarEquipos() const;
    void mostrarTrabajadores() const;
    void mostrarEstadisticas() const;
};

#endif // INDUSTRIA_H
