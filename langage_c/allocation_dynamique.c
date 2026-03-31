/*
 * ============================================================
 *  FICHIER  : allocation_dynamique.c
 *  SUJET    : L'allocation dynamique en C
 *  NIVEAU   : Intermédiaire — Leçon 2
 *  COMPILE  : gcc -Wall -Wextra allocation_dynamique.c -o alloc
 *  EXECUTE  : ./alloc
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>   /* malloc, calloc, realloc, free */
#include <string.h>   /* memset, strcpy */

/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);
void afficher_tableau(int *tab, int taille);
int  *creer_tableau(int taille);
void remplir_tableau(int *tab, int taille);


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 2 : Allocation dynamique\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — PILE vs TAS (STACK vs HEAP)
     *
     * La mémoire d'un programme C est divisée en zones :
     *
     *  PILE (Stack) :
     *   - Variables locales, paramètres de fonctions
     *   - Taille connue à la compilation
     *   - Gérée AUTOMATIQUEMENT (créée/détruite avec la fonction)
     *   - Limitée en taille (~1-8 Mo selon l'OS)
     *
     *  TAS (Heap) :
     *   - Mémoire allouée DYNAMIQUEMENT pendant l'exécution
     *   - Taille connue seulement à l'exécution
     *   - Gérée MANUELLEMENT (malloc → free)
     *   - Beaucoup plus grande (~gigaoctets disponibles)
     *   - Persiste jusqu'à free() ou fin du programme
     * ---------------------------------------------------------- */
    afficher_separateur("1. Pile (Stack) vs Tas (Heap)");

    /* Variables sur la PILE : taille connue à la compilation */
    int tableau_pile[5] = {1, 2, 3, 4, 5};
    printf("Tableau sur la PILE (taille fixe = 5) :\n");
    afficher_tableau(tableau_pile, 5);

    /* Le problème : on ne peut pas toujours connaître la taille
     * à l'avance. Ex : l'utilisateur saisit la taille. */
    int taille_souhaitee = 8;   /* En pratique : lu au clavier */
    printf("\nOn veut un tableau de %d elements...\n", taille_souhaitee);
    printf("Avec la pile : int tab[?] — impossible !\n");
    printf("Avec le tas  : malloc() — possible !\n\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — malloc() : ALLOUER DE LA MÉMOIRE
     *
     * malloc() alloue un bloc de N octets dans le TAS.
     * Elle retourne un void* (pointeur générique).
     * Elle ne initialise PAS la mémoire (contenu aléatoire).
     *
     * Syntaxe : void *malloc(size_t taille_en_octets);
     *
     * Bonne pratique :
     *   type *p = (type*)malloc(n * sizeof(type));
     *
     * TOUJOURS vérifier que malloc n'a pas retourné NULL !
     * NULL = échec de l'allocation (mémoire insuffisante).
     * ---------------------------------------------------------- */
    afficher_separateur("2. malloc() : allouer de la memoire");

    int n = 6;
    int *tab_dyn = (int*)malloc(n * sizeof(int));

    /* Vérification OBLIGATOIRE */
    if (tab_dyn == NULL) {
        printf("ERREUR : malloc a echoue !\n");
        return 1;   /* Quitter le programme */
    }

    printf("malloc(%d * %lu) = malloc(%lu octets)\n",
           n, sizeof(int), n * sizeof(int));
    printf("Adresse allouee : %p\n", (void*)tab_dyn);

    /* La mémoire n'est PAS initialisée : valeurs aléatoires */
    printf("Contenu brut (non initialise) :\n");
    afficher_tableau(tab_dyn, n);

    /* On initialise manuellement */
    for (int i = 0; i < n; i++) {
        tab_dyn[i] = (i + 1) * 10;
    }
    printf("Apres initialisation manuelle :\n");
    afficher_tableau(tab_dyn, n);

    /* LIBÉRER la mémoire quand on a terminé */
    free(tab_dyn);
    tab_dyn = NULL;   /* Bonne pratique : évite le pointeur dangling */
    printf("Memoire liberee avec free()\n\n");


    /* ----------------------------------------------------------
     * PARTIE 3 — calloc() : ALLOUER ET INITIALISER À ZÉRO
     *
     * calloc() alloue N éléments de taille T chacun.
     * CONTRAIREMENT à malloc(), elle initialise tout à ZÉRO.
     * Plus sûre que malloc() pour éviter les valeurs parasites.
     *
     * Syntaxe : void *calloc(size_t nb_elements, size_t taille);
     *
     * calloc(n, sizeof(int)) == malloc(n * sizeof(int)) + zéros
     * ---------------------------------------------------------- */
    afficher_separateur("3. calloc() : allouer et initialiser a zero");

    int m = 5;
    int *tab_zero = (int*)calloc(m, sizeof(int));

    if (tab_zero == NULL) {
        printf("ERREUR : calloc a echoue !\n");
        return 1;
    }

    printf("calloc(%d, %lu) :\n", m, sizeof(int));
    printf("Contenu IMMEDIATEMENT apres calloc (tout a 0) :\n");
    afficher_tableau(tab_zero, m);

    /* Comparaison */
    printf("\nComparaison malloc vs calloc :\n");
    printf("  malloc : contenu aleatoire → initialiser manuellement\n");
    printf("  calloc : contenu = 0       → pret a l'emploi\n\n");

    free(tab_zero);
    tab_zero = NULL;


    /* ----------------------------------------------------------
     * PARTIE 4 — realloc() : REDIMENSIONNER UN BLOC
     *
     * realloc() change la taille d'un bloc déjà alloué.
     * Les données existantes sont CONSERVÉES.
     * Si le nouveau bloc est plus grand, les nouveaux octets
     * ont un contenu indéfini (comme malloc).
     *
     * Syntaxe : void *realloc(void *ptr, size_t nouvelle_taille);
     *
     * ATTENTION : realloc peut changer l'adresse du bloc !
     * Toujours utiliser le pointeur retourné par realloc.
     *
     * Si realloc échoue → retourne NULL et le bloc original
     * est TOUJOURS valide (ne pas écraser le pointeur !).
     * ---------------------------------------------------------- */
    afficher_separateur("4. realloc() : redimensionner un bloc");

    /* Allouer un tableau de 3 entiers */
    int taille_initiale = 3;
    int *tab_realloc = (int*)malloc(taille_initiale * sizeof(int));

    if (tab_realloc == NULL) { return 1; }

    tab_realloc[0] = 10;
    tab_realloc[1] = 20;
    tab_realloc[2] = 30;

    printf("Tableau initial (3 elements) :\n");
    afficher_tableau(tab_realloc, taille_initiale);
    printf("Adresse initiale : %p\n", (void*)tab_realloc);

    /* Agrandir à 6 éléments */
    int nouvelle_taille = 6;
    int *tmp = (int*)realloc(tab_realloc, nouvelle_taille * sizeof(int));

    /* Vérification CRITIQUE : ne pas écraser tab_realloc si NULL */
    if (tmp == NULL) {
        printf("ERREUR : realloc a echoue ! Bloc original intact.\n");
        free(tab_realloc);
        return 1;
    }
    tab_realloc = tmp;   /* Mise à jour du pointeur */

    /* Les 3 premières valeurs sont conservées */
    tab_realloc[3] = 40;
    tab_realloc[4] = 50;
    tab_realloc[5] = 60;

    printf("Apres realloc (6 elements) :\n");
    afficher_tableau(tab_realloc, nouvelle_taille);
    printf("Nouvelle adresse : %p\n", (void*)tab_realloc);
    printf("(peut etre differente si le bloc a ete deplace)\n\n");

    free(tab_realloc);
    tab_realloc = NULL;


    /* ----------------------------------------------------------
     * PARTIE 5 — free() : LIBÉRER LA MÉMOIRE
     *
     * free() libère un bloc alloué avec malloc/calloc/realloc.
     * Après free(), la mémoire est rendue au système.
     * Le pointeur devient un "pointeur dangling" (pendouillant) :
     * il pointe vers une zone libérée — dangereux à utiliser !
     *
     * Règles d'or :
     *   1. free() uniquement ce qui a été alloué dynamiquement
     *   2. Ne jamais free() deux fois le même bloc (double free)
     *   3. Mettre le pointeur à NULL après free()
     *   4. Chaque malloc/calloc doit avoir son free()
     * ---------------------------------------------------------- */
    afficher_separateur("5. free() : liberer la memoire");

    int *p = (int*)malloc(4 * sizeof(int));
    if (p == NULL) { return 1; }

    p[0] = 1; p[1] = 2; p[2] = 3; p[3] = 4;
    printf("Avant free : p = %p, p[0] = %d\n", (void*)p, p[0]);

    free(p);
    p = NULL;   /* TOUJOURS mettre à NULL après free */

    printf("Apres free + NULL : p = %p\n", (void*)p);
    printf("Tentative d'acces apres NULL → verifiable avec if(p)\n");

    if (p == NULL) {
        printf("p est NULL → acces interdit ✓\n");
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — FUITES MÉMOIRE ET COMMENT LES ÉVITER
     *
     * Une fuite mémoire (memory leak) survient quand on alloue
     * de la mémoire sans jamais la libérer.
     * Le programme consomme de plus en plus de RAM jusqu'à
     * potentiellement faire planter le système.
     *
     * Causes courantes :
     *   - Oublier free() avant de quitter une fonction
     *   - Écraser un pointeur sans libérer l'ancien bloc
     *   - Sortir d'une boucle sans free()
     *
     * Outil de détection : valgrind
     *   valgrind --leak-check=full ./programme
     * ---------------------------------------------------------- */
    afficher_separateur("6. Fuites memoire");

    /* FUITE : le pointeur est ecrase sans liberer l'ancien bloc */
    int *fuite = (int*)malloc(10 * sizeof(int));
    if (fuite == NULL) { return 1; }
    /* ... utilisation ... */
    /* fuite = malloc(20 * sizeof(int));  ← FUITE ! ancien bloc perdu */
    /* Correct : */
    free(fuite);
    fuite = (int*)malloc(20 * sizeof(int));  /* Maintenant OK */
    if (fuite == NULL) { return 1; }
    free(fuite);
    fuite = NULL;

    printf("Bonne pratique : toujours free() avant de reaffecter\n");
    printf("Detection de fuites : valgrind --leak-check=full ./prog\n\n");


    /* ----------------------------------------------------------
     * PARTIE 7 — POINTEURS NULS (NULL) ET VÉRIFICATIONS
     *
     * NULL est une valeur spéciale signifiant "ne pointe nulle part".
     * malloc/calloc/realloc retournent NULL si l'allocation échoue.
     * Déréférencer NULL provoque un SEGFAULT (crash immédiat).
     *
     * Règle absolue : TOUJOURS vérifier le retour de malloc !
     * ---------------------------------------------------------- */
    afficher_separateur("7. NULL et verifications");

    /* Démonstration de la vérification systématique */
    int *tableau = NULL;
    int taille_tab = 10;

    printf("Allocation de %d entiers...\n", taille_tab);
    tableau = (int*)malloc(taille_tab * sizeof(int));

    /* Pattern de vérification standard */
    if (tableau == NULL) {
        fprintf(stderr, "ERREUR : Allocation echouee !\n");
        return 1;
    }

    printf("Allocation reussie : %p\n", (void*)tableau);

    /* Utilisation sécurisée */
    for (int i = 0; i < taille_tab; i++) {
        tableau[i] = i * i;   /* 0, 1, 4, 9, 16... */
    }
    printf("Contenu : ");
    afficher_tableau(tableau, taille_tab);

    free(tableau);
    tableau = NULL;
    printf("Libere et mis a NULL.\n\n");


    /* ----------------------------------------------------------
     * PARTIE 8 — TABLEAU DYNAMIQUE COMPLET
     *
     * Exemple complet : tableau dont la taille est déterminée
     * à l'exécution, qu'on peut agrandir au besoin.
     * Illustration du cycle de vie complet :
     *   malloc → utilisation → realloc → utilisation → free
     * ---------------------------------------------------------- */
    afficher_separateur("8. Exemple complet : tableau dynamique");

    int capacite  = 3;   /* taille initiale */
    int nb_elems  = 0;   /* nombre d'éléments actuels */
    int *dynarray = (int*)malloc(capacite * sizeof(int));

    if (dynarray == NULL) { return 1; }

    /* Simuler l'ajout d'éléments un par un */
    int elements_a_ajouter[] = {5, 12, 8, 3, 19, 7, 14};
    int nb_a_ajouter = 7;

    for (int i = 0; i < nb_a_ajouter; i++) {
        /* Si tableau plein → agrandir */
        if (nb_elems == capacite) {
            capacite *= 2;   /* Doubler la capacité */
            int *tmp2 = (int*)realloc(dynarray, capacite * sizeof(int));
            if (tmp2 == NULL) {
                printf("realloc echoue !\n");
                free(dynarray);
                return 1;
            }
            dynarray = tmp2;
            printf("  → Capacite doublee : maintenant %d cases\n", capacite);
        }

        dynarray[nb_elems] = elements_a_ajouter[i];
        nb_elems++;

        printf("Ajout de %2d | elements: %d | capacite: %d | ",
               elements_a_ajouter[i], nb_elems, capacite);
        afficher_tableau(dynarray, nb_elems);
    }

    free(dynarray);
    dynarray = NULL;
    printf("\nTableau libere.\n\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  malloc(n*sizeof(T))      → alloue n cases (non init)\n");
    printf("  calloc(n, sizeof(T))     → alloue n cases (= 0)\n");
    printf("  realloc(ptr, new_taille) → redimensionne\n");
    printf("  free(ptr); ptr = NULL;   → libere et securise\n");
    printf("  Toujours tester NULL apres malloc !\n");
    printf("  1 malloc = 1 free (pas plus, pas moins)\n");
    printf("  valgrind pour detecter les fuites\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS DES FONCTIONS
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

void afficher_tableau(int *tab, int taille) {
    printf("[");
    for (int i = 0; i < taille; i++) {
        printf("%d", tab[i]);
        if (i < taille - 1) printf(", ");
    }
    printf("]\n");
}

/* Crée un tableau dynamique initialisé avec des valeurs */
int *creer_tableau(int taille) {
    int *t = (int*)calloc(taille, sizeof(int));
    return t;   /* Retourne NULL si échec */
}

void remplir_tableau(int *tab, int taille) {
    for (int i = 0; i < taille; i++) {
        tab[i] = (i + 1) * 5;
    }
}