#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LENGTH 28  // Définir une taille de buffer pour fgets
#define TAILLE sizeof(tableau) / sizeof(int)
#define PORT 1618
#define BUFFER_SIZE 1024

int min(int *tableau) {

    int index = 0;

    for (int i = 1; i < TAILLE-1; i++)
    {
        if (tableau[i] < tableau[index] && tableau[i] != -1)
        {
            index = i;
        }
        
    }
    
    return index;
}

int max(int *tableau) {

    int index = 0;
    

    for (int i = 1; i < (sizeof(tableau) / sizeof(int))-1; i++)
    {
        if (tableau[i] > tableau[index])
        {
            index = i;
        }
        
    }
    
    return index;
}

int calcul_moyenne(int *tableau) {
    int somme = 0, count = 0;
    

    for (int i = 0; i < (sizeof(tableau) / sizeof(int))-1; i++) {
        if (tableau[i] != -1){
            somme += tableau[i];
            count++;
        }
    }

    return (float)somme / count;
}

void IsolatioNumber(char *chaine, int *tableau) {
    int number = 0, index = 0, i = 0;

    printf("Chaîne à traiter : ");
    for (int j = 0; chaine[j] != '\0'; j++) {
        printf("%c", chaine[j]);
    }
    printf("\n");


    while (chaine[index] != '\0') {
        // Si le caractère est un chiffre
        if (chaine[index] >= '0' && chaine[index] <= '9') {
            // Convertir le caractère en entier et l'ajouter au nombre
            number = number * 10 + (chaine[index] - '0');
        } 
        // Si c'est une virgule
        else if (chaine[index] == ',') {
            // Stocker le nombre actuel dans le tableau
            tableau[i] = number;
            i++;
            // Réinitialiser le nombre pour le prochain
            number = 0;
        }
        // Passer au caractère suivant
        index++;
    }
    
    // Ne pas oublier le dernier nombre après la dernière virgule
    tableau[i] = number;
    
    // Pour déboguer, affichons les valeurs
    printf("Valeurs extraites : ");
    for (int j = 0; j <= i; j++) {
        printf("%d ", tableau[j]);
    }
    printf("\n");
}

void treatment(char *buffer) {

    int number = 0, index =0 ,tableau[8];

    IsolatioNumber(buffer, tableau);

    for (int i = 0; i < (sizeof(tableau) / sizeof(int))-1; i++)
    {
        printf("%d\n", tableau[i]);
    }

    for (int j = 0; j < 2; j++)
    {
        tableau[min(tableau)] = -1;
        tableau[max(tableau)] = -1;
    }
    

    printf("%d\n", calcul_moyenne(tableau));
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the port
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);
    printf("Listening on IP: 0.0.0.0, Port: %d\n", PORT);

    // Continuously listen for incoming trams
    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("Receive failed");
            continue; // Continue listening even if an error occurs
        }

        buffer[n] = '\0'; // Null-terminate the received data
        printf("Received IP tram: %s\n", buffer);
        treatment(buffer);
    }

    // Close the socket (unreachable in this case)
    close(sockfd);
    return 0;
}

