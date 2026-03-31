/*
 * ============================================================
 *  FICHIER  : structures.c
 *  SUJET    : Les structures (struct) en C
 *  NIVEAU   : Intermédiaire — Leçon 3
 *  COMPILE  : gcc -Wall -Wextra structures.c -o structures
 *  EXECUTE  : ./structures
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * DÉCLARATIONS DES STRUCTURES
 *
 * Les structures se déclarent EN DEHORS des fonctions,
 * généralement en haut du fichier (ou dans un .h).
 * ============================================================ */

/* Structure simple */
struct Point {
    float x;
    float y;
};

/* Structure avec typedef (forme recommandée) */
typedef struct {
    char   nom[50];
    char   prenom[50];
    int    age;
    float  salaire;
} Employe;

/* Structure imbriquée : Date à l'intérieur de Personne */
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    char   nom[50];
    int    age;
    Date   naissance;   /* struct imbriquée */
} Personne;

/* Structure avec pointeur (pour liste chaînée simple) */
typedef struct Noeud {
    int            valeur;
    struct Noeud  *suivant;   /* pointeur vers le même type */
} Noeud;


/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);
void afficher_point(struct Point p);
void afficher_employe(Employe e);
void afficher_personne(Personne p);
float distance(struct Point a, struct Point b);
void augmenter_salaire(Employe *e, float pourcentage);
Employe creer_employe(char *nom, char *prenom, int age, float salaire);
void afficher_tableau_employes(Employe tab[], int n);
int  comparer_ages(const void *a, const void *b);


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 3 : Structures (struct)\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — DÉCLARER ET UTILISER UNE STRUCTURE
     *
     * Une structure regroupe plusieurs variables de types
     * différents sous un seul nom.
     * Chaque variable dans la structure s'appelle un "membre"
     * ou un "champ".
     *
     * Syntaxe de déclaration :
     *   struct NomStruct {
     *       type membre1;
     *       type membre2;
     *   };
     *
     * Accès aux membres : variable.membre  (opérateur point)
     * ---------------------------------------------------------- */
    afficher_separateur("1. Declarer et utiliser une structure");

    /* Déclaration d'une variable de type struct Point */
    struct Point p1;

    /* Accès et affectation avec l'opérateur point (.) */
    p1.x = 3.0f;
    p1.y = 4.0f;

    printf("Point p1 : x=%.1f, y=%.1f\n", p1.x, p1.y);
    afficher_point(p1);

    /* Calcul avec les membres */
    float dist_origine = distance(p1, (struct Point){0.0f, 0.0f});
    printf("Distance a l'origine : %.2f\n\n", dist_origine);


    /* ----------------------------------------------------------
     * PARTIE 2 — INITIALISER UNE STRUCTURE
     *
     * Plusieurs façons d'initialiser une structure :
     *   1. Membre par membre après déclaration
     *   2. Initialisateur à la déclaration (style tableau)
     *   3. Initialisateur désigné (C99) — recommandé
     *   4. Via une fonction constructeur
     * ---------------------------------------------------------- */
    afficher_separateur("2. Initialiser une structure");

    /* Méthode 1 : membre par membre */
    struct Point p2;
    p2.x = 1.5f;
    p2.y = 2.5f;
    printf("Methode 1 (membre par membre) : (%.1f, %.1f)\n", p2.x, p2.y);

    /* Méthode 2 : initialisateur positionnel */
    struct Point p3 = {5.0f, 7.0f};
    printf("Methode 2 (positionnel)       : (%.1f, %.1f)\n", p3.x, p3.y);

    /* Méthode 3 : initialisateur désigné (C99) — le plus clair */
    struct Point p4 = {.x = 10.0f, .y = 20.0f};
    printf("Methode 3 (designe C99)       : (%.1f, %.1f)\n", p4.x, p4.y);

    /* Méthode 4 : via une fonction */
    Employe emp1 = creer_employe("Martin", "Sophie", 32, 3500.0f);
    printf("Methode 4 (fonction)          : %s %s, %d ans\n\n",
           emp1.prenom, emp1.nom, emp1.age);


    /* ----------------------------------------------------------
     * PARTIE 3 — ACCÉDER AUX MEMBRES (.  et ->)
     *
     * Il existe deux opérateurs d'accès aux membres :
     *
     *   variable.membre   → accès direct (variable ordinaire)
     *   pointeur->membre  → accès via pointeur
     *                       (équivalent à (*pointeur).membre)
     * ---------------------------------------------------------- */
    afficher_separateur("3. Acces aux membres : . et ->");

    Employe emp2 = creer_employe("Dupont", "Jean", 45, 4200.0f);

    /* Accès direct avec . */
    printf("Acces direct (.) :\n");
    printf("  emp2.nom    = %s\n",   emp2.nom);
    printf("  emp2.age    = %d\n",   emp2.age);
    printf("  emp2.salaire = %.2f\n", emp2.salaire);

    /* Accès via pointeur avec -> */
    Employe *ptr_emp = &emp2;
    printf("\nAcces via pointeur (->) :\n");
    printf("  ptr_emp->nom    = %s\n",   ptr_emp->nom);
    printf("  ptr_emp->age    = %d\n",   ptr_emp->age);
    printf("  ptr_emp->salaire = %.2f\n", ptr_emp->salaire);

    /* Les deux notations sont équivalentes */
    printf("\n(*ptr_emp).age == ptr_emp->age : %d == %d\n\n",
           (*ptr_emp).age, ptr_emp->age);


    /* ----------------------------------------------------------
     * PARTIE 4 — STRUCTURES IMBRIQUÉES
     *
     * Un membre d'une structure peut lui-même être une structure.
     * On accède aux membres intérieurs en enchaînant les .
     * ---------------------------------------------------------- */
    afficher_separateur("4. Structures imbriquees");

    Personne pers1;
    strcpy(pers1.nom, "Bernard");
    pers1.age = 30;
    pers1.naissance.jour  = 15;    /* accès au membre de la sous-struct */
    pers1.naissance.mois  = 6;
    pers1.naissance.annee = 1994;

    afficher_personne(pers1);

    /* Initialisation complète en une fois */
    Personne pers2 = {
        .nom = "Laurent",
        .age = 25,
        .naissance = {.jour = 3, .mois = 11, .annee = 1999}
    };
    afficher_personne(pers2);
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 5 — TABLEAU DE STRUCTURES
     *
     * On peut créer des tableaux dont les éléments sont
     * des structures. Très utile pour gérer des collections
     * d'objets (liste d'employés, de points, de produits...).
     * ---------------------------------------------------------- */
    afficher_separateur("5. Tableau de structures");

    Employe equipe[4];
    equipe[0] = creer_employe("Blanc",   "Alice",   28, 3200.0f);
    equipe[1] = creer_employe("Noir",    "Bob",     35, 4100.0f);
    equipe[2] = creer_employe("Rouge",   "Charlie", 42, 4800.0f);
    equipe[3] = creer_employe("Vert",    "Diana",   31, 3700.0f);

    printf("Equipe complète :\n");
    afficher_tableau_employes(equipe, 4);

    /* Calcul du salaire moyen */
    float total = 0.0f;
    for (int i = 0; i < 4; i++) {
        total += equipe[i].salaire;
    }
    printf("Salaire moyen : %.2f €\n\n", total / 4);


    /* ----------------------------------------------------------
     * PARTIE 6 — PASSER UNE STRUCTURE À UNE FONCTION
     *
     * Deux façons de passer une structure à une fonction :
     *
     *   Par valeur   : func(Employe e)   → copie de toute la struct
     *                  La fonction ne peut pas modifier l'original.
     *                  Coûteux pour les grandes structures.
     *
     *   Par pointeur : func(Employe *e)  → adresse de la struct
     *                  La fonction PEUT modifier l'original.
     *                  Efficace (on passe juste une adresse).
     * ---------------------------------------------------------- */
    afficher_separateur("6. Passer une structure a une fonction");

    Employe emp3 = creer_employe("Petit", "Marc", 38, 3900.0f);

    printf("Avant augmentation : %s gagne %.2f €\n",
           emp3.prenom, emp3.salaire);

    /* Passage par pointeur → modifie emp3 */
    augmenter_salaire(&emp3, 10.0f);   /* augmentation de 10% */

    printf("Apres augmentation (+10%%) : %s gagne %.2f €\n\n",
           emp3.prenom, emp3.salaire);


    /* ----------------------------------------------------------
     * PARTIE 7 — typedef AVEC LES STRUCTURES
     *
     * typedef crée un alias pour un type, ce qui permet
     * d'écrire "Employe" au lieu de "struct Employe".
     *
     * Deux formes courantes :
     *
     *   Form 1 : typedef struct NomTag { ... } Alias;
     *   Form 2 : typedef struct { ... } Alias;  (anonymous)
     *
     * C'est la forme qu'on utilise depuis le début de ce fichier.
     * ---------------------------------------------------------- */
    afficher_separateur("7. typedef avec struct");

    printf("Sans typedef : struct Point p;\n");
    printf("Avec typedef : Point p;  (plus court !)\n\n");

    /* Démonstration : les deux sont équivalents */
    struct Point pt_long;          /* sans typedef */
    pt_long.x = 1.0f; pt_long.y = 2.0f;

    /* Employe utilise déjà typedef */
    Employe emp_court = creer_employe("Durand", "Luc", 29, 3100.0f);

    printf("struct Point  : (%.1f, %.1f)\n", pt_long.x, pt_long.y);
    printf("Employe       : %s %s\n\n", emp_court.prenom, emp_court.nom);


    /* ----------------------------------------------------------
     * PARTIE 8 — POINTEURS SUR STRUCTURES ET ALLOCATION DYNAMIQUE
     *
     * On peut allouer une structure dynamiquement avec malloc.
     * L'accès aux membres se fait alors avec ->
     * N'oublier pas de free() à la fin !
     * ---------------------------------------------------------- */
    afficher_separateur("8. Pointeurs sur structures et malloc");

    /* Allouer une structure sur le tas */
    Employe *emp_dyn = (Employe*)malloc(sizeof(Employe));
    if (emp_dyn == NULL) {
        printf("Erreur malloc\n");
        return 1;
    }

    /* Remplir via -> */
    strcpy(emp_dyn->nom,    "Moreau");
    strcpy(emp_dyn->prenom, "Julie");
    emp_dyn->age     = 27;
    emp_dyn->salaire = 3300.0f;

    printf("Structure allouee dynamiquement :\n");
    afficher_employe(*emp_dyn);
    printf("Taille : %lu octets\n", sizeof(Employe));

    free(emp_dyn);
    emp_dyn = NULL;

    /* Tableau de structures alloué dynamiquement */
    int nb = 3;
    Employe *tab_dyn = (Employe*)malloc(nb * sizeof(Employe));
    if (tab_dyn == NULL) { return 1; }

    tab_dyn[0] = creer_employe("Roy",   "Emma",  24, 2900.0f);
    tab_dyn[1] = creer_employe("Faure", "Louis", 39, 4500.0f);
    tab_dyn[2] = creer_employe("Brun",  "Chloe", 33, 3800.0f);

    printf("\nTableau dynamique de %d employes :\n", nb);
    afficher_tableau_employes(tab_dyn, nb);

    free(tab_dyn);
    tab_dyn = NULL;
    printf("\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  struct Point { float x; float y; };\n");
    printf("  typedef struct { ... } Employe;\n");
    printf("  p.x, p.y          → acces direct\n");
    printf("  ptr->x, ptr->y    → acces via pointeur\n");
    printf("  struct imbriquee  → p.naissance.jour\n");
    printf("  Employe tab[N]    → tableau de structs\n");
    printf("  func(Employe e)   → passage par valeur\n");
    printf("  func(Employe *e)  → passage par pointeur\n");
    printf("  malloc(sizeof(S)) → struct dynamique\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS DES FONCTIONS
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

void afficher_point(struct Point p) {
    printf("Point(%.2f, %.2f)\n", p.x, p.y);
}

void afficher_employe(Employe e) {
    printf("  %s %s | age: %d | salaire: %.2f €\n",
           e.prenom, e.nom, e.age, e.salaire);
}

void afficher_personne(Personne p) {
    printf("  %s, %d ans, ne le %02d/%02d/%d\n",
           p.nom, p.age,
           p.naissance.jour, p.naissance.mois, p.naissance.annee);
}

/* Calcul de la distance entre deux points */
float distance(struct Point a, struct Point b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dist = 0.0f;
    /* Approximation de sqrt sans math.h */
    float val = dx*dx + dy*dy;
    if (val > 0) {
        dist = val;
        for (int i = 0; i < 20; i++)
            dist = 0.5f * (dist + val/dist);
    }
    return dist;
}

/* Modifie le salaire via un pointeur */
void augmenter_salaire(Employe *e, float pourcentage) {
    e->salaire *= (1.0f + pourcentage / 100.0f);
}

/* Fonction "constructeur" : crée et retourne un Employe */
Employe creer_employe(char *nom, char *prenom, int age, float salaire) {
    Employe e;
    strncpy(e.nom,    nom,    sizeof(e.nom)    - 1);
    strncpy(e.prenom, prenom, sizeof(e.prenom) - 1);
    e.nom[sizeof(e.nom)-1]       = '\0';
    e.prenom[sizeof(e.prenom)-1] = '\0';
    e.age     = age;
    e.salaire = salaire;
    return e;   /* retourne une copie de la structure */
}

void afficher_tableau_employes(Employe tab[], int n) {
    for (int i = 0; i < n; i++) {
        printf("  [%d] ", i);
        afficher_employe(tab[i]);
    }
}

/* Comparateur pour qsort (tri par age) */
int comparer_ages(const void *a, const void *b) {
    const Employe *ea = (const Employe*)a;
    const Employe *eb = (const Employe*)b;
    return ea->age - eb->age;
}