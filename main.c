//Maxence Dulche - Sarah
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LENGTH 6  // Définir une taille de buffer pour fgets
void isolatioNumber (char *chaine, int *tableau){

    int number = 0, index = 0, check = 0, i = 0;

    while (check && chaine[index] != '\0'){

        if (chaine[index] < '0' || chaine[index] > '9'){
            number = number * 10 + (chaine[index] - '0');
        } else if (chaine[index] == ',') {
            tableau[i] = number;
            number = 0;
            i++;
        }
    }
}

int main() {

    char *filename = "mc.txt";
    int number = 0, index =0 ,tableau[8];

    FILE *inputFile = fopen(filename, "r");

    char chaine[LENGTH];  // Buffer pour stocker une ligne

    fgets(chaine, LENGTH, inputFile); // Recuperation de la ligne de chiffre

    IsolatioNumber(chaine, tableau);

    for (int i = 0; i < LENGTH; i++)
    {
        printf("%d\n", tableau[i]);
    }

    

    
    fclose(inputFile);
    return 0;
}
