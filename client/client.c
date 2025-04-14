#include <stdio.h> // for printf
#include <stdlib.h> // for exit
#include <string.h> // for memset
#include <time.h> // for srand and rand
#include <arpa/inet.h> // for inet_addr
#include <unistd.h> // for close

#define PORT 1618 // Port number given by Guigui
#define NUM_COUNT 8 
#define MAX_VALUE 2023
//#define SERVER_IP "172.16.20.11" // PC Sarah
#define SERVER_IP "127.0.0.1"

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int numbers[NUM_COUNT];
    char buffer[1024]; // Buffer size for sending data

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); 

    // Generate random numbers
    srand(time(NULL));
    for (int i = 0; i < NUM_COUNT; i++) {
        numbers[i] = rand() % (MAX_VALUE + 1);
    }

    // Prepare the message
    snprintf(buffer, sizeof(buffer), "%d,%d,%d,%d,%d,%d,%d,%d",
             numbers[0], numbers[1], numbers[2], numbers[3],
             numbers[4], numbers[5], numbers[6], numbers[7]);

    printf("Sending to IP: %s, Port: %d\n", SERVER_IP, PORT);

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
