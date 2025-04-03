#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 1618
#define NUM_COUNT 8
#define MAX_VALUE 2023

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int numbers[NUM_COUNT];
    char buffer[1024];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("172.16.20.11"); // Replace with the target IP address

    // Generate random numbers
    srand(time(NULL));
    for (int i = 0; i < NUM_COUNT; i++) {
        numbers[i] = rand() % (MAX_VALUE + 1);
    }

    // Prepare the message
    snprintf(buffer, sizeof(buffer), "%d,%d,%d,%d,%d,%d,%d,%d",
             numbers[0], numbers[1], numbers[2], numbers[3],
             numbers[4], numbers[5], numbers[6], numbers[7]);

    // Send the message
    if (sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("IP tram sent: %s\n", buffer);

    // Close the socket
    close(sockfd);
    return 0;
}
