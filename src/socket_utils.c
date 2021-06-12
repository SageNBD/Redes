/*
 * 
 * Vitor Augusto de Oliveira - 9360815 
 *
 *      TRABALHO 1 - REDES
 */

#include <socket_utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3001

/*
 * int create_socket()
 * 
 * Criacao de um socket com base no protocolo TCP
 *
 * Params:
 * 
 * Return:
 *      int socket_fd: file_descriptor para o socket
 */
int create_socket()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) 
    {
        fprintf(stderr, "Erro ao criar socket!\n");
        exit(1);
    }

    fprintf(stderr, "Socket criado com sucesso.\n");

    return socket_fd;
}

/*
 * void bind_port_to_socket(int socket_fd, struct sockaddr_in *server)
 * 
 * Faz o bind de uma porta especificada via define ao socket do servidor
 * 
 * Params:
 *      @socket_fd  int             file descriptor do socket
 *      @struct     sockaddr_in *   struct que carrega infos sobre o endereco do socket
 * Return:
 *      void
 */
void bind_port_to_socket(int socket_fd, struct sockaddr_in *server)
{
    server->sin_family = AF_INET;
    server->sin_port = htons(PORT);
    inet_aton("127.0.0.1", &(server->sin_addr));

    fprintf(stderr, "Tentando abrir a porta %d...\n", PORT);

    if (bind(socket_fd, (struct sockaddr *) server, sizeof(*server)) != 0)
    {
        fprintf(stderr, "Erro ao abrir a porta %d!\n", PORT);
        exit(1);
    }

    fprintf(stderr, "Porta %d aberta com sucesso!\n", PORT);
}