/*
 * 
 * Vitor Augusto de Oliveira - 9360815 
 *
 *      TRABALHO 1 - REDES
 */

#include <netinet/in.h>

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
int create_socket();

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
void bind_port_to_socket(int socket_fd, struct sockaddr_in *server);