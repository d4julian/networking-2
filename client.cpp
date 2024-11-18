#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./client <port>" << std::endl;
        return 1;
    }

    const int port = std::stoi(argv[1]);

    int new_socket = 0;
    struct sockaddr_in server_address;

    if ((new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Could not create socket" << std::endl;
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        std::cerr << "Could not connect to server" << std::endl;
        return 1;
    }

    if (connect(new_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Could not connect to server" << std::endl;
        return 1;
    }

    send(new_socket, message, strlen(message), 0);

    char buffer[512] = {0};
    recv(new_socket, buffer, sizeof(buffer) - 1, 0);
    std::cout << buffer << std::endl;

    close(new_socket);
    return 0;
}
