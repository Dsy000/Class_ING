#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
//TCP_client

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);  // Use the server's IP (localhost)

    // 2. Connect to the server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // 3. Send a message to the server
    char message[] = "Hello from Client!";
    send(sock, message, strlen(message), 0);
    printf("Sent to server: %s\n", message);

    // 4. Receive response from the server
    read(sock, buffer, sizeof(buffer));
    printf("Received from server: %s\n", buffer);

    // 5. Close the socket
    close(sock);
    return 0;
}
