/*
 * ============================================================
 *  PROGRAMME : bases_syntaxiques_c.c
 *  OBJECTIF  : Couvrir toutes les bases syntaxiques du langage C
 *  NIVEAU    : Débutant
 *  COMPILE   : gcc bases_syntaxiques_c.c -o bases_c
 *  EXECUTE   : ./bases_c
 * ============================================================
 */

/* 1. INCLUSION DES BIBLIOTHÈQUES STANDARD */
#include <stdio.h>    // printf, scanf, getchar, putchar
#include <string.h>   // strlen, strcpy, strcat, strcmp
#include <math.h>     // sqrt, pow  (compiler avec -lm)

/* ============================================================
 * 2. CONSTANTES ET MACROS (Préprocesseur)
 * ============================================================ */
#define NOM_PROGRAMME  "Bases du C"
#define VERSION         1
#define PI              3.14159

/* ============================================================
 * 3. DÉCLARATIONS DE FONCTIONS (prototypes)
 * ============================================================ */
void section_types_variables();
void section_operateurs();
void section_entrees_sorties();
void section_conditions();
void section_boucles();
void section_tableaux();
void section_chaines();
void section_fonctions_demo();
void afficher_separateur(char *titre);
int  additionner(int a, int b);
float calculer_aire_cercle(float rayon);

/* ============================================================
 * 4. PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    /* --- Affichage de l'en-tête --- */
    printf("\n");
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║   %s  —  Version %d                    ║\n", NOM_PROGRAMME, VERSION);
    printf("║   Bases syntaxiques du langage C             ║\n");
    printf("╚══════════════════════════════════════════════╝\n\n");

    /* --- Appel de chaque section pédagogique --- */
    section_types_variables();
    section_operateurs();
    section_entrees_sorties();
    section_conditions();
    section_boucles();
    section_tableaux();
    section_chaines();
    section_fonctions_demo();

    printf("\n✓ Programme terminé avec succès !\n\n");
    return 0; // Code de retour : 0 = succès
}

/* ============================================================
 * SECTION 1 — TYPES DE DONNÉES ET VARIABLES
 * ============================================================ */
void section_types_variables() {

    afficher_separateur("1. TYPES DE DONNÉES ET VARIABLES");

    /* --- Types entiers --- */
    int          age        = 25;          // Entier signé (4 octets)
    short        petitNb    = 100;         // Entier court  (2 octets)
    long         grandNb    = 1000000L;    // Entier long   (8 octets)
    unsigned int positif    = 42;          // Entier non signé

    /* --- Types flottants --- */
    float        taille     = 1.75f;       // Flottant simple précision
    double       pi_precis  = 3.141592653; // Double précision
    long double  tres_precis = 3.14159265358979L;

    /* --- Caractère --- */
    char         lettre     = 'A';         // Un seul caractère (1 octet)
    char         newline    = '\n';        // Caractère d'échappement

    /* --- Booléen simulé (pas de bool natif en C89) --- */
    int          vrai       = 1;           // 1 = vrai
    int          faux       = 0;           // 0 = faux

    /* --- Affichage avec les bons formats --- */
    printf("  int          age      = %d\n",   age);
    printf("  short        petitNb  = %hd\n",  petitNb);
    printf("  long         grandNb  = %ld\n",  grandNb);
    printf("  unsigned int positif  = %u\n",   positif);
    printf("  float        taille   = %.2f m\n", taille);
    printf("  double       pi       = %.9f\n", pi_precis);
    printf("  char         lettre   = %c  (code ASCII : %d)\n", lettre, lettre);
    printf("  bool (int)   vrai     = %d, faux = %d\n", vrai, faux);

    /* --- Tailles en mémoire --- */
    printf("\n  Tailles mémoire :\n");
    printf("  sizeof(char)   = %lu octet(s)\n",  sizeof(char));
    printf("  sizeof(int)    = %lu octet(s)\n",  sizeof(int));
    printf("  sizeof(float)  = %lu octet(s)\n",  sizeof(float));
    printf("  sizeof(double) = %lu octet(s)\n",  sizeof(double));

    /* --- Variable non initialisée (à éviter !) --- */
    // int danger;  // ⚠ Contient une valeur aléatoire !
    int securise = 0;   // Toujours initialiser ses variables
    printf("\n  Variable sécurisée initialisée à 0 : %d\n", securise);
}

/* ============================================================
 * SECTION 2 — OPÉRATEURS
 * ============================================================ */
void section_operateurs() {

    afficher_separateur("2. OPÉRATEURS");

    int a = 10, b = 3;
    printf("  a = %d, b = %d\n\n", a, b);

    /* --- Opérateurs arithmétiques --- */
    printf("  >> Arithmétiques :\n");
    printf("  a + b  = %d\n",  a + b);   // Addition
    printf("  a - b  = %d\n",  a - b);   // Soustraction
    printf("  a * b  = %d\n",  a * b);   // Multiplication
    printf("  a / b  = %d\n",  a / b);   // Division entière
    printf("  a %% b  = %d\n", a % b);   // Modulo (reste)
    printf("  a / (float)b = %.2f\n", a / (float)b); // Division réelle

    /* --- Opérateurs de comparaison --- */
    printf("\n  >> Comparaisons :\n");
    printf("  a == b : %d\n", a == b);   // Égalité
    printf("  a != b : %d\n", a != b);   // Différence
    printf("  a >  b : %d\n", a >  b);   // Supérieur
    printf("  a <  b : %d\n", a <  b);   // Inférieur
    printf("  a >= b : %d\n", a >= b);   // Supérieur ou égal
    printf("  a <= b : %d\n", a <= b);   // Inférieur ou égal

    /* --- Opérateurs logiques --- */
    printf("\n  >> Logiques :\n");
    printf("  (a>5) && (b<5) : %d  (ET logique)\n",  (a>5) && (b<5));
    printf("  (a>5) || (b>5) : %d  (OU logique)\n",  (a>5) || (b>5));
    printf("  !(a == b)      : %d  (NON logique)\n",  !(a == b));

    /* --- Opérateurs d'affectation --- */
    int x = 10;
    printf("\n  >> Affectations (x = 10 au départ) :\n");
    x += 5;  printf("  x += 5  → x = %d\n", x);
    x -= 3;  printf("  x -= 3  → x = %d\n", x);
    x *= 2;  printf("  x *= 2  → x = %d\n", x);
    x /= 4;  printf("  x /= 4  → x = %d\n", x);
    x %= 3;  printf("  x %%= 3  → x = %d\n", x);

    /* --- Incrémentation / Décrémentation --- */
    int n = 5;
    printf("\n  >> Incrémentation / Décrémentation (n = 5) :\n");
    printf("  n++  (post) : %d  puis n = %d\n", n++, n);
    printf("  ++n  (pré)  : %d  \n", ++n);
    printf("  n--  (post) : %d  puis n = %d\n", n--, n);

    /* --- Opérateur ternaire --- */
    int max = (a > b) ? a : b;
    printf("\n  >> Ternaire : max(a,b) = %d\n", max);
}

/* ============================================================
 * SECTION 3 — ENTRÉES / SORTIES
 * ============================================================ */
void section_entrees_sorties() {

    afficher_separateur("3. ENTRÉES / SORTIES");

    /* --- printf avec différents formats --- */
    printf("  >> Formats d'affichage :\n");
    printf("  Entier   : [%5d]   (largeur 5)\n",    42);
    printf("  Entier   : [%-5d]  (aligné gauche)\n", 42);
    printf("  Entier   : [%05d]  (zéros devant)\n",  42);
    printf("  Float    : [%8.3f] (8 large, 3 déc)\n", 3.14159);
    printf("  Chaîne   : [%10s]  (largeur 10)\n",   "bonjour");
    printf("  Hexa     : %x  (42 en hexadécimal)\n",  42);
    printf("  Octal    : %o  (42 en octal)\n",         42);

    /* --- putchar : afficher un caractère --- */
    printf("\n  >> putchar — afficher 'C' : ");
    putchar('C');
    putchar('\n');

    /* --- Simulation d'une saisie (valeur codée en dur ici) --- */
    int annee_naissance = 1999;
    char prenom[30] = "Alice";
    float note = 17.5f;

    printf("\n  >> scanf (simulation avec valeurs prédéfinies) :\n");
    printf("  Prénom         : %s\n", prenom);
    printf("  Année de naiss.: %d\n", annee_naissance);
    printf("  Note           : %.1f/20\n", note);

    /* --- Caractères spéciaux --- */
    printf("\n  >> Caractères d'échappement :\n");
    printf("  \\n = nouvelle ligne\n");
    printf("  \\t = tabulation :\tici\n");
    printf("  \\\\ = antislash : \\\n");
    printf("  \\\" = guillemet : \"\n");
}

/* ============================================================
 * SECTION 4 — CONDITIONS
 * ============================================================ */
void section_conditions() {

    afficher_separateur("4. STRUCTURES CONDITIONNELLES");

    int note = 14;
    printf("  Note de l'étudiant : %d/20\n\n", note);

    /* --- if / else if / else --- */
    printf("  >> if / else if / else :\n  ");
    if (note >= 16) {
        printf("Mention Très Bien 🎉\n");
    } else if (note >= 14) {
        printf("Mention Bien 👍\n");
    } else if (note >= 12) {
        printf("Mention Assez Bien\n");
    } else if (note >= 10) {
        printf("Admis\n");
    } else {
        printf("Recalé ❌\n");
    }

    /* --- switch / case --- */
    int jour = 3;
    printf("\n  >> switch/case (jour = %d) :\n  ", jour);
    switch (jour) {
        case 1:  printf("Lundi\n");    break;
        case 2:  printf("Mardi\n");    break;
        case 3:  printf("Mercredi\n"); break;  // ← exécuté
        case 4:  printf("Jeudi\n");    break;
        case 5:  printf("Vendredi\n"); break;
        case 6:  printf("Samedi\n");   break;
        case 7:  printf("Dimanche\n"); break;
        default: printf("Jour invalide\n");
    }

    /* --- switch avec groupement de cas --- */
    printf("\n  >> switch groupé :\n  Jour %d est un ", jour);
    switch (jour) {
        case 1: case 2: case 3: case 4: case 5:
            printf("jour de semaine\n");
            break;
        case 6: case 7:
            printf("week-end\n");
            break;
        default:
            printf("jour inconnu\n");
    }

    /* --- Conditions imbriquées --- */
    int age = 20;
    int a_carte = 1;
    printf("\n  >> Conditions imbriquées (age=%d, carte=%d) :\n  ", age, a_carte);
    if (age >= 18) {
        if (a_carte) {
            printf("Accès autorisé ✓\n");
        } else {
            printf("Majeur mais sans carte\n");
        }
    } else {
        printf("Mineur, accès refusé\n");
    }
}

/* ============================================================
 * SECTION 5 — BOUCLES
 * ============================================================ */
void section_boucles() {

    afficher_separateur("5. BOUCLES");

    int i;

    /* --- Boucle for --- */
    printf("  >> for (0 à 4) :\n  ");
    for (i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    /* --- for avec pas de 2 --- */
    printf("\n  >> for (nombres pairs 0 à 10) :\n  ");
    for (i = 0; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    /* --- Boucle while --- */
    printf("\n  >> while (compte à rebours) :\n  ");
    int compteur = 5;
    while (compteur > 0) {
        printf("%d ", compteur);
        compteur--;
    }
    printf("🚀\n");

    /* --- Boucle do-while (s'exécute au moins 1 fois) --- */
    printf("\n  >> do-while :\n  ");
    int val = 1;
    do {
        printf("%d ", val);
        val *= 2;
    } while (val <= 32);
    printf("\n");

    /* --- break et continue --- */
    printf("\n  >> break (stoppe à 5) :\n  ");
    for (i = 0; i < 10; i++) {
        if (i == 5) break;
        printf("%d ", i);
    }
    printf("(arrêt)\n");

    printf("\n  >> continue (saute les impairs) :\n  ");
    for (i = 0; i < 10; i++) {
        if (i % 2 != 0) continue;
        printf("%d ", i);
    }
    printf("\n");

    /* --- Boucles imbriquées : table de multiplication --- */
    printf("\n  >> Boucles imbriquées — Table de 3 :\n");
    for (i = 1; i <= 5; i++) {
        printf("  3 x %d = %d\n", i, 3 * i);
    }
}

/* ============================================================
 * SECTION 6 — TABLEAUX
 * ============================================================ */
void section_tableaux() {

    afficher_separateur("6. TABLEAUX");

    /* --- Tableau 1D --- */
    int notes[5] = {12, 15, 9, 18, 11};
    int i;

    printf("  >> Tableau 1D (notes) :\n  ");
    for (i = 0; i < 5; i++) {
        printf("[%d]=%d  ", i, notes[i]);
    }
    printf("\n");

    /* --- Calcul de la moyenne --- */
    int somme = 0;
    for (i = 0; i < 5; i++) {
        somme += notes[i];
    }
    printf("  Moyenne : %.1f/20\n", (float)somme / 5);

    /* --- Tableau initialisé à zéro --- */
    int zeros[5] = {0};
    printf("\n  >> Tableau initialisé à 0 :\n  ");
    for (i = 0; i < 5; i++) printf("%d ", zeros[i]);
    printf("\n");

    /* --- Tableau 2D --- */
    int matrice[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int j;

    printf("\n  >> Tableau 2D (matrice 3x3) :\n");
    for (i = 0; i < 3; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            printf("%3d", matrice[i][j]);
        }
        printf("\n");
    }

    /* --- Trouver le max --- */
    int max = notes[0];
    for (i = 1; i < 5; i++) {
        if (notes[i] > max) {
            max = notes[i];
        }
    }
    printf("\n  Meilleure note : %d/20\n", max);
}

/* ============================================================
 * SECTION 7 — CHAÎNES DE CARACTÈRES
 * ============================================================ */
void section_chaines() {

    afficher_separateur("7. CHAÎNES DE CARACTÈRES");

    char prenom[50] = "Alice";
    char nom[50]    = "Dupont";
    char complet[100];
    char copie[50];

    /* --- Longueur --- */
    printf("  strlen(\"%s\") = %lu\n", prenom, strlen(prenom));

    /* --- Copie --- */
    strcpy(copie, prenom);
    printf("  strcpy  → copie = \"%s\"\n", copie);

    /* --- Concaténation --- */
    strcpy(complet, prenom);
    strcat(complet, " ");
    strcat(complet, nom);
    printf("  strcat  → complet = \"%s\"\n", complet);

    /* --- Comparaison --- */
    char mot1[20] = "bonjour";
    char mot2[20] = "bonjour";
    char mot3[20] = "Bonjour";

    printf("\n  strcmp(\"%s\", \"%s\") = %d (égaux)\n",
           mot1, mot2, strcmp(mot1, mot2));
    printf("  strcmp(\"%s\", \"%s\") = %d (différents)\n",
           mot1, mot3, strcmp(mot1, mot3));

    /* --- Tableau de chaînes --- */
    char jours[7][12] = {
        "Lundi", "Mardi", "Mercredi",
        "Jeudi", "Vendredi", "Samedi", "Dimanche"
    };
    printf("\n  >> Tableau de chaînes :\n  ");
    int i;
    for (i = 0; i < 7; i++) {
        printf("%s", jours[i]);
        if (i < 6) printf(", ");
    }
    printf("\n");

    /* --- Parcourir char par char --- */
    printf("\n  >> Caractère par caractère : \"%s\" → ", prenom);
    for (i = 0; prenom[i] != '\0'; i++) {
        printf("%c-", prenom[i]);
    }
    printf("\b \n"); // Efface le dernier tiret
}

/* ============================================================
 * SECTION 8 — FONCTIONS
 * ============================================================ */
void section_fonctions_demo() {

    afficher_separateur("8. FONCTIONS");

    /* --- Appel simple --- */
    int resultat = additionner(7, 5);
    printf("  additionner(7, 5)          = %d\n", resultat);

    /* --- Fonction avec calcul --- */
    float aire = calculer_aire_cercle(5.0f);
    printf("  aire_cercle(rayon=5)       = %.2f\n", aire);

    /* --- Appels multiples --- */
    printf("\n  >> Factorielle de 1 à 6 :\n");
    int i;
    // Calcul inline sans fonction récursive (niveau débutant)
    int fact = 1;
    for (i = 1; i <= 6; i++) {
        fact *= i;
        printf("  %d! = %d\n", i, fact);
    }

    /* --- Variable locale vs paramètre --- */
    printf("\n  >> Valeur de PI (constante) = %.5f\n", PI);
    printf("  sqrt(PI) via <math.h>      = %.5f\n", sqrt(PI));
}

/* ============================================================
 * FONCTIONS UTILITAIRES
 * ============================================================ */

/* Affiche un séparateur visuel pour chaque section */
void afficher_separateur(char *titre) {
    printf("\n────────────────────────────────────────────────\n");
    printf("  %s\n", titre);
    printf("────────────────────────────────────────────────\n");
}

/* Retourne la somme de deux entiers */
int additionner(int a, int b) {
    return a + b;
}

/* Retourne l'aire d'un cercle */
float calculer_aire_cercle(float rayon) {
    return (float)(PI * rayon * rayon);
}