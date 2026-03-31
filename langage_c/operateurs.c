/*
 * ============================================================
 *  FICHIER  : operateurs.c
 *  SUJET    : Les opérateurs en C
 *  NIVEAU   : Débutant — Leçon 2
 *  COMPILE  : gcc operateurs.c -o operateurs
 *  EXECUTE  : ./operateurs
 * ============================================================
 */

#include <stdio.h>

int main() {

    printf("==============================================\n");
    printf("  LECON 2 : Les operateurs\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — OPÉRATEURS ARITHMÉTIQUES
     *
     * Ce sont les opérations mathématiques de base.
     * Ils s'appliquent sur des nombres (int, float, double).
     * ---------------------------------------------------------- */
    printf("--- 1. Operateurs arithmetiques ---\n");

    int a = 10;
    int b = 3;

    printf("a = %d, b = %d\n\n", a, b);

    printf("a + b = %d\n", a + b);   /* Addition       → 13 */
    printf("a - b = %d\n", a - b);   /* Soustraction   →  7 */
    printf("a * b = %d\n", a * b);   /* Multiplication → 30 */
    printf("a / b = %d\n", a / b);   /* Division       →  3  (entière !) */
    printf("a %% b = %d\n", a % b);  /* Modulo (reste) →  1 */

    /* ATTENTION : la division entre deux entiers est entière.
     * 10 / 3 = 3 et non 3.33
     * Pour obtenir un résultat décimal, au moins un des deux
     * nombres doit être un flottant → on "caste" avec (float) */
    float division_reelle = (float)a / b;
    printf("(float)a / b = %.2f\n", division_reelle); /* → 3.33 */

    /* Le modulo % donne le RESTE de la division entière.
     * Très utile pour savoir si un nombre est pair ou impair. */
    printf("\n10 %% 2 = %d  (pair : reste 0)\n",  10 % 2);
    printf("11 %% 2 = %d  (impair : reste 1)\n\n", 11 % 2);


    /* ----------------------------------------------------------
     * PARTIE 2 — DIVISION ENTIÈRE VS DIVISION RÉELLE
     *
     * C'est un piège classique pour les débutants.
     * Le type des opérandes détermine le type du résultat.
     * ---------------------------------------------------------- */
    printf("--- 2. Division entiere vs reelle ---\n");

    int   x = 7, y = 2;
    float fx = 7.0f, fy = 2.0f;

    printf("7 / 2          = %d    (int / int = int)\n",       x / y);
    printf("7.0 / 2.0      = %.1f  (float / float = float)\n", fx / fy);
    printf("(float)7 / 2   = %.1f  (cast → float)\n",   (float)x / y);
    printf("7 / (float)2   = %.1f  (cast → float)\n",   x / (float)y);
    printf("7.0f / 2       = %.1f  (un float suffit)\n\n", 7.0f / y);


    /* ----------------------------------------------------------
     * PARTIE 3 — OPÉRATEURS DE COMPARAISON
     *
     * Ils comparent deux valeurs et retournent :
     *   1 si la comparaison est VRAIE
     *   0 si la comparaison est FAUSSE
     * ---------------------------------------------------------- */
    printf("--- 3. Operateurs de comparaison ---\n");

    int p = 10, q = 3;
    printf("p = %d, q = %d\n\n", p, q);

    printf("p == q  : %d  (egal a)\n",            p == q);
    printf("p != q  : %d  (different de)\n",      p != q);
    printf("p >  q  : %d  (superieur a)\n",       p >  q);
    printf("p <  q  : %d  (inferieur a)\n",       p <  q);
    printf("p >= q  : %d  (superieur ou egal)\n", p >= q);
    printf("p <= q  : %d  (inferieur ou egal)\n\n", p <= q);

    /* PIÈGE CLASSIQUE : = vs ==
     * = affecte une valeur (ex: age = 20)
     * == compare deux valeurs (ex: age == 20)
     * Utiliser = dans un if est une erreur très courante ! */
    printf("PIEGE : age = 20  →  affectation\n");
    printf("        age == 20 →  comparaison\n\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — OPÉRATEURS LOGIQUES
     *
     * Ils combinent plusieurs conditions.
     * Retournent 1 (vrai) ou 0 (faux).
     * ---------------------------------------------------------- */
    printf("--- 4. Operateurs logiques ---\n");

    int age    = 20;
    int permis = 1;   /* 1 = a le permis, 0 = n'a pas le permis */

    printf("age = %d, permis = %d\n\n", age, permis);

    /* && (ET) : vrai si LES DEUX conditions sont vraies */
    printf("age>=18 && permis : %d  (ET  → les deux doivent etre vrais)\n",
           age >= 18 && permis);

    /* || (OU) : vrai si AU MOINS UNE condition est vraie */
    printf("age>=18 || permis : %d  (OU  → au moins un vrai suffit)\n",
           age >= 18 || permis);

    /* ! (NON) : inverse la valeur logique */
    printf("!permis           : %d  (NON → inverse 1 en 0, 0 en 1)\n\n",
           !permis);

    /* Exemples concrets */
    int heure = 14;
    int weekend = 0;

    printf("heure = %d, weekend = %d\n", heure, weekend);
    printf("Est en pause dejeuner (12-14h) : %d\n",
           heure >= 12 && heure <= 14);
    printf("Peut faire la grasse matinee   : %d\n",
           weekend == 1 || heure < 7);
    printf("N'est pas le weekend           : %d\n\n", !weekend);


    /* ----------------------------------------------------------
     * PARTIE 5 — OPÉRATEURS D'AFFECTATION COMPOSÉE
     *
     * Ce sont des raccourcis d'écriture très courants.
     * x += 5  est exactement identique à  x = x + 5
     * ---------------------------------------------------------- */
    printf("--- 5. Affectation composee ---\n");

    int n = 20;
    printf("n = %d  (valeur de depart)\n", n);

    n += 5;  printf("n += 5  →  n = %d  (n = n + 5)\n", n);
    n -= 3;  printf("n -= 3  →  n = %d  (n = n - 3)\n", n);
    n *= 2;  printf("n *= 2  →  n = %d  (n = n * 2)\n", n);
    n /= 6;  printf("n /= 6  →  n = %d  (n = n / 6)\n", n);
    n %= 3;  printf("n %%= 3  →  n = %d  (n = n %% 3)\n\n", n);


    /* ----------------------------------------------------------
     * PARTIE 6 — INCRÉMENTATION ET DÉCRÉMENTATION
     *
     * ++ ajoute 1, -- soustrait 1.
     * La position de l'opérateur change QUAND l'opération se fait :
     *
     *   n++  →  post : utilise n PUIS ajoute 1
     *   ++n  →  pré  : ajoute 1 PUIS utilise n
     * ---------------------------------------------------------- */
    printf("--- 6. Incrementation et decrementation ---\n");

    int c = 5;
    printf("c = %d  (valeur de depart)\n\n", c);

    /* Post-incrément : on lit d'abord, on incrémente ensuite */
    printf("printf(c++) affiche : %d  puis c devient %d\n", c++, c);

    /* Pré-incrément : on incrémente d'abord, on lit ensuite */
    printf("printf(++c) affiche : %d  (c vaut deja %d)\n", ++c, c);

    /* Décrément */
    printf("printf(c--) affiche : %d  puis c devient %d\n", c--, c);
    printf("printf(--c) affiche : %d  (c vaut deja %d)\n\n", --c, c);

    /* Cas le plus courant : utilisation dans une boucle for.
     * Là, la différence pré/post ne compte pas. */
    printf("Utilisation classique dans une boucle :\n");
    int i;
    for (i = 0; i < 5; i++) {   /* i++ ou ++i : même résultat ici */
        printf("%d ", i);
    }
    printf("\n\n");


    /* ----------------------------------------------------------
     * PARTIE 7 — OPÉRATEUR TERNAIRE
     *
     * C'est un if/else condensé sur une seule ligne.
     * Syntaxe : condition ? valeur_si_vrai : valeur_si_faux
     *
     * Utile pour des affectations simples.
     * À ne pas abuser pour ne pas perdre en lisibilité.
     * ---------------------------------------------------------- */
    printf("--- 7. Operateur ternaire ---\n");

    int score = 14;

    /* Équivalent à :
     * if (score >= 10) resultat = "Admis" else resultat = "Recale" */
    char *resultat = (score >= 10) ? "Admis" : "Recale";
    printf("Score %d : %s\n", score, resultat);

    /* Trouver le maximum de deux nombres */
    int num1 = 42, num2 = 17;
    int maximum = (num1 > num2) ? num1 : num2;
    printf("max(%d, %d) = %d\n", num1, num2, maximum);

    /* Afficher pair ou impair */
    int nombre = 7;
    printf("%d est %s\n\n", nombre, (nombre % 2 == 0) ? "pair" : "impair");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    printf("==============================================\n");
    printf("  RECAPITULATIF DES OPERATEURS\n");
    printf("==============================================\n");
    printf("  Arithm.   : +  -  *  /  %%\n");
    printf("  Compar.   : == != >  <  >= <=\n");
    printf("  Logiques  : && || !\n");
    printf("  Affect.   : += -= *= /= %%=\n");
    printf("  Incr/Decr : ++  --  (pre et post)\n");
    printf("  Ternaire  : condition ? vrai : faux\n");
    printf("\n");

    return 0;
}