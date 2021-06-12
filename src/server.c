/*
 * 
 * Vitor Augusto de Oliveira - 9360815 
 *
 *      TRABALHO 1 - REDES
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <socket_utils.h>

#define MAX_PENDING_CONNECTIONS     3
#define MAX_BYTES_TO_RECEIVE        40

/*
 * void send_message_to_client(int socket_fd)
 * 
 * Fica esperando por uma mensagem de um cliente via funcao accept()
 * e retorna a mensagem padrao do servidor para o mesmo.
 *
 * Params:
 *      @socket_fd  int     file descriptor do socket
 * Return:
 *      void
 */
void send_message_to_client(int socket_fd)
{
    char default_server_response_msg[] = "Vc se conectou ao servidor!";
    int default_msg_len = strlen(default_server_response_msg);

    for (;;)
    {
        struct sockaddr_in client;
        socklen_t client_len = (socklen_t) sizeof(client);

        fprintf(stderr, "Esperando por uma mensagem...\n");

        int connection_fd = accept(socket_fd, (struct sockaddr *) &client, &client_len);

        fprintf(stderr, "Nova mensagem recebida!\n");

        char buffer[50];
        recv(connection_fd, buffer, MAX_BYTES_TO_RECEIVE, 0);

        // Recuperando o IP do cliente que enviou:
        char ip_client[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client.sin_addr), ip_client, INET_ADDRSTRLEN);

        int send_ret_val = send(connection_fd, default_server_response_msg, default_msg_len, 0);
        if (send_ret_val < 0) 
        {
            fprintf(stderr, "Erro ao enviar a mensagem ao cliente!\n");
        }
    }

}

int main(int argc, char *argv[])
{
    int socket_fd = create_socket();

    // Bind da porta ao socket
    struct sockaddr_in server;
    bind_port_to_socket(socket_fd, &server);

    // Ouvindo conexoes no socket
    listen(socket_fd, MAX_PENDING_CONNECTIONS);

    send_message_to_client(socket_fd);

    close(socket_fd);

    return 0;
}