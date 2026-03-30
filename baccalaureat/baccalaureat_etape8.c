/*
 * ==============================================================================================================================================================================
 *  FICHIER  : baccalaureat_etape8.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 1 - Étape 8 : Version “pro” avec tableaux
 *
 *  DESCRIPTION :
 *  Ce programme (plus optimisé) genere : 
 *      - Ajout une fonction void enlever_saut_ligne(char *mot)
 *      - Ajout d'une fonction int verifier_reponse(char *categorie, char *mot, char lettre) (modifié : si "vide")
 *      - Une lettre aleatoire
 *      - Tableau catégorie et réponse
 *      - Boucle saisir et répondre
 *      - Boucle affichage des réponses
 *      - Vérifier les réponses avec la lettre aléatoire + si "vide" (version optimisé)
 *      - Afficher un score final
 *  
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape8.c -o baccalaureat_etape8 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape8.c -o baccalaureat_etape8.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape8
 * 
 *  Sous Windows   : baccalaureat_etape8.exe
 * ==============================================================================================================================================================================
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

int verifier_reponse(char *categorie, char *mot, char lettre) {

    // Vérifier si le mot est vide
    if (mot[0] == '\0') {
        printf("%s invalide (vide)\n", categorie);
        return 0;
    }

    // Vérification de la première lettre
    if (toupper(mot[0]) == lettre) {
        printf("%s valide\n", categorie);
        return 1;
    } else {
        printf("%s invalide\n", categorie);
        return 0;
    }
}

int main() {
    printf("=== Jeu du Baccalaureat ===\n\n");

    srand(time(NULL));
    char lettre = 'A' + rand() % 26;

    printf("Lettre : %c\n\n", lettre);

    // Variables pour stocker les réponses
    char *categories[] = {"Prenom", "Ville", "Pays", "Animal", "Objet"};

    char reponses[5][50];

    // Saisie utilisateur
    for (int i = 0; i < 5; i++) {
        printf("%d. %s : ", i + 1, categories[i]);
        fgets(reponses[i], 50, stdin);
        enlever_saut_ligne(reponses[i]);
}

    // Affichage des réponses
    printf("\n--- Tes reponses ---\n");

    for (int i = 0; i < 5; i++) {
        printf("%s : %s\n", categories[i], reponses[i]);
    }

    // Vérification des réponses
    int score = 0;

    printf("\n--- Verification ---\n");

    for (int i = 0; i < 5; i++) {
        score += verifier_reponse(categories[i], reponses[i], lettre);
    }

    printf("\nScore : %d / 5\n", score);
    
    return 0;
}

// char prenom[50];
// char ville[50]; 
// char pays[50];
// char animal[50];
// char objet[50];

// printf("1. Prenom : ");
// fgets(prenom, 50, stdin);
// enlever_saut_ligne(prenom);

// printf("2. Ville : ");
// fgets(ville, 50, stdin);
// enlever_saut_ligne(ville);

// printf("3. Pays : ");
// fgets(pays, 50, stdin);
// enlever_saut_ligne(pays);

// printf("4. Animal : ");
// fgets(animal, 50, stdin);
// enlever_saut_ligne(animal);

// printf("5. Objet : ");
// fgets(objet, 50, stdin);
// enlever_saut_ligne(objet);

// printf("\n--- Tes reponses ---\n");
// printf("Prenom : %s\n", prenom);
// printf("Ville : %s\n", ville);
// printf("Pays : %s\n", pays);
// printf("Animal : %s\n", animal);
// printf("Objet : %s\n", objet);

// printf("\n--- Verification ---\n");

//     score += verifier_reponse("Prenom", prenom, lettre);
//     score += verifier_reponse("Ville", ville, lettre);
//     score += verifier_reponse("Pays", pays, lettre);
//     score += verifier_reponse("Animal", animal, lettre);
//     score += verifier_reponse("Objet", objet, lettre);
