/*
 * ============================================================
 *  FICHIER  : conditions.c
 *  SUJET    : Structures conditionnelles en C
 *  NIVEAU   : Débutant — Leçon 4
 *  COMPILE  : gcc conditions.c -o conditions
 *  EXECUTE  : ./conditions
 * ============================================================
 */

#include <stdio.h>

int main() {

    printf("==============================================\n");
    printf("  LECON 4 : Structures conditionnelles\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — if SIMPLE
     *
     * Le if exécute un bloc de code UNIQUEMENT si
     * la condition entre parenthèses est vraie (≠ 0).
     *
     * Syntaxe :
     *   if (condition) {
     *       // code exécuté si condition est vraie
     *   }
     * ---------------------------------------------------------- */
    printf("--- 1. if simple ---\n");

    int temperature = 35;
    printf("Temperature : %d degres\n", temperature);

    if (temperature > 30) {
        printf("Il fait chaud !\n");
    }

    if (temperature > 40) {
        printf("Canicule !\n");   /* Non affiché : 35 n'est pas > 40 */
    }

    /* Un if sans accolades fonctionne mais ne couvre
     * qu'UNE seule instruction. Toujours préférer les accolades. */
    if (temperature > 0)
        printf("Il ne gele pas.\n");   /* Une seule ligne, ok */

    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — if / else
     *
     * else est le "sinon" : il s'exécute quand la condition
     * du if est fausse.
     *
     * Syntaxe :
     *   if (condition) {
     *       // si vrai
     *   } else {
     *       // si faux
     *   }
     * ---------------------------------------------------------- */
    printf("--- 2. if / else ---\n");

    int heure = 14;
    printf("Heure : %dh\n", heure);

    if (heure < 12) {
        printf("Bonjour (matin)\n");
    } else {
        printf("Bonjour (apres-midi ou soir)\n");
    }

    /* Exemple avec un booléen simulé */
    int est_connecte = 0;   /* 0 = faux, 1 = vrai */

    if (est_connecte) {
        printf("Bienvenue, utilisateur !\n");
    } else {
        printf("Veuillez vous connecter.\n");
    }

    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 3 — if / else if / else
     *
     * Permet de tester PLUSIEURS conditions à la suite.
     * Les conditions sont évaluées dans l'ordre : dès qu'une
     * est vraie, son bloc s'exécute et les autres sont ignorées.
     *
     * Syntaxe :
     *   if (cond1) { ... }
     *   else if (cond2) { ... }
     *   else if (cond3) { ... }
     *   else { ... }
     * ---------------------------------------------------------- */
    printf("--- 3. if / else if / else ---\n");

    int note = 14;
    printf("Note : %d/20\n", note);

    if (note >= 16) {
        printf("Mention : Tres Bien\n");
    } else if (note >= 14) {
        printf("Mention : Bien\n");          /* Affiché : 14 >= 14 */
    } else if (note >= 12) {
        printf("Mention : Assez Bien\n");
    } else if (note >= 10) {
        printf("Mention : Admis\n");
    } else {
        printf("Mention : Recale\n");
    }

    /* Autre exemple : tranche d'âge */
    int age = 17;
    printf("\nAge : %d ans\n", age);

    if (age < 0) {
        printf("Age invalide\n");
    } else if (age < 12) {
        printf("Enfant\n");
    } else if (age < 18) {
        printf("Adolescent\n");              /* Affiché : 17 < 18 */
    } else if (age < 65) {
        printf("Adulte\n");
    } else {
        printf("Senior\n");
    }

    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — CONDITIONS IMBRIQUÉES
     *
     * On peut mettre un if à l'intérieur d'un autre if.
     * Utile quand plusieurs critères doivent être vérifiés
     * de façon hiérarchique.
     * Attention : trop d'imbrications rend le code illisible.
     * ---------------------------------------------------------- */
    printf("--- 4. Conditions imbriquees ---\n");

    int solde       = 500;
    int carte_valide = 1;    /* 1 = oui */
    int montant     = 200;

    printf("Solde : %d€, Montant retire : %d€\n", solde, montant);

    if (carte_valide) {
        printf("Carte valide.\n");
        if (montant <= solde) {
            printf("Retrait autorise : %d euros.\n", montant);
            solde -= montant;
            printf("Nouveau solde : %d euros.\n", solde);
        } else {
            printf("Solde insuffisant.\n");
        }
    } else {
        printf("Carte invalide ou expiree.\n");
    }

    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 5 — switch / case
     *
     * Le switch teste la valeur d'UNE variable entière (ou char)
     * et exécute le cas correspondant.
     * Plus lisible qu'une longue chaîne de if/else if
     * quand on compare une variable à plusieurs valeurs précises.
     *
     * Syntaxe :
     *   switch (variable) {
     *       case valeur1: ... break;
     *       case valeur2: ... break;
     *       default: ...
     *   }
     * ---------------------------------------------------------- */
    printf("--- 5. switch / case ---\n");

    int jour = 3;
    printf("Jour numero : %d\n", jour);

    switch (jour) {
        case 1:
            printf("Lundi\n");
            break;
        case 2:
            printf("Mardi\n");
            break;
        case 3:
            printf("Mercredi\n");    /* Affiché */
            break;
        case 4:
            printf("Jeudi\n");
            break;
        case 5:
            printf("Vendredi\n");
            break;
        case 6:
            printf("Samedi\n");
            break;
        case 7:
            printf("Dimanche\n");
            break;
        default:
            printf("Jour invalide (1-7)\n");
    }

    /* switch avec des caractères */
    char grade = 'B';
    printf("\nGrade : %c\n", grade);

    switch (grade) {
        case 'A':
            printf("Excellent !\n");
            break;
        case 'B':
            printf("Bien.\n");        /* Affiché */
            break;
        case 'C':
            printf("Passable.\n");
            break;
        default:
            printf("Grade inconnu.\n");
    }

    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — GROUPEMENT DE CAS DANS UN switch
     *
     * Plusieurs case peuvent partager le même bloc de code.
     * Il suffit de les mettre à la suite sans break entre eux.
     * ---------------------------------------------------------- */
    printf("--- 6. Groupement de cas ---\n");

    int num_jour = 6;
    printf("Jour %d : ", num_jour);

    switch (num_jour) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("Jour de semaine\n");
            break;
        case 6:
        case 7:
            printf("Week-end !\n");    /* Affiché : 6 et 7 → même bloc */
            break;
        default:
            printf("Numero invalide\n");
    }

    /* Autre exemple : saisons */
    int mois = 4;
    printf("Mois %d : ", mois);

    switch (mois) {
        case 12: case 1: case 2:
            printf("Hiver\n");
            break;
        case 3: case 4: case 5:
            printf("Printemps\n");    /* Affiché : mois 4 */
            break;
        case 6: case 7: case 8:
            printf("Ete\n");
            break;
        case 9: case 10: case 11:
            printf("Automne\n");
            break;
        default:
            printf("Mois invalide\n");
    }

    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 7 — RÔLE DU break ET DU default
     *
     * break  : stoppe le switch immédiatement après le cas.
     *          Sans break, l'exécution "tombe" dans le cas
     *          suivant (comportement appelé "fall-through").
     *
     * default : cas par défaut, exécuté si aucun case ne
     *           correspond. Équivalent du else pour le switch.
     * ---------------------------------------------------------- */
    printf("--- 7. Role de break et default ---\n");

    /* Démonstration du fall-through (sans break) */
    int val = 2;
    printf("val = %d, switch SANS break :\n", val);

    switch (val) {
        case 1:
            printf("  cas 1\n");
        case 2:
            printf("  cas 2\n");    /* Affiché */
        case 3:
            printf("  cas 3\n");    /* Affiché aussi ! fall-through */
        default:
            printf("  default\n");  /* Affiché aussi ! */
    }

    printf("\nval = %d, switch AVEC break :\n", val);

    switch (val) {
        case 1:
            printf("  cas 1\n");
            break;
        case 2:
            printf("  cas 2\n");    /* Affiché */
            break;                  /* Stoppe ici */
        case 3:
            printf("  cas 3\n");
            break;
        default:
            printf("  default\n");
    }

    /* default quand aucun cas ne correspond */
    int code = 99;
    printf("\ncode = %d :\n", code);

    switch (code) {
        case 1:  printf("  Code OK\n");       break;
        case 2:  printf("  Code WARN\n");     break;
        case 3:  printf("  Code ERROR\n");    break;
        default: printf("  Code inconnu\n");  /* Affiché : 99 ≠ 1,2,3 */
    }

    printf("\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    printf("==============================================\n");
    printf("  RECAPITULATIF\n");
    printf("==============================================\n");
    printf("  if (cond) { }               → si\n");
    printf("  if { } else { }             → si / sinon\n");
    printf("  if { } else if { } else { } → si / sinon si / sinon\n");
    printf("  if imbriques                → conditions hierarchiques\n");
    printf("  switch / case / break       → valeur precise\n");
    printf("  groupement de case          → plusieurs valeurs, meme bloc\n");
    printf("  break  → sort du switch\n");
    printf("  default → cas par defaut\n");
    printf("\n");

    return 0;
}