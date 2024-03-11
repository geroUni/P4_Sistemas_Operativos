#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

#define MAX_LONGITUD_LINEA 100

int main(int argc, char *argv[]) {
    // Verifica si se proporcionan los argumentos correctos en la línea de comandos
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    // Abre el archivo de entrada
    FILE *archivo_entrada = fopen(argv[1], "r");
    // Verifica si hubo un error al abrir el archivo de entrada
    if (archivo_entrada == NULL) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    // Abre el archivo de salida
    FILE *archivo_salida = fopen(argv[2], "w");
    // Verifica si hubo un error al abrir el archivo de salida
    if (archivo_salida == NULL) {
        perror("Error al abrir el archivo de salida");
        fclose(archivo_entrada);
        return 1;
    }

    // Procesa cada rompecabezas de Sudoku del archivo de entrada
    char linea[MAX_LONGITUD_LINEA];
    while (fgets(linea, sizeof(linea), archivo_entrada) != NULL) {
        // Convierte la línea del archivo en un rompecabezas de Sudoku
        int rompecabezas[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                rompecabezas[i][j] = linea[i * N + j] - '0';
            }
        }

        // Resuelve el rompecabezas de Sudoku
        sudoku_solve(rompecabezas, 0, 0);

        // Escribe la solución en el archivo de salida
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fprintf(archivo_salida, "%d", rompecabezas[i][j]);
            }
        }
        fprintf(archivo_salida, "\n");
    }

    // Cierra los archivos
    fclose(archivo_entrada);
    fclose(archivo_salida);

    // Imprime un mensaje indicando que se resolvieron los rompecabezas de Sudoku correctamente
    printf("Se han resuelto los rompecabezas de Sudoku correctamente.\n");

    return 0;
}
