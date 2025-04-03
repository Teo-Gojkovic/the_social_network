// PASCAL Maxime
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define RESPONSE_SIZE 1500  // Buffer plus grand pour la réponse
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

// Fonction pour obtenir la date et l'heure actuelle
void getCurrentDateTime(char *datetime, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(datetime, size, "%d/%m/%Y %H:%M:%S", tm_info);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUFFER_SIZE];
    char datetime[50];  // Taille suffisante pour la date et l'heure
    char response[RESPONSE_SIZE];  // Buffer plus grand pour la réponse
    
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
        
        // Récupération de l'adresse IP du client
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(cliaddr.sin_addr), client_ip, INET_ADDRSTRLEN);
        
        // Déchiffrement du message reçu
        cesarDecrypt(buffer, CESAR);
        printf("Message reçu de %s déchiffré : %s\n", client_ip, buffer);
        
        // Récupération de la date et heure actuelle
        getCurrentDateTime(datetime, sizeof(datetime));
        
        // Préparation de la réponse avec des informations supplémentaires
        // Utilisation de snprintf avec vérification de la limite
        int resp_len = snprintf(response, RESPONSE_SIZE, 
                 "Message reçu le %s | Votre IP: %s | Longueur du message: %d caractères", 
                 datetime, client_ip, (int)strlen(buffer));
        
        // Vérification si la chaîne a été tronquée
        if (resp_len >= RESPONSE_SIZE) {
            printf("Attention: La réponse a été tronquée\n");
            response[RESPONSE_SIZE - 1] = '\0';  // S'assurer que la chaîne est terminée
        }
        
        // Chiffrement de la réponse
        cesarEncrypt(response, CESAR);
        
        // Envoi de la réponse chiffrée
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&cliaddr, len);
        printf("Réponse envoyée au client\n");
    }
    
    close(sockfd);
    return 0;
}