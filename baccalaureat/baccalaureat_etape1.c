/*
 * ====================================================================================
 *  FICHIER  : baccalaureat_etape1.c
 *  PROJET   : Jeu du Baccalaureat
 *  ETAPE    : Phase 1 — Étape 1 : Générer une lettre aléatoire
 *
 *  DESCRIPTION :
 *  Ce programme genere une lettre aleatoire.
 *
 *  COMPILATION :
 *  Sous Linux/Mac : gcc baccalaureat_etape1.c -o baccalaureat_etape1 -Wall -g
 * 
 *  Sous Windows   : gcc baccalaureat_etape1.c -o baccalaureat_etape1.exe -Wall -g
 *
 *  EXECUTION :
 *  Sous Linux/Mac : ./baccalaureat_etape1
 * 
 *  Sous Windows   : baccalaureat_etape1.exe
 * ====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    printf("Bienvenue dans le jeu du Baccalaureat !\n");

    // Initialiser le générateur aléatoire
    srand(time(NULL));

    // Générer une lettre entre A et Z
    char lettre = 'A' + rand() % 26;

    // Afficher la lettre
    printf("Lettre choisie : %c\n", lettre);

    return 0;
}