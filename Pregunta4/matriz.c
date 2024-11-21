#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 1000000

// Función para recorrer la matriz por fila y luego por columna
void recorrer_por_filas(int **matriz, int N, int M) {
    long suma = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            suma += matriz[i][j];
        }
    }
}

// Función para recorrer la matriz por columna y luego por fila
void recorrer_por_columnas(int **matriz, int N, int M) {
    long suma = 0;
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            suma += matriz[i][j];
        }
    }
}

// Función para medir el tiempo de ejecución de una operación
double medir_tiempo(void (*func)(int**, int, int), int **matriz, int N, int M) {
    clock_t start, end;
    start = clock();
    func(matriz, N, M);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC; // Tiempo en segundos
}

// Función para generar una matriz aleatoria de tamaño N x M
int** generar_matriz(int N, int M) {
    int **matriz = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matriz[i] = malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            matriz[i][j] = rand() % 100;  // Llenar la matriz con números aleatorios entre 0 y 99
        }
    }
    return matriz;
}

// Función para liberar la memoria de la matriz
void liberar_matriz(int **matriz, int N) {
    for (int i = 0; i < N; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main() {
    // Definir los tamaños de las matrices N x M
    int tamanos[] = {100, 1000, 10000};
    int num_pruebas = sizeof(tamanos) / sizeof(tamanos[0]);

    // Variable para almacenar los tiempos de ejecución
    double tiempo_filas, tiempo_columnas;

    // Medir los tiempos para cada combinación de N x M
    for (int i = 0; i < num_pruebas; i++) {
        int N = tamanos[i];
        int M = tamanos[i];

        printf("Ejecutando prueba para matriz de tamaño %d x %d...\n", N, M);

        // Generar la matriz
        int **matriz = generar_matriz(N, M);

        // Ejecutar la prueba 3 veces y obtener el promedio de los tiempos
        double tiempo_total_filas = 0;
        double tiempo_total_columnas = 0;

        for (int j = 0; j < 3; j++) {
            tiempo_total_filas += medir_tiempo(recorrer_por_filas, matriz, N, M);
            tiempo_total_columnas += medir_tiempo(recorrer_por_columnas, matriz, N, M);
        }

        printf("Tiempo promedio para recorrer por filas: %.6f segundos\n", tiempo_total_filas / 3);
        printf("Tiempo promedio para recorrer por columnas: %.6f segundos\n", tiempo_total_columnas / 3);

        // Liberar la memoria de la matriz
        liberar_matriz(matriz, N);
    }

    return 0;
}
