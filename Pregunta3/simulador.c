#include "simulador.h"
#include <stdlib.h>

Tipo tipos[MAX_TIPOS]; // Lista de tipos definidos
int num_tipos = 0; // Contador de tipos definidos

// Buscar un tipo por nombre
int buscar_tipo(const char *nombre) {
    for (int i = 0; i < num_tipos; i++) {
        if ((tipos[i].tipo == ATOMICO && strcmp(tipos[i].definicion.atomico.nombre, nombre) == 0) ||
            (tipos[i].tipo != ATOMICO && strcmp(tipos[i].definicion.compuesto.nombre, nombre) == 0)) {
            return i;
        }
    }
    return -1;
}

// Definir un tipo atómico
void definir_atomico(char *nombre, int tamano, int alineacion) {
    if (buscar_tipo(nombre) != -1) {
        printf("Error: Tipo '%s' ya definido.\n", nombre);
        return;
    }

    Tipo nuevo_tipo;
    nuevo_tipo.tipo = ATOMICO;
    strcpy(nuevo_tipo.definicion.atomico.nombre, nombre);
    nuevo_tipo.definicion.atomico.tamano = tamano;
    nuevo_tipo.definicion.atomico.alineacion = alineacion;

    tipos[num_tipos++] = nuevo_tipo;
    printf("Tipo atómico '%s' definido.\n", nombre);
}

// Calcular el tamaño de un struct
int calcular_tamano_struct(char componentes[MAX_COMPONENTES][50], int num_componentes, int *alineacion_max) {
    int tamano_total = 0;
    *alineacion_max = 1;

    for (int i = 0; i < num_componentes; i++) {
        int idx = buscar_tipo(componentes[i]);
        if (idx == -1) {
            printf("Error: Tipo '%s' no definido.\n", componentes[i]);
            return -1;
        }

        Tipo tipo = tipos[idx];
        int tamano = tipo.definicion.atomico.tamano;
        int alineacion = tipo.definicion.atomico.alineacion;

        if (tamano_total % alineacion != 0) {
            tamano_total += alineacion - (tamano_total % alineacion);
        }

        tamano_total += tamano;

        if (alineacion > *alineacion_max) {
            *alineacion_max = alineacion;
        }
    }

    if (tamano_total % *alineacion_max != 0) {
        tamano_total += *alineacion_max - (tamano_total % *alineacion_max);
    }

    return tamano_total;
}

// Calcular el tamaño de una union
int calcular_tamano_union(char componentes[MAX_COMPONENTES][50], int num_componentes, int *alineacion_max) {
    int tamano_max = 0;
    *alineacion_max = 1;

    for (int i = 0; i < num_componentes; i++) {
        int idx = buscar_tipo(componentes[i]);
        if (idx == -1) {
            printf("Error: Tipo '%s' no definido.\n", componentes[i]);
            return -1;
        }

        Tipo tipo = tipos[idx];
        int tamano = tipo.definicion.atomico.tamano;
        int alineacion = tipo.definicion.atomico.alineacion;

        if (tamano > tamano_max) {
            tamano_max = tamano;
        }

        if (alineacion > *alineacion_max) {
            *alineacion_max = alineacion;
        }
    }

    if (tamano_max % *alineacion_max != 0) {
        tamano_max += *alineacion_max - (tamano_max % *alineacion_max);
    }

    return tamano_max;
}

// Definir un struct o union
void definir_compuesto(char *nombre, char *componentes[], int num_componentes, TipoDef tipo) {
    if (buscar_tipo(nombre) != -1) {
        printf("Error: Tipo '%s' ya definido.\n", nombre);
        return;
    }

    for (int i = 0; i < num_componentes; i++) {
        if (buscar_tipo(componentes[i]) == -1) {
            printf("Error: Tipo '%s' no definido.\n", componentes[i]);
            return;
        }
    }

    Tipo nuevo_tipo;
    nuevo_tipo.tipo = tipo;
    strcpy(nuevo_tipo.definicion.compuesto.nombre, nombre);
    nuevo_tipo.definicion.compuesto.num_componentes = num_componentes;

    for (int i = 0; i < num_componentes; i++) {
        strcpy(nuevo_tipo.definicion.compuesto.componentes[i], componentes[i]);
    }

    tipos[num_tipos++] = nuevo_tipo;
    printf("Tipo %s '%s' definido.\n", tipo == STRUCT ? "struct" : "union", nombre);
}

// Describir un tipo
void describir_tipo(char *nombre) {
    int idx = buscar_tipo(nombre);
    if (idx == -1) {
        printf("Error: Tipo '%s' no definido.\n", nombre);
        return;
    }

    Tipo tipo = tipos[idx];
    if (tipo.tipo == ATOMICO) {
        printf("Tipo: ATOMICO\n");
        printf("Nombre: %s\n", tipo.definicion.atomico.nombre);
        printf("Tamaño: %d bytes\n", tipo.definicion.atomico.tamano);
        printf("Alineación: %d bytes\n", tipo.definicion.atomico.alineacion);
    } else {
        int tamano_total, alineacion_max;
        if (tipo.tipo == STRUCT) {
            tamano_total = calcular_tamano_struct(tipo.definicion.compuesto.componentes,
                                                  tipo.definicion.compuesto.num_componentes, &alineacion_max);
            printf("Tipo: STRUCT\n");
        } else { // UNION
            tamano_total = calcular_tamano_union(tipo.definicion.compuesto.componentes,
                                                 tipo.definicion.compuesto.num_componentes, &alineacion_max);
            printf("Tipo: UNION\n");
        }

        printf("Nombre: %s\n", tipo.definicion.compuesto.nombre);
        printf("Tamaño total: %d bytes\n", tamano_total);
        printf("Alineación: %d bytes\n", alineacion_max);
    }
}

// Procesar comandos del usuario
void procesar_comando(char *comando) {
    char accion[50], nombre[50], componentes[500];
    int tamano, alineacion;
    char *tokens[MAX_COMPONENTES];
    int num_tokens;

    if (sscanf(comando, "ATOMICO %s %d %d", nombre, &tamano, &alineacion) == 3) {
        definir_atomico(nombre, tamano, alineacion);
    } else if (sscanf(comando, "STRUCT %s %[^\n]", nombre, componentes) == 2) {
        num_tokens = 0;
        tokens[num_tokens] = strtok(componentes, " ");
        while (tokens[num_tokens] != NULL) {
            tokens[++num_tokens] = strtok(NULL, " ");
        }
        definir_compuesto(nombre, tokens, num_tokens, STRUCT);
    } else if (sscanf(comando, "UNION %s %[^\n]", nombre, componentes) == 2) {
        num_tokens = 0;
        tokens[num_tokens] = strtok(componentes, " ");
        while (tokens[num_tokens] != NULL) {
            tokens[++num_tokens] = strtok(NULL, " ");
        }
        definir_compuesto(nombre, tokens, num_tokens, UNION);
    } else if (sscanf(comando, "DESCRIBIR %s", nombre) == 1) {
        describir_tipo(nombre);
    } else if (strcmp(comando, "SALIR") == 0) {
        exit(0);
    } else {
        printf("Comando no reconocido.\n");
    }
}

int main() {
    char comando[512];

    printf("Simulador de Tipos de Datos\n");
    while (1) {
        printf("\n");
        fgets(comando, 512, stdin);
        comando[strcspn(comando, "\n")] = '\0'; // Eliminar salto de línea
        procesar_comando(comando);
    }

    return 0;
}

