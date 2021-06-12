/*
 * 
 * Vitor Augusto de Oliveira - 9360815 
 *
 *      TRABALHO 1 - REDES
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <socket_utils.h>

int main(int argc, char *argv[])
{
    int socket_fd = create_socket();
    
    // Bind da porta ao socket
    struct sockaddr_in client;
    bind_port_to_socket(socket_fd, &client);
}