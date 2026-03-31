/*
 * ============================================================
 *  FICHIER  : tableaux.c
 *  SUJET    : Les tableaux en C
 *  NIVEAU   : Débutant — Leçon 6
 *  COMPILE  : gcc tableaux.c -o tableaux
 *  EXECUTE  : ./tableaux
 * ============================================================
 */

#include <stdio.h>

int main() {

    printf("==============================================\n");
    printf("  LECON 6 : Les tableaux\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — DÉCLARER ET INITIALISER UN TABLEAU 1D
     *
     * Un tableau est une suite de cases mémoire contiguës
     * qui stockent des valeurs du MÊME type.
     *
     * Syntaxe : type nom[taille] = {val1, val2, ...};
     *
     * Les indices vont toujours de 0 à taille-1.
     * Un tableau de 5 éléments a les indices 0, 1, 2, 3, 4.
     * ---------------------------------------------------------- */
    printf("--- 1. Declaration et initialisation ---\n");

    /* Déclaration avec initialisation complète */
    int notes[5] = {12, 15, 9, 18, 11};

    /* Déclaration puis initialisation élément par élément */
    int scores[3];
    scores[0] = 100;
    scores[1] = 85;
    scores[2] = 92;

    /* Initialisation partielle : le reste est mis à 0 */
    int partiel[5] = {1, 2};   /* → {1, 2, 0, 0, 0} */

    /* Initialisation complète à zéro */
    int zeros[5] = {0};        /* → {0, 0, 0, 0, 0} */

    /* Taille déduite automatiquement */
    int auto_taille[] = {10, 20, 30, 40};  /* taille = 4 */

    printf("notes    : ");
    for (int i = 0; i < 5; i++) printf("%d ", notes[i]);
    printf("\n");

    printf("scores   : ");
    for (int i = 0; i < 3; i++) printf("%d ", scores[i]);
    printf("\n");

    printf("partiel  : ");
    for (int i = 0; i < 5; i++) printf("%d ", partiel[i]);
    printf("\n");

    printf("zeros    : ");
    for (int i = 0; i < 5; i++) printf("%d ", zeros[i]);
    printf("\n");

    printf("auto     : ");
    for (int i = 0; i < 4; i++) printf("%d ", auto_taille[i]);
    printf("\n\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — ACCÉDER ET MODIFIER UN ÉLÉMENT PAR SON INDEX
     *
     * On accède à un élément avec : nom[index]
     * L'index commence à 0 (pas à 1 !).
     * On peut lire et modifier un élément de la même façon.
     * ---------------------------------------------------------- */
    printf("--- 2. Acces et modification par index ---\n");

    int temperatures[5] = {22, 25, 19, 28, 21};

    /* Lire un élément */
    printf("temperatures[0] = %d  (premier)\n",  temperatures[0]);
    printf("temperatures[2] = %d  (troisieme)\n", temperatures[2]);
    printf("temperatures[4] = %d  (dernier)\n",  temperatures[4]);

    /* Modifier un élément */
    printf("\nAvant modification : temperatures[1] = %d\n", temperatures[1]);
    temperatures[1] = 30;
    printf("Apres modification : temperatures[1] = %d\n", temperatures[1]);

    /* Utiliser une variable comme index */
    int idx = 3;
    printf("temperatures[idx=%d] = %d\n\n", idx, temperatures[idx]);


    /* ----------------------------------------------------------
     * PARTIE 3 — PARCOURIR UN TABLEAU AVEC UNE BOUCLE
     *
     * La boucle for est la méthode standard pour parcourir
     * tous les éléments d'un tableau.
     * On commence à 0 et on s'arrête AVANT la taille.
     * ---------------------------------------------------------- */
    printf("--- 3. Parcourir un tableau ---\n");

    int valeurs[6] = {3, 7, 1, 9, 4, 6};
    int taille = 6;

    /* Affichage simple */
    printf("Elements : ");
    for (int i = 0; i < taille; i++) {
        printf("valeurs[%d]=%d  ", i, valeurs[i]);
    }
    printf("\n");

    /* Recherche du minimum et du maximum */
    int min = valeurs[0];
    int max = valeurs[0];

    for (int i = 1; i < taille; i++) {
        if (valeurs[i] < min) min = valeurs[i];
        if (valeurs[i] > max) max = valeurs[i];
    }
    printf("Minimum : %d\n", min);
    printf("Maximum : %d\n", max);

    /* Calcul de la somme et de la moyenne */
    int somme = 0;
    for (int i = 0; i < taille; i++) {
        somme += valeurs[i];
    }
    printf("Somme   : %d\n", somme);
    printf("Moyenne : %.2f\n\n", (float)somme / taille);


    /* ----------------------------------------------------------
     * PARTIE 4 — CALCULER LA TAILLE AVEC sizeof
     *
     * sizeof(tableau) retourne le nombre total d'octets.
     * sizeof(tableau[0]) retourne la taille d'un élément.
     * La division donne le nombre d'éléments.
     *
     * C'est la bonne façon de ne pas coder la taille en dur.
     * ---------------------------------------------------------- */
    printf("--- 4. Taille avec sizeof ---\n");

    int mois[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    int nb_elements = sizeof(mois) / sizeof(mois[0]);

    printf("sizeof(mois)      = %lu octets\n",  sizeof(mois));
    printf("sizeof(mois[0])   = %lu octets\n",  sizeof(mois[0]));
    printf("Nombre d'elements = %d\n", nb_elements);

    /* Utilisation dans la boucle : plus besoin de coder 12 en dur */
    int total_jours = 0;
    for (int i = 0; i < nb_elements; i++) {
        total_jours += mois[i];
    }
    printf("Jours dans l'annee : %d\n\n", total_jours);


    /* ----------------------------------------------------------
     * PARTIE 5 — TABLEAUX 2D (MATRICES)
     *
     * Un tableau 2D est un tableau de tableaux.
     * On l'imagine comme une grille : lignes × colonnes.
     *
     * Syntaxe : type nom[nb_lignes][nb_colonnes];
     * Accès   : nom[ligne][colonne]
     *
     * Les indices commencent à 0 pour les lignes ET les colonnes.
     * ---------------------------------------------------------- */
    printf("--- 5. Tableau 2D (matrice) ---\n");

    /* Déclaration et initialisation */
    int matrice[3][4] = {
        {1,  2,  3,  4},   /* ligne 0 */
        {5,  6,  7,  8},   /* ligne 1 */
        {9, 10, 11, 12}    /* ligne 2 */
    };

    /* Accès à un élément */
    printf("matrice[0][0] = %d  (ligne 0, col 0)\n", matrice[0][0]);
    printf("matrice[1][2] = %d  (ligne 1, col 2)\n", matrice[1][2]);
    printf("matrice[2][3] = %d  (ligne 2, col 3)\n", matrice[2][3]);

    /* Affichage de la matrice complète */
    printf("\nMatrice complete :\n");
    for (int i = 0; i < 3; i++) {
        printf("  ligne %d : ", i);
        for (int j = 0; j < 4; j++) {
            printf("%3d", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — PARCOURIR UN TABLEAU 2D
     *
     * On utilise deux boucles imbriquées :
     *   - la boucle extérieure parcourt les LIGNES
     *   - la boucle intérieure parcourt les COLONNES
     * ---------------------------------------------------------- */
    printf("--- 6. Parcourir un tableau 2D ---\n");

    int grille[3][3] = {
        {2, 4, 6},
        {1, 3, 5},
        {7, 8, 9}
    };

    /* Somme de toute la grille */
    int total = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            total += grille[i][j];
        }
    }
    printf("Somme de la grille : %d\n", total);

    /* Somme de chaque ligne */
    printf("Somme par ligne :\n");
    for (int i = 0; i < 3; i++) {
        int somme_ligne = 0;
        for (int j = 0; j < 3; j++) {
            somme_ligne += grille[i][j];
        }
        printf("  ligne %d : %d\n", i, somme_ligne);
    }

    /* Somme de chaque colonne */
    printf("Somme par colonne :\n");
    for (int j = 0; j < 3; j++) {
        int somme_col = 0;
        for (int i = 0; i < 3; i++) {
            somme_col += grille[i][j];
        }
        printf("  colonne %d : %d\n", j, somme_col);
    }

    /* Trouver le maximum dans la grille */
    int max_grille = grille[0][0];
    int max_li = 0, max_co = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i][j] > max_grille) {
                max_grille = grille[i][j];
                max_li = i;
                max_co = j;
            }
        }
    }
    printf("Maximum : %d a la position [%d][%d]\n\n",
           max_grille, max_li, max_co);


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    printf("==============================================\n");
    printf("  RECAPITULATIF\n");
    printf("==============================================\n");
    printf("  Declarer  : int tab[5] = {1,2,3,4,5};\n");
    printf("  Acceder   : tab[index]  (index : 0 a N-1)\n");
    printf("  Modifier  : tab[2] = 99;\n");
    printf("  Parcourir : for (i=0; i<taille; i++)\n");
    printf("  Taille    : sizeof(tab)/sizeof(tab[0])\n");
    printf("  2D declarer  : int mat[3][4];\n");
    printf("  2D acceder   : mat[ligne][colonne]\n");
    printf("  2D parcourir : 2 boucles imbriquees\n");
    printf("\n");

    return 0;
}