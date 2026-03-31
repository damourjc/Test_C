/*
 * ============================================================
 *  FICHIER  : unions.c
 *  SUJET    : Les unions (union) en C
 *  NIVEAU   : Intermédiaire — Leçon 4
 *  COMPILE  : gcc -Wall -Wextra unions.c -o unions
 *  EXECUTE  : ./unions
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

/* ============================================================
 * DÉCLARATIONS
 * ============================================================ */

/* Union simple : tous les membres partagent la même mémoire */
union Nombre {
    int    entier;
    float  flottant;
    double double_prec;
};

/* Typedef (comme pour les structs) */
typedef union {
    int   i;
    float f;
    char  c;
} Valeur;

/* Cas d'usage classique : union avec tag (tagged union)
 * On combine une union avec un enum pour savoir quel
 * membre est actuellement valide */
typedef enum {
    TYPE_ENTIER,
    TYPE_FLOTTANT,
    TYPE_CHAINE
} TypeDonnee;

typedef struct {
    TypeDonnee type;    /* indique quel membre de l'union utiliser */
    union {
        int   entier;
        float flottant;
        char  chaine[32];
    } valeur;
} Donnee;

/* Union pour inspecter les octets d'un float */
typedef union {
    float         f;
    unsigned int  i;
    unsigned char octets[4];
} InspecteurFloat;

/* Union pour inspecter les octets d'un int */
typedef union {
    int           val;
    unsigned char octets[4];
} InspecteurInt;


/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);
void afficher_donnee(Donnee d);
void afficher_octets_float(float f);
void afficher_octets_int(int v);


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 4 : Les unions\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — DIFFÉRENCE STRUCT vs UNION
     *
     * STRUCT : chaque membre a son propre emplacement mémoire.
     *          La taille totale = somme des tailles des membres.
     *
     * UNION  : tous les membres PARTAGENT le même emplacement.
     *          La taille totale = taille du PLUS GRAND membre.
     *          → On ne peut lire valablement qu'UN seul membre
     *            à la fois (le dernier écrit).
     * ---------------------------------------------------------- */
    afficher_separateur("1. Struct vs Union : la difference fondamentale");

    /* Tailles comparées */
    struct StructExemple {
        int   i;      /* 4 octets */
        float f;      /* 4 octets */
        char  c;      /* 1 octet  */
    };

    union UnionExemple {
        int   i;      /* 4 octets */
        float f;      /* 4 octets */
        char  c;      /* 1 octet  */
    };

    printf("struct { int i; float f; char c; } :\n");
    printf("  sizeof = %lu octets  (4 + 4 + 1 + alignement)\n\n",
           sizeof(struct StructExemple));

    printf("union  { int i; float f; char c; } :\n");
    printf("  sizeof = %lu octets  (seulement le plus grand)\n\n",
           sizeof(union UnionExemple));

    printf("STRUCT : chaque membre a sa propre adresse\n");
    printf("UNION  : tous les membres ont LA MEME adresse\n\n");

    /* Démonstration des adresses */
    union UnionExemple u;
    printf("Adresse de u   : %p\n", (void*)&u);
    printf("Adresse de u.i : %p\n", (void*)&u.i);
    printf("Adresse de u.f : %p\n", (void*)&u.f);
    printf("Adresse de u.c : %p\n\n", (void*)&u.c);


    /* ----------------------------------------------------------
     * PARTIE 2 — DÉCLARER ET UTILISER UNE UNION
     *
     * La syntaxe est identique à struct.
     * ATTENTION : écrire dans un membre modifie la mémoire
     * partagée → les autres membres changent de valeur !
     *
     * On ne peut utiliser QUE le dernier membre écrit.
     * ---------------------------------------------------------- */
    afficher_separateur("2. Declarer et utiliser une union");

    union Nombre n;

    /* Écriture dans le membre 'entier' */
    n.entier = 42;
    printf("Apres n.entier = 42 :\n");
    printf("  n.entier    = %d    (valide - vient d'etre ecrit)\n",
           n.entier);
    printf("  n.flottant  = %f   (invalide - interprete les memes octets)\n",
           n.flottant);

    /* Écriture dans le membre 'flottant' (écrase 'entier') */
    n.flottant = 3.14f;
    printf("\nApres n.flottant = 3.14f :\n");
    printf("  n.flottant  = %f  (valide - vient d'etre ecrit)\n",
           n.flottant);
    printf("  n.entier    = %d  (invalide - les octets ont change)\n\n",
           n.entier);


    /* ----------------------------------------------------------
     * PARTIE 3 — TAILLE EN MÉMOIRE
     *
     * L'union ne réserve que l'espace nécessaire pour
     * son plus grand membre. Économie de mémoire garantie
     * quand on n'a besoin que d'un membre à la fois.
     * ---------------------------------------------------------- */
    afficher_separateur("3. Taille en memoire");

    union Nombre num;

    printf("Membres de union Nombre :\n");
    printf("  int    : %lu octets\n", sizeof(int));
    printf("  float  : %lu octets\n", sizeof(float));
    printf("  double : %lu octets\n", sizeof(double));
    printf("\n");
    printf("sizeof(union Nombre) = %lu octets\n",  sizeof(union Nombre));
    printf("  → taille du plus grand membre (double)\n\n");

    /* Comparaison avec une struct équivalente */
    struct NombreStruct {
        int    entier;
        float  flottant;
        double double_prec;
    };
    printf("sizeof(struct NombreStruct) = %lu octets\n",
           sizeof(struct NombreStruct));
    printf("  → somme de tous les membres\n");
    printf("  → union economise %lu octets ici\n\n",
           sizeof(struct NombreStruct) - sizeof(union Nombre));


    /* ----------------------------------------------------------
     * PARTIE 4 — CAS D'USAGE : ÉCONOMIE MÉMOIRE
     *
     * L'union est utile quand une variable peut contenir
     * un type OU un autre, mais jamais les deux simultanément.
     * Exemple : un champ peut être un entier OU une chaîne.
     *
     * C'est fondamental dans les systèmes embarqués où
     * chaque octet compte.
     * ---------------------------------------------------------- */
    afficher_separateur("4. Cas d'usage : economie memoire");

    /* Sans union : on gaspille de la mémoire */
    struct SansUnion {
        int   entier;      /* 4 octets toujours réservés */
        float flottant;    /* 4 octets toujours réservés */
        char  chaine[32];  /* 32 octets toujours réservés */
        int   type;        /* pour savoir lequel utiliser */
    };

    /* Avec union : seul le plus grand est réservé */
    struct AvecUnion {
        int type;
        union {
            int   entier;
            float flottant;
            char  chaine[32];
        } valeur;
    };

    printf("struct SansUnion : %lu octets\n", sizeof(struct SansUnion));
    printf("struct AvecUnion : %lu octets\n", sizeof(struct AvecUnion));
    printf("Economie : %lu octets\n\n",
           sizeof(struct SansUnion) - sizeof(struct AvecUnion));

    /* Exemple concret */
    struct AvecUnion capteur;
    capteur.type = 0;   /* 0 = entier */
    capteur.valeur.entier = 255;
    printf("Capteur (entier) : %d\n", capteur.valeur.entier);

    capteur.type = 1;   /* 1 = flottant */
    capteur.valeur.flottant = 36.6f;
    printf("Capteur (float)  : %.1f\n\n", capteur.valeur.flottant);


    /* ----------------------------------------------------------
     * PARTIE 5 — TAGGED UNION : LA BONNE PRATIQUE
     *
     * Une tagged union (union étiquetée) combine :
     *   - Un champ "type" (enum) qui indique quel membre est valide
     *   - Une union avec les différentes valeurs possibles
     *
     * C'est le pattern recommandé car on sait toujours
     * quel membre lire sans risquer d'interpréter les mauvais octets.
     * ---------------------------------------------------------- */
    afficher_separateur("5. Tagged union : la bonne pratique");

    /* Créer des données de types différents */
    Donnee d1, d2, d3;

    d1.type          = TYPE_ENTIER;
    d1.valeur.entier = 42;

    d2.type             = TYPE_FLOTTANT;
    d2.valeur.flottant  = 3.14f;

    d3.type = TYPE_CHAINE;
    strcpy(d3.valeur.chaine, "Bonjour C !");

    printf("Donnees avec tagged union :\n");
    afficher_donnee(d1);
    afficher_donnee(d2);
    afficher_donnee(d3);
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — INSPECTER LES OCTETS EN MÉMOIRE
     *
     * Un usage très pratique des unions : accéder aux octets
     * bruts d'un type quelconque. On crée une union entre
     * le type voulu et un tableau d'unsigned char.
     *
     * Cela permet de :
     *   - Comprendre l'encodage binaire des types
     *   - Faire de la sérialisation / désérialisation
     *   - Analyser des protocoles réseau bas niveau
     * ---------------------------------------------------------- */
    afficher_separateur("6. Inspecter les octets en memoire");

    /* Inspecter un int */
    printf("Representation de l'entier 256 :\n");
    afficher_octets_int(256);

    printf("\nRepresentation de l'entier 1 :\n");
    afficher_octets_int(1);

    /* Inspecter un float */
    printf("\nRepresentation du float 1.0f :\n");
    afficher_octets_float(1.0f);

    printf("\nRepresentation du float 3.14f :\n");
    afficher_octets_float(3.14f);

    printf("\nNote : l'ordre des octets depend de l'architecture\n");
    printf("(little-endian sur x86 : octet de poids faible en premier)\n\n");


    /* ----------------------------------------------------------
     * PARTIE 7 — UNION AVEC typedef
     *
     * Comme pour les structs, typedef simplifie l'écriture.
     * ---------------------------------------------------------- */
    afficher_separateur("7. Union avec typedef");

    /* Utilisation du typedef Valeur défini en haut */
    Valeur v;

    v.i = 65;
    printf("v.i = %d\n", v.i);
    printf("v.c = '%c'  (memes octets, interprete comme char)\n\n", v.c);

    v.f = 1.5f;
    printf("v.f = %.1f\n", v.f);
    printf("v.i = %d   (memes octets, interprete comme int)\n\n", v.i);

    printf("sizeof(Valeur) = %lu\n\n", sizeof(Valeur));


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  union { int i; float f; } u;\n");
    printf("  → tous les membres partagent la meme adresse\n");
    printf("  → taille = taille du plus grand membre\n");
    printf("  → un seul membre valide a la fois\n");
    printf("  → economie memoire vs struct\n\n");
    printf("  Tagged union = union + enum type\n");
    printf("  → savoir quel membre lire (bonne pratique)\n\n");
    printf("  Inspection memoire :\n");
    printf("  union { float f; unsigned char b[4]; }\n");
    printf("  → lire les octets bruts d'un float\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

void afficher_donnee(Donnee d) {
    printf("  Type: ");
    switch (d.type) {
        case TYPE_ENTIER:
            printf("ENTIER   → valeur = %d\n", d.valeur.entier);
            break;
        case TYPE_FLOTTANT:
            printf("FLOTTANT → valeur = %.2f\n", d.valeur.flottant);
            break;
        case TYPE_CHAINE:
            printf("CHAINE   → valeur = \"%s\"\n", d.valeur.chaine);
            break;
    }
}

void afficher_octets_float(float f) {
    InspecteurFloat insp;
    insp.f = f;
    printf("  float %.4f → ", f);
    for (int i = 3; i >= 0; i--) {
        printf("%02X ", insp.octets[i]);
    }
    printf("(hex, big-endian)\n");
    printf("  Binaire : ");
    for (int i = 3; i >= 0; i--) {
        for (int b = 7; b >= 0; b--) {
            printf("%d", (insp.octets[i] >> b) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

void afficher_octets_int(int v) {
    InspecteurInt insp;
    insp.val = v;
    printf("  int %d → ", v);
    for (int i = 3; i >= 0; i--) {
        printf("%02X ", insp.octets[i]);
    }
    printf("(hex, big-endian)\n");
}