#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Macro to define the maximum number of characters per line
#define MAX_CARACTERES_POR_LINEA 1000

// Function to check if a string is a palindrome
int es_palindromo(const char *cadena)
{
    int inicio = 0;               // Index for the start of the string
    int fin = strlen(cadena) - 1; // Index for the end of the string

    while (inicio < fin)
    {
        // Skip non-alphanumeric characters
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

        // Compare characters at the start and end of the string
        if (tolower((unsigned char)cadena[inicio]) != tolower((unsigned char)cadena[fin]))
        {
            return 0; // Not a palindrome
        }
        inicio++;
        fin--;
    }
    return 1; // Palindrome
}

// Function to clean the string, removing non-alphanumeric characters and converting to lowercase
void limpiar_cadena(const char *cadena_original, char *cadena_limpiada)
{

    while (*cadena_original)
    {
        // Check if the character is alphanumeric
        if (isalnum((unsigned char)*cadena_original))
        {
            // Convert the character to lowercase and add it to the cleaned string
            *cadena_limpiada = tolower((unsigned char)*cadena_original);

            cadena_limpiada++;
        }

        cadena_original++;
    }

    // Add null character at the end of the cleaned string
    *cadena_limpiada = '\0';
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // Print usage instructions and exit with error code
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Enter the filename (<filename>) to use for checking if words or phrases are palindromes.\n");
        return 1;
    }

    // Open the input file provided as the first command-line argument in read mode
    FILE *input_file = fopen(argv[1], "r");

    // Open a new file called "palindromes.txt" in write mode. This file will be used to store palindromes.
    FILE *palindromes_file = fopen("palindromes.txt", "w");

    // Open a new file called "not-palindromes.txt" in write mode. This file will be used to store words that are not palindromes.
    FILE *not_palindromes_file = fopen("not-palindromes.txt", "w");

    if (!input_file || !palindromes_file || !not_palindromes_file)
    {
        // Print error message and exit with error code
        perror("Error opening file");
        return 1;
    }

    char line[MAX_CARACTERES_POR_LINEA];                  // Character array to store a line of text
    char processed_line[MAX_CARACTERES_POR_LINEA];        // Character array to store a processed line of text
    int palindrome_count = 0, not_palindrome_count = 0; // Two integer variables to count the number of words that are palindromes and the number that are not.

    while (fgets(line, MAX_CARACTERES_POR_LINEA, input_file))
    {
        limpiar_cadena(line, processed_line);
        if (es_palindromo(processed_line))
        {
            fprintf(palindromes_file, "%s", line);
            palindrome_count++;
        }
        else
        {
            fprintf(not_palindromes_file, "%s", line);
            not_palindrome_count++;
        }
    }

    // Print the number of palindromes and non-palindromes found
    printf("Palindromes: %d\nNon-palindromes: %d\n", palindrome_count, not_palindrome_count);

    fclose(input_file);
    fclose(palindromes_file);
    fclose(not_palindromes_file);

    return 0;
}
