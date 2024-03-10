#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error: Could not create socket\n";
        return 1;
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080); // Port to connect to, adjust as needed
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address, adjust as needed

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Error: Connection failed\n";
        return 1;
    }

    std::cout << "Connected to server\n";

    char message[1024];
    std::cout << "Enter message: ";
    std::cin.getline(message, 1024);

    if (send(sock, message, strlen(message), 0) < 0) {
        std::cerr << "Error: Send failed\n";
        return 1;
    }

    std::cout << "Message sent\n";

    char server_reply[2000];
    if (recv(sock, server_reply, 2000, 0) < 0) {
        std::cerr << "Error: Receive failed\n";
        return 1;
    }

    std::cout << "Server reply: " << server_reply << "\n";

    close(sock);

    return 0;
}
