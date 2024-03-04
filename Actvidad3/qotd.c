#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PUERTO 17
#define TAM_MAX_RESPUESTA 512
#define MAX_NOMBRE_ARCHIVO 25 // Aumentar el tamaño máximo del nombre de archivo

void manejar_error(const char *mensaje) {
    perror(mensaje);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <IP servidor QOTD> <número de solicitudes> <nombre del archivo>\n", argv[0]);
        printf("Proporciona los siguientes argumentos: la dirección IP del servidor, el número de solicitudes que deseas realizar al servidor y el nombre del archivo donde se guardarán las respuestas del servidor.\n");
        return 1;
    }

    const char *ip_servidor = argv[1];
    int num_solicitudes = atoi(argv[2]);
    const char *nombre_archivo_base = argv[3];

    if (num_solicitudes <= 0) {
        printf("El número de solicitudes debe ser un número positivo.\n");
        return 1;
    }

    struct sockaddr_in direccion_servidor;
    direccion_servidor.sin_family = AF_INET;
    direccion_servidor.sin_port = htons(PUERTO);
    if (inet_pton(AF_INET, ip_servidor, &direccion_servidor.sin_addr) <= 0) {
        manejar_error("Error al convertir la dirección IP");
    }

    int socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_cliente < 0) {
        manejar_error("Error al crear el socket");
    }

    if (connect(socket_cliente, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) {
        manejar_error("Error al conectar con el servidor");
    }

    char respuesta[TAM_MAX_RESPUESTA];
    char nombre_archivo[MAX_NOMBRE_ARCHIVO];
    FILE *archivo;
    
    for (int i = 0; i < num_solicitudes; i++) {
        memset(respuesta, 0, TAM_MAX_RESPUESTA); // Limpiar el buffer de respuesta
        int bytes_recibidos = recv(socket_cliente, respuesta, TAM_MAX_RESPUESTA, 0);
        if (bytes_recibidos < 0) {
            manejar_error("Error al recibir datos del servidor");
        } else if (bytes_recibidos == 0) {
            printf("El servidor cerró la conexión\n");
            break;
        }
        
        sprintf(nombre_archivo, "%s_%d.txt", nombre_archivo_base, i+1);
        archivo = fopen(nombre_archivo, "w");
        if (!archivo) {
            manejar_error("Error al abrir el archivo para escribir");
        }
        
        fprintf(archivo, "%.*s", bytes_recibidos, respuesta);
        fclose(archivo);

        close(socket_cliente); // Cerrar el socket al finalizar cada iteración
        socket_cliente = socket(AF_INET, SOCK_STREAM, 0); // Crear un nuevo socket para la próxima iteración
        if (socket_cliente < 0) {
            manejar_error("Error al crear el socket");
        }

        if (connect(socket_cliente, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) {
            manejar_error("Error al conectar con el servidor");
        }
    }

    close(socket_cliente);
    return 0;
}
