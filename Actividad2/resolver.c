#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    // Abrir archivo de entrada
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    // Abrir archivo de salida
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        perror("Error al abrir el archivo de salida");
        fclose(input_file);
        return 1;
    }

    // Procesar cada rompecabezas de Sudoku del archivo de entrada
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), input_file) != NULL) {
        // Convertir la línea del archivo en un rompecabezas de Sudoku
        int puzzle[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                puzzle[i][j] = line[i * N + j] - '0';
            }
        }

        // Resolver el rompecabezas de Sudoku
        sudoku_solve(puzzle, 0, 0);

        // Escribir la solución en el archivo de salida
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fprintf(output_file, "%d", puzzle[i][j]);
            }
        }
        fprintf(output_file, "\n");
    }

    // Cerrar archivos
    fclose(input_file);
    fclose(output_file);

    printf("Se han resuelto los rompecabezas de Sudoku correctamente.\n");

    return 0;
}
