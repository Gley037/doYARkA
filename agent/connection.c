#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <connection.h>
#include <string.h>


const int MAX_BUFFER = 2048;


int initialize_socket(char* server_address, int port)
{
    struct sockaddr_in server;
    int server_sockfd;
    int size, write_size;
    char buffer[MAX_BUFFER];

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1)
    {
        perror("Socket Created Failed");
        return -1;
    }

    printf("Socket Create Success\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_address);
    server.sin_port = htons(port);

    if (connect(server_sockfd, (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Connection Error");
		return -1;
	}

    printf("Connected to %s:%d\n", server_address, port);

    return server_sockfd;
}


void close_socket(int server_sockfd)
{
    close(server_sockfd);
}


void send_message(int server_sockfd, char* message)
{
    if (send(server_sockfd, message, strlen(message), 0) < 0)
	{
		perror("Send failed");
		return;
	}

	printf("Data Send\n");
}