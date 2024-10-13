#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int server_fd = -1;

void handle_signal(int signal) __attribute__((unused));

void handle_signal(int signal) {
    if (server_fd != -1) {
        close(server_fd);
        std::cout << "Socket closed" << std::endl;
    }
    exit(0);
}

int main() {
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello from server";

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        std::cout << "Waiting for a connection..." << std::endl;

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        std::cout << "Connection accepted" << std::endl;

        send(new_socket, hello, strlen(hello), 0);
        std::cout << "Hello message sent" << std::endl;

        read(new_socket, buffer, BUFFER_SIZE);
        std::cout << "Received message: " << buffer << std::endl;

        close(new_socket);
    }

    close(server_fd);
    return 0;
}