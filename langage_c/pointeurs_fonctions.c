/*
 * ============================================================
 *  FICHIER  : pointeurs_fonctions.c
 *  SUJET    : Les pointeurs sur fonctions en C
 *  NIVEAU   : Intermédiaire — Leçon 7
 *  COMPILE  : gcc -Wall -Wextra pointeurs_fonctions.c -o ptf
 *  EXECUTE  : ./ptf
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * FONCTIONS UTILISÉES COMME DONNÉES (pointées)
 * ============================================================ */

/* Opérations mathématiques */
int addition(int a, int b)       { return a + b; }
int soustraction(int a, int b)   { return a - b; }
int multiplication(int a, int b) { return a * b; }
int division(int a, int b)       { return b != 0 ? a / b : 0; }

/* Fonctions de comparaison pour le tri */
int comparer_croissant(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int comparer_decroissant(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

/* Fonctions de transformation */
int doubler(int x) { return x * 2;   }
int carré(int x)   { return x * x;   }
int negatif(int x) { return -x;      }
int absolu(int x)  { return x < 0 ? -x : x; }

/* Fonctions de prédicats (retournent 0 ou 1) */
int est_pair(int x)    { return x % 2 == 0; }
int est_impair(int x)  { return x % 2 != 0; }
int est_positif(int x) { return x > 0;       }
int est_negatif(int x) { return x < 0;       }

/* Fonctions de validation */
int valider_age(int n)   { return n >= 0 && n <= 150; }
int valider_note(int n)  { return n >= 0 && n <= 20;  }
int valider_jour(int n)  { return n >= 1 && n <= 31;  }

/* Affichage */
void afficher_separateur(char *titre);
void afficher_tableau(int *tab, int n);


/* ============================================================
 * FONCTIONS D'ORDRE SUPÉRIEUR (reçoivent des pointeurs)
 * ============================================================ */

/* Applique une opération binaire sur deux entiers */
int appliquer_op(int a, int b, int (*op)(int, int)) {
    return op(a, b);   /* appel via le pointeur */
}

/* Applique une transformation sur chaque élément d'un tableau */
void transformer_tableau(int *tab, int n, int (*transform)(int)) {
    for (int i = 0; i < n; i++) {
        tab[i] = transform(tab[i]);
    }
}

/* Filtre un tableau : garde les éléments qui satisfont le prédicat */
int filtrer(int *src, int n, int *dst, int (*predicat)(int)) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (predicat(src[i])) {
            dst[count++] = src[i];
        }
    }
    return count;   /* nombre d'éléments retenus */
}

/* Réduit un tableau en une valeur avec une opération binaire */
int reduire(int *tab, int n, int init, int (*op)(int, int)) {
    int acc = init;
    for (int i = 0; i < n; i++) {
        acc = op(acc, tab[i]);
    }
    return acc;
}

/* Valide une valeur avec une fonction de validation */
int valider(int val, int (*validateur)(int), char *nom) {
    if (validateur(val)) {
        printf("  '%s' = %d → VALIDE\n", nom, val);
        return 1;
    } else {
        printf("  '%s' = %d → INVALIDE\n", nom, val);
        return 0;
    }
}


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 7 : Pointeurs sur fonctions\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — DÉCLARER UN POINTEUR SUR FONCTION
     *
     * Un pointeur sur fonction stocke l'adresse d'une fonction.
     * On peut l'appeler exactement comme la fonction originale.
     *
     * Syntaxe : type_retour (*nom_pointeur)(types_paramètres);
     *
     * La parenthèse autour de *nom est OBLIGATOIRE :
     *   int *f(int, int)   → prototype de fonction retournant int*
     *   int (*f)(int, int) → pointeur vers fonction retournant int
     * ---------------------------------------------------------- */
    afficher_separateur("1. Declarer un pointeur sur fonction");

    /* Déclaration d'un pointeur sur fonction */
    int (*pf)(int, int);   /* pf pointe vers une fonction (int,int)→int */

    /* Affectation : on prend l'adresse de la fonction */
    pf = addition;         /* sans parenthèses ! (= &addition) */

    /* Appel via le pointeur */
    int res = pf(10, 5);
    printf("pf = addition   → pf(10, 5) = %d\n", res);

    /* Réutiliser le même pointeur avec une autre fonction */
    pf = soustraction;
    printf("pf = soustraction → pf(10, 5) = %d\n", pf(10, 5));

    pf = multiplication;
    printf("pf = multiplication → pf(10, 5) = %d\n", pf(10, 5));

    pf = division;
    printf("pf = division → pf(10, 5) = %d\n\n", pf(10, 5));


    /* ----------------------------------------------------------
     * PARTIE 2 — APPELER VIA UN POINTEUR
     *
     * Deux syntaxes d'appel équivalentes :
     *   pf(args)       → syntaxe moderne (recommandée)
     *   (*pf)(args)    → syntaxe explicite (plus ancienne)
     *
     * Vérifier NULL avant d'appeler !
     * ---------------------------------------------------------- */
    afficher_separateur("2. Appeler une fonction via un pointeur");

    int (*op)(int, int) = addition;

    /* Les deux syntaxes font la même chose */
    printf("op(3, 4)    = %d  (syntaxe moderne)\n",    op(3, 4));
    printf("(*op)(3, 4) = %d  (syntaxe explicite)\n",  (*op)(3, 4));

    /* Toujours vérifier NULL avant l'appel */
    int (*peut_etre_null)(int, int) = NULL;
    printf("\nPointeur NULL : %p\n", (void*)peut_etre_null);

    if (peut_etre_null != NULL) {
        peut_etre_null(1, 2);   /* Jamais exécuté */
    } else {
        printf("Pointeur NULL → appel impossible (segfault si force)\n\n");
    }


    /* ----------------------------------------------------------
     * PARTIE 3 — PASSER UNE FONCTION EN PARAMÈTRE (CALLBACK)
     *
     * Un "callback" est une fonction passée en argument à
     * une autre fonction. C'est l'usage le plus courant
     * des pointeurs sur fonctions.
     *
     * Permet de créer des fonctions génériques qui adaptent
     * leur comportement selon la fonction reçue.
     * ---------------------------------------------------------- */
    afficher_separateur("3. Passer une fonction en parametre (callback)");

    /* appliquer_op prend une fonction comme 3e argument */
    printf("appliquer_op(20, 4, addition)        = %d\n",
           appliquer_op(20, 4, addition));
    printf("appliquer_op(20, 4, soustraction)    = %d\n",
           appliquer_op(20, 4, soustraction));
    printf("appliquer_op(20, 4, multiplication)  = %d\n",
           appliquer_op(20, 4, multiplication));
    printf("appliquer_op(20, 4, division)        = %d\n\n",
           appliquer_op(20, 4, division));

    /* Transformer chaque élément d'un tableau */
    int tab[] = {1, 2, 3, 4, 5};
    int n     = 5;

    printf("Tableau initial : ");
    afficher_tableau(tab, n);

    transformer_tableau(tab, n, doubler);
    printf("Apres doubler() : ");
    afficher_tableau(tab, n);

    transformer_tableau(tab, n, negatif);
    printf("Apres negatif() : ");
    afficher_tableau(tab, n);

    transformer_tableau(tab, n, absolu);
    printf("Apres absolu()  : ");
    afficher_tableau(tab, n);
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — qsort() : CALLBACK DE LA BIBLIOTHÈQUE STANDARD
     *
     * qsort() est l'exemple parfait de callback en C standard.
     * Elle trie n'importe quel tableau en recevant une fonction
     * de comparaison qui décide de l'ordre.
     *
     * Syntaxe :
     *   void qsort(void *tab, size_t n, size_t taille,
     *              int (*compar)(const void*, const void*));
     *
     * La fonction de comparaison doit retourner :
     *   < 0  si a doit venir avant b
     *     0  si a == b
     *   > 0  si a doit venir après b
     * ---------------------------------------------------------- */
    afficher_separateur("4. qsort() : le callback classique de stdlib");

    int nombres[] = {64, 34, 25, 12, 22, 11, 90};
    int taille    = 7;

    printf("Original    : ");
    afficher_tableau(nombres, taille);

    /* Tri croissant */
    qsort(nombres, taille, sizeof(int), comparer_croissant);
    printf("Croissant   : ");
    afficher_tableau(nombres, taille);

    /* Tri décroissant */
    qsort(nombres, taille, sizeof(int), comparer_decroissant);
    printf("Decroissant : ");
    afficher_tableau(nombres, taille);
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 5 — TABLEAU DE POINTEURS SUR FONCTIONS
     *
     * On peut créer un tableau dont chaque élément est un
     * pointeur sur une fonction. Très utile pour :
     *   - Dispatcher selon un choix (menu, commandes...)
     *   - Implémenter une machine à états
     *   - Remplacer un long switch/case
     * ---------------------------------------------------------- */
    afficher_separateur("5. Tableau de pointeurs sur fonctions");

    /* Tableau d'opérations */
    int (*ops[])(int, int) = {
        addition, soustraction, multiplication, division
    };
    const char *noms_ops[] = {
        "addition", "soustraction", "multiplication", "division"
    };
    int nb_ops = 4;

    int a = 12, b = 4;
    printf("a = %d, b = %d\n", a, b);
    for (int i = 0; i < nb_ops; i++) {
        printf("  ops[%d] (%s) : %d\n",
               i, noms_ops[i], ops[i](a, b));
    }
    printf("\n");

    /* Tableau de transformations */
    int (*transforms[])(int) = {doubler, carré, negatif, absolu};
    const char *noms_tr[] = {"doubler", "carre", "negatif", "absolu"};
    int nb_tr = 4;

    int valeur = 5;
    printf("Transformations de %d :\n", valeur);
    for (int i = 0; i < nb_tr; i++) {
        printf("  %s(%d) = %d\n", noms_tr[i], valeur, transforms[i](valeur));
    }
    printf("\n");

    /* Simulation d'un menu de calculatrice */
    printf("Simulation calculatrice (choix 2 = multiplication) :\n");
    int choix = 2;   /* 0=+, 1=-, 2=*, 3=/ */
    if (choix >= 0 && choix < nb_ops) {
        printf("  %d %s %d = %d\n",
               a, noms_ops[choix], b, ops[choix](a, b));
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — FILTRE ET RÉDUCTION AVEC CALLBACKS
     *
     * Ces patterns fonctionnels (filter, map, reduce) sont
     * rendus possibles grâce aux pointeurs sur fonctions.
     * Ce sont des opérations fondamentales en programmation.
     * ---------------------------------------------------------- */
    afficher_separateur("6. Filter et Reduce avec callbacks");

    int data[] = {-3, 1, -7, 4, -2, 6, 0, 8, -1, 5};
    int nd = 10;
    int filtres[10];
    int nf;

    printf("Tableau : ");
    afficher_tableau(data, nd);

    /* Filtrer les pairs */
    nf = filtrer(data, nd, filtres, est_pair);
    printf("Pairs       : ");
    afficher_tableau(filtres, nf);

    /* Filtrer les positifs */
    nf = filtrer(data, nd, filtres, est_positif);
    printf("Positifs    : ");
    afficher_tableau(filtres, nf);

    /* Filtrer les négatifs */
    nf = filtrer(data, nd, filtres, est_negatif);
    printf("Negatifs    : ");
    afficher_tableau(filtres, nf);

    /* Réduire (somme et produit des positifs) */
    int positifs[10];
    int np = filtrer(data, nd, positifs, est_positif);

    int somme  = reduire(positifs, np, 0, addition);
    printf("\nSomme des positifs    : %d\n", somme);

    int produit = reduire(positifs, np, 1, multiplication);
    printf("Produit des positifs  : %d\n\n", produit);


    /* ----------------------------------------------------------
     * PARTIE 7 — typedef POUR LES POINTEURS SUR FONCTIONS
     *
     * La syntaxe des pointeurs sur fonctions est verbeuse.
     * typedef simplifie les déclarations en créant un alias.
     *
     * Sans typedef : int (*f)(int, int) = addition;
     * Avec typedef : Operation f = addition;
     * ---------------------------------------------------------- */
    afficher_separateur("7. typedef pour simplifier la syntaxe");

    /* Sans typedef : syntaxe lourde */
    int (*fonc1)(int, int) = addition;
    printf("Sans typedef : int (*fonc1)(int, int) = addition\n");
    printf("  fonc1(3, 4) = %d\n\n", fonc1(3, 4));

    /* Avec typedef : syntaxe claire */
    typedef int (*Operation)(int, int);       /* alias pour une op binaire */
    typedef int (*Predicat)(int);             /* alias pour un prédicat    */
    typedef int (*Validateur)(int);           /* alias pour un validateur  */
    typedef int (*Transformation)(int);       /* alias pour une transform  */

    Operation op1 = multiplication;
    Operation op2 = division;
    Predicat  pred = est_pair;
    Transformation tr = doubler;

    printf("Avec typedef Operation :\n");
    printf("  op1(6, 7) = %d  (multiplication)\n", op1(6, 7));
    printf("  op2(15, 3) = %d  (division)\n",       op2(15, 3));
    printf("  pred(4) = %d  (est_pair)\n",           pred(4));
    printf("  tr(8) = %d  (doubler)\n\n",            tr(8));

    /* Tableau avec typedef : beaucoup plus lisible */
    Operation calculatrice[] = {addition, soustraction, multiplication, division};
    printf("Tableau avec typedef :\n");
    for (int i = 0; i < 4; i++) {
        printf("  calculatrice[%d](10, 2) = %d\n",
               i, calculatrice[i](10, 2));
    }

    /* Validation avec typedef */
    printf("\nValidation avec typedef Validateur :\n");
    Validateur validators[] = {valider_age, valider_note, valider_jour};
    const char *vnames[]    = {"age", "note", "jour"};
    int vals[]              = {25, 18, 45};

    for (int i = 0; i < 3; i++) {
        valider(vals[i], validators[i], vnames[i]);
    }
    printf("\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  int (*pf)(int, int);      → declaration\n");
    printf("  pf = ma_fonction;         → affectation\n");
    printf("  pf(a, b);                 → appel direct\n");
    printf("  (*pf)(a, b);              → appel explicite\n");
    printf("  func(a, b, ma_fonction)   → callback\n");
    printf("  int (*tab[])(int, int)    → tableau de pf\n");
    printf("  typedef int (*Op)(int,int)→ alias lisible\n");
    printf("  qsort(tab, n, sz, cmp)    → exemple stdlib\n");
    printf("  Toujours verifier != NULL avant appel !\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS UTILITAIRES
 * ============================================================ */
void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

void afficher_tableau(int *tab, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", tab[i], i < n-1 ? ", " : "");
    }
    printf("]\n");
}