/*
 * ============================================================
 *  FICHIER  : entrees_sorties.c
 *  SUJET    : Entrées / Sorties (I/O) en C
 *  NIVEAU   : Débutant — Leçon 3
 *  COMPILE  : gcc entrees_sorties.c -o entrees_sorties
 *  EXECUTE  : ./entrees_sorties
 * ============================================================
 */

#include <stdio.h>   /* printf, scanf, getchar, putchar, fgets */

int main() {

    printf("==============================================\n");
    printf("  LECON 3 : Entrees / Sorties (I/O)\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — printf() : AFFICHER DU TEXTE
     *
     * printf() est la fonction d'affichage principale en C.
     * Elle affiche du texte dans le terminal.
     * On peut y insérer des variables grâce aux "spécificateurs
     * de format" qui commencent par %.
     * ---------------------------------------------------------- */
    printf("--- 1. printf() : afficher du texte ---\n");

    /* Texte simple */
    printf("Bonjour tout le monde !\n");

    /* Avec des variables */
    int    age    = 22;
    float  taille = 1.78f;
    char   initiale = 'L';
    char   prenom[] = "Lucas";

    printf("Prenom   : %s\n", prenom);    /* %s = chaîne de caractères */
    printf("Initiale : %c\n", initiale);  /* %c = caractère            */
    printf("Age      : %d\n", age);       /* %d = entier (int)         */
    printf("Taille   : %f\n\n", taille);  /* %f = flottant             */


    /* ----------------------------------------------------------
     * PARTIE 2 — SPÉCIFICATEURS DE FORMAT
     *
     * Chaque type de variable a son propre spécificateur.
     * Les connaître est indispensable pour afficher correctement.
     * ---------------------------------------------------------- */
    printf("--- 2. Specificateurs de format ---\n");

    int     nb_entier  = 42;
    long    nb_long    = 1234567890L;
    unsigned int u     = 300;
    float   nb_float   = 3.14f;
    double  nb_double  = 3.141592653589;

    printf("%%d  → int          : %d\n",   nb_entier);
    printf("%%ld → long         : %ld\n",  nb_long);
    printf("%%u  → unsigned int : %u\n",   u);
    printf("%%f  → float        : %f\n",   nb_float);
    printf("%%lf → double       : %lf\n",  nb_double);
    printf("%%c  → char         : %c\n",   'A');
    printf("%%s  → string       : %s\n",   "bonjour");
    printf("%%x  → hexadecimal  : %x\n",   nb_entier);  /* → 2a  */
    printf("%%o  → octal        : %o\n",   nb_entier);  /* → 52  */
    printf("%%%%  → affiche %%    : %%\n\n");


    /* ----------------------------------------------------------
     * PARTIE 3 — OPTIONS DE FORMATAGE
     *
     * On peut contrôler la largeur, la précision et l'alignement
     * en ajoutant des options entre % et la lettre du format.
     *
     * Syntaxe : %[drapeaux][largeur][.precision]type
     * ---------------------------------------------------------- */
    printf("--- 3. Options de formatage ---\n");

    /* Largeur minimale d'affichage */
    printf("[%10d]   ← largeur 10, aligne a droite\n",  42);
    printf("[%-10d]   ← largeur 10, aligne a gauche\n", 42);
    printf("[%010d]   ← largeur 10, rempli de zeros\n", 42);

    printf("\n");

    /* Précision sur les flottants */
    float pi = 3.14159f;
    printf("[%f]    ← par defaut (6 decimales)\n",   pi);
    printf("[%.0f]    ← 0 decimale\n",               pi);
    printf("[%.2f]    ← 2 decimales\n",               pi);
    printf("[%.5f]    ← 5 decimales\n",               pi);
    printf("[%10.2f]  ← largeur 10, 2 decimales\n",  pi);

    printf("\n");

    /* Largeur sur les chaînes */
    printf("[%15s]   ← largeur 15, aligne a droite\n", "bonjour");
    printf("[%-15s]   ← largeur 15, aligne a gauche\n", "bonjour");
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — CARACTÈRES D'ÉCHAPPEMENT
     *
     * Ce sont des séquences spéciales qui commencent par \
     * Elles représentent des caractères non imprimables ou
     * des caractères qui ont un sens spécial en C.
     * ---------------------------------------------------------- */
    printf("--- 4. Caracteres d'echappement ---\n");

    printf("\\n → nouvelle ligne   :\n  (on est ici)\n");
    printf("\\t → tabulation      :\tici\n");
    printf("\\\\ → antislash       : \\\n");
    printf("\\\" → guillemet       : \"\n");
    printf("\\' → apostrophe      : \'\n");
    printf("\\0 → caractere nul   : (fin de chaine, invisible)\n");

    /* Exemple concret : tableau aligné avec \t */
    printf("\nTableau aligne avec tabulations :\n");
    printf("Nom\t\tAge\tVille\n");
    printf("Alice\t\t25\tParis\n");
    printf("Bob\t\t30\tLyon\n");
    printf("Charlie\t\t22\tNice\n\n");


    /* ----------------------------------------------------------
     * PARTIE 5 — scanf() : LIRE UNE ENTRÉE CLAVIER
     *
     * scanf() lit ce que l'utilisateur tape au clavier.
     * IMPORTANT : il faut passer l'ADRESSE de la variable
     * avec l'opérateur & (sauf pour les tableaux/chaînes).
     * ---------------------------------------------------------- */
    printf("--- 5. scanf() : lire une entree ---\n");

    int    annee;
    float  note;
    char   nom[50];

    /* Lecture d'un entier */
    printf("Entrez votre annee de naissance : ");
    scanf("%d", &annee);           /* & obligatoire ! */
    printf("Vous avez saisi : %d\n", annee);

    /* Lecture d'un flottant */
    printf("Entrez votre note sur 20 : ");
    scanf("%f", &note);
    printf("Note saisie : %.1f/20\n", note);

    /* Lecture d'un mot (sans espace) */
    printf("Entrez votre nom : ");
    scanf("%49s", nom);            /* Pas de & pour un tableau ! */
                                   /* 49 = limite pour éviter le dépassement */
    printf("Nom saisi : %s\n\n", nom);


    /* ----------------------------------------------------------
     * PARTIE 6 — fgets() : LIRE UNE LIGNE ENTIÈRE
     *
     * scanf("%s") s'arrête au premier espace.
     * Pour lire une phrase entière (avec espaces), on utilise
     * fgets() qui lit jusqu'à la fin de ligne.
     * ---------------------------------------------------------- */
    printf("--- 6. fgets() : lire une ligne entiere ---\n");

    char phrase[100];

    /* Vider le buffer clavier (résidu du dernier scanf) */
    while (getchar() != '\n');

    printf("Entrez une phrase complete : ");
    fgets(phrase, sizeof(phrase), stdin);
    /* fgets garde le '\n' final dans la chaîne.
     * On peut l'enlever ainsi : */
    int i = 0;
    while (phrase[i] != '\n' && phrase[i] != '\0') i++;
    phrase[i] = '\0';   /* Remplace \n par \0 */

    printf("Phrase saisie : \"%s\"\n\n", phrase);


    /* ----------------------------------------------------------
     * PARTIE 7 — getchar() ET putchar()
     *
     * getchar() lit UN seul caractère depuis le clavier.
     * putchar() affiche UN seul caractère dans le terminal.
     * Fonctions simples et légères, utiles pour traiter
     * des caractères un par un.
     * ---------------------------------------------------------- */
    printf("--- 7. getchar() et putchar() ---\n");

    char car;

    /* Vider le buffer */
    while (getchar() != '\n');

    printf("Entrez un caractere : ");
    car = getchar();

    printf("Caractere saisi    : ");
    putchar(car);
    printf("\n");

    printf("Code ASCII de '%c' : %d\n", car, car);

    /* putchar pour afficher une chaîne caractère par caractère */
    printf("Affichage lettre par lettre : ");
    char mot[] = "Bonjour";
    int j = 0;
    while (mot[j] != '\0') {
        putchar(mot[j]);
        putchar('-');
        j++;
    }
    printf("\n\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    printf("==============================================\n");
    printf("  RECAPITULATIF I/O\n");
    printf("==============================================\n");
    printf("  printf()   → afficher du texte\n");
    printf("  scanf()    → lire un mot/nombre\n");
    printf("  fgets()    → lire une ligne entiere\n");
    printf("  getchar()  → lire un caractere\n");
    printf("  putchar()  → afficher un caractere\n");
    printf("\n  Formats : %%d %%ld %%u %%f %%lf %%c %%s %%x %%o\n");
    printf("  Options : largeur  .precision  - 0\n");
    printf("  Echap.  : \\n \\t \\\\ \\\" \\'\n");
    printf("\n");

    return 0;
}