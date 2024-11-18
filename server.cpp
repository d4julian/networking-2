#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid port" << std::endl;
        return 1;
    }

    const int port = std::stoi(argv[1]);
    const char *response = "Welcome to the server running on REPTILIAN";

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[512] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Could not create socket" << std::endl;
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Could not bind to port " << port << std::endl;
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Could not listen on port " << port << std::endl;
        return 1;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        std::cerr << "Could not accept connection" << std::endl;
        return 1;
    }

    recv(new_socket, buffer, sizeof(buffer) - 1, 0);
    std::cout << buffer << std::endl;

    send(new_socket, response, strlen(response), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
