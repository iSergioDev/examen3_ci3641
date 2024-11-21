#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <stdio.h>
#include <string.h>

#define MAX_TIPOS 100
#define MAX_COMPONENTES 10

typedef enum { ATOMICO, STRUCT, UNION } TipoDef;

typedef struct {
    char nombre[50];
    int tamano;
    int alineacion;
} TipoAtomico;

typedef struct {
    char nombre[50];
    int num_componentes;
    char componentes[MAX_COMPONENTES][50];
} TipoCompuesto;

typedef struct {
    TipoDef tipo;
    union {
        TipoAtomico atomico;
        TipoCompuesto compuesto;
    } definicion;
} Tipo;

extern Tipo tipos[MAX_TIPOS]; // Lista de tipos definidos
extern int num_tipos;

// Declaraciones de funciones
int buscar_tipo(const char *nombre);
void definir_atomico(char *nombre, int tamano, int alineacion);
int calcular_tamano_struct(char componentes[MAX_COMPONENTES][50], int num_componentes, int *alineacion_max);
int calcular_tamano_union(char componentes[MAX_COMPONENTES][50], int num_componentes, int *alineacion_max);
void definir_compuesto(char *nombre, char *componentes[], int num_componentes, TipoDef tipo);
void describir_tipo(char *nombre);
void procesar_comando(char *comando);

#endif // SIMULADOR_H

