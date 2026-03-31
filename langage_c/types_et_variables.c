/*
 * ============================================================
 *  FICHIER  : types_et_variables.c
 *  SUJET    : Types de données et variables en C
 *  NIVEAU   : Débutant — Leçon 1
 *  COMPILE  : gcc types_et_variables.c -o types_et_variables
 *  EXECUTE  : ./types_et_variables
 * ============================================================
 */

#include <stdio.h>   /* Pour printf */

/* ============================================================
 * CONSTANTES (définies avant main, disponibles partout)
 *
 * #define crée un nom qui sera remplacé par sa valeur
 * avant la compilation. Ce n'est pas une variable,
 * il n'a pas de type et ne prend pas de place en mémoire.
 * ============================================================ */
#define AGE_MAJORITE  18
#define PI            3.14159
#define NOM_ECOLE     "OpenClassrooms"

/* Variable GLOBALE : déclarée en dehors de toute fonction.
 * Elle est accessible depuis tout le programme.
 * À utiliser avec modération. */
int compteur_global = 0;

/* ============================================================
 *  PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  LECON 1 : Types de donnees et variables\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — DÉCLARATION ET INITIALISATION
     *
     * Déclarer une variable = réserver une case mémoire.
     * Initialiser = lui donner une valeur de départ.
     *
     * Syntaxe : type nom_variable = valeur;
     * ---------------------------------------------------------- */
    printf("--- 1. Declaration et initialisation ---\n");

    int age = 20;            /* Déclarée ET initialisée */
    int annee;               /* Déclarée mais PAS initialisée */
    annee = 2025;            /* Initialisation sur une ligne séparée */

    printf("age   = %d\n", age);
    printf("annee = %d\n\n", annee);

    /* BONNE PRATIQUE : toujours initialiser une variable.
     * Une variable non initialisée contient une valeur
     * aléatoire (ce qui reste en mémoire). */
    int valeur_sure = 0;     /* Initialisée à zéro par sécurité */
    printf("valeur_sure = %d  (initialisee a 0)\n\n", valeur_sure);


    /* ----------------------------------------------------------
     * PARTIE 2 — TYPES ENTIERS
     *
     * Les types entiers stockent des nombres SANS virgule.
     * Ils diffèrent par leur taille et la plage de valeurs.
     * ---------------------------------------------------------- */
    printf("--- 2. Types entiers ---\n");

    short  petite_valeur  = 32000;       /* 2 octets, max ~32 000 */
    int    nombre         = 150000;      /* 4 octets, max ~2 milliards */
    long   grande_valeur  = 1000000000L; /* 8 octets, très grand */

    printf("short : %hd\n", petite_valeur);
    printf("int   : %d\n",  nombre);
    printf("long  : %ld\n", grande_valeur);

    /* unsigned : uniquement des valeurs POSITIVES.
     * On gagne le double de la plage positive. */
    unsigned int positif = 4000000000U; /* Ne peut pas être négatif */
    printf("unsigned int : %u\n\n", positif);


    /* ----------------------------------------------------------
     * PARTIE 3 — TYPES FLOTTANTS
     *
     * Les flottants stockent des nombres AVEC virgule.
     * Plus le type est grand, plus la précision est élevée.
     * ---------------------------------------------------------- */
    printf("--- 3. Types flottants ---\n");

    float  taille    = 1.75f;           /* f obligatoire pour float */
    double pi_precis = 3.141592653589;  /* Plus précis que float */

    printf("float  taille    = %f\n",   taille);
    printf("float  taille    = %.2f\n", taille);    /* 2 décimales */
    printf("double pi_precis = %.9f\n", pi_precis); /* 9 décimales */

    /* ATTENTION : float et double ne sont pas exactement précis.
     * C'est une limite de la représentation binaire. */
    float approximation = 0.1f + 0.2f;
    printf("0.1 + 0.2 (float) = %.10f  <- pas exactement 0.3 !\n\n",
           approximation);


    /* ----------------------------------------------------------
     * PARTIE 4 — TYPE CARACTÈRE
     *
     * Un char stocke UN seul caractère (entre apostrophes).
     * En mémoire, c'est simplement un nombre entier (code ASCII).
     * ---------------------------------------------------------- */
    printf("--- 4. Type caractere (char) ---\n");

    char lettre   = 'A';
    char chiffre  = '7';    /* Attention : '7' != 7  */
    char espace   = ' ';
    char newline  = '\n';   /* Caractère spécial : nouvelle ligne */

    printf("lettre   = %c\n",   lettre);        /* Affiche: A  */
    printf("lettre   = %d\n",   lettre);        /* Affiche: 65 (code ASCII) */
    printf("chiffre  = %c  (code ASCII : %d)\n", chiffre, chiffre);
    printf("espace   = '%c' (code ASCII : %d)\n", espace, espace);

    /* Les caractères sont des entiers : on peut faire des calculs */
    char lettre_suivante = lettre + 1;   /* A + 1 = B */
    printf("Lettre suivante apres %c : %c\n\n", lettre, lettre_suivante);


    /* ----------------------------------------------------------
     * PARTIE 5 — SIZEOF : TAILLE EN MÉMOIRE
     *
     * sizeof() retourne le nombre d'octets occupés
     * par un type ou une variable en mémoire.
     * ---------------------------------------------------------- */
    printf("--- 5. Taille en memoire (sizeof) ---\n");

    printf("sizeof(char)   = %lu octet(s)\n",  sizeof(char));
    printf("sizeof(short)  = %lu octet(s)\n",  sizeof(short));
    printf("sizeof(int)    = %lu octet(s)\n",  sizeof(int));
    printf("sizeof(long)   = %lu octet(s)\n",  sizeof(long));
    printf("sizeof(float)  = %lu octet(s)\n",  sizeof(float));
    printf("sizeof(double) = %lu octet(s)\n\n", sizeof(double));


    /* ----------------------------------------------------------
     * PARTIE 6 — PORTÉE DES VARIABLES
     *
     * Une variable locale n'existe que dans le bloc { }
     * où elle est déclarée. Elle disparaît à la fin du bloc.
     * ---------------------------------------------------------- */
    printf("--- 6. Portee des variables ---\n");

    int variable_locale = 10;   /* Visible dans tout main() */
    printf("variable_locale (dans main) = %d\n", variable_locale);

    /* Bloc imbriqué : crée sa propre portée */
    {
        int variable_de_bloc = 99;  /* N'existe que dans ce bloc */
        printf("variable_de_bloc (dans le bloc) = %d\n", variable_de_bloc);
        printf("variable_locale (toujours visible) = %d\n", variable_locale);
    }
    /* Ici, variable_de_bloc n'existe plus.
     * Décommenter la ligne suivante provoquerait une erreur :
     * printf("%d", variable_de_bloc);  <- ERREUR ! */

    /* Variable globale : accessible depuis n'importe où */
    compteur_global = 5;
    printf("compteur_global = %d\n\n", compteur_global);


    /* ----------------------------------------------------------
     * PARTIE 7 — CONSTANTES
     *
     * Une constante est une valeur qui ne change jamais.
     * Deux façons de la déclarer :
     *   1. #define  (préprocesseur, pas de type)
     *   2. const    (vrai type C, recommandé)
     * ---------------------------------------------------------- */
    printf("--- 7. Constantes ---\n");

    /* Avec #define (défini en haut du fichier) */
    printf("AGE_MAJORITE (define) = %d\n", AGE_MAJORITE);
    printf("PI           (define) = %.5f\n", PI);
    printf("NOM_ECOLE    (define) = %s\n", NOM_ECOLE);

    /* Avec const : la variable ne peut pas être modifiée */
    const int NB_JOURS_SEMAINE = 7;
    const float TAUX_TVA       = 20.0f;

    printf("NB_JOURS_SEMAINE (const) = %d\n", NB_JOURS_SEMAINE);
    printf("TAUX_TVA         (const) = %.1f%%\n", TAUX_TVA);

    /* Essayer de modifier une constante provoque une erreur :
     * NB_JOURS_SEMAINE = 8;  <- ERREUR de compilation ! */


    /* ----------------------------------------------------------
     * RÉCAPITULATIF VISUEL
     * ---------------------------------------------------------- */
    printf("\n==============================================\n");
    printf("  RECAPITULATIF\n");
    printf("==============================================\n");
    printf("  %-12s %-8s %-20s\n", "Type", "Octets", "Exemple");
    printf("  %-12s %-8s %-20s\n", "------------", "------", "-------------------");
    printf("  %-12s %-8lu %-20d\n", "char",   sizeof(char),   'A');
    printf("  %-12s %-8lu %-20d\n", "short",  sizeof(short),  32000);
    printf("  %-12s %-8lu %-20d\n", "int",    sizeof(int),    150000);
    printf("  %-12s %-8lu %-20ld\n","long",   sizeof(long),   1000000000L);
    printf("  %-12s %-8lu %-20.2f\n","float", sizeof(float),  1.75f);
    printf("  %-12s %-8lu %-20.6f\n","double",sizeof(double), 3.141593);
    printf("\n");

    return 0;
}