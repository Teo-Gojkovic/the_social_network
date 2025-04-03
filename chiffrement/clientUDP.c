// PASCAL Maxime
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
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE];
    
    // Création du socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erreur de socket");
        exit(EXIT_FAILURE);
    }
    
    // Configuration du serveur
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    
    printf("Entrez votre message : ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Supprime le retour à la ligne
    
    // Chiffrement du message avant envoi
    cesarEncrypt(buffer, CESAR);
    
    // Envoi du message chiffré
    sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Message chiffré envoyé au serveur\n");
    
    // Réception de la réponse chiffrée
    socklen_t len = sizeof(servaddr);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    
    // Déchiffrement de la réponse
    cesarDecrypt(buffer, CESAR);
    printf("Réponse du serveur déchiffrée : %s\n", buffer);
    
    close(sockfd);
    return 0;
}