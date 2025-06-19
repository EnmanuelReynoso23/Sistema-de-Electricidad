#ifndef GRAFICOS_AVANZADOS_H
#define GRAFICOS_AVANZADOS_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

// Librería de gráficos avanzados para visualización de datos
class GraficosAvanzados {
public:
    // Estructura para almacenar datos de gráficos
    struct DatoGrafico {
        std::string etiqueta;
        double valor;
        std::string color;
        
        DatoGrafico(const std::string& e, double v, const std::string& c = "blue") 
            : etiqueta(e), valor(v), color(c) {}
    };
    
    // Colores disponibles para los gráficos
    enum Color {
        ROJO = 31,
        VERDE = 32,
        AMARILLO = 33,
        AZUL = 34,
        MAGENTA = 35,
        CYAN = 36,
        BLANCO = 37
    };
    
    // Generar gráfico de barras horizontales
    static void graficoBarrasHorizontales(const std::vector<DatoGrafico>& datos, 
                                         const std::string& titulo, 
                                         int ancho_maximo = 50);
    
    // Generar gráfico de barras verticales
    static void graficoBarrasVerticales(const std::vector<DatoGrafico>& datos, 
                                       const std::string& titulo, 
                                       int altura_maxima = 20);
    
    // Generar gráfico circular (pie chart) ASCII
    static void graficoCircular(const std::vector<DatoGrafico>& datos, 
                               const std::string& titulo);
    
    // Generar gráfico de líneas
    static void graficoLineas(const std::vector<DatoGrafico>& datos, 
                             const std::string& titulo, 
                             int ancho = 60, int altura = 15);
    
    // Generar histograma de consumo por meses
    static void histogramaConsumo(const std::vector<double>& consumos_mensuales, 
                                  const std::string& titulo);
    
    // Generar dashboard completo
    static void dashboardCompleto(const std::vector<DatoGrafico>& equipos,
                                 const std::vector<DatoGrafico>& trabajadores,
                                 const std::vector<double>& consumos_mensuales);
    
    // Funciones auxiliares
    static void imprimirTitulo(const std::string& titulo);
    static void imprimirLeyenda(const std::vector<DatoGrafico>& datos);
    static std::string colorTexto(int color, const std::string& texto);
    static char obtenerCaracterBarra(const std::string& color);
};

#endif // GRAFICOS_AVANZADOS_H