/*
 * ============================================================
 *  FICHIER  : pointeurs.c
 *  SUJET    : Les pointeurs en C
 *  NIVEAU   : Intermédiaire — Leçon 1
 *  COMPILE  : gcc -Wall -Wextra pointeurs.c -o pointeurs
 *  EXECUTE  : ./pointeurs
 * ============================================================
 */

#include <stdio.h>

/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);

/* Fonctions démontrant le passage par adresse */
void incrementer(int *p);
void echanger(int *a, int *b);
void doubler_tableau(int *tab, int taille);

/* Fonctions avec pointeurs génériques */
void afficher_octets(void *ptr, int taille);


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 1 : Les pointeurs\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — QU'EST-CE QU'UNE ADRESSE MÉMOIRE ?
     *
     * La mémoire RAM est comme une longue rue avec des maisons
     * numérotées. Chaque maison = 1 octet.
     * Chaque variable occupe une ou plusieurs maisons.
     * L'adresse mémoire = le numéro de la première maison.
     *
     * & (esperluette) : opérateur "adresse de"
     *   → donne l'adresse mémoire d'une variable
     * ---------------------------------------------------------- */
    afficher_separateur("1. Adresses memoire");

    int    age     = 25;
    float  taille  = 1.75f;
    char   lettre  = 'A';

    /* %p affiche une adresse en hexadécimal */
    printf("Variable 'age'    : valeur=%d, adresse=%p\n",
           age, (void*)&age);
    printf("Variable 'taille' : valeur=%.2f, adresse=%p\n",
           taille, (void*)&taille);
    printf("Variable 'lettre' : valeur=%c, adresse=%p\n",
           lettre, (void*)&lettre);

    printf("\nsizeof(int)   = %lu → occupe %lu adresse(s)\n",
           sizeof(int), sizeof(int));
    printf("sizeof(float) = %lu → occupe %lu adresse(s)\n",
           sizeof(float), sizeof(float));
    printf("sizeof(char)  = %lu → occupe %lu adresse(s)\n\n",
           sizeof(char), sizeof(char));


    /* ----------------------------------------------------------
     * PARTIE 2 — DÉCLARER ET UTILISER UN POINTEUR
     *
     * Un pointeur est une variable qui CONTIENT une adresse.
     * Il "pointe vers" une autre variable.
     *
     * Déclaration : type *nom_pointeur;
     *   → l'étoile * fait partie du TYPE, pas du nom
     *
     * Deux opérateurs fondamentaux :
     *   &variable  → donne l'adresse de la variable
     *   *pointeur  → accède à la valeur pointée (déréférencement)
     * ---------------------------------------------------------- */
    afficher_separateur("2. Declarer et utiliser un pointeur");

    int valeur = 42;
    int *p;          /* p est un pointeur vers un int */

    p = &valeur;     /* p POINTE VERS valeur (stocke son adresse) */

    printf("valeur       = %d\n",   valeur);
    printf("&valeur      = %p\n",   (void*)&valeur);
    printf("p            = %p\n",   (void*)p);      /* même adresse */
    printf("*p           = %d\n\n", *p);            /* valeur pointée = 42 */

    /* Modifier la valeur via le pointeur */
    *p = 100;        /* équivalent à : valeur = 100 */
    printf("Apres *p = 100 :\n");
    printf("valeur = %d  (modifiee via le pointeur !)\n\n", valeur);

    /* Schéma mental :
     *   valeur [42] ← p pointe ici
     *   p      [adresse de valeur]
     *   *p     → déréférence = accède à [42]
     */


    /* ----------------------------------------------------------
     * PARTIE 3 — RELATION ENTRE POINTEURS ET TABLEAUX
     *
     * En C, le nom d'un tableau EST une adresse.
     * Il pointe vers le PREMIER élément du tableau.
     * On peut donc utiliser un pointeur pour parcourir un tableau.
     *
     * tab == &tab[0]   (le nom du tableau = adresse de tab[0])
     * tab[i] == *(tab + i)   (deux notations équivalentes)
     * ---------------------------------------------------------- */
    afficher_separateur("3. Pointeurs et tableaux");

    int tab[] = {10, 20, 30, 40, 50};
    int *pt   = tab;   /* pt pointe sur le premier élément */

    printf("tab      = %p  (adresse du tableau)\n",  (void*)tab);
    printf("&tab[0]  = %p  (adresse de tab[0])\n",   (void*)&tab[0]);
    printf("pt       = %p  (pointe sur tab[0])\n\n", (void*)pt);

    /* Les deux notations sont équivalentes */
    printf("Deux notations identiques :\n");
    for (int i = 0; i < 5; i++) {
        printf("  tab[%d] = %d  ←→  *(tab+%d) = %d\n",
               i, tab[i], i, *(tab + i));
    }

    /* Parcourir avec un pointeur */
    printf("\nParcours par pointeur :\n");
    int *cur = tab;
    for (int i = 0; i < 5; i++) {
        printf("  *cur = %d  (adresse %p)\n", *cur, (void*)cur);
        cur++;   /* avance d'un int (4 octets) */
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — ARITHMÉTIQUE DE POINTEURS
     *
     * On peut faire des calculs sur les pointeurs.
     * p + 1 ne signifie pas "adresse + 1 octet" mais
     * "adresse + 1 élément du type pointé".
     *
     * Pour un int* : p + 1 avance de sizeof(int) = 4 octets
     * Pour un char*: p + 1 avance de sizeof(char) = 1 octet
     *
     * Opérations autorisées :
     *   p + n   → avance de n éléments
     *   p - n   → recule de n éléments
     *   p++, p-- → incrémentation/décrémentation
     *   p1 - p2 → distance en nombre d'éléments entre deux pointeurs
     * ---------------------------------------------------------- */
    afficher_separateur("4. Arithmetique de pointeurs");

    int nombres[] = {1, 2, 3, 4, 5};
    int *debut    = nombres;
    int *fin      = nombres + 4;  /* pointe sur le dernier élément */

    printf("debut    pointe sur nombres[0] = %d  (adresse %p)\n",
           *debut, (void*)debut);
    printf("debut+1  pointe sur nombres[1] = %d  (adresse %p)\n",
           *(debut+1), (void*)(debut+1));
    printf("debut+2  pointe sur nombres[2] = %d  (adresse %p)\n",
           *(debut+2), (void*)(debut+2));
    printf("fin      pointe sur nombres[4] = %d  (adresse %p)\n",
           *fin, (void*)fin);

    /* Distance entre deux pointeurs */
    printf("\nfin - debut = %td elements\n", fin - debut);

    /* Différence d'adresses en octets */
    printf("Distance en octets = %td\n\n",
           (char*)fin - (char*)debut);


    /* ----------------------------------------------------------
     * PARTIE 5 — POINTEURS ET FONCTIONS
     *             MODIFIER UNE VARIABLE DEPUIS UNE FONCTION
     *
     * En C, les arguments sont copiés (passage par valeur).
     * Pour qu'une fonction modifie la variable originale,
     * on lui passe son ADRESSE (pointeur).
     * La fonction déréférence le pointeur pour modifier l'original.
     * ---------------------------------------------------------- */
    afficher_separateur("5. Modifier une variable via une fonction");

    int compteur = 10;
    printf("Avant incrementer() : compteur = %d\n", compteur);
    incrementer(&compteur);   /* on passe l'ADRESSE */
    printf("Apres incrementer() : compteur = %d\n\n", compteur);

    /* Échanger deux variables — impossible sans pointeurs ! */
    int x = 5, y = 8;
    printf("Avant echanger() : x=%d, y=%d\n", x, y);
    echanger(&x, &y);
    printf("Apres echanger() : x=%d, y=%d\n\n", x, y);

    /* Modifier un tableau entier */
    int valeurs[] = {1, 2, 3, 4, 5};
    printf("Avant doubler : ");
    for (int i = 0; i < 5; i++) printf("%d ", valeurs[i]);
    printf("\n");
    doubler_tableau(valeurs, 5);
    printf("Apres doubler : ");
    for (int i = 0; i < 5; i++) printf("%d ", valeurs[i]);
    printf("\n\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — POINTEURS SUR POINTEURS (**)
     *
     * Un pointeur peut lui-même avoir son adresse pointée
     * par un autre pointeur : c'est le pointeur de pointeur.
     *
     * int *p   → p contient l'adresse d'un int
     * int **pp → pp contient l'adresse d'un pointeur sur int
     *
     * Utile pour : modifier un pointeur depuis une fonction,
     *              tableaux de chaînes, matrices dynamiques.
     * ---------------------------------------------------------- */
    afficher_separateur("6. Pointeur sur pointeur (**)");

    int  val  = 99;
    int *ptr  = &val;    /* ptr  pointe vers val */
    int **pptr = &ptr;   /* pptr pointe vers ptr */

    printf("val   = %d\n",    val);
    printf("ptr   = %p  (adresse de val)\n", (void*)ptr);
    printf("*ptr  = %d  (valeur de val)\n",  *ptr);
    printf("pptr  = %p  (adresse de ptr)\n", (void*)pptr);
    printf("*pptr = %p  (adresse de val via pptr)\n", (void*)*pptr);
    printf("**pptr= %d  (valeur de val via pptr)\n\n", **pptr);

    /* Modifier val via pptr */
    **pptr = 200;
    printf("Apres **pptr = 200 : val = %d\n\n", val);


    /* ----------------------------------------------------------
     * PARTIE 7 — POINTEURS GÉNÉRIQUES (void *)
     *
     * void * est un pointeur "universel" : il peut pointer
     * vers n'importe quel type sans cast explicite à l'affectation.
     * Avant d'être déréférencé, il doit être casté vers le bon type.
     *
     * Très utilisé dans :
     *   - malloc() qui retourne un void*
     *   - fonctions génériques (qsort, memcpy...)
     * ---------------------------------------------------------- */
    afficher_separateur("7. Pointeurs generiques (void *)");

    int    n   = 42;
    float  f   = 3.14f;
    char   c   = 'Z';

    void *gp;   /* pointeur générique */

    /* Peut pointer vers n'importe quel type */
    gp = &n;
    printf("void* sur int   : %d\n", *(int*)gp);   /* cast obligatoire */

    gp = &f;
    printf("void* sur float : %.2f\n", *(float*)gp);

    gp = &c;
    printf("void* sur char  : %c\n\n", *(char*)gp);

    /* Afficher les octets en mémoire d'un int */
    printf("Octets de l'entier %d en memoire :\n", n);
    afficher_octets(&n, sizeof(int));
    printf("\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  int *p = &var   → p pointe vers var\n");
    printf("  *p              → valeur pointee\n");
    printf("  p + n           → avance de n elements\n");
    printf("  p1 - p2         → distance en elements\n");
    printf("  func(&var)      → modifier var depuis func\n");
    printf("  int **pp        → pointeur sur pointeur\n");
    printf("  void *          → pointeur generique\n");
    printf("  tab == &tab[0]  → tableau = pointeur\n");
    printf("  tab[i] = *(tab+i)  notation equivalente\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS DES FONCTIONS
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

/* Incrémente la variable pointée par p */
void incrementer(int *p) {
    /* *p déréférence → accède à la variable originale */
    *p = *p + 1;
    /* Sans pointeur, la modification serait perdue */
}

/* Échange les valeurs de deux variables via leurs adresses */
void echanger(int *a, int *b) {
    int temp = *a;   /* sauvegarde la valeur de a */
    *a = *b;         /* a prend la valeur de b */
    *b = temp;       /* b prend l'ancienne valeur de a */
}

/* Double chaque élément d'un tableau */
void doubler_tableau(int *tab, int taille) {
    /* Le tableau est passé par adresse : on modifie l'original */
    for (int i = 0; i < taille; i++) {
        tab[i] *= 2;
        /* équivalent : *(tab + i) *= 2; */
    }
}

/* Affiche les octets en mémoire de n'importe quelle variable */
void afficher_octets(void *ptr, int taille) {
    unsigned char *octets = (unsigned char *)ptr;
    for (int i = 0; i < taille; i++) {
        printf("  octet[%d] = 0x%02X (%3d)\n", i, octets[i], octets[i]);
    }
}