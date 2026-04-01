/*
 * ============================================================
 *  FICHIER  : enumerations.c
 *  SUJET    : Les énumérations (enum) en C
 *  NIVEAU   : Intermédiaire — Leçon 8
 *  COMPILE  : gcc -Wall -Wextra enumerations.c -o enums
 *  EXECUTE  : ./enums
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

/* ============================================================
 * DÉCLARATIONS DES ÉNUMÉRATIONS
 * (hors de toute fonction, avant leur utilisation)
 * ============================================================ */

/* Enum simple : valeurs 0, 1, 2... par défaut */
enum Jour {
    LUNDI,      /* 0 */
    MARDI,      /* 1 */
    MERCREDI,   /* 2 */
    JEUDI,      /* 3 */
    VENDREDI,   /* 4 */
    SAMEDI,     /* 5 */
    DIMANCHE    /* 6 */
};

/* Enum avec valeurs personnalisées */
enum CodeHTTP {
    HTTP_OK         = 200,
    HTTP_CREATED    = 201,
    HTTP_NO_CONTENT = 204,
    HTTP_NOT_FOUND  = 404,
    HTTP_FORBIDDEN  = 403,
    HTTP_SERVER_ERR = 500
};

/* Enum avec séquence partielle : la suite continue depuis la dernière valeur */
enum Priorite {
    PRIORITE_BASSE   = 1,
    PRIORITE_NORMALE,    /* 2 (automatique) */
    PRIORITE_HAUTE,      /* 3 (automatique) */
    PRIORITE_CRITIQUE = 10
};

/* Enum avec typedef : forme recommandée */
typedef enum {
    ROUGE,
    VERT,
    BLEU,
    JAUNE,
    BLANC,
    NOIR
} Couleur;

/* Enum pour une machine à états */
typedef enum {
    ETAT_INITIAL,
    ETAT_EN_COURS,
    ETAT_EN_PAUSE,
    ETAT_TERMINE,
    ETAT_ERREUR
} EtatTache;

/* Enum pour les directions */
typedef enum {
    NORD = 0,
    EST  = 90,
    SUD  = 180,
    OUEST = 270
} Direction;

/* Enum combinée avec struct (tagged union pattern) */
typedef enum {
    VAL_ENTIER,
    VAL_FLOTTANT,
    VAL_BOOLEEN
} TypeValeur;

typedef struct {
    TypeValeur type;
    union {
        int   entier;
        float flottant;
        int   booleen;   /* 0 ou 1 */
    } donnee;
} Valeur;


/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);
const char *nom_jour(enum Jour j);
const char *nom_etat(EtatTache e);
const char *nom_couleur(Couleur c);
const char *nom_direction(Direction d);
void afficher_valeur(Valeur v);
void avancer_etat(EtatTache *etat);


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 8 : Enumerations\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — DÉCLARER ET UTILISER UN ENUM
     *
     * Un enum (énumération) définit un ensemble de constantes
     * entières nommées. Il améliore la lisibilité du code
     * en remplaçant des valeurs magiques (0, 1, 2...) par
     * des noms explicites.
     *
     * Syntaxe : enum NomEnum { CONST1, CONST2, CONST3 };
     *
     * Par défaut, les valeurs commencent à 0 et s'incrémentent.
     * ---------------------------------------------------------- */
    afficher_separateur("1. Declarer et utiliser un enum");

    /* Déclaration d'une variable de type enum Jour */
    enum Jour aujourd_hui = MERCREDI;
    enum Jour demain      = JEUDI;

    printf("Aujourd'hui : %d → %s\n",
           aujourd_hui, nom_jour(aujourd_hui));
    printf("Demain      : %d → %s\n",
           demain, nom_jour(demain));

    /* Comparaison */
    if (aujourd_hui == MERCREDI) {
        printf("C'est le milieu de la semaine !\n");
    }

    /* Les enum sont des int : arithmétique possible */
    enum Jour apres_demain = (enum Jour)(aujourd_hui + 2);
    printf("Apres-demain : %s\n\n",
           nom_jour(apres_demain));


    /* ----------------------------------------------------------
     * PARTIE 2 — VALEURS PERSONNALISÉES
     *
     * On peut assigner n'importe quelle valeur entière à chaque
     * constante. Très utile pour des codes d'erreur, protocoles
     * réseau, registres matériels, etc.
     *
     * Après une valeur personnalisée, les suivantes continuent
     * à s'incrémenter automatiquement depuis cette valeur.
     * ---------------------------------------------------------- */
    afficher_separateur("2. Valeurs personnalisees");

    /* Codes HTTP */
    enum CodeHTTP reponse = HTTP_NOT_FOUND;
    printf("Code HTTP : %d\n", reponse);

    /* Switch sur l'enum */
    switch (reponse) {
        case HTTP_OK:
            printf("  Succes !\n");
            break;
        case HTTP_NOT_FOUND:
            printf("  Ressource introuvable (404)\n");
            break;
        case HTTP_SERVER_ERR:
            printf("  Erreur serveur (500)\n");
            break;
        default:
            printf("  Autre code : %d\n", reponse);
    }

    /* Enum avec séquence mixte */
    printf("\nPriorites :\n");
    printf("  BASSE    = %d\n", PRIORITE_BASSE);
    printf("  NORMALE  = %d\n", PRIORITE_NORMALE);
    printf("  HAUTE    = %d\n", PRIORITE_HAUTE);
    printf("  CRITIQUE = %d\n\n", PRIORITE_CRITIQUE);


    /* ----------------------------------------------------------
     * PARTIE 3 — ENUM DANS UN SWITCH
     *
     * L'usage principal des enums est dans un switch/case.
     * Le compilateur peut avertir si un cas de l'enum
     * n'est pas traité dans le switch (avec -Wswitch).
     * ---------------------------------------------------------- */
    afficher_separateur("3. Enum dans un switch");

    /* Parcourir tous les jours et les catégoriser */
    enum Jour j;
    printf("Classement des jours :\n");
    for (j = LUNDI; j <= DIMANCHE; j++) {
        printf("  %s : ", nom_jour(j));
        switch (j) {
            case LUNDI:
            case MARDI:
            case MERCREDI:
            case JEUDI:
            case VENDREDI:
                printf("jour de semaine\n");
                break;
            case SAMEDI:
            case DIMANCHE:
                printf("week-end !\n");
                break;
        }
    }
    printf("\n");

    /* Switch sur les codes HTTP */
    enum CodeHTTP codes[] = {
        HTTP_OK, HTTP_CREATED, HTTP_NOT_FOUND,
        HTTP_FORBIDDEN, HTTP_SERVER_ERR
    };
    int nb_codes = 5;

    printf("Analyse des codes HTTP :\n");
    for (int i = 0; i < nb_codes; i++) {
        printf("  %d : ", codes[i]);
        switch (codes[i]) {
            case HTTP_OK:         printf("OK\n");             break;
            case HTTP_CREATED:    printf("Created\n");        break;
            case HTTP_NO_CONTENT: printf("No Content\n");     break;
            case HTTP_NOT_FOUND:  printf("Not Found\n");      break;
            case HTTP_FORBIDDEN:  printf("Forbidden\n");      break;
            case HTTP_SERVER_ERR: printf("Server Error\n");   break;
            default:              printf("Inconnu\n");
        }
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — typedef enum : LA FORME RECOMMANDÉE
     *
     * Sans typedef : on doit écrire "enum Couleur" partout.
     * Avec typedef : on écrit juste "Couleur".
     *
     * Même principe que pour les structs.
     * C'est la forme la plus utilisée dans le code professionnel.
     * ---------------------------------------------------------- */
    afficher_separateur("4. typedef enum");

    /* Sans typedef : verbose */
    enum Jour lundi_long = LUNDI;
    printf("Sans typedef : enum Jour j = LUNDI (=%d)\n", lundi_long);

    /* Avec typedef : concis */
    Couleur fond  = BLEU;
    Couleur texte = BLANC;
    Direction cap = EST;

    printf("Avec typedef :\n");
    printf("  fond    = %s (%d)\n", nom_couleur(fond),  fond);
    printf("  texte   = %s (%d)\n", nom_couleur(texte), texte);
    printf("  cap     = %s (%d degres)\n\n",
           nom_direction(cap), cap);

    /* Tableau de couleurs */
    Couleur palette[] = {ROUGE, VERT, BLEU, JAUNE};
    int nb_couleurs = 4;
    printf("Palette :\n");
    for (int i = 0; i < nb_couleurs; i++) {
        printf("  palette[%d] = %s\n", i, nom_couleur(palette[i]));
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 5 — ENUM DANS UNE MACHINE À ÉTATS
     *
     * Les enums sont parfaits pour modéliser des machines à états.
     * L'état courant est une variable de type enum.
     * Les transitions entre états se font via des fonctions.
     * ---------------------------------------------------------- */
    afficher_separateur("5. Machine a etats avec enum");

    EtatTache tache = ETAT_INITIAL;
    printf("Etat initial : %s\n", nom_etat(tache));

    /* Simuler des transitions */
    printf("Demarrage de la tache...\n");
    avancer_etat(&tache);
    printf("  → %s\n", nom_etat(tache));

    printf("Pause...\n");
    if (tache == ETAT_EN_COURS) {
        tache = ETAT_EN_PAUSE;
        printf("  → %s\n", nom_etat(tache));
    }

    printf("Reprise...\n");
    if (tache == ETAT_EN_PAUSE) {
        tache = ETAT_EN_COURS;
        printf("  → %s\n", nom_etat(tache));
    }

    printf("Fin...\n");
    avancer_etat(&tache);
    printf("  → %s\n\n", nom_etat(tache));


    /* ----------------------------------------------------------
     * PARTIE 6 — ENUM COMBINÉ AVEC STRUCT (TAGGED UNION)
     *
     * Rappel de la leçon 4 : la tagged union utilise un enum
     * comme "tag" pour identifier le membre actif de l'union.
     * C'est le pattern le plus puissant qui combine
     * enum + struct + union.
     * ---------------------------------------------------------- */
    afficher_separateur("6. Enum + struct (tagged union)");

    Valeur v1 = {VAL_ENTIER,   {.entier   = 42}};
    Valeur v2 = {VAL_FLOTTANT, {.flottant = 3.14f}};
    Valeur v3 = {VAL_BOOLEEN,  {.booleen  = 1}};

    printf("Valeurs typees :\n");
    afficher_valeur(v1);
    afficher_valeur(v2);
    afficher_valeur(v3);

    /* Tableau de valeurs hétérogènes */
    Valeur valeurs[] = {
        {VAL_ENTIER,   {.entier   = 100}},
        {VAL_FLOTTANT, {.flottant = 2.71f}},
        {VAL_BOOLEEN,  {.booleen  = 0}},
        {VAL_ENTIER,   {.entier   = -5}},
    };
    int nv = 4;

    printf("\nTableau heterogene :\n");
    for (int i = 0; i < nv; i++) {
        printf("  [%d] ", i);
        afficher_valeur(valeurs[i]);
    }
    printf("\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  enum Nom { A=0, B, C };     → declaration basique\n");
    printf("  enum Nom { A=10, B=20 };    → valeurs personnalisees\n");
    printf("  typedef enum { ... } Alias; → forme recommandee\n");
    printf("  switch (mon_enum) { ... }   → usage principal\n");
    printf("  for (e=A; e<=C; e++)        → parcourir un enum\n");
    printf("  EtatMachine e = ETAT_INIT;  → machine a etats\n");
    printf("  struct + union + enum       → tagged union\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS DES FONCTIONS
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

const char *nom_jour(enum Jour j) {
    switch (j) {
        case LUNDI:    return "Lundi";
        case MARDI:    return "Mardi";
        case MERCREDI: return "Mercredi";
        case JEUDI:    return "Jeudi";
        case VENDREDI: return "Vendredi";
        case SAMEDI:   return "Samedi";
        case DIMANCHE: return "Dimanche";
        default:       return "Inconnu";
    }
}

const char *nom_etat(EtatTache e) {
    switch (e) {
        case ETAT_INITIAL:  return "INITIAL";
        case ETAT_EN_COURS: return "EN_COURS";
        case ETAT_EN_PAUSE: return "EN_PAUSE";
        case ETAT_TERMINE:  return "TERMINE";
        case ETAT_ERREUR:   return "ERREUR";
        default:            return "INCONNU";
    }
}

const char *nom_couleur(Couleur c) {
    switch (c) {
        case ROUGE:  return "Rouge";
        case VERT:   return "Vert";
        case BLEU:   return "Bleu";
        case JAUNE:  return "Jaune";
        case BLANC:  return "Blanc";
        case NOIR:   return "Noir";
        default:     return "Inconnue";
    }
}

const char *nom_direction(Direction d) {
    switch (d) {
        case NORD:  return "Nord";
        case EST:   return "Est";
        case SUD:   return "Sud";
        case OUEST: return "Ouest";
        default:    return "Inconnue";
    }
}

void afficher_valeur(Valeur v) {
    switch (v.type) {
        case VAL_ENTIER:
            printf("int     = %d\n", v.donnee.entier);
            break;
        case VAL_FLOTTANT:
            printf("float   = %.2f\n", v.donnee.flottant);
            break;
        case VAL_BOOLEEN:
            printf("bool    = %s\n",
                   v.donnee.booleen ? "true" : "false");
            break;
    }
}

void avancer_etat(EtatTache *etat) {
    switch (*etat) {
        case ETAT_INITIAL:  *etat = ETAT_EN_COURS; break;
        case ETAT_EN_COURS: *etat = ETAT_TERMINE;  break;
        case ETAT_EN_PAUSE: *etat = ETAT_EN_COURS; break;
        case ETAT_TERMINE:
        case ETAT_ERREUR:
            /* Rester dans l'état final */
            break;
    }
}