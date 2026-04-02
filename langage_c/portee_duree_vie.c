/*
 * ============================================================
 *  FICHIER  : portee_duree_vie.c
 *  SUJET    : Portée et durée de vie avancées en C
 *  NIVEAU   : Intermédiaire — Leçon 9
 *  COMPILE  : gcc -Wall -Wextra portee_duree_vie.c -o portee
 *  EXECUTE  : ./portee
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

/* ============================================================
 * VARIABLES GLOBALES ET MODIFICATEURS AU NIVEAU FICHIER
 * ============================================================ */

/* Variable globale "normale" : accessible depuis tout le programme
 * (y compris d'autres fichiers avec extern) */
int compteur_global = 0;

/* Variable globale static : accessible UNIQUEMENT dans ce fichier.
 * Invisible pour les autres fichiers .c même avec extern.
 * Durée de vie = toute la durée du programme. */
static int compteur_prive = 0;

/* Constante globale utile partout */
static const int VERSION = 9;


/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);

/* Fonctions démontrant static local */
int  compter_appels();
void incrementer_compteur();
int  generer_id();
void afficher_stats();

/* Fonctions démontrant static global */
static void fonction_privee();   /* visible seulement ici */
void        fonction_publique(); /* visible dans tout le programme */

/* Fonctions pour const + pointeurs */
void lire_seulement(const int *p);
void lire_et_modifier(int *p);
void pointeur_fixe_demo();


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON %d : Portee avancee\n", VERSION);
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — static LOCAL : VARIABLE PERSISTANTE ENTRE APPELS
     *
     * Une variable locale static conserve sa valeur entre les
     * appels successifs à la fonction.
     *
     * Différence avec une variable locale ordinaire :
     *   locale normale : créée à chaque appel, détruite à la fin
     *   locale static  : créée UNE fois, persiste TOUJOURS
     *
     * La variable est initialisée UNE seule fois (à la première
     * exécution). Initialisée à 0 par défaut si non spécifié.
     * ---------------------------------------------------------- */
    afficher_separateur("1. static local : persistance entre appels");

    printf("Appels a compter_appels() :\n");
    for (int i = 0; i < 5; i++) {
        printf("  Appel %d → retourne %d\n", i+1, compter_appels());
    }
    printf("\n");

    printf("Appels a generer_id() :\n");
    for (int i = 0; i < 4; i++) {
        printf("  ID genere : %d\n", generer_id());
    }
    printf("\n");

    /* Démonstration avec plusieurs fonctions */
    incrementer_compteur();
    incrementer_compteur();
    incrementer_compteur();
    afficher_stats();
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — static GLOBAL : VARIABLE PRIVÉE AU FICHIER
     *
     * Une variable globale static n'est visible que dans
     * le fichier source où elle est déclarée.
     * Cela permet de "masquer" des données d'implémentation.
     *
     * C'est l'équivalent C des variables "private" en POO.
     * Essentiel pour la modularité et l'encapsulation.
     * ---------------------------------------------------------- */
    afficher_separateur("2. static global : prive au fichier");

    printf("compteur_global (accessible depuis partout) = %d\n",
           compteur_global);
    printf("compteur_prive  (accessible seulement ici) = %d\n\n",
           compteur_prive);

    /* Modifier la globale publique */
    compteur_global = 42;
    printf("Apres modification : compteur_global = %d\n", compteur_global);

    /* La globale privée ne peut pas être accédée de l'extérieur */
    compteur_prive = 7;
    printf("Apres modification : compteur_prive  = %d\n\n", compteur_prive);


    /* ----------------------------------------------------------
     * PARTIE 3 — static SUR UNE FONCTION
     *
     * Une fonction static n'est visible que dans le fichier
     * source où elle est définie. Elle est "privée" au fichier.
     *
     * Sans static : la fonction est exportée et peut être
     *               appelée depuis d'autres fichiers .c
     * Avec static : la fonction est locale au fichier (privée)
     *
     * Bonne pratique : toujours mettre static sur les fonctions
     * qui ne font pas partie de l'interface publique du module.
     * ---------------------------------------------------------- */
    afficher_separateur("3. static sur une fonction");

    printf("Appel de fonction_publique() :\n");
    fonction_publique();   /* visible depuis n'importe quel fichier */

    printf("\nAppel de fonction_privee() :\n");
    fonction_privee();     /* uniquement accessible dans ce fichier */

    printf("\n/* Note : depuis un autre fichier.c, appeler */\n");
    printf("/* fonction_privee() causerait une erreur !  */\n\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — extern : PARTAGER UNE VARIABLE ENTRE FICHIERS
     *
     * extern déclare qu'une variable est DÉFINIE ailleurs
     * (dans un autre fichier .c).
     * Elle ne crée pas la variable, elle la "référence".
     *
     * Dans fichier_a.c : int nb_connexions = 0;  (définition)
     * Dans fichier_b.c : extern int nb_connexions; (déclaration)
     *
     * Règle d'or :
     *   - La DÉFINITION est dans UN seul .c (sans extern)
     *   - Les DÉCLARATIONS sont dans le .h (avec extern)
     *   - Les autres .c incluent le .h
     * ---------------------------------------------------------- */
    afficher_separateur("4. extern : partager entre fichiers");

    printf("Principe d'extern :\n\n");
    printf("  fichier_a.c :\n");
    printf("    int nb_connexions = 0;    ← DEFINITION\n");
    printf("    void connecter() { nb_connexions++; }\n\n");
    printf("  reseau.h :\n");
    printf("    extern int nb_connexions; ← DECLARATION\n");
    printf("    void connecter();\n\n");
    printf("  fichier_b.c :\n");
    printf("    #include \"reseau.h\"\n");
    printf("    // nb_connexions accessible ici !\n\n");

    /* Simulation avec notre propre globale */
    printf("Simulation avec compteur_global :\n");
    printf("  Avant : compteur_global = %d\n", compteur_global);
    compteur_global++;
    printf("  Apres : compteur_global = %d\n\n", compteur_global);


    /* ----------------------------------------------------------
     * PARTIE 5 — const SUR LES POINTEURS
     *
     * const avec les pointeurs est source de confusion.
     * Il y a trois cas distincts selon la position de const :
     *
     *   const int *p    → le contenu pointé est constant (valeur)
     *                      mais p peut être réaffecté
     *
     *   int * const p   → le pointeur lui-même est constant
     *                      mais *p peut être modifié
     *
     *   const int * const p → tout est constant
     *
     * Astuce de lecture : lire de droite à gauche.
     *   "p est un const pointeur vers un int const"
     * ---------------------------------------------------------- */
    afficher_separateur("5. const sur les pointeurs");

    int valeur = 10;
    int autre  = 99;

    /* const int *p : protège la VALEUR pointée */
    const int *p1 = &valeur;
    printf("const int *p1 = &valeur (%d)\n", *p1);
    /* *p1 = 20;  ← ERREUR : ne peut pas modifier la valeur */
    p1 = &autre;   /* OK : peut changer où pointe p1 */
    printf("Après p1 = &autre : *p1 = %d\n\n", *p1);

    /* int * const p : protège le POINTEUR lui-même */
    int * const p2 = &valeur;
    printf("int * const p2 = &valeur (%d)\n", *p2);
    *p2 = 50;    /* OK : peut modifier la valeur */
    printf("Après *p2 = 50 : valeur = %d\n", valeur);
    /* p2 = &autre;  ← ERREUR : ne peut pas changer p2 */
    printf("p2 ne peut pas etre reassigne.\n\n");

    /* const int * const p : tout est protégé */
    const int * const p3 = &valeur;
    printf("const int * const p3 = &valeur (%d)\n", *p3);
    /* *p3 = 20;    ← ERREUR */
    /* p3 = &autre; ← ERREUR */
    printf("Ni la valeur ni le pointeur ne peuvent changer.\n\n");

    /* Utilisation pratique : paramètre de fonction */
    printf("Usage pratique dans les fonctions :\n");
    lire_seulement(&valeur);    /* const int *p : lecture seule */
    lire_et_modifier(&valeur);  /* int *p : peut modifier */
    printf("Apres lire_et_modifier : valeur = %d\n\n", valeur);


    /* ----------------------------------------------------------
     * PARTIE 6 — volatile : NE PAS OPTIMISER
     *
     * volatile indique au compilateur que la valeur peut
     * changer à tout moment, de façon imprévisible
     * (interruption matérielle, autre thread, registre matériel).
     *
     * Sans volatile, le compilateur peut "optimiser" en
     * gardant la valeur en cache (registre CPU), ce qui
     * donne des résultats incorrects dans certains contextes.
     *
     * Cas d'usage :
     *   - Registres matériels (programmation embarquée)
     *   - Variables modifiées par des interruptions
     *   - Variables partagées entre threads (en partie)
     * ---------------------------------------------------------- */
    afficher_separateur("6. volatile : signaler au compilateur");

    printf("Cas d'usage de volatile :\n\n");

    printf("  1. Registre materiel (embarque) :\n");
    printf("     volatile int *reg = (int*)0x4000;\n");
    printf("     while (*reg & 0x01);  ← re-lit a chaque tour\n\n");

    printf("  2. Drapeau d'interruption :\n");
    printf("     volatile int signal_recu = 0;\n");
    printf("     // Gestionnaire d'interruption :\n");
    printf("     void ISR() { signal_recu = 1; }\n");
    printf("     // Boucle principale :\n");
    printf("     while (!signal_recu) { attendre(); }\n\n");

    printf("  3. Sans volatile (MAUVAIS pour registres) :\n");
    printf("     int statut = *registre_hw;  ← lu une fois\n");
    printf("     // Compilateur optimise en : if(statut)...\n");
    printf("     // → ne re-lit JAMAIS le registre !\n\n");

    /* Démonstration de la syntaxe */
    volatile int drapeau = 0;
    printf("Syntaxe : volatile int drapeau = %d;\n", drapeau);
    drapeau = 1;
    printf("Apres modif : drapeau = %d\n\n", drapeau);


    /* ----------------------------------------------------------
     * PARTIE 7 — RÉSUMÉ DES MODIFICATEURS
     * ---------------------------------------------------------- */
    afficher_separateur("7. Resume des modificateurs");

    printf("PORTEE ET DUREE DE VIE :\n\n");

    printf("Variable LOCALE (sans qualificateur) :\n");
    printf("  Portee   : bloc { } courant\n");
    printf("  Duree    : entree/sortie du bloc\n");
    printf("  Init     : aleatoire (non initialisee)\n\n");

    printf("Variable LOCALE STATIC :\n");
    printf("  Portee   : bloc { } courant\n");
    printf("  Duree    : tout le programme\n");
    printf("  Init     : une seule fois (0 par defaut)\n\n");

    printf("Variable GLOBALE :\n");
    printf("  Portee   : tout le programme\n");
    printf("  Duree    : tout le programme\n");
    printf("  Init     : 0 par defaut\n\n");

    printf("Variable GLOBALE STATIC :\n");
    printf("  Portee   : ce fichier .c uniquement\n");
    printf("  Duree    : tout le programme\n");
    printf("  Init     : 0 par defaut\n\n");

    printf("EXTERN : declaration (pas de creation)\n");
    printf("  Accede a une variable definie ailleurs\n\n");

    printf("CONST : valeur immuable\n");
    printf("  const int x   : x ne peut pas changer\n");
    printf("  const int *p  : *p ne peut pas changer\n");
    printf("  int * const p : p ne peut pas etre reassigne\n\n");

    printf("VOLATILE : interdire l'optimisation\n");
    printf("  Pour registres HW, interruptions, multi-thread\n\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS DES FONCTIONS
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

/* static local : la variable count persiste entre les appels */
int compter_appels() {
    static int count = 0;   /* initialisée UNE fois à 0 */
    count++;                 /* se souvient de la valeur précédente */
    return count;
}

/* Autre exemple de static local : générateur d'IDs uniques */
int generer_id() {
    static int prochain_id = 1000;   /* commence à 1000 */
    return prochain_id++;
}

/* static local dans plusieurs fonctions distinctes */
void incrementer_compteur() {
    static int appels = 0;
    static int total  = 0;
    appels++;
    total += appels;
    /* Ces variables partagent leur état entre les appels */
}

void afficher_stats() {
    /* Ces variables NE SONT PAS les mêmes que dans incrementer_compteur */
    /* Chaque fonction a ses propres variables static locales */
    printf("(Fonctions static local independantes par fonction)\n");
}

/* Fonction static : privée au fichier */
static void fonction_privee() {
    static int nb_appels_prives = 0;
    nb_appels_prives++;
    printf("  fonction_privee() - appel #%d\n", nb_appels_prives);
    printf("  (inaccessible depuis les autres fichiers .c)\n");
}

/* Fonction publique : accessible depuis partout */
void fonction_publique() {
    printf("  fonction_publique() - visible depuis tout le projet\n");
    printf("  (peut appeler fonction_privee() car meme fichier)\n");
    fonction_privee();   /* appel interne autorisé */
}

/* const int *p : ne peut pas modifier la valeur pointée */
void lire_seulement(const int *p) {
    printf("  lire_seulement : *p = %d (lecture seule)\n", *p);
    /* *p = 99;  ← ERREUR de compilation */
}

/* int *p : peut modifier la valeur pointée */
void lire_et_modifier(int *p) {
    printf("  lire_et_modifier : *p etait %d\n", *p);
    *p *= 2;   /* modification autorisée */
    printf("  lire_et_modifier : *p devient %d\n", *p);
}

void pointeur_fixe_demo() {
    int x = 5;
    int y = 10;
    int * const pf = &x;   /* pointeur constant vers x */
    *pf = 99;              /* OK : modifie x */
    /* pf = &y; ← ERREUR : pf ne peut pas être réaffecté */
    (void)y;               /* éviter warning unused */
}