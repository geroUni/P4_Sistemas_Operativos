#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

#define MAX_LONGITUD_LINEA 100

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    // Abrir archivo de entrada
    FILE *archivo_entrada = fopen(argv[1], "r");
    if (archivo_entrada == NULL) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    // Abrir archivo de salida
    FILE *archivo_salida = fopen(argv[2], "w");
    if (archivo_salida == NULL) {
        perror("Error al abrir el archivo de salida");
        fclose(archivo_entrada);
        return 1;
    }

    // Procesar cada rompecabezas de Sudoku del archivo de entrada
    char linea[MAX_LONGITUD_LINEA];
    while (fgets(linea, sizeof(linea), archivo_entrada) != NULL) {
        // Convertir la línea del archivo en un rompecabezas de Sudoku
        int rompecabezas[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                rompecabezas[i][j] = linea[i * N + j] - '0';
            }
        }

        // Resolver el rompecabezas de Sudoku
        sudoku_solve(rompecabezas, 0, 0);

        // Escribir la solución en el archivo de salida
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fprintf(archivo_salida, "%d", rompecabezas[i][j]);
            }
        }
        fprintf(archivo_salida, "\n");
    }

    // Cerrar archivos
    fclose(archivo_entrada);
    fclose(archivo_salida);

    printf("Se han resuelto los rompecabezas de Sudoku correctamente.\n");

    return 0;
}
