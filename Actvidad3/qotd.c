#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // Para close
#include <stdlib.h>
#include <string.h>

#define PORT 17
#define MAX_RESPONSE_SIZE 512

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <IP servidor QOTD> <número de solicitudes> <nombre del archivo>\n", argv[0]);
        return 1;
    }

    char *ipAddr = argv[1];
    int numRequests = atoi(argv[2]);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, ipAddr, &serverAddr.sin_addr);

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error al crear el socket");
        return 1;
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error al conectar al servidor");
        return 1;
    }

    char response[MAX_RESPONSE_SIZE];
    for (int i = 0; i < numRequests; i++) {
        recv(clientSocket, response, MAX_RESPONSE_SIZE, 0);
        char filename[15]; // Tamaño aumentado para evitar el desbordamiento del búfer
        sprintf(filename, "%d.txt", i+1);
        FILE *file = fopen(filename, "w");
        fprintf(file, "%s", response);
        fclose(file);
    }

    close(clientSocket);
    return 0;
}

