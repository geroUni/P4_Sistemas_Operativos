#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CARACTERES_POR_LINEA 1000

// Función para verificar si una cadena es un palíndromo
int es_palindromo(const char *cadena)
{
    int inicio = 0;               // Índice del inicio de la cadena
    int fin = strlen(cadena) - 1; // Índice del final de la cadena

    while (inicio < fin)
    {
        // Ignorar caracteres que no sean alfanuméricos
        if (!isalnum((unsigned char)cadena[inicio]))
        {
            inicio++;
            continue;
        }
        if (!isalnum((unsigned char)cadena[fin]))
        {
            fin--;
            continue;
        }

        // Compara los caracteres en las posiciones inicio y fin de la cadena
        if (tolower((unsigned char)cadena[inicio]) != tolower((unsigned char)cadena[fin]))
        {
            return 0; // No es un palíndromo
        }
        inicio++;
        fin--;
    }
    return 1; // Es un palíndromo
}

// Función para limpiar la cadena, eliminando caracteres no alfanuméricos y convirtiendo a minúsculas
void limpiar_cadena(const char *cadena_original, char *cadena_limpiada)
{

    while (*cadena_original)
    {
        // Verifica si el carácter actual es alfanumérico
        if (isalnum((unsigned char)*cadena_original))
        {
            // Si es alfanumérico, convierte el carácter a minúsculas y lo asigna a la cadena limpiada
            *cadena_limpiada = tolower((unsigned char)*cadena_original);

            cadena_limpiada++;
        }

        cadena_original++;
    }

    // Al llegar al final de la cadena, se agrega el carácter nulo para marcar el final de la cadena
    *cadena_limpiada = '\0';
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nombre_archivo>\n", argv[0]);
        fprintf(stderr, "Introduzca el nombre del archivo (<nombre_archivo>) que desea utilizar para verificar si las palabras u oraciones son palíndromos.\n");
        return 1;
    }
    // Abre el archivo de entrada proporcionado por el primer argumento de la línea de comandos en modo lectura.
    FILE *archivo_entrada = fopen(argv[1], "r");

    // Abre un archivo nuevo llamado "palindromos.txt" en modo escritura. Este archivo se utilizará para almacenar palíndromos.
    FILE *archivo_palindromos = fopen("palindromos.txt", "w");

    // Abre un archivo nuevo llamado "not-palindromos.txt" en modo escritura. Este archivo se utilizará para almacenar palabras que no son palíndromos.
    FILE *archivo_no_palindromos = fopen("not-palindromos.txt", "w");

    if (!archivo_entrada || !archivo_palindromos || !archivo_no_palindromos)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    char linea[MAX_CARACTERES_POR_LINEA];                  // Declaración de una cadena de caracteres para almacenar una línea de texto
    char linea_procesada[MAX_CARACTERES_POR_LINEA];        // Declaración de otra cadena de caracteres para almacenar una línea de texto procesada
    int cuenta_palindromos = 0, cuenta_no_palindromos = 0; // Declaración de dos variables enteras para contar la cantidad de palabras que son palíndromos y las que no lo son.

    while (fgets(linea, MAX_CARACTERES_POR_LINEA, archivo_entrada))
    {
        limpiar_cadena(linea, linea_procesada);
        if (es_palindromo(linea_procesada))
        {
            fprintf(archivo_palindromos, "%s", linea);
            cuenta_palindromos++;
        }
        else
        {
            fprintf(archivo_no_palindromos, "%s", linea);
            cuenta_no_palindromos++;
        }
    }

    printf("Palíndromos: %d\nNo palíndromos: %d\n", cuenta_palindromos, cuenta_no_palindromos);

    fclose(archivo_entrada);
    fclose(archivo_palindromos);
    fclose(archivo_no_palindromos);

    return 0;
}
