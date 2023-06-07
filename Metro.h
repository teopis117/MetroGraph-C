#ifndef METRO_H
#define METRO_H
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "metro.h"
#include <stdbool.h>

typedef struct Estacion {
    char* nombre;
    bool visitado;
    int distancia;
    struct Estacion* previo;
    int num_conexiones;
    struct Estacion** conexion;
    struct Estacion** conexiones;
} Estacion;

typedef struct Linea {
    int num_Estaciones;
    Estacion** estaciones;
} Linea;

typedef struct RedMetro {
    int num_Lineas;
    Linea** lineas;
} RedMetro;

void liberar_red_metro(RedMetro* redMetro) {
    if (redMetro == NULL) {
        return;
    }

    for (int i = 0; i < redMetro->num_Lineas; i++) {
        Linea* linea = redMetro->lineas[i];
        if (linea != NULL) {
            for (int j = 0; j < linea->num_Estaciones; j++) {
                Estacion* estacion = linea->estaciones[j];
                if (estacion != NULL) {
                    free(estacion->nombre);
                    free(estacion->conexiones);
                    free(estacion);
                }
            }
            free(linea->estaciones);
            free(linea);
        }
    }

    free(redMetro->lineas);
    free(redMetro);
}

RedMetro* crear_red_metro(int num_Lineas) {
    RedMetro* redMetro = (RedMetro *)malloc(sizeof(RedMetro));
    redMetro->num_Lineas = num_Lineas;
    redMetro->lineas = (Linea **)malloc(num_Lineas * sizeof(Linea *));
    return redMetro;
}

Linea* crear_linea(int num_Estaciones) {
    Linea* linea = (Linea *)malloc(sizeof(Linea));
    linea->num_Estaciones = num_Estaciones;
    linea->estaciones = (Estacion **)malloc(num_Estaciones * sizeof(Estacion *));
    return linea;
}

Estacion* crear_estacion(char* nombre) {
    Estacion* estacion = (Estacion *)malloc(sizeof(Estacion));
    estacion->nombre = strdup(nombre);
    estacion->visitado = false;
    estacion->distancia = INT_MAX;
    estacion->previo = NULL;
    estacion->num_conexiones = 0;
    estacion->conexiones = NULL;
    return estacion;
}

void agregar_conexion(Estacion* estacion1, Estacion* estacion2) {
    estacion1->num_conexiones++;
    estacion1->conexiones = (Estacion **)realloc(estacion1->conexiones, estacion1->num_conexiones * sizeof(Estacion *));
    estacion1->conexiones[estacion1->num_conexiones - 1] = estacion2;

    estacion2->num_conexiones++;
    estacion2->conexiones = (Estacion **)realloc(estacion2->conexiones, estacion2->num_conexiones * sizeof(Estacion *));
    estacion2->conexiones[estacion2->num_conexiones - 1] = estacion1;
}

Estacion** obtener_todas_estaciones(RedMetro* redMetro, int* totalEstaciones) {
    int i, j;
    *totalEstaciones = 0;
    for (i = 0; i < redMetro->num_Lineas; i++) {
        *totalEstaciones += redMetro->lineas[i]->num_Estaciones;
    }

    Estacion** todasEstaciones = (Estacion *)malloc(*totalEstaciones * sizeof(Estacion));
    int k = 0;
    for (i = 0; i < redMetro->num_Lineas; i++) {
        for (j = 0; j < redMetro->lineas[i]->num_Estaciones; j++) {
            todasEstaciones[k] = redMetro->lineas[i]->estaciones[j];
            k++;
        }

    for (int i = 0; i < redMetro->num_Lineas; i++) {
        Linea* linea = redMetro->lineas[i];
        if (linea != NULL) {
            for (int j = 0; j < linea->num_Estaciones; j++) {
                Estacion* estacion = linea->estaciones[j];
                if (estacion != NULL) {
                    free(estacion->nombre);
                    free(estacion->conexiones);
                    free(estacion);
                }
                }
                }}
                }}
void dijkstra(RedMetro* redMetro, Estacion* origen, Estacion* destino) {
    int i, j;
    int totalEstaciones;
    Estacion** todasEstaciones = obtener_todas_estaciones(redMetro, &totalEstaciones);

    origen->distancia = 0;

    for (i = 0; i < totalEstaciones; i++) {
        Estacion* estacionActual = NULL;
        int distanciaMinima = INT_MAX;

        for (j = 0; j < totalEstaciones; j++) {
            if (!todasEstaciones[j]->visitado && todasEstaciones[j]->distancia <= distanciaMinima) {
                distanciaMinima = todasEstaciones[j]->distancia;
                estacionActual = todasEstaciones[j];
            }
        }

        estacionActual->visitado = true;

        for (j = 0; j < estacionActual->num_conexiones; j++) {
            Estacion* estacionAdyacente = estacionActual->conexiones[j];
            if (!estacionAdyacente->visitado && estacionAdyacente->distancia > estacionActual->distancia + 1) {
                estacionAdyacente->distancia = estacionActual->distancia + 1;
                estacionAdyacente->previo = estacionActual;
            }
        }
    }

    free(todasEstaciones);
}


RedMetro* crear_red_metro(int num_Lineas);
Linea* crear_linea(int num_Estaciones);
Estacion* crear_estacion(char* nombre);
void agregar_conexion(Estacion* estacion1, Estacion* estacion2);
Estacion** obtener_todas_estaciones(RedMetro* redMetro, int* totalEstaciones);
void dijkstra(RedMetro* redMetro, Estacion* inicio, Estacion* destino);
Estacion* estacion_minima_distancia(Estacion** estaciones, int num_Estaciones);
Estacion** obtener_ruta(Estacion* destino, int* numEstacionesRuta);
void liberar_red_metro(RedMetro* redMetro);



#endif // METRO_H