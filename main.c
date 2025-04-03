#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 6  // Définir une taille de buffer pour fgets
int IsolatioNumber(char *chaine){
    int number = 0, index = 0, check = 0;
    while (check && chaine[index] != '\0'){
        if (chaine[index] < '0' || chaine[index] > '9'){
            check = 1;
        }
        if (check){
            number = number * 10 + (chaine[index] - '0');
        }
        index++;
    }
    return number;
}
int main() {
    char *filename = "mc.txt";
    int number = 0, index =0 ,tableau = [8], i = 0;
    FILE *inputFile = fopen(filename, "r");
    char buffer[MAX_LINE_LENGTH];  // Buffer pour stocker une ligne
    while (fgets(buffer, MAX_LINE_LENGTH, inputFile) != NULL) {
        tableau[i] = IsolatioNumber(buffer);
        printf("%d\n", tableau[i]);  // Affichage de la ligne
        i++;
    }
    fclose(inputFile);
    return 0;
}