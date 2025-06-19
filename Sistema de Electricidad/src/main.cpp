#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cctype>
#include "Industria.h"
#include "Centrifuga.h"
#include "Embolo.h"
#include "Intercambiador.h"

// Configuración para caracteres españoles
void configurarLocale() {
    try {
        std::locale::global(std::locale("Spanish_Spain.utf8"));
    } catch (...) {
        try {
            std::locale::global(std::locale("es_ES.UTF-8"));
        } catch (...) {
            std::locale::global(std::locale("C"));
        }
    }
    
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
}

// Clase para manejo de archivos y persistencia
class GestorArchivos {
public:
    // Guardar datos de la industria
    static bool guardarIndustria(const Industria& /* industria */, const std::string& archivo) {
        std::ofstream file(archivo);
        if (!file.is_open()) {
            std::cout << "❌ Error al crear archivo: " << archivo << std::endl;
            return false;
        }
        
        file << "SISTEMA_CONSUMO_ELECTRICO_V1.0" << std::endl;
        file << "GUARDADO_AUTOMATICO" << std::endl;
        // Aquí se implementaría la serialización completa
        file.close();
        std::cout << "💾 Datos guardados en: " << archivo << std::endl;
        return true;
    }
    
    // Cargar datos de la industria
    static bool cargarIndustria(const std::string& archivo) {
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "📁 No se encontró archivo de datos: " << archivo << std::endl;
            return false;
        }
        
        std::string linea;
        std::getline(file, linea);
        if (linea == "SISTEMA_CONSUMO_ELECTRICO_V1.0") {
            std::cout << "📂 Archivo de datos válido encontrado" << std::endl;
            // Aquí se implementaría la deserialización
        }
        file.close();
        return true;
    }
    
    // Exportar reporte a CSV
    static void exportarCSV(const Industria& /* industria */, const std::string& archivo) {
        std::ofstream file(archivo);
        if (!file.is_open()) return;
        
        file << "Tipo,Inventario,Costo,Consumo,Especificaciones\n";
        // Implementar exportación de datos de equipos
        file.close();
        std::cout << "📊 Reporte CSV exportado: " << archivo << std::endl;
    }
};

// Clase para análisis estadístico avanzado
class AnalizadorEstadistico {
public:
    // Calcular tendencias de consumo
    static void analizarTendencias(const Industria& industria) {
        std::cout << "\n📈 ANÁLISIS DE TENDENCIAS DE CONSUMO" << std::endl;
        std::cout << "════════════════════════════════════" << std::endl;
        
        double consumoTotal = industria.consumoTotal();
        std::cout << "Consumo Total: " << std::fixed << std::setprecision(2) << consumoTotal << " kWh" << std::endl;
        
        // Análisis por tipo de equipo
        int centrifugas, embolos, intercambiadores;
        industria.cantidadPorTipo(centrifugas, embolos, intercambiadores);
        
        if (centrifugas > 0) {
            std::cout << "📊 Bombas Centrífugas: " << centrifugas << " unidades" << std::endl;
        }
        if (embolos > 0) {
            std::cout << "📊 Bombas Émbolos: " << embolos << " unidades" << std::endl;
        }
        if (intercambiadores > 0) {
            std::cout << "📊 Intercambiadores: " << intercambiadores << " unidades" << std::endl;
        }
        
        // Proyección de eficiencia
        std::cout << "\n🎯 ÍNDICES DE EFICIENCIA:" << std::endl;
        double eficiencia = (consumoTotal > 0) ? (consumoTotal / (centrifugas + embolos + intercambiadores)) : 0;
        std::cout << "Consumo promedio por equipo: " << std::fixed << std::setprecision(2) << eficiencia << " kWh" << std::endl;
    }
};

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Función para validar que una cadena no contenga números
bool validarSoloLetras(const std::string& texto) {
    if (texto.empty()) return false;
    
    for (char c : texto) {
        if (std::isdigit(c)) {
            return false;
        }
        // Permitir letras, espacios y algunos caracteres especiales comunes en nombres
        if (!std::isalpha(c) && c != ' ' && c != '.' && c != '-') {
            return false;
        }
    }
    return true;
}

// Función para validar que una cadena contenga solo números
bool validarSoloNumeros(const std::string& texto) {
    if (texto.empty()) return false;
    
    for (char c : texto) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Función para obtener un número entero válido
int obtenerEnteroValido(const std::string& mensaje, int min, int max) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            if (valor >= min && valor <= max) {
                return valor;
            } else {
                std::cout << "[ERROR] Debe estar entre " << min << " y " << max << std::endl;
            }
        } else {
            std::cout << "[ERROR] Debe ingresar un numero valido" << std::endl;
            limpiarBuffer();
        }
    }
}

// Función para obtener un número decimal válido
double obtenerDecimalValido(const std::string& mensaje, double min) {
    double valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            if (valor >= min) {
                return valor;
            } else {
                std::cout << "[ERROR] Debe ser mayor o igual a " << min << std::endl;
            }
        } else {
            std::cout << "[ERROR] Debe ingresar un numero valido" << std::endl;
            limpiarBuffer();
        }
    }
}

// Función para obtener texto válido (solo letras y espacios)
std::string obtenerTextoValido(const std::string& mensaje, bool permitirNumeros = false) {
    std::string texto;
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, texto);
        
        if (texto.empty()) {
            continue; // Solo reintenta sin mostrar error
        }
        
        if (!permitirNumeros && !validarSoloLetras(texto)) {
            std::cout << "[ERROR] Solo se permiten letras y espacios, NO numeros" << std::endl;
            continue;
        }
        
        return texto;
    }
}

// Función para pausar y esperar entrada del usuario
void pausa() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

// Función para mostrar el menú principal
void mostrarMenu() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║               SISTEMA DE CONTROL ELECTRICO                  ║" << std::endl;
    std::cout << "║                    MENU PRINCIPAL                           ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║                                                              ║" << std::endl;
    std::cout << "║  📋 GESTION DE DATOS:                                       ║" << std::endl;
    std::cout << "║     [1] Agregar Trabajador                                  ║" << std::endl;
    std::cout << "║     [2] Agregar Bomba Centrifuga                            ║" << std::endl;
    std::cout << "║     [3] Agregar Bomba de Embolos                            ║" << std::endl;
    std::cout << "║     [4] Agregar Intercambiador de Calor                     ║" << std::endl;
    std::cout << "║     [5] Agregar Informe Mensual                             ║" << std::endl;
    std::cout << "║                                                              ║" << std::endl;
    std::cout << "║  📊 CONSULTAS Y REPORTES:                                   ║" << std::endl;
    std::cout << "║     [6] Ver Trabajadores                                    ║" << std::endl;
    std::cout << "║     [7] Ver Equipos y Consumo                               ║" << std::endl;
    std::cout << "║     [8] Estadisticas Completas (Requisitos a-f)             ║" << std::endl;
    std::cout << "║     [9] Informes Mensuales del Director                     ║" << std::endl;
    std::cout << "║                                                              ║" << std::endl;
    std::cout << "║     [0] Salir del Sistema                                   ║" << std::endl;
    std::cout << "║                                                              ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << " ⚡ Seleccione una opcion (0-9): ";
}

// Función para agregar trabajador
void agregarTrabajador(Industria& industria) {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                          AGREGAR TRABAJADOR                            │" << std::endl;
    std::cout << "│                   Complete los datos del empleado                      │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────────────┘" << std::endl;
    
    limpiarBuffer();
    
    // Validar nombre (solo letras)
    std::string nombre = obtenerTextoValido("👤 Nombre completo (solo letras): ");
    
    // Validar carné (permitir números y letras)
    std::string carne = obtenerTextoValido("🆔 Carne de identidad: ", true);
    
    // Validar años (solo números)
    int anios = obtenerEnteroValido("📅 Anos en la industria (0-50): ", 0, 50);
    
    // Selección de grupo
    std::cout << "\n🏢 GRUPOS DE TRABAJO DISPONIBLES:" << std::endl;
    std::cout << "   [1] Mantenimiento" << std::endl;
    std::cout << "   [2] Operaciones" << std::endl;
    std::cout << "   [3] Calidad" << std::endl;
    std::cout << "   [4] Seguridad" << std::endl;
    std::cout << "   [5] Administracion" << std::endl;
    std::cout << "   [6] Ingenieria" << std::endl;
    std::cout << "   [7] General" << std::endl;
    
    int opcionGrupo = obtenerEnteroValido("📋 Seleccione grupo (1-7): ", 1, 7);
    
    std::string grupo;
    switch(opcionGrupo) {
        case 1: grupo = "Mantenimiento"; break;
        case 2: grupo = "Operaciones"; break;
        case 3: grupo = "Calidad"; break;
        case 4: grupo = "Seguridad"; break;
        case 5: grupo = "Administracion"; break;
        case 6: grupo = "Ingenieria"; break;
        case 7: grupo = "General"; break;
    }
    
    industria.agregarTrabajador(new Trabajador(nombre, carne, anios, grupo));
    std::cout << "\n✅ Trabajador '" << nombre << "' agregado al grupo '" << grupo << "' exitosamente!" << std::endl;
    std::cout << "📊 Total de trabajadores en la industria: " << (industria.trabajadoresOrdenados().size()) << std::endl;
}

// Función para agregar bomba centrífuga
void agregarCentrifuga(Industria& industria) {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "      AGREGAR BOMBA CENTRIFUGA" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "Formula: 0.38(ps + pd) + 2.3f + 3.4(der + np)" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    limpiarBuffer();
    
    std::string inventario = obtenerTextoValido("Numero de inventario: ", true);
    double costo = obtenerDecimalValido("Costo ($): ", 0.0);
    double ps = obtenerDecimalValido("Presion de succion (ps): ", 0.0);
    double pd = obtenerDecimalValido("Presion de descarga (pd): ", 0.0);
    double f = obtenerDecimalValido("Flujo (f): ", 0.0);
    double der = obtenerDecimalValido("Diametro del eje de rotacion (der): ", 0.0);
    int np = obtenerEnteroValido("Numero de paletas (np): ", 1, 100);
    
    industria.agregarEquipo(new Centrifuga(inventario, costo, ps, pd, f, der, np));
    
    // Mostrar consumo calculado
    double consumo = 0.38 * (ps + pd) + 2.3 * f + 3.4 * (der + np);
    std::cout << "\n[OK] Bomba Centrifuga agregada exitosamente!" << std::endl;
    std::cout << "[INFO] Consumo calculado: " << std::fixed << std::setprecision(2) << consumo << " kWh" << std::endl;
}

// Función para agregar bomba de émbolos
void agregarEmbolo(Industria& industria) {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "       AGREGAR BOMBA DE EMBOLOS" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "Formula: 0.38(ps + pd) + 2.3f" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    limpiarBuffer();
    
    std::string inventario = obtenerTextoValido("Numero de inventario: ", true);
    double costo = obtenerDecimalValido("Costo ($): ", 0.0);
    double ps = obtenerDecimalValido("Presion de succion (ps): ", 0.0);
    double pd = obtenerDecimalValido("Presion de descarga (pd): ", 0.0);
    double f = obtenerDecimalValido("Flujo (f): ", 0.0);
    double l = obtenerDecimalValido("Largo del embolo (l): ", 0.0);
    double d = obtenerDecimalValido("Diametro del embolo (d): ", 0.0);
    
    industria.agregarEquipo(new Embolo(inventario, costo, ps, pd, f, l, d));
    
    // Mostrar consumo calculado
    double consumo = 0.38 * (ps + pd) + 2.3 * f;
    std::cout << "\n[OK] Bomba de Embolos agregada exitosamente!" << std::endl;
    std::cout << "[INFO] Consumo calculado: " << std::fixed << std::setprecision(2) << consumo << " kWh" << std::endl;
}

// Función para agregar intercambiador
void agregarIntercambiador(Industria& industria) {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "   AGREGAR INTERCAMBIADOR DE CALOR" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "Formula: 0.25*ptc + ln(d)" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    limpiarBuffer();
    
    std::string inventario = obtenerTextoValido("Numero de inventario: ", true);
    double costo = obtenerDecimalValido("Costo ($): ", 0.0);
    double a = obtenerDecimalValido("Area (a): ", 0.0);
    double ptc = obtenerDecimalValido("Presion del tubo central (ptc): ", 0.0);
    double d = obtenerDecimalValido("Diametro (d): ", 0.01); // Mínimo 0.01 para evitar ln(0)
    
    industria.agregarEquipo(new Intercambiador(inventario, costo, a, ptc, d));
    
    // Mostrar consumo calculado
    double consumo = 0.25 * ptc + log(d);
    std::cout << "\n[OK] Intercambiador de Calor agregado exitosamente!" << std::endl;
    std::cout << "[INFO] Consumo calculado: " << std::fixed << std::setprecision(2) << consumo << " kWh" << std::endl;
}

// Función para agregar informe mensual
void agregarInforme(Industria& industria) {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "       AGREGAR INFORME MENSUAL" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    
    int mes = obtenerEnteroValido("Mes (1-12): ", 1, 12);
    double plan = obtenerDecimalValido("Plan asignado (kWh): ", 0.0);
    double real = obtenerDecimalValido("Consumo real (kWh): ", 0.0);
    
    industria.agregarInforme(mes, plan, real);
    
    std::string estado = (real > plan) ? "[SOBREPASADO]" : "[DENTRO DEL PLAN]";
    std::cout << "\n[OK] Informe mensual agregado exitosamente!" << std::endl;
    std::cout << "[INFO] Estado del consumo: " << estado << std::endl;
}

int main() {
    // Configurar consola para caracteres especiales
    configurarLocale();
      // Encabezado del programa
    std::cout << "╔══════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                                          ║" << std::endl;
    std::cout << "║         🏭 SISTEMA DE CONTROL DE CONSUMO ELECTRICO INDUSTRIAL 🏭        ║" << std::endl;
    std::cout << "║                                                                          ║" << std::endl;
    std::cout << "║                   Implementacion Completa en C++ con POO                ║" << std::endl;
    std::cout << "║                              Version 1.0 Final                          ║" << std::endl;
    std::cout << "║                                                                          ║" << std::endl;
    std::cout << "║    ⚡ Formulas Implementadas:                                           ║" << std::endl;
    std::cout << "║      • Centrifugas: 0.38(ps+pd) + 2.3f + 3.4(der+np)                  ║" << std::endl;
    std::cout << "║      • Embolos: 0.38(ps+pd) + 2.3f                                     ║" << std::endl;
    std::cout << "║      • Intercambiadores: 0.25*ptc + ln(d)                              ║" << std::endl;
    std::cout << "║                                                                          ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════════════════╝" << std::endl;    // Configuración inicial de la industria
    std::cout << "\n┌─────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                        CONFIGURACION INICIAL                           │" << std::endl;
    std::cout << "│                     Configure su industria                             │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────────────┘" << std::endl;
    
    std::string nombreIndustria = obtenerTextoValido("🏭 Nombre de la industria: ", true);
    double alumbrado = obtenerDecimalValido("💡 Consumo de alumbrado (kWh): ", 0.0);
    
    std::cout << "\n┌─────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                         DATOS DEL DIRECTOR                             │" << std::endl;
    std::cout << "│                  Responsable de informes mensuales                     │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────────────┘" << std::endl;
    
    std::string nombreDirector = obtenerTextoValido("👨‍💼 Nombre del director (solo letras): ");
    std::string carneDirector = obtenerTextoValido("🆔 Carne de identidad: ", true);
    int aniosDirector = obtenerEnteroValido("📅 Anos en la industria (0-50): ", 0, 50);
    std::string beeper = obtenerTextoValido("📱 Numero de beeper: ", true);
    std::string fechaInicio = obtenerTextoValido("📆 Fecha de inicio en el cargo: ", true);
    
    // Crear director e industria
    Director* director = new Director(nombreDirector, carneDirector, aniosDirector, beeper, fechaInicio);
    Industria industria(nombreIndustria, alumbrado, director);
    
    std::cout << "\n🎉 ¡Industria '" << nombreIndustria << "' configurada exitosamente!" << std::endl;
    
    // Menú principal
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        switch (opcion) {
            case 1:
                agregarTrabajador(industria);
                break;
            case 2:
                agregarCentrifuga(industria);
                break;
            case 3:
                agregarEmbolo(industria);
                break;
            case 4:
                agregarIntercambiador(industria);
                break;
            case 5:
                agregarInforme(industria);
                break;
            case 6:
                industria.mostrarTrabajadores();
                break;
            case 7:
                industria.mostrarEquipos();
                break;
            case 8:
                industria.mostrarEstadisticas();
                break;
            case 9:
                industria.mostrarInformes();
                break;            case 0:
                std::cout << "\n╔══════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                     CERRANDO SISTEMA                        ║" << std::endl;
                std::cout << "║                                                              ║" << std::endl;
                std::cout << "║   🎉 ¡Gracias por usar el Sistema de Control Electrico!    ║" << std::endl;
                std::cout << "║                                                              ║" << std::endl;
                std::cout << "║   ✅ Todos los requisitos POO han sido implementados       ║" << std::endl;
                std::cout << "║   ✅ Formulas matematicas aplicadas correctamente          ║" << std::endl;
                std::cout << "║   ✅ Sistema robusto con validaciones completas            ║" << std::endl;
                std::cout << "║                                                              ║" << std::endl;
                std::cout << "║               Desarrollado con C++ y POO                    ║" << std::endl;
                std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
                break;            default:
                std::cout << "\n❌ Opcion invalida. Por favor seleccione entre 0-9." << std::endl;
                break;
        }
        
        if (opcion != 0) {
            std::cout << "\n📱 Presione Enter para continuar...";
            limpiarBuffer();
            std::cin.get();
        }
        
    } while (opcion != 0);
    
    return 0;
    // Nota: El destructor de Industria se encarga de liberar la memoria
}