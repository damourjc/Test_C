/*
 * ====================================================================================
 *  FICHIER  : baccalaureat_etape3.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 1 - Étape 3 : Saisir les réponses
 *
 *  DESCRIPTION :
 *  Ce programme genere une lettre aleatoire, permet au joueur de remplir plusieurs 
 *  categories et il permet aussi au joueur de répondre dans des champs de saisie.
 *  
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape3.c -o baccalaureat_etape3 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape3.c -o baccalaureat_etape3.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape3
 * 
 *  Sous Windows   : baccalaureat_etape3.exe
 * ====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    printf("=== Jeu du Baccalaureat ===\n\n");

    srand(time(NULL));
    char lettre = 'A' + rand() % 26;

    printf("Lettre : %c\n\n", lettre);

    // Variables pour stocker les réponses
    char prenom[50];
    char ville[50];
    char pays[50];
    char animal[50];
    char objet[50];

    // Saisie utilisateur
    printf("1. Prenom : ");
    fgets(prenom, 50, stdin);

    printf("2. Ville : ");
    fgets(ville, 50, stdin);

    printf("3. Pays : ");
    fgets(pays, 50, stdin);

    printf("4. Animal : ");
    fgets(animal, 50, stdin);

    printf("5. Objet : ");
    fgets(objet, 50, stdin);

    // Affichage des réponses
    printf("\n--- Tes reponses ---\n");
    printf("Prenom : %s", prenom);
    printf("Ville : %s", ville);
    printf("Pays : %s", pays);
    printf("Animal : %s", animal);
    printf("Objet : %s", objet);

    return 0;
}