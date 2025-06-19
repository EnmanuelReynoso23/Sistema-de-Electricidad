#include "GraficosAvanzados.h"

// Implementar gráfico de barras horizontales
void GraficosAvanzados::graficoBarrasHorizontales(const std::vector<DatoGrafico>& datos, 
                                                 const std::string& titulo, 
                                                 int ancho_maximo) {
    imprimirTitulo(titulo);
    
    if (datos.empty()) {
        std::cout << "No hay datos para mostrar" << std::endl;
        return;
    }
    
    // Encontrar el valor máximo para escalar
    double valor_max = 0;
    for (const auto& dato : datos) {
        if (dato.valor > valor_max) valor_max = dato.valor;
    }
    
    if (valor_max == 0) valor_max = 1; // Evitar división por cero
    
    // Mostrar barras
    for (const auto& dato : datos) {
        int longitud_barra = static_cast<int>((dato.valor / valor_max) * ancho_maximo);
        
        // Imprimir etiqueta
        std::cout << std::left << std::setw(20) << dato.etiqueta.substr(0, 19) << " |";
        
        // Imprimir barra con color
        char caracter_barra = obtenerCaracterBarra(dato.color);
        for (int i = 0; i < longitud_barra; ++i) {
            std::cout << caracter_barra;
        }
        
        // Imprimir valor
        std::cout << " " << std::fixed << std::setprecision(2) << dato.valor;
        std::cout << std::endl;
    }
    
    std::cout << std::string(80, '-') << std::endl;
}

// Implementar gráfico de barras verticales
void GraficosAvanzados::graficoBarrasVerticales(const std::vector<DatoGrafico>& datos, 
                                               const std::string& titulo, 
                                               int altura_maxima) {
    imprimirTitulo(titulo);
    
    if (datos.empty()) {
        std::cout << "No hay datos para mostrar" << std::endl;
        return;
    }
    
    // Encontrar el valor máximo
    double valor_max = 0;
    for (const auto& dato : datos) {
        if (dato.valor > valor_max) valor_max = dato.valor;
    }
    
    if (valor_max == 0) valor_max = 1;
    
    // Imprimir gráfico de arriba hacia abajo
    for (int nivel = altura_maxima; nivel >= 0; --nivel) {
        double umbral = (static_cast<double>(nivel) / altura_maxima) * valor_max;
        
        for (const auto& dato : datos) {
            if (dato.valor >= umbral && nivel > 0) {
                std::cout << obtenerCaracterBarra(dato.color) << " ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    
    // Imprimir base
    for (size_t i = 0; i < datos.size(); ++i) {
        std::cout << "--";
    }
    std::cout << std::endl;
    
    // Imprimir etiquetas
    for (const auto& dato : datos) {
        std::cout << dato.etiqueta.substr(0, 1) << " ";
    }
    std::cout << std::endl;
    
    // Imprimir valores
    for (const auto& dato : datos) {
        std::cout << std::fixed << std::setprecision(0) << dato.valor << " ";
    }
    std::cout << std::endl << std::string(80, '-') << std::endl;
}

// Implementar gráfico circular (pie chart)
void GraficosAvanzados::graficoCircular(const std::vector<DatoGrafico>& datos, 
                                       const std::string& titulo) {
    imprimirTitulo(titulo);
    
    if (datos.empty()) {
        std::cout << "No hay datos para mostrar" << std::endl;
        return;
    }
    
    // Calcular total
    double total = 0;
    for (const auto& dato : datos) {
        total += dato.valor;
    }
    
    if (total == 0) {
        std::cout << "Total de datos es cero" << std::endl;
        return;
    }
    
    std::cout << "        DISTRIBUCIÓN CIRCULAR" << std::endl;
    std::cout << "    ╭─────────────────────────╮" << std::endl;
    
    // Dibujar círculo simple con caracteres ASCII
    const std::vector<std::string> circulo = {
        "  ╭─────────────────────╮  ",
        " ╱                     ╲ ",
        "╱                       ╲",
        "│                       │",
        "│         PIE           │",
        "│        CHART          │",
        "│                       │",
        "╲                       ╱",
        " ╲_____________________╱ ",
        "  ╰─────────────────────╯  "
    };
    
    for (const auto& linea : circulo) {
        std::cout << linea << std::endl;
    }
    
    // Mostrar porcentajes
    std::cout << "\nDISTRIBUCIÓN PORCENTUAL:" << std::endl;
    for (const auto& dato : datos) {
        double porcentaje = (dato.valor / total) * 100.0;
        char simbolo = obtenerCaracterBarra(dato.color);
        
        std::cout << simbolo << " " << std::left << std::setw(15) << dato.etiqueta 
                  << " " << std::right << std::setw(6) << std::fixed << std::setprecision(1) 
                  << porcentaje << "%" << std::endl;
    }
    std::cout << std::string(80, '-') << std::endl;
}

// Implementar gráfico de líneas
void GraficosAvanzados::graficoLineas(const std::vector<DatoGrafico>& datos, 
                                     const std::string& titulo, 
                                     int ancho, int altura) {
    imprimirTitulo(titulo);
    
    if (datos.empty()) {
        std::cout << "No hay datos para mostrar" << std::endl;
        return;
    }
    
    // Encontrar valores mín y máx
    double valor_min = datos[0].valor;
    double valor_max = datos[0].valor;
    
    for (const auto& dato : datos) {
        if (dato.valor < valor_min) valor_min = dato.valor;
        if (dato.valor > valor_max) valor_max = dato.valor;
    }
    
    if (valor_max == valor_min) valor_max = valor_min + 1;
    
    // Crear matriz para el gráfico
    std::vector<std::vector<char>> matriz(altura, std::vector<char>(ancho, ' '));
    
    // Dibujar ejes
    for (int i = 0; i < altura; ++i) {
        matriz[i][0] = '|';
    }
    for (int j = 0; j < ancho; ++j) {
        matriz[altura - 1][j] = '-';
    }
    matriz[altura - 1][0] = '+';
    
    // Plotear puntos
    for (size_t i = 0; i < datos.size() && i < static_cast<size_t>(ancho - 1); ++i) {
        int x = static_cast<int>(i + 1);
        double valor_normalizado = (datos[i].valor - valor_min) / (valor_max - valor_min);
        int y = altura - 2 - static_cast<int>(valor_normalizado * (altura - 2));
        
        if (x < ancho && y >= 0 && y < altura - 1) {
            matriz[y][x] = '*';
        }
        
        // Conectar con línea si hay punto anterior
        if (i > 0) {
            double valor_ant_norm = (datos[i-1].valor - valor_min) / (valor_max - valor_min);
            int y_ant = altura - 2 - static_cast<int>(valor_ant_norm * (altura - 2));
            
            // Dibujar línea simple entre puntos
            int x_ant = static_cast<int>(i);
            if (y != y_ant) {
                int step = (y > y_ant) ? 1 : -1;
                for (int temp_y = y_ant + step; temp_y != y; temp_y += step) {
                    if (temp_y >= 0 && temp_y < altura - 1 && x_ant < ancho) {
                        matriz[temp_y][x_ant] = '|';
                    }
                }
            }
        }
    }
    
    // Imprimir matriz
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < ancho; ++j) {
            std::cout << matriz[i][j];
        }
        
        // Etiquetas del eje Y
        if (i == 0) {
            std::cout << "  " << std::fixed << std::setprecision(1) << valor_max;
        } else if (i == altura - 1) {
            std::cout << "  " << std::fixed << std::setprecision(1) << valor_min;
        }
        std::cout << std::endl;
    }
    
    std::cout << std::string(80, '-') << std::endl;
}

// Implementar histograma de consumo
void GraficosAvanzados::histogramaConsumo(const std::vector<double>& consumos_mensuales, 
                                          const std::string& titulo) {
    std::vector<DatoGrafico> datos;
    std::vector<std::string> meses = {
        "Ene", "Feb", "Mar", "Abr", "May", "Jun",
        "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"
    };
    
    std::vector<std::string> colores = {"rojo", "verde", "azul", "amarillo", "magenta", "cyan"};
    
    for (size_t i = 0; i < consumos_mensuales.size() && i < 12; ++i) {
        std::string color = colores[i % colores.size()];
        datos.emplace_back(meses[i], consumos_mensuales[i], color);
    }
    
    graficoBarrasHorizontales(datos, titulo + " - HISTOGRAMA MENSUAL", 40);
}

// Implementar dashboard completo
void GraficosAvanzados::dashboardCompleto(const std::vector<DatoGrafico>& equipos,
                                         const std::vector<DatoGrafico>& trabajadores,
                                         const std::vector<double>& consumos_mensuales) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                         📊 DASHBOARD INDUSTRIAL COMPLETO                    ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    
    // Gráfico de equipos
    if (!equipos.empty()) {
        graficoBarrasHorizontales(equipos, "🔧 CONSUMO POR EQUIPOS", 50);
        std::cout << std::endl;
    }
    
    // Gráfico circular de distribución
    if (!equipos.empty()) {
        graficoCircular(equipos, "📊 DISTRIBUCIÓN DE CONSUMO");
        std::cout << std::endl;
    }
    
    // Histograma de consumos mensuales
    if (!consumos_mensuales.empty()) {
        histogramaConsumo(consumos_mensuales, "📅 TENDENCIA TEMPORAL");
        std::cout << std::endl;
    }
    
    // Gráfico de barras verticales para trabajadores
    if (!trabajadores.empty()) {
        graficoBarrasVerticales(trabajadores, "👥 EXPERIENCIA DE TRABAJADORES", 15);
    }
    
    std::cout << "\n🎯 RESUMEN EJECUTIVO:" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    
    if (!equipos.empty()) {
        double total_consumo = 0;
        for (const auto& equipo : equipos) {
            total_consumo += equipo.valor;
        }
        std::cout << "⚡ Consumo Total: " << std::fixed << std::setprecision(2) << total_consumo << " kWh" << std::endl;
        std::cout << "🔧 Equipos Monitoreados: " << equipos.size() << " unidades" << std::endl;
    }
    
    if (!trabajadores.empty()) {
        std::cout << "👥 Personal Registrado: " << trabajadores.size() << " trabajadores" << std::endl;
    }
    
    if (!consumos_mensuales.empty()) {
        double promedio_mensual = 0;
        for (double consumo : consumos_mensuales) {
            promedio_mensual += consumo;
        }
        promedio_mensual /= consumos_mensuales.size();
        std::cout << "📊 Consumo Promedio Mensual: " << std::fixed << std::setprecision(2) << promedio_mensual << " kWh" << std::endl;
    }
    
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

// Funciones auxiliares
void GraficosAvanzados::imprimirTitulo(const std::string& titulo) {
    int longitud = titulo.length();
    int padding = (80 - longitud - 4) / 2;
    
    std::cout << "\n";
    std::cout << std::string(80, '═') << std::endl;
    std::cout << std::string(padding, ' ') << "📊 " << titulo << " 📊" << std::endl;
    std::cout << std::string(80, '═') << std::endl;
}

void GraficosAvanzados::imprimirLeyenda(const std::vector<DatoGrafico>& datos) {
    std::cout << "\nLEYENDA:" << std::endl;
    for (const auto& dato : datos) {
        char simbolo = obtenerCaracterBarra(dato.color);
        std::cout << simbolo << " = " << dato.etiqueta << std::endl;
    }
}

std::string GraficosAvanzados::colorTexto(int color, const std::string& texto) {
    return "\033[" + std::to_string(color) + "m" + texto + "\033[0m";
}

char GraficosAvanzados::obtenerCaracterBarra(const std::string& color) {
    if (color == "rojo") return '█';
    else if (color == "verde") return '▓';
    else if (color == "azul") return '▒';
    else if (color == "amarillo") return '░';
    else if (color == "magenta") return '■';
    else if (color == "cyan") return '▪';
    else return '█'; // Por defecto
}