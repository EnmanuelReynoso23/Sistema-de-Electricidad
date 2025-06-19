#include "Industria.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Constructor: inicializa la industria con nombre, consumo de alumbrado y director
Industria::Industria(std::string nombre, double alum, Director* dir)
    : nombre(nombre), alumbrado(alum), director(dir) {}

// Destructor: libera toda la memoria dinámica (gestión correcta de memoria)
Industria::~Industria() {
    // Liberar memoria de trabajadores
    for (Trabajador* t : trabajadores) {
        delete t;
    }
    // Liberar memoria de equipos (polimorfismo - cada objeto se destruye correctamente)
    for (Equipo* e : equipos) {
        delete e;
    }
    // Liberar memoria del director
    delete director;
}

// Métodos para agregar elementos a la industria
void Industria::agregarTrabajador(Trabajador* t) {
    trabajadores.push_back(t);
}

void Industria::agregarEquipo(Equipo* e) {
    equipos.push_back(e);
}

// Agrega un informe mensual calculando automáticamente min/max anuales
void Industria::agregarInforme(int mes, double plan, double real) {
    // Calcular min y max actuales del año
    double min = real, max = real;
    
    for (const auto& informe : informes) {
        if (informe.real < min) min = informe.real;
        if (informe.real > max) max = informe.real;
    }
    
    // Ajustar si el nuevo valor es menor o mayor
    if (real < min) min = real;
    if (real > max) max = real;
    
    informes.emplace_back(mes, plan, real, min, max);
}

// Calcula el consumo total: alumbrado + suma de todos los equipos
double Industria::consumoTotal() const {
    double total = alumbrado;
    for (const Equipo* e : equipos) {
        total += e->consumo(); // Polimorfismo: cada equipo calcula su consumo
    }
    return total;
}

// REQUISITO A: Encuentra el equipo que más corriente consume
Equipo* Industria::equipoMayorConsumo() const {
    if (equipos.empty()) return nullptr;
    
    Equipo* mayor = equipos[0];
    for (Equipo* e : equipos) {
        if (e->consumo() > mayor->consumo()) {
            mayor = e;
        }
    }
    return mayor;
}

// REQUISITO B: Obtener centrífugas ordenadas descendentemente por diámetro
std::vector<Centrifuga*> Industria::centrifugasOrdenadas() const {
    std::vector<Centrifuga*> centrifugas;
    
    // Recopilar todas las centrífugas usando dynamic_cast (RTTI)
    for (Equipo* e : equipos) {
        Centrifuga* c = dynamic_cast<Centrifuga*>(e);
        if (c != nullptr) {
            centrifugas.push_back(c);
        }
    }
    
    // Ordenar descendentemente por diámetro usando lambda
    std::sort(centrifugas.begin(), centrifugas.end(),
              [](const Centrifuga* a, const Centrifuga* b) {
                  return a->getDer() > b->getDer();
              });
    
    return centrifugas;
}

// REQUISITO C: Obtener cantidad de equipos por tipo
void Industria::cantidadPorTipo(int& cent, int& emb, int& interc) const {
    cent = emb = interc = 0;
    
    // Usar dynamic_cast para identificar tipos en tiempo de ejecución
    for (const Equipo* e : equipos) {
        if (dynamic_cast<const Centrifuga*>(e)) {
            cent++;
        } else if (dynamic_cast<const Embolo*>(e)) {
            emb++;
        } else if (dynamic_cast<const Intercambiador*>(e)) {
            interc++;
        }
    }
}

// REQUISITO D: Trabajadores ordenados alfabéticamente
std::vector<Trabajador*> Industria::trabajadoresOrdenados() const {
    std::vector<Trabajador*> trabajadoresOrden = trabajadores;
    
    // Incluir al director en la lista (director también es trabajador)
    trabajadoresOrden.push_back(director);
    
    // Ordenar alfabéticamente por nombre usando lambda
    std::sort(trabajadoresOrden.begin(), trabajadoresOrden.end(),
              [](const Trabajador* a, const Trabajador* b) {
                  return a->getNombre() < b->getNombre();
              });
    
    return trabajadoresOrden;
}

// REQUISITO E: Trabajador que más años lleva en la industria
Trabajador* Industria::trabajadorMasAntiguo() const {
    if (trabajadores.empty() && director == nullptr) return nullptr;
    
    Trabajador* masAntiguo = director;
    
    // Buscar el trabajador con más años (incluye director)
    for (Trabajador* t : trabajadores) {
        if (masAntiguo == nullptr || t->getAnios() > masAntiguo->getAnios()) {
            masAntiguo = t;
        }
    }
    
    return masAntiguo;
}

// REQUISITO F: Meses en que se sobrepasó el plan de consumo
std::vector<int> Industria::mesesSobrepasados() const {
    std::vector<int> meses;
    
    // Revisar cada informe para identificar sobrepasamiento
    for (const auto& informe : informes) {
        if (informe.real > informe.plan) {
            meses.push_back(informe.mes);
        }
    }
    
    return meses;
}

void Industria::mostrarInformes() const {
    std::cout << "\n=== INFORMES MENSUALES ===" << std::endl;
    
    if (informes.empty()) {
        std::cout << "No hay informes registrados." << std::endl;
        return;
    }
    
    for (const auto& informe : informes) {
        director->renderInforme(informe.mes, informe.plan, informe.real, informe.min, informe.max);
    }
}

void Industria::mostrarEquipos() const {
    std::cout << "\n=== EQUIPOS DE LA INDUSTRIA ===" << std::endl;
    std::cout << "Consumo de alumbrado: " << std::fixed << std::setprecision(2) << alumbrado << " kWh" << std::endl;
    std::cout << "Total de equipos: " << equipos.size() << std::endl;
    
    for (const Equipo* e : equipos) {
        e->mostrarInfo();
    }
    
    std::cout << "\nConsumo total de la industria: " << std::fixed << std::setprecision(2) 
              << consumoTotal() << " kWh" << std::endl;
}

void Industria::mostrarTrabajadores() const {
    std::cout << "\n=== TRABAJADORES DE LA INDUSTRIA ===" << std::endl;
    std::cout << "Director:" << std::endl;
    director->mostrarInfo();
    
    std::cout << "\nTrabajadores (" << trabajadores.size() << "):" << std::endl;
    for (const Trabajador* t : trabajadores) {
        t->mostrarInfo();
    }
}

void Industria::mostrarEstadisticas() const {
    std::cout << "\n=== ESTADÍSTICAS Y REPORTES ===" << std::endl;
    
    // a) Equipo que más corriente consume
    Equipo* mayorConsumo = equipoMayorConsumo();
    if (mayorConsumo) {
        std::cout << "\na) Equipo con mayor consumo:" << std::endl;
        mayorConsumo->mostrarInfo();
    }
    
    // b) Centrífugas ordenadas por diámetro
    std::cout << "\nb) Centrífugas ordenadas por diámetro (descendente):" << std::endl;
    auto centrifugas = centrifugasOrdenadas();
    if (centrifugas.empty()) {
        std::cout << "No hay centrífugas en la industria." << std::endl;
    } else {
        for (const Centrifuga* c : centrifugas) {
            c->mostrarInfo();
        }
    }
    
    // c) Cantidad de equipos por tipo
    int cent, emb, interc;
    cantidadPorTipo(cent, emb, interc);
    std::cout << "\nc) Cantidad de equipos por tipo:" << std::endl;
    std::cout << "   Bombas Centrífugas: " << cent << std::endl;
    std::cout << "   Bombas de Émbolos: " << emb << std::endl;
    std::cout << "   Intercambiadores de Calor: " << interc << std::endl;
    
    // d) Trabajadores ordenados alfabéticamente
    std::cout << "\nd) Trabajadores ordenados alfabéticamente:" << std::endl;
    auto trabajadoresOrden = trabajadoresOrdenados();
    for (const Trabajador* t : trabajadoresOrden) {
        t->mostrarInfo();
    }
    
    // e) Trabajador más antiguo
    Trabajador* masAntiguo = trabajadorMasAntiguo();
    if (masAntiguo) {
        std::cout << "\ne) Trabajador más antiguo:" << std::endl;
        masAntiguo->mostrarInfo();
    }
    
    // f) Meses que sobrepasaron el plan
    std::cout << "\nf) Meses que sobrepasaron el plan de consumo:" << std::endl;
    auto mesesSobre = mesesSobrepasados();
    if (mesesSobre.empty()) {
        std::cout << "No se ha sobrepasado el plan en ningún mes." << std::endl;
    } else {
        std::string nombresMeses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                                     "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
        for (int mes : mesesSobre) {
            std::cout << "   " << nombresMeses[mes-1] << std::endl;
        }
    }
}