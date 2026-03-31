/*
 * ============================================================
 *  FICHIER  : boucles.c
 *  SUJET    : Les boucles en C
 *  NIVEAU   : Débutant — Leçon 5
 *  COMPILE  : gcc boucles.c -o boucles
 *  EXECUTE  : ./boucles
 * ============================================================
 */

#include <stdio.h>

int main() {

    printf("==============================================\n");
    printf("  LECON 5 : Les boucles\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — BOUCLE for
     *
     * La boucle for est utilisée quand on connaît à l'avance
     * le nombre d'itérations.
     *
     * Syntaxe :
     *   for (initialisation; condition; increment) {
     *       // code répété
     *   }
     *
     * Les 3 parties :
     *   initialisation : exécutée UNE seule fois au départ
     *   condition       : vérifiée AVANT chaque itération
     *   incrément       : exécuté APRÈS chaque itération
     * ---------------------------------------------------------- */
    printf("--- 1. Boucle for ---\n");

    int i;

    /* Compter de 0 à 4 */
    printf("0 a 4 : ");
    for (i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    /* Compter de 1 à 10 */
    printf("1 a 10 : ");
    for (i = 1; i <= 10; i++) {
        printf("%d ", i);
    }
    printf("\n");

    /* Compter à rebours */
    printf("Rebours : ");
    for (i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n");

    /* Pas de 2 */
    printf("Pairs  : ");
    for (i = 0; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    /* Pas de 3 */
    printf("x3     : ");
    for (i = 0; i <= 15; i += 3) {
        printf("%d ", i);
    }
    printf("\n\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — BOUCLE while
     *
     * La boucle while répète un bloc TANT QU'une condition
     * est vraie. Elle est préférée quand on ne connaît pas
     * à l'avance le nombre d'itérations.
     *
     * Syntaxe :
     *   while (condition) {
     *       // code répété
     *   }
     *
     * ATTENTION : si la condition ne devient jamais fausse,
     * la boucle tourne à l'infini (boucle infinie).
     * ---------------------------------------------------------- */
    printf("--- 2. Boucle while ---\n");

    /* Compte à rebours */
    printf("Compte a rebours : ");
    int compteur = 5;
    while (compteur >= 1) {
        printf("%d ", compteur);
        compteur--;           /* Ne pas oublier ! Sinon boucle infinie */
    }
    printf("Partez !\n");

    /* Diviser par 2 jusqu'à atteindre 1 */
    printf("Divisions par 2 : ");
    int n = 64;
    while (n >= 1) {
        printf("%d ", n);
        n /= 2;
    }
    printf("\n");

    /* Trouver la première puissance de 2 > 1000 */
    int puissance = 1;
    while (puissance <= 1000) {
        puissance *= 2;
    }
    printf("Premiere puissance de 2 > 1000 : %d\n\n", puissance);


    /* ----------------------------------------------------------
     * PARTIE 3 — BOUCLE do-while
     *
     * La boucle do-while exécute le bloc UNE FOIS d'abord,
     * puis vérifie la condition.
     * Elle s'exécute donc TOUJOURS au moins une fois,
     * même si la condition est fausse dès le départ.
     *
     * Syntaxe :
     *   do {
     *       // code répété
     *   } while (condition);   ← point-virgule obligatoire !
     * ---------------------------------------------------------- */
    printf("--- 3. Boucle do-while ---\n");

    /* Exemple simple */
    int x = 1;
    printf("Puissances de 2 : ");
    do {
        printf("%d ", x);
        x *= 2;
    } while (x <= 32);
    printf("\n");

    /* Différence clé : s'exécute même si condition fausse */
    int val = 100;
    printf("while  (val < 10) avec val=100 : ");
    while (val < 10) {              /* Condition fausse dès le départ */
        printf("jamais affiche");   /* N'est JAMAIS exécuté */
    }
    printf("(rien affiche)\n");

    printf("do-while (val < 10) avec val=100 : ");
    do {
        printf("affiche une fois !");  /* Exécuté UNE fois quand même */
    } while (val < 10);               /* Puis condition vérifiée → fausse */
    printf("\n\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — CHOISIR LA BONNE BOUCLE
     *
     * for     → nombre d'itérations CONNU à l'avance
     * while   → nombre d'itérations INCONNU, condition vérifiée avant
     * do-while → on veut s'assurer d'exécuter le bloc AU MOINS UNE FOIS
     * ---------------------------------------------------------- */
    printf("--- 4. Choisir la bonne boucle ---\n");

    /* for : afficher les 5 premiers multiples de 7 */
    printf("for     → 5 premiers multiples de 7 : ");
    for (i = 1; i <= 5; i++) {
        printf("%d ", 7 * i);
    }
    printf("\n");

    /* while : chercher le premier multiple de 13 > 100 */
    printf("while   → premier multiple de 13 > 100 : ");
    int m = 13;
    while (m <= 100) {
        m += 13;
    }
    printf("%d\n", m);

    /* do-while : menu (toujours affiché au moins une fois) */
    printf("do-while→ menu affiché au moins une fois\n");
    int choix = 0;
    do {
        printf("          [Menu] 1-Jouer  2-Options  3-Quitter\n");
        choix = 3;   /* Simulation d'un choix utilisateur */
        printf("          Choix simule : %d\n", choix);
    } while (choix != 3);
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 5 — break : SORTIR D'UNE BOUCLE
     *
     * break interrompt immédiatement la boucle en cours.
     * L'exécution reprend à la première instruction
     * qui suit la boucle.
     * ---------------------------------------------------------- */
    printf("--- 5. break ---\n");

    /* Chercher le premier multiple de 7 > 50 */
    printf("Premier multiple de 7 > 50 : ");
    for (i = 1; ; i++) {        /* Boucle sans condition de fin ! */
        if (7 * i > 50) {
            printf("%d\n", 7 * i);
            break;              /* Sort de la boucle dès trouvé */
        }
    }

    /* Trouver un nombre dans un tableau */
    int tableau[] = {4, 7, 2, 9, 1, 5, 8};
    int taille    = 7;
    int cible     = 9;
    int trouve    = 0;

    printf("Recherche de %d dans le tableau : ", cible);
    for (i = 0; i < taille; i++) {
        if (tableau[i] == cible) {
            printf("trouve a l'index %d !\n", i);
            trouve = 1;
            break;              /* Inutile de continuer */
        }
    }
    if (!trouve) {
        printf("non trouve.\n");
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — continue : PASSER À L'ITÉRATION SUIVANTE
     *
     * continue saute le reste du bloc courant et passe
     * directement à l'itération suivante.
     * Contrairement à break, il NE sort PAS de la boucle.
     * ---------------------------------------------------------- */
    printf("--- 6. continue ---\n");

    /* Afficher uniquement les nombres pairs */
    printf("Pairs de 0 a 10 (avec continue) : ");
    for (i = 0; i <= 10; i++) {
        if (i % 2 != 0) {
            continue;   /* Saute les impairs */
        }
        printf("%d ", i);
    }
    printf("\n");

    /* Afficher les nombres sauf les multiples de 3 */
    printf("1 a 15 sauf multiples de 3 : ");
    for (i = 1; i <= 15; i++) {
        if (i % 3 == 0) {
            continue;   /* Saute 3, 6, 9, 12, 15 */
        }
        printf("%d ", i);
    }
    printf("\n");

    /* Calculer la somme des nombres positifs uniquement */
    int nombres[] = {3, -1, 4, -2, 7, -5, 2};
    int somme = 0;
    printf("Somme des positifs dans {3,-1,4,-2,7,-5,2} : ");
    for (i = 0; i < 7; i++) {
        if (nombres[i] < 0) {
            continue;   /* Ignorer les négatifs */
        }
        somme += nombres[i];
    }
    printf("%d\n\n", somme);


    /* ----------------------------------------------------------
     * PARTIE 7 — BOUCLES IMBRIQUÉES
     *
     * On peut mettre une boucle à l'intérieur d'une autre.
     * La boucle intérieure s'exécute EN ENTIER à chaque
     * itération de la boucle extérieure.
     * Très utile pour les tableaux 2D, les matrices, les grilles.
     * ---------------------------------------------------------- */
    printf("--- 7. Boucles imbriquees ---\n");

    int j;

    /* Table de multiplication (3x3) */
    printf("Table de multiplication (1 a 4) :\n");
    printf("     ");
    for (j = 1; j <= 4; j++) printf("%4d", j);
    printf("\n     ----+----+----+----\n");

    for (i = 1; i <= 4; i++) {
        printf("%3d |", i);
        for (j = 1; j <= 4; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }
    printf("\n");

    /* Dessin d'un triangle */
    printf("Triangle d'etoiles :\n");
    for (i = 1; i <= 5; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");

    /* Dessin d'un carré */
    printf("Carre 4x4 :\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("# ");
        }
        printf("\n");
    }
    printf("\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    printf("==============================================\n");
    printf("  RECAPITULATIF\n");
    printf("==============================================\n");
    printf("  for      → nb iterations connu\n");
    printf("  while    → condition verifiee AVANT\n");
    printf("  do-while → condition verifiee APRES (min 1 fois)\n");
    printf("  break    → sort de la boucle\n");
    printf("  continue → passe a l'iteration suivante\n");
    printf("  imbriquees → boucle dans une boucle\n");
    printf("\n");

    return 0;
}