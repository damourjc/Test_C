/*
 * ============================================================
 *  FICHIER  : compilation.c
 *  SUJET    : La compilation en C
 *  NIVEAU   : Débutant — Leçon 9
 *  COMPILE  : gcc compilation.c -o compilation
 *  EXECUTE  : ./compilation
 * ============================================================
 *
 *  Ce fichier illustre TOUS les concepts de compilation de base :
 *  - Les 4 étapes de compilation
 *  - La commande gcc et ses options
 *  - Les fichiers .h et .c
 *  - Les bibliothèques statiques et dynamiques
 *  - Le Makefile
 *  - Les erreurs et avertissements courants
 *  - Les options d'optimisation
 * ============================================================
 */

/* ============================================================
 * ÉTAPE 1 DU COMPILATEUR : LE PRÉPROCESSEUR
 *
 * Avant de compiler, le préprocesseur traite toutes
 * les directives qui commencent par #.
 * Il travaille sur le TEXTE, pas sur le code C.
 *
 * Directives courantes :
 *   #include  → copie le contenu d'un fichier .h ici
 *   #define   → remplace un nom par une valeur
 *   #ifdef    → compilation conditionnelle
 * ============================================================ */

/* #include <...>  → cherche dans les dossiers système */
#include <stdio.h>    /* Entrées/Sorties : printf, scanf... */
#include <stdlib.h>   /* Utilitaires    : exit, malloc...  */
#include <string.h>   /* Chaînes        : strlen, strcpy.. */

/* #include "..."  → cherche d'abord dans le dossier courant */
/* #include "mon_fichier.h"  ← fichier personnel */

/* #define : substitution textuelle avant compilation */
#define VERSION      9
#define NOM_LECON    "Compilation"
#define MAX_TAILLE   100
#define CARRE(x)     ((x) * (x))   /* Macro avec paramètre */

/* Compilation conditionnelle : active du code selon la plateforme */
#ifdef _WIN32
    #define OS "Windows"
#elif defined(__APPLE__)
    #define OS "macOS"
#elif defined(__linux__)
    #define OS "Linux"
#else
    #define OS "Inconnu"
#endif


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  LECON %d : %s\n", VERSION, NOM_LECON);
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — LES 4 ÉTAPES DE COMPILATION
     *
     * gcc ne transforme pas directement le .c en exécutable.
     * Il passe par 4 étapes distinctes :
     *
     *  1. Préprocesseur → remplace #include, #define...
     *  2. Compilateur   → traduit le C en assembleur (.s)
     *  3. Assembleur    → traduit l'assembleur en binaire (.o)
     *  4. Éditeur de liens → relie les .o en exécutable
     * ---------------------------------------------------------- */
    printf("--- 1. Les 4 etapes de compilation ---\n");
    printf("1. Preprocesseur : traite #include, #define\n");
    printf("   $ gcc -E  source.c -o source.i\n\n");

    printf("2. Compilation   : C → assembleur\n");
    printf("   $ gcc -S  source.c -o source.s\n\n");

    printf("3. Assemblage    : assembleur → binaire objet\n");
    printf("   $ gcc -c  source.c -o source.o\n\n");

    printf("4. Edition liens : relie tout → executable\n");
    printf("   $ gcc source.o -o programme\n\n");

    printf("Tout en une commande (cas habituel) :\n");
    printf("   $ gcc source.c -o programme\n\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — COMMANDE gcc ET SES OPTIONS PRINCIPALES
     *
     * gcc est le compilateur C le plus répandu sous Linux/macOS.
     * Syntaxe de base : gcc [options] fichier.c -o executable
     *
     * Options essentielles :
     *   -o nom    → nom de l'exécutable de sortie
     *   -Wall     → affiche TOUS les avertissements
     *   -Wextra   → avertissements supplémentaires
     *   -g        → informations de débogage (pour gdb)
     *   -O2       → optimisation niveau 2
     *   -lm       → lier la bibliothèque mathématique
     *   -std=c99  → utiliser le standard C99
     * ---------------------------------------------------------- */
    printf("--- 2. Options gcc ---\n");
    printf("Compilation minimale :\n");
    printf("  gcc source.c -o prog\n\n");

    printf("Compilation recommandee (tous avertissements) :\n");
    printf("  gcc -Wall -Wextra source.c -o prog\n\n");

    printf("Avec debogage (pour gdb) :\n");
    printf("  gcc -Wall -g source.c -o prog\n\n");

    printf("Avec bibliotheque math :\n");
    printf("  gcc source.c -o prog -lm\n\n");

    printf("Avec standard C specifique :\n");
    printf("  gcc -std=c99 source.c -o prog\n\n");

    printf("Tout combine :\n");
    printf("  gcc -Wall -Wextra -g -std=c99 source.c -o prog\n\n");


    /* ----------------------------------------------------------
     * PARTIE 3 — FICHIERS .h ET .c : SÉPARER SON CODE
     *
     * Pour les programmes plus longs, on sépare le code en
     * plusieurs fichiers :
     *
     *  fichier.h → déclarations (prototypes, #define, structures)
     *  fichier.c → définitions  (corps des fonctions)
     *
     * Exemple d'organisation :
     *   math_perso.h  → prototypes de vos fonctions maths
     *   math_perso.c  → corps de ces fonctions
     *   main.c        → programme principal
     *
     * Pour compiler plusieurs fichiers .c ensemble :
     *   gcc main.c math_perso.c -o programme
     * ---------------------------------------------------------- */
    printf("--- 3. Fichiers .h et .c ---\n");

    printf("Structure d'un projet multi-fichiers :\n");
    printf("  mon_projet/\n");
    printf("  |-- main.c        (programme principal)\n");
    printf("  |-- calculs.h     (prototypes + #define)\n");
    printf("  |-- calculs.c     (corps des fonctions)\n");
    printf("  |-- affichage.h\n");
    printf("  `-- affichage.c\n\n");

    printf("Contenu type d'un fichier .h :\n");
    printf("  #ifndef CALCULS_H   <- garde d'inclusion\n");
    printf("  #define CALCULS_H\n");
    printf("  int additionner(int a, int b);\n");
    printf("  float moyenne(int tab[], int n);\n");
    printf("  #endif\n\n");

    printf("Compilation multi-fichiers :\n");
    printf("  gcc main.c calculs.c affichage.c -o prog\n\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — GARDE D'INCLUSION (#ifndef)
     *
     * Un fichier .h peut être inclus plusieurs fois indirectement.
     * La garde d'inclusion évite les déclarations en double.
     *
     *  #ifndef NOM_DU_FICHIER_H   → si pas encore défini
     *  #define NOM_DU_FICHIER_H   → le définir
     *  ...contenu du .h...
     *  #endif                     → fin du bloc conditionnel
     * ---------------------------------------------------------- */
    printf("--- 4. Garde d'inclusion ---\n");

    printf("Sans garde : si A.h et B.h incluent tous les deux\n");
    printf("C.h, et que main.c inclut A.h ET B.h :\n");
    printf("→ C.h serait inclus 2 fois → erreur !\n\n");

    printf("Avec garde dans C.h :\n");
    printf("  #ifndef C_H\n");
    printf("  #define C_H\n");
    printf("  // contenu\n");
    printf("  #endif\n");
    printf("→ La 2e inclusion est ignoree automatiquement.\n\n");

    /* Démonstration des #define vus par le préprocesseur */
    printf("Demonstration des #define de ce fichier :\n");
    printf("  VERSION   → %d\n",       VERSION);
    printf("  NOM_LECON → %s\n",       NOM_LECON);
    printf("  MAX_TAILLE→ %d\n",       MAX_TAILLE);
    printf("  CARRE(5)  → %d\n",       CARRE(5));
    printf("  OS detect → %s\n\n",     OS);


    /* ----------------------------------------------------------
     * PARTIE 5 — BIBLIOTHÈQUES : -l ET LEURS USAGES
     *
     * Une bibliothèque est un ensemble de fonctions précompilées.
     * On lie une bibliothèque avec l'option -l (minuscule L).
     *
     * Bibliothèques courantes :
     *   -lm       → math.h   : sqrt, pow, sin, cos...
     *   -lstring  → string.h : (déjà incluse par défaut)
     *   -lpthread → threads POSIX
     *   -lssl     → OpenSSL (chiffrement)
     *
     * Deux types de bibliothèques :
     *   Statique  (.a)  → code copié dans l'exécutable
     *   Dynamique (.so) → chargée au démarrage du programme
     * ---------------------------------------------------------- */
    printf("--- 5. Bibliotheques ---\n");

    printf("Bibliothèque mathematique (math.h) :\n");
    printf("  gcc source.c -o prog -lm\n\n");

    printf("Types de bibliotheques :\n");
    printf("  Statique (.a)  : code integre dans l'exe\n");
    printf("     → executable plus grand\n");
    printf("     → fonctionne sans installation\n\n");

    printf("  Dynamique (.so): code charge au demarrage\n");
    printf("     → executable plus petit\n");
    printf("     → necessite la lib installee\n\n");

    printf("Exemple avec plusieurs bibliotheques :\n");
    printf("  gcc prog.c -o prog -lm -lpthread -lssl\n\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — ERREURS ET AVERTISSEMENTS COURANTS
     *
     * Le compilateur signale deux types de problèmes :
     *
     *  Erreur (error) : le code ne peut PAS compiler.
     *                   Il faut obligatoirement la corriger.
     *
     *  Avertissement (warning) : le code compile MAIS il y a
     *                   un problème potentiel.
     *                   Toujours traiter les warnings !
     *
     * Exemples d'erreurs :
     *   - variable non déclarée
     *   - point-virgule manquant
     *   - accolade non fermée
     *   - type incorrect
     *
     * Exemples de warnings :
     *   - variable déclarée mais non utilisée
     *   - comparaison signed/unsigned
     *   - format printf incorrect (%d pour float)
     *   - variable non initialisée
     * ---------------------------------------------------------- */
    printf("--- 6. Erreurs et avertissements ---\n");

    printf("ERREURS (empechent la compilation) :\n");
    printf("  error: 'x' undeclared\n");
    printf("  → Variable x utilisee sans declaration\n\n");

    printf("  error: expected ';' before '}'\n");
    printf("  → Point-virgule manquant\n\n");

    printf("  error: too few arguments to function\n");
    printf("  → Mauvais nombre d'arguments\n\n");

    printf("AVERTISSEMENTS (le code compile mais...)\n");
    printf("  warning: unused variable 'n'\n");
    printf("  → Variable declaree mais jamais utilisee\n\n");

    printf("  warning: format '%%d' expects 'int' but arg is 'float'\n");
    printf("  → Mauvais specificateur printf\n\n");

    printf("  warning: 'x' is used uninitialized\n");
    printf("  → Variable utilisee sans valeur initiale\n\n");

    printf("Commande pour voir TOUS les warnings :\n");
    printf("  gcc -Wall -Wextra source.c -o prog\n\n");


    /* ----------------------------------------------------------
     * PARTIE 7 — OPTIONS D'OPTIMISATION
     *
     * gcc peut optimiser le code généré pour qu'il s'exécute
     * plus vite ou prenne moins de place en mémoire.
     *
     *  -O0  → Pas d'optimisation (débogage facilité)
     *  -O1  → Optimisations basiques
     *  -O2  → Optimisations standard (recommandé en production)
     *  -O3  → Optimisations agressives (peut changer le comportement)
     *  -Os  → Optimise pour la taille de l'exécutable
     *
     * IMPORTANT : Ne pas utiliser -O avec -g (débogage),
     * le code optimisé est difficile à déboguer.
     * ---------------------------------------------------------- */
    printf("--- 7. Optimisation ---\n");

    printf("Niveaux d'optimisation :\n");
    printf("  gcc -O0 prog.c -o prog  (aucune, debogage)\n");
    printf("  gcc -O1 prog.c -o prog  (basique)\n");
    printf("  gcc -O2 prog.c -o prog  (standard, production)\n");
    printf("  gcc -O3 prog.c -o prog  (agressive)\n");
    printf("  gcc -Os prog.c -o prog  (petite taille)\n\n");

    printf("Regles pratiques :\n");
    printf("  Dev / Debug   → -g -O0 (pas d'optim)\n");
    printf("  Production    → -O2     (standard)\n");
    printf("  Embarque      → -Os     (economie mem)\n\n");


    /* ----------------------------------------------------------
     * PARTIE 8 — LE MAKEFILE : AUTOMATISER LA COMPILATION
     *
     * Pour un projet avec plusieurs fichiers, recompiler
     * à la main devient vite fastidieux.
     * Un Makefile automatise ça : il sait quels fichiers
     * ont changé et recompile uniquement ce qui est nécessaire.
     *
     * Syntaxe de base :
     *   cible : dependances
     *   [TAB] commande
     *
     * Commandes :
     *   make        → compile selon le Makefile
     *   make clean  → supprime les fichiers générés
     * ---------------------------------------------------------- */
    printf("--- 8. Makefile ---\n");

    printf("Exemple de Makefile simple :\n\n");
    printf("  CC = gcc\n");
    printf("  CFLAGS = -Wall -Wextra -g\n\n");
    printf("  prog: main.o calculs.o\n");
    printf("  \t$(CC) main.o calculs.o -o prog\n\n");
    printf("  main.o: main.c calculs.h\n");
    printf("  \t$(CC) $(CFLAGS) -c main.c\n\n");
    printf("  calculs.o: calculs.c calculs.h\n");
    printf("  \t$(CC) $(CFLAGS) -c calculs.c\n\n");
    printf("  clean:\n");
    printf("  \trm -f *.o prog\n\n");

    printf("Utilisation :\n");
    printf("  $ make          → compile le projet\n");
    printf("  $ make clean    → nettoie les fichiers\n\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF COMPLET
     * ---------------------------------------------------------- */
    printf("==============================================\n");
    printf("  RECAPITULATIF DE LA COMPILATION\n");
    printf("==============================================\n");
    printf("  4 etapes : preprocess → compile → assemble → lier\n");
    printf("  gcc base : gcc source.c -o prog\n");
    printf("  Recommande : gcc -Wall -Wextra -g source.c -o prog\n");
    printf("  Multi-fich : gcc main.c utils.c -o prog\n");
    printf("  Biblio math: gcc source.c -o prog -lm\n");
    printf("  .h contient: prototypes + #define + gardes\n");
    printf("  Garde .h   : #ifndef / #define / #endif\n");
    printf("  Erreur     : empeche la compilation\n");
    printf("  Warning    : compile mais a corriger\n");
    printf("  Optim prod : -O2\n");
    printf("  Optim debug: -g -O0\n");
    printf("  Makefile   : automatise la compilation\n");
    printf("\n");

    return 0;
}