/*
 * ==============================================================================================================================================================================
 *  FICHIER  : baccalaureat_etapeA1.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 2 - Étape A.1 : STRUCT (ultra important)
 *
 *  DESCRIPTION :
 *  Ce programme (plus optimisé) genere : 
 *      - voir description "baccalaureat_etape1.c" à "baccalaureat_etape14.c"
 *      - 
 *  
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etapeA1.c -o baccalaureat_etapeA1 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etapeA1.c -o baccalaureat_etapeA1.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etapeA1
 * 
 *  Sous Windows   : baccalaureat_etapeA1.exe
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

typedef struct {
    char nom[50];
    int score;
} Joueur;

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

        if (choix != 1 && choix != 2) {
        printf("Choix invalide !\n");
        }

        if (choix == 1){

            int rejouer;

            do {
                printf("=== Jeu du Baccalaureat ===\n\n");

                int nb_joueurs = 2;

                Joueur joueurs[2];

                for (int i = 0; i < nb_joueurs; i++) {
                    printf("Nom du joueur %d : ", i + 1);
                    fgets(joueurs[i].nom, 50, stdin);
                    enlever_saut_ligne(joueurs[i].nom);
                }
                
                int difficulte;

                printf("\nChoisir la difficulte :\n");
                printf("1. Facile (5 categories)\n");
                printf("2. Moyen (7 categories)\n");
                printf("3. Difficile (10 categories)\n");
                printf("Choix : ");
                scanf("%d", &difficulte);
                getchar();

                int nb_categories;

                if (difficulte == 1) {
                    nb_categories = 5;
                } else if (difficulte == 2) {
                    nb_categories = 7;
                } else {
                    nb_categories = 10;
                }

                char lettre = 'A' + rand() % 26;

                printf("Lettre : %c\n\n", lettre);

                // Variables pour stocker les réponses
                char *toutes_categories[] = { "Prenom", "Ville", "Pays", "Animal", "Objet", "Fruit", "Metier", "Couleur", "Sport", "Marque" };

                char reponses[10][50]; // max = 10;

                for (int j = 0; j < nb_joueurs; j++) {

                    system("cls");   // Windows
                    // system("clear"); // Linux/Mac

                    printf("\n=== Tour de %s ===\n", joueurs[j].nom);

                    int score = 0;

                    // AVANT saisie
                    time_t debut = time(NULL);

                    // Saisie
                    for (int i = 0; i < nb_categories; i++) {
                        printf("%d. %s : ", i + 1, toutes_categories[i]);
                        fgets(reponses[i], 50, stdin);
                        enlever_saut_ligne(reponses[i]);
                    }

                    // APRÈS saisie
                    time_t fin = time(NULL);
                    int temps_ecoule = (int)(fin - debut);

                    // Vérification
                    if (temps_ecoule > 30) {
                        printf("Temps depasse ! Score annule.\n");
                        score = 0;
                    } else {
                        printf("\n--- Verification ---\n");

                        for (int i = 0; i < nb_categories; i++) {
                            score += verifier_reponse(toutes_categories[i], reponses[i], lettre);
                        }
                    }

                    // Affichage des réponses
                    printf("\n--- Tes reponses ---\n");

                    for (int i = 0; i < nb_categories; i++) {
                        printf("%s : %s\n", toutes_categories[i], reponses[i]);
                    }

                    // Affichage temps
                    printf("\nTemps ecoule : %d secondes\n", temps_ecoule);

                    printf("\nScore : %d / %d\n", score, nb_categories * 2);

                    joueurs[j].score = score;
                }

                printf("\n=== RESULTATS ===\n");

                for (int i = 0; i < nb_joueurs; i++) {
                    printf("%s : %d points\n", joueurs[i].nom, joueurs[i].score);
                }

                if (joueurs[0].score > joueurs[1].score) {
                    printf("Gagnant : %s\n", joueurs[0].nom);
                } else if (joueurs[1].score > joueurs[0].score) {
                    printf("Gagnant : %s\n", joueurs[1].nom);
                } else {
                    printf("Egalite !\n");
                }

                printf("\nVoulez-vous rejouer ? (1 = oui, 0 = non) : ");
                scanf("%d", &rejouer);
                getchar();
                
            } while (rejouer == 1);
        }

    } while (choix != 2);
    
    return 0;
}