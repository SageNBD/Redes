#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#define MAX_PENDING_CONNECTIONS     3
#define MAX_BYTES_TO_RECEIVE        3
#define PORT                        3001

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
    // Criando o Socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) 
    {
        fprintf(stderr, "Erro ao criar socket!\n");
        return 0;
    }
    fprintf(stderr, "Socket criado com sucesso.\n");

    // Bind da porta ao socket
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &(server.sin_addr));

    fprintf(stderr, "Abrindo a porta %d...\n", PORT);
    if (bind(socket_fd, (struct sockaddr *) &server, sizeof(server)) != 0)
    {
        fprintf(stderr, "Erro ao abrir a porta %d!\n", PORT);
        return 0;
    }

    // Ouvindo na porta
    listen(socket_fd, MAX_PENDING_CONNECTIONS);

    send_message_to_client(socket_fd);

    close(socket_fd);

    return 0;
}