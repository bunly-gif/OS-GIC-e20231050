#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from client!";

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid server address");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    printf("Connecting to server...\n");
    if (connect(sock, (struct sockaddr *)&server_address,
                sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");

    // Send message
    send(sock, message, strlen(message), 0);
    printf("Sent: %s\n", message);

    // Receive server response
    read(sock, buffer, BUFFER_SIZE - 1);
    printf("Received: %s\n", buffer);

    // Close socket
    close(sock);
    printf("Connection closed.\n");

    return 0;
}
