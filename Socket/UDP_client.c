#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024
//UDP_Client

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // 1. Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);  // Server's IP (localhost)

    // 2. Send message to server
    char message[] = "Hello from UDP client!";
    sendto(sock, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Sent to server: %s\n", message);

    // 3. Receive response from the server
    recvfrom(sock, buffer, BUF_SIZE, 0, NULL, NULL);
    printf("Received from server: %s\n", buffer);

    // 4. Close the socket
    close(sock);
    return 0;
}
