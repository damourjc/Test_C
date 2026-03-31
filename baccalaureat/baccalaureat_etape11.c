/*
 * ==============================================================================================================================================================================
 *  FICHIER  : baccalaureat_etape11.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 1 - Étape 11 : Menu du jeu
 *
 *  DESCRIPTION :
 *  Ce programme (plus optimisé) genere : 
 *      - Fonction void enlever_saut_ligne(char *mot)
 *      - Fonction int verifier_reponse(char *categorie, char *mot, char lettre) + ajoute du point score s'il remplit condition (modifié : si "vide")
 *      - Ajout d'une boucle menu (1 : Jouer ou 2 : Quitter)
 *      - Une boucle de jeu (rejouer)
 *      - Une lettre aleatoire
 *      - Tableau catégorie et réponse
 *      - Boucle saisir et répondre
 *      - Boucle affichage des réponses
 *      - Vérifier les réponses avec la lettre aléatoire + si "vide" (version optimisé)
 *      - Afficher un score final
 *      - Demande au joueur s'il veut rejouer
 *  
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape11.c -o baccalaureat_etape11 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape11.c -o baccalaureat_etape11.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape11
 * 
 *  Sous Windows   : baccalaureat_etape11.exe
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

    srand(time(NULL));

    int choix;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Jouer\n");
        printf("2. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1){

            int rejouer;

            do {
                printf("=== Jeu du Baccalaureat ===\n\n");

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

                printf("\nVoulez-vous rejouer ? (1 = oui, 0 = non) : ");
                scanf("%d", &rejouer);
                getchar();
                
            } while (rejouer == 1);
        }

    } while (choix != 2);
    
    return 0;
}