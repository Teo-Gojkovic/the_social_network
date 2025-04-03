#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define CESAR 3 // Clé de chiffrement

// Chiffrement César
void cesarEncrypt(char *text, int cesar) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 32 && text[i] <= 126) {
            text[i] = ((text[i] - 32 + cesar) % 95) + 32;
        }
    }
}

// Déchiffrement César
void cesarDecrypt(char *text, int cesar) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 32 && text[i] <= 126) {
            text[i] = ((text[i] - 32 - cesar + 95) % 95) + 32;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUFFER_SIZE];

    // Création du socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erreur de socket");
        exit(EXIT_FAILURE);
    }

    // Configuration du serveur
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Liaison du socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Erreur de bind");
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente de messages...\n");

    while (1) {
        socklen_t len = sizeof(cliaddr);
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';

        // Déchiffrement du message reçu
        cesarDecrypt(buffer, CESAR);
        printf("Message reçu déchiffré : %s\n", buffer);

        // Traitement du message (réponse fixe ici)
        char response[BUFFER_SIZE] = "Message reçu et compris !";
        
        // Chiffrement de la réponse
        cesarEncrypt(response, CESAR);

        // Envoi de la réponse chiffrée
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&cliaddr, len);
    }

    close(sockfd);
    return 0;
}
