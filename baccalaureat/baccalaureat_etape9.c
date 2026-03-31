/*
 * ==============================================================================================================================================================================
 *  FICHIER  : baccalaureat_etape9.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 1 - Étape 9 : Système de score amélioré
 *
 *  DESCRIPTION :
 *  Ce programme (plus optimisé) genere : 
 *      - Ajout une fonction void enlever_saut_ligne(char *mot)
 *      - Ajout d'une fonction int verifier_reponse(char *categorie, char *mot, char lettre) + ajoute du point score s'il remplit condition (modifié : si "vide")
 *      - Une lettre aleatoire
 *      - Tableau catégorie et réponse
 *      - Boucle saisir et répondre
 *      - Boucle affichage des réponses
 *      - Vérifier les réponses avec la lettre aléatoire + si "vide" (version optimisé)
 *      - Afficher un score final
 *  
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape9.c -o baccalaureat_etape9 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape9.c -o baccalaureat_etape9.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape9
 * 
 *  Sous Windows   : baccalaureat_etape9.exe
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

    if (mot[0] == '\0') {
        printf("%s invalide (vide)\n", categorie);
        return 0;
    }

    if (toupper(mot[0]) == lettre) {

        int longueur = 0;
        for (int i = 0; mot[i] != '\0'; i++) {
            longueur++;
        }

        if (longueur > 5) {
            printf("%s valide (+2 points)\n", categorie);
            return 2;
        } else {
            printf("%s valide (+1 point)\n", categorie);
            return 1;
        }

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

    int nb_categories = 5;

    // Saisie utilisateur
    for (int i = 0; i < nb_categories; i++) {
        printf("%d. %s : ", i + 1, categories[i]);
        fgets(reponses[i], 50, stdin);
        enlever_saut_ligne(reponses[i]);
}

    // Affichage des réponses
    printf("\n--- Tes reponses ---\n");

    for (int i = 0; i < nb_categories; i++) {
        printf("%s : %s\n", categories[i], reponses[i]);
    }

    // Vérification des réponses
    int score = 0;

    printf("\n--- Verification ---\n");

    for (int i = 0; i < nb_categories; i++) {
        score += verifier_reponse(categories[i], reponses[i], lettre);
    }

    printf("\nScore : %d / %d\n", score, nb_categories * 2);
    
    return 0;
}