#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE];
    socklen_t client_len = sizeof(client_addr);

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    server_addr.sin_port = htons(PORT);  // Port 8080

    // 2. Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("UDP server is listening on port %d...\n", PORT);

    // 3. Receive message from client
    recvfrom(server_fd, buffer, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
    printf("Received from client: %s\n", buffer);

    // 4. Send response to client
    char response[] = "Hello from UDP server!";
    sendto(server_fd, response, strlen(response), 0, (struct sockaddr*)&client_addr, client_len);
    printf("Sent to client: %s\n", response);

    // 5. Close the socket
    close(server_fd);
    return 0;
}
