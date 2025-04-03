//Maxence Dulche - Sarah
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 28  // Définir une taille de buffer pour fgets

int min(int *list, int lenght) {

    if (lenght <= 0) return -1; // Sert à verifier si la taille est valide

    int index = 0;
    

    for (int i = 1; i < lenght; i++)
    {
        if (list[i] < list[index])
        {
            index = i;
        }
        
    }
    
    return index;
}

int max(int *list, int lenght) {

    if (lenght <= 0) return -1; // Sert à verifier si la taille est valide

    int index = 0;
    

    for (int i = 1; i < lenght; i++)
    {
        if (list[i] > list[index])
        {
            index = i;
        }
        
    }
    
    return index;
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

int main() {

    char *filename = "mc.txt";
    int number = 0, index =0 ,tableau[8];

    FILE *inputFile = fopen(filename, "r");

    char chaine[LENGTH];  // Buffer pour stocker une ligne

    fgets(chaine, LENGTH, inputFile); // Recuperation de la ligne de chiffre

    IsolatioNumber(chaine, tableau);

    for (int i = 0; i < (sizeof(tableau) / sizeof(int))-1; i++)
    {
        
        printf("%d\n", tableau[i]);
    }

    

    
    fclose(inputFile);
    return 0;
}
