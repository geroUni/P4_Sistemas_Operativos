#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define PUERTO 17
#define TAM_MAX_RESPUESTA 512
#define MAX_NOMBRE_ARCHIVO 25 // Aumentar el tamaño máximo del nombre de archivo

int main(int argc, char *argv[]) {
    // Check for the correct number of command-line arguments
    if (argc != 4) {
        printf("Usage: %s <IP server QOTD> <number of requests> <file name>\n", argv[0]);
        printf("Provide the following arguments: IP address of the server, the number of requests to make to the server, and the name of the file where the server's responses will be saved.\n");
        return 1;
    }

    const char *ip_servidor = argv[1]; // Server IP address
    int num_solicitudes = atoi(argv[2]); // Number of requests from the command line
    const char *nombre_archivo_base = argv[3]; // Base file name

    // Verify that the number of requests is positive
    if (num_solicitudes <= 0) {
        printf("The number of requests must be a positive number.\n");
        return 1;
    }

    struct sockaddr_in direccion_servidor; // Structure to store the server address
    direccion_servidor.sin_family = AF_INET; // Set the address family to IPv4
    direccion_servidor.sin_port = htons(PUERTO); // Set the server port
    if (inet_pton(AF_INET, ip_servidor, &direccion_servidor.sin_addr) <= 0) { // Convert the IP address from text to binary
        perror("Error converting IP address");
    }

    int socket_cliente = socket(AF_INET, SOCK_STREAM, 0); // Create a socket for communication with the server
    if (socket_cliente < 0) { // Check for errors when creating the socket
        perror("Error creating the socket");
    }

    if (connect(socket_cliente, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) { // Establish a connection with the server
        perror("Error connecting to the server");
    }

    char respuesta[TAM_MAX_RESPUESTA]; // Buffer to store the server's response
    char nombre_archivo[MAX_NOMBRE_ARCHIVO]; // Buffer to store the file name for each response
    FILE *archivo; // File pointer to write responses

    for (int i = 0; i < num_solicitudes; i++) {
        memset(respuesta, 0, TAM_MAX_RESPUESTA); // Clear the response buffer

        int bytes_recibidos = recv(socket_cliente, respuesta, TAM_MAX_RESPUESTA, 0); // Receive data from the server
        if (bytes_recibidos < 0) { // Check for errors when receiving data
            perror("Error receiving data from the server");
        } else if (bytes_recibidos == 0) { // Check if the server closed the connection
            printf("The server closed the connection\n");
            break;
        }

        sprintf(nombre_archivo, "%s_%d.txt", nombre_archivo_base, i+1); // Create the file name for this response
        archivo = fopen(nombre_archivo, "w"); // Open the file to write the response
        if (!archivo) { // Check for errors when opening the file
            perror("Error opening the file for writing");
        }

        fprintf(archivo, "%.*s", bytes_recibidos, respuesta); // Write the response to the file
        fclose(archivo); // Close the file

        close(socket_cliente); // Close the socket at the end of each iteration
        socket_cliente = socket(AF_INET, SOCK_STREAM, 0); // Create a new socket for the next iteration
        if (socket_cliente < 0) { // Check for errors when creating the socket
            perror("Error creating the socket");
        }

        if (connect(socket_cliente, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) { // Establish a connection with the server again
            perror("Error connecting to the server");
        }
    }

    close(socket_cliente);
    return 0;
}

