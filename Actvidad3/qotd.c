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

int main(int argc, char *argv[]) {
    if (argc != 4) { // Verificación de la cantidad correcta de argumentos de línea de comandos
        printf("Uso: %s <IP servidor QOTD> <número de solicitudes> <nombre del archivo>\n", argv[0]);
        printf("Proporciona los siguientes argumentos: la dirección IP del servidor, el número de solicitudes que deseas realizar al servidor y el nombre del archivo donde se guardarán las respuestas del servidor.\n");
        return 1;
    }

    const char *ip_servidor = argv[1]; // Dirección IP del servidor
    int num_solicitudes = atoi(argv[2]); // Número de solicitudes desde la línea de comandos
    const char *nombre_archivo_base = argv[3]; // Nnombre base del archivo

    if (num_solicitudes <= 0) { // Verifica que el número de solicitudes sea positivo
        printf("El número de solicitudes debe ser un número positivo.\n");
        return 1;
    }

    struct sockaddr_in direccion_servidor; // Estructura para almacenar la dirección del servidor
    direccion_servidor.sin_family = AF_INET; // Establece la familia de direcciones a IPv4
    direccion_servidor.sin_port = htons(PUERTO); // Establece el puerto del servidor
    if (inet_pton(AF_INET, ip_servidor, &direccion_servidor.sin_addr) <= 0) { // Convierte la dirección IP de texto a binario
        perror("Error al convertir la dirección IP");
    }

    int socket_cliente = socket(AF_INET, SOCK_STREAM, 0); // Crea un socket para la comunicación con el servidor
    if (socket_cliente < 0) { // Verifica si hay errores al crear el socket
        perror("Error al crear el socket");
    }

    if (connect(socket_cliente, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) { // Establece la conexión con el servidor
        perror("Error al conectar con el servidor");
    }

    char respuesta[TAM_MAX_RESPUESTA]; // Almacena la respuesta del servidor
    char nombre_archivo[MAX_NOMBRE_ARCHIVO]; // Almacena el nombre del archivo para cada respuesta
    FILE *archivo; // Puntero al archivo donde se escribirán las respuestas
    
    for (int i = 0; i < num_solicitudes; i++) {
        memset(respuesta, 0, TAM_MAX_RESPUESTA); // Limpia el buffer de respuesta
        
        int bytes_recibidos = recv(socket_cliente, respuesta, TAM_MAX_RESPUESTA, 0); // Recibe datos del servidor
        if (bytes_recibidos < 0) { // Verifica si hay errores al recibir datos
            perror("Error al recibir datos del servidor");
        } else if (bytes_recibidos == 0) { // Verifica si el servidor cerró la conexión
            printf("El servidor cerró la conexión\n");
            break;
        }
        
        sprintf(nombre_archivo, "%s_%d.txt", nombre_archivo_base, i+1); // Crea el nombre del archivo para esta respuesta
        archivo = fopen(nombre_archivo, "w"); // Abre el archivo para escribir la respuesta
        if (!archivo) { // Verifica si hay errores al abrir el archivo
            perror("Error al abrir el archivo para escribir");
        }
        
        fprintf(archivo, "%.*s", bytes_recibidos, respuesta); // Escribe la respuesta en el archivo
        fclose(archivo); // Cierra el archivo
        
        close(socket_cliente); // Cierra el socket al finalizar cada iteración
        socket_cliente = socket(AF_INET, SOCK_STREAM, 0); // Crea un nuevo socket para la próxima iteración
        if (socket_cliente < 0) { // Verifica si hay errores al crear el socket
            perror("Error al crear el socket");
        }

        if (connect(socket_cliente, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) { // Establece la conexión con el servidor nuevamente
            perror("Error al conectar con el servidor");
        }
    }

    close(socket_cliente);
    return 0;
}
