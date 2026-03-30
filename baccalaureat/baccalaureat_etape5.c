/*
 * ====================================================================================
 *  FICHIER  : baccalaureat_etape5.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 1 - Étape 5 : Nettoyer les chaînes + points
 *
 *  DESCRIPTION :
 *  Ce programme genere : 
 *      - Ajout une fonction void enlever_saut_ligne(char *mot)
 *      - Une lettre aleatoire
 *      - Permet au joueur de remplir plusieurs categories
 *      - Permet au joueur de répondre dans des champs de saisie
 *      - Vérifier les réponses avec la lettre aléatoire
 *      - Afficher un score final
 *  
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape5.c -o baccalaureat_etape5 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape5.c -o baccalaureat_etape5.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape5
 * 
 *  Sous Windows   : baccalaureat_etape5.exe
 * ====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void enlever_saut_ligne(char *mot) {
    for (int i = 0; mot[i] != '\0'; i++) {
        if (mot[i] == '\n') {
            mot[i] = '\0';
            break;
        }
    }
}

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
    enlever_saut_ligne(prenom);

    printf("2. Ville : ");
    fgets(ville, 50, stdin);
    enlever_saut_ligne(ville);

    printf("3. Pays : ");
    fgets(pays, 50, stdin);
    enlever_saut_ligne(pays);

    printf("4. Animal : ");
    fgets(animal, 50, stdin);
    enlever_saut_ligne(animal);

    printf("5. Objet : ");
    fgets(objet, 50, stdin);
    enlever_saut_ligne(objet);

    // Affichage des réponses
    printf("\n--- Tes reponses ---\n");
    printf("Prenom : %s\n", prenom);
    printf("Ville : %s\n", ville);
    printf("Pays : %s\n", pays);
    printf("Animal : %s\n", animal);
    printf("Objet : %s\n", objet);

    int score = 0;

    // Vérification des réponses
    printf("\n--- Verification ---\n");

    if (toupper(prenom[0]) == lettre){
        printf("Prenom valide\n");
        score++;
    }else{
        printf("Prenom invalide\n");
    }
    if (toupper(ville[0]) == lettre){
        printf("Ville valide\n");
        score++;
    }else{
        printf("Ville invalide\n");
    }
    if (toupper(pays[0]) == lettre){
        printf("Pays valide\n");
        score++;
    }else{
        printf("Pays invalide\n");
    }
    if (toupper(animal[0]) == lettre){
        printf("Animal valide\n");
        score++;
    }else{
        printf("Animal invalide\n");
    }
    if (toupper(objet[0]) == lettre){
        printf("Objet valide\n");
        score++;
    }else{
        printf("Objet invalide\n");
    }

    printf("\nScore : %d / 5\n", score);
    
    return 0;
}