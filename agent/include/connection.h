#ifndef CONNECTION_H
#define CONNECTION_H

int initialize_socket(char* server_address, int port);

void close_socket(int server_sockfd);

void send_message(int server_sockfd, char* message);

#endif