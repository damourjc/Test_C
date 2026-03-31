/*
 * ============================================================
 *  FICHIER  : fonctions.c
 *  SUJET    : Les fonctions en C
 *  NIVEAU   : Débutant — Leçon 8
 *  COMPILE  : gcc fonctions.c -o fonctions
 *  EXECUTE  : ./fonctions
 * ============================================================
 */

#include <stdio.h>

/* ============================================================
 * PROTOTYPES (déclarations)
 *
 * En C, une fonction doit être connue AVANT d'être utilisée.
 * Si la définition est après main(), on déclare le prototype ici.
 * Le prototype = la signature sans le corps : type nom(params);
 * ============================================================ */
void        afficher_bonjour();
void        afficher_separateur(char *titre);
int         additionner(int a, int b);
float       calculer_moyenne(int a, int b, int c);
int         est_pair(int n);
int         maximum(int a, int b);
void        afficher_tableau(int tab[], int taille);
int         compter_voyelles(char chaine[]);
void        afficher_table(int n);


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  LECON 8 : Les fonctions\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — POURQUOI UTILISER DES FONCTIONS ?
     *
     * Une fonction est un bloc de code réutilisable auquel on
     * donne un nom. Elle permet de :
     *   - Éviter la répétition de code (DRY : Don't Repeat Yourself)
     *   - Découper le programme en petites parties lisibles
     *   - Tester et corriger chaque partie indépendamment
     *   - Réutiliser le même code à plusieurs endroits
     * ---------------------------------------------------------- */
    afficher_separateur("1. Pourquoi des fonctions ?");

    /* Sans fonction : on répèterait le même printf 3 fois */
    /* Avec fonction : un seul appel suffit */
    afficher_bonjour();
    afficher_bonjour();
    afficher_bonjour();
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — PROTOTYPE (DÉCLARATION)
     *
     * Le prototype informe le compilateur de l'existence
     * d'une fonction avant sa définition complète.
     *
     * Syntaxe : type_retour nom_fonction(type param1, type param2);
     *
     * Les prototypes se placent en haut du fichier,
     * avant main(). On les voit déclarés au-dessus.
     * ---------------------------------------------------------- */
    afficher_separateur("2. Prototype (declaration)");

    printf("Les prototypes sont declares en haut du fichier.\n");
    printf("Ils permettent au compilateur de connaitre :\n");
    printf("  - le nom de la fonction\n");
    printf("  - le type de valeur retournee\n");
    printf("  - les types des parametres\n");
    printf("Avant meme de lire sa definition complete.\n\n");


    /* ----------------------------------------------------------
     * PARTIE 3 — DÉFINITION D'UNE FONCTION
     *
     * La définition contient le corps de la fonction :
     * le code qui sera exécuté à chaque appel.
     *
     * Syntaxe :
     *   type_retour nom(type param1, type param2) {
     *       // code
     *       return valeur;   ← obligatoire si type != void
     *   }
     * ---------------------------------------------------------- */
    afficher_separateur("3. Definition et appel");

    /* Appel de la fonction additionner */
    int resultat = additionner(7, 5);
    printf("additionner(7, 5)     = %d\n", resultat);
    printf("additionner(100, 200) = %d\n", additionner(100, 200));
    printf("additionner(-3, 10)   = %d\n\n", additionner(-3, 10));


    /* ----------------------------------------------------------
     * PARTIE 4 — PARAMÈTRES ET VALEUR DE RETOUR
     *
     * Paramètres : les valeurs données à la fonction à l'appel.
     *              La fonction travaille sur des COPIES (passage par valeur).
     *
     * Valeur de retour : le résultat que la fonction renvoie avec return.
     *                    Le type doit correspondre au type déclaré.
     * ---------------------------------------------------------- */
    afficher_separateur("4. Parametres et valeur de retour");

    /* Fonction avec 3 paramètres et retour float */
    float moy = calculer_moyenne(12, 15, 9);
    printf("calculer_moyenne(12, 15, 9) = %.2f\n", moy);

    /* Fonction qui retourne un booléen (0 ou 1) */
    printf("est_pair(4)  = %d  (1=oui, 0=non)\n", est_pair(4));
    printf("est_pair(7)  = %d\n", est_pair(7));

    /* Fonction qui retourne le max de deux entiers */
    printf("maximum(8, 3) = %d\n", maximum(8, 3));
    printf("maximum(2, 9) = %d\n\n", maximum(2, 9));


    /* ----------------------------------------------------------
     * PARTIE 5 — VOID : FONCTION SANS VALEUR DE RETOUR
     *
     * Une fonction void effectue une action mais ne retourne rien.
     * Le mot-clé return est optionnel (on peut l'omettre).
     * On ne peut pas utiliser son résultat dans une expression.
     * ---------------------------------------------------------- */
    afficher_separateur("5. void (sans retour)");

    /* Ces fonctions effectuent une action sans retourner de valeur */
    afficher_bonjour();                        /* void : rien à récupérer */
    afficher_tableau((int[]){1,2,3,4,5}, 5);  /* void : affiche et c'est tout */
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — PASSAGE PAR VALEUR
     *
     * En C, les arguments sont COPIÉS dans les paramètres.
     * La fonction travaille sur sa propre copie locale.
     * Modifier le paramètre dans la fonction ne change PAS
     * la variable originale dans main().
     * ---------------------------------------------------------- */
    afficher_separateur("6. Passage par valeur");

    int x = 10;
    printf("Avant appel : x = %d\n", x);

    /* La fonction additionner reçoit une copie de x */
    /* Elle ne peut pas modifier x dans main */
    int somme = additionner(x, 5);
    printf("Apres appel : x = %d  (inchange !)\n", x);
    printf("Resultat    : %d\n\n", somme);


    /* ----------------------------------------------------------
     * PARTIE 7 — VARIABLES LOCALES À UNE FONCTION
     *
     * Les variables déclarées DANS une fonction n'existent que
     * pendant l'exécution de cette fonction.
     * Elles disparaissent dès que la fonction se termine.
     * Deux fonctions peuvent avoir des variables du même nom
     * sans conflit : elles sont indépendantes.
     * ---------------------------------------------------------- */
    afficher_separateur("7. Variables locales");

    printf("La variable 'resultat' dans additionner()\n");
    printf("n'existe que pendant l'execution de la fonction.\n");
    printf("Dans main(), 'resultat' est une variable differente.\n\n");

    int r1 = additionner(3, 4);   /* variable locale 'resultat' dans additionner */
    int r2 = additionner(10, 20); /* une nouvelle copie locale à chaque appel */
    printf("r1 = %d, r2 = %d  (deux appels independants)\n\n", r1, r2);


    /* ----------------------------------------------------------
     * PARTIE 8 — FONCTIONS AVEC TABLEAUX EN PARAMÈTRE
     *
     * Quand on passe un tableau à une fonction, on passe
     * son adresse (pas une copie). La fonction peut donc
     * MODIFIER le tableau original.
     * On passe toujours la taille en paramètre séparé,
     * car sizeof() ne fonctionne pas dans la fonction.
     * ---------------------------------------------------------- */
    afficher_separateur("8. Fonctions avec tableaux");

    int notes[] = {14, 8, 17, 11, 15};
    int taille  = sizeof(notes) / sizeof(notes[0]);

    printf("Tableau notes : ");
    afficher_tableau(notes, taille);

    int nb_voyelles = compter_voyelles("Programmation en C");
    printf("Voyelles dans \"Programmation en C\" : %d\n\n", nb_voyelles);


    /* ----------------------------------------------------------
     * PARTIE 9 — APPELS MULTIPLES ET RÉUTILISABILITÉ
     *
     * Le vrai intérêt des fonctions : écrire le code UNE fois
     * et l'appeler autant de fois qu'on veut, avec des arguments
     * différents à chaque fois.
     * ---------------------------------------------------------- */
    afficher_separateur("9. Reutilisabilite");

    /* La même fonction afficher_table pour plusieurs valeurs */
    afficher_table(3);
    afficher_table(7);
    printf("\n");

    /* Combiner plusieurs fonctions */
    int tab[] = {4, 11, 7, 2, 9, 6};
    int nb = sizeof(tab) / sizeof(tab[0]);

    printf("Tableau : ");
    afficher_tableau(tab, nb);

    int max_val = tab[0];
    for (int i = 1; i < nb; i++) {
        max_val = maximum(max_val, tab[i]);
    }
    printf("Maximum : %d\n", max_val);

    int pairs = 0;
    for (int i = 0; i < nb; i++) {
        if (est_pair(tab[i])) pairs++;
    }
    printf("Nombres pairs : %d/%d\n\n", pairs, nb);


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  Prototype  : type nom(type p1, type p2);\n");
    printf("  Definition : type nom(type p1) { return ...; }\n");
    printf("  Appel      : resultat = nom(arg1, arg2);\n");
    printf("  void       : pas de valeur de retour\n");
    printf("  return     : renvoie une valeur et quitte\n");
    printf("  Par valeur : la fonction recoit une COPIE\n");
    printf("  Locale     : variable morte apres la fonction\n");
    printf("  Tableau    : passage par adresse (modifiable)\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS DES FONCTIONS
 * (Corps complet de chaque fonction)
 * ============================================================ */

/* ------ Fonction sans paramètre, sans retour ------ */
void afficher_bonjour() {
    printf("  Bonjour depuis une fonction !\n");
}

/* ------ Séparateur visuel ------ */
void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}

/* ------ Additionner deux entiers ------ */
int additionner(int a, int b) {
    int resultat = a + b;   /* variable LOCALE à cette fonction */
    return resultat;        /* renvoie la valeur à l'appelant */
}

/* ------ Moyenne de trois entiers ------ */
float calculer_moyenne(int a, int b, int c) {
    return (float)(a + b + c) / 3;
}

/* ------ Tester si un nombre est pair ------ */
int est_pair(int n) {
    if (n % 2 == 0) {
        return 1;   /* vrai */
    } else {
        return 0;   /* faux */
    }
    /* Version courte : return (n % 2 == 0); */
}

/* ------ Retourner le plus grand de deux entiers ------ */
int maximum(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/* ------ Afficher un tableau d'entiers ------ */
void afficher_tableau(int tab[], int taille) {
    printf("[");
    for (int i = 0; i < taille; i++) {
        printf("%d", tab[i]);
        if (i < taille - 1) printf(", ");
    }
    printf("]\n");
}

/* ------ Compter les voyelles dans une chaîne ------ */
int compter_voyelles(char chaine[]) {
    int compte = 0;
    char voyelles[] = "aeiouAEIOU";

    for (int i = 0; chaine[i] != '\0'; i++) {
        for (int j = 0; voyelles[j] != '\0'; j++) {
            if (chaine[i] == voyelles[j]) {
                compte++;
                break;
            }
        }
    }
    return compte;
}

/* ------ Afficher la table de multiplication d'un nombre ------ */
void afficher_table(int n) {
    printf("Table de %d : ", n);
    for (int i = 1; i <= 5; i++) {
        printf("%d ", n * i);
    }
    printf("\n");
}