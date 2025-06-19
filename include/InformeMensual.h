#ifndef INFORME_MENSUAL_H
#define INFORME_MENSUAL_H

// Estructura para almacenar datos de informes mensuales
struct InformeMensual {
    int mes;       // Mes del año (1-12)
    double plan;   // Plan de consumo asignado
    double real;   // Consumo real registrado
    double min;    // Mínimo consumo del año hasta la fecha
    double max;    // Máximo consumo del año hasta la fecha
    
    // Constructor para inicializar todos los campos
    InformeMensual(int m, double p, double r, double mn, double mx)
        : mes(m), plan(p), real(r), min(mn), max(mx) {}
};

#endif // INFORME_MENSUAL_H
