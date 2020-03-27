#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char address = argv[1];
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80);
    inet_pton(client_socket, address, sizeof(address));

    connect(client_socket, (struct sockaddr *)&remote_address, sizeof(remote_address));
    char request = "GET / HTTP/1.1\r\n\r\n";
    char respose[4096];
    send(client_socket, request, sizeof(request), 0);
    recv(client_socket, &respose, sizeof(respose), 0);
    printf("respose from the server is - %s/n", respose);
    close(client_socket);

    return 0;
}