/*
 * ====================================================================================
 *  FICHIER  : baccalaureat_etape4.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 1 - Étape 4 : Vérifier les réponses
 *
 *  DESCRIPTION :
 *  Ce programme genere : 
 *      - Une lettre aleatoire
 *      - Permet au joueur de remplir plusieurs categories
 *      - Permet au joueur de répondre dans des champs de saisie
 *      - Vérifier les réponses avec la lettre aléatoire
 *  
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape4.c -o baccalaureat_etape4 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape4.c -o baccalaureat_etape4.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape4
 * 
 *  Sous Windows   : baccalaureat_etape4.exe
 * ====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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

    // Vérification des réponses
    printf("\n--- Verification ---\n");

    if (toupper(prenom[0]) == lettre)
        printf("Prenom valide\n");
    else
        printf("Prenom invalide\n");

    if (toupper(ville[0]) == lettre)
        printf("Ville valide\n");
    else
        printf("Ville invalide\n");

    if (toupper(pays[0]) == lettre)
        printf("Pays valide\n");
    else
        printf("Pays invalide\n");

    if (toupper(animal[0]) == lettre)
        printf("Animal valide\n");
    else
        printf("Animal invalide\n");

    if (toupper(objet[0]) == lettre)
        printf("Objet valide\n");
    else
        printf("Objet invalide\n");

    return 0;
}