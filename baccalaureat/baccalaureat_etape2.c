/*
 * ====================================================================================
 *  FICHIER  : baccalaureat_etape3.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 2 - Étape 2 : Afficher les catégories
 *
 *  DESCRIPTION :
 *  Ce programme genere une lettre aleatoire, permet au joueur de remplir plusieurs 
 *  categories.
 *
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape2.c -o baccalaureat_etape2 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape2.c -o baccalaureat_etape2.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape2
 * 
 *  Sous Windows   : baccalaureat_etape2.exe
 * ====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    printf("Bienvenue dans le jeu du Baccalaureat !\n\n");

    srand(time(NULL));
    char lettre = 'A' + rand() % 26;

    printf("Lettre choisie : %c\n\n", lettre);

    printf("Categories :\n");
    printf("1. Prenom :\n");
    printf("2. Ville :\n");
    printf("3. Pays :\n");
    printf("4. Animal :\n");
    printf("5. Objet :\n");

    return 0;
}