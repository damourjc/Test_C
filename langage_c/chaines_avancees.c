/*
 * ============================================================
 *  FICHIER  : chaines_avancees.c
 *  SUJET    : Les chaînes avancées en C
 *  NIVEAU   : Intermédiaire — Leçon 6
 *  COMPILE  : gcc -Wall -Wextra chaines_avancees.c -o chaines_av
 *  EXECUTE  : ./chaines_av
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   /* strlen, strcpy, strncpy, strcat, strncat,    */
                      /* strcmp, strncmp, strchr, strstr, strtok, ...  */
#include <ctype.h>    /* toupper, tolower, isalpha, isdigit, isspace   */

/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 6 : Chaines avancees\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — sprintf() ET sscanf() : CHAÎNES COMME I/O
     *
     * sprintf() écrit dans une chaîne au lieu de stdout.
     * sscanf() lit depuis une chaîne au lieu de stdin.
     * Très utiles pour formater des données en mémoire
     * avant de les afficher, envoyer, ou analyser.
     *
     * sprintf(buffer, format, ...) → renvoie nb de chars écrits
     * sscanf(source, format, ...) → renvoie nb d'éléments lus
     * ---------------------------------------------------------- */
    afficher_separateur("1. sprintf() et sscanf()");

    /* sprintf : construire une chaîne formatée */
    char message[100];
    int  age    = 28;
    char prenom[] = "Lucas";
    float note  = 15.75f;

    sprintf(message, "Etudiant : %s, age %d, note %.2f", prenom, age, note);
    printf("sprintf → \"%s\"\n", message);

    /* Construire un nom de fichier dynamiquement */
    char nom_fichier[50];
    int  numero = 42;
    sprintf(nom_fichier, "rapport_%03d.txt", numero);
    printf("Nom fichier → \"%s\"\n", nom_fichier);

    /* Convertir un nombre en chaîne */
    char nb_str[20];
    sprintf(nb_str, "%d", 12345);
    printf("Nombre → chaine : \"%s\" (longueur %lu)\n\n",
           nb_str, strlen(nb_str));

    /* sscanf : extraire des données depuis une chaîne */
    char ligne[] = "Alice 25 18.5";
    char nom[50];
    int  a;
    float n;

    int lus = sscanf(ligne, "%49s %d %f", nom, &a, &n);
    printf("sscanf depuis \"%s\" :\n", ligne);
    printf("  → nom=\"%s\", age=%d, note=%.1f (%d element(s) lus)\n\n",
           nom, a, n, lus);

    /* Analyser une date au format JJ/MM/AAAA */
    char date[] = "15/06/2024";
    int  jour, mois, annee;
    sscanf(date, "%d/%d/%d", &jour, &mois, &annee);
    printf("sscanf date \"%s\" → j=%d m=%d a=%d\n\n",
           date, jour, mois, annee);


    /* ----------------------------------------------------------
     * PARTIE 2 — strncpy(), strncat(), strncmp()
     *            VERSIONS SÉCURISÉES AVEC LIMITE DE TAILLE
     *
     * strcpy, strcat, strcmp n'ont aucune limite de taille.
     * Si la source est trop grande → dépassement de tampon !
     *
     * Les versions avec 'n' prennent un paramètre supplémentaire
     * qui limite le nombre de caractères traités.
     *
     * strncpy(dest, src, n) → copie max n chars (ATTENTION : peut
     *                          ne pas ajouter '\0' !)
     * strncat(dest, src, n) → concatène max n chars de src
     * strncmp(s1, s2, n)    → compare les n premiers chars
     * ---------------------------------------------------------- */
    afficher_separateur("2. strncpy / strncat / strncmp");

    char dest[20];
    char source[] = "Programmation en C";

    /* strncpy : copie au plus n caractères */
    strncpy(dest, source, sizeof(dest) - 1);
    dest[sizeof(dest) - 1] = '\0';   /* TOUJOURS forcer le terminateur ! */
    printf("strncpy(%zu chars) : \"%s\"\n", sizeof(dest)-1, dest);

    /* Copier seulement les premiers mots */
    char debut[15];
    strncpy(debut, source, 13);
    debut[13] = '\0';   /* Forcer '\0' */
    printf("strncpy(13 chars)  : \"%s\"\n\n", debut);

    /* strncat : concatène au plus n chars */
    char base[30] = "Bonjour";
    char suite[]  = " tout le monde !";
    strncat(base, suite, sizeof(base) - strlen(base) - 1);
    printf("strncat : \"%s\"\n\n", base);

    /* strncmp : compare les n premiers caractères */
    char s1[] = "Bonjour tout le monde";
    char s2[] = "Bonjour a tous";
    char s3[] = "Au revoir";

    printf("strncmp(\"%s\", \"%s\", 7) = %d  (premiers mots egaux)\n",
           s1, s2, strncmp(s1, s2, 7));
    printf("strncmp(\"%s\", \"%s\", 7) = %d  (differents)\n\n",
           s1, s3, strncmp(s1, s3, 7));


    /* ----------------------------------------------------------
     * PARTIE 3 — strchr() ET strstr() : RECHERCHE DANS UNE CHAÎNE
     *
     * strchr(s, c)   → cherche la PREMIÈRE occurrence du char c
     *                  dans la chaîne s.
     *                  Retourne un pointeur sur le char trouvé,
     *                  ou NULL si absent.
     *
     * strstr(s, sub) → cherche la PREMIÈRE occurrence de la
     *                  sous-chaîne 'sub' dans la chaîne s.
     *                  Retourne un pointeur sur le début de la
     *                  sous-chaîne, ou NULL si absente.
     * ---------------------------------------------------------- */
    afficher_separateur("3. strchr() et strstr()");

    char texte[] = "Bonjour le monde, bonjour C !";

    /* strchr : chercher un caractère */
    char *pos = strchr(texte, 'o');
    if (pos != NULL) {
        printf("strchr 'o' : trouve a l'index %ld → \"%s\"\n",
               pos - texte, pos);
    }

    /* Chercher depuis une position donnée (avancer le pointeur) */
    char *pos2 = strchr(pos + 1, 'o');
    if (pos2 != NULL) {
        printf("strchr 'o' (2e) : index %ld → \"%s\"\n",
               pos2 - texte, pos2);
    }

    /* Compter les occurrences d'un caractère */
    int count = 0;
    char *p = texte;
    while ((p = strchr(p, 'o')) != NULL) {
        count++;
        p++;   /* avancer pour ne pas boucler à l'infini */
    }
    printf("Nombre de 'o' dans la chaine : %d\n\n", count);

    /* strstr : chercher une sous-chaîne */
    char *sub = strstr(texte, "monde");
    if (sub != NULL) {
        printf("strstr \"monde\" : index %ld → \"%s\"\n",
               sub - texte, sub);
    }

    sub = strstr(texte, "bonjour");
    if (sub != NULL) {
        printf("strstr \"bonjour\" : index %ld → \"%s\"\n",
               sub - texte, sub);
    }

    sub = strstr(texte, "python");
    printf("strstr \"python\" : %s\n\n",
           sub == NULL ? "NULL (non trouve)" : sub);


    /* ----------------------------------------------------------
     * PARTIE 4 — strtok() : DÉCOUPER UNE CHAÎNE
     *
     * strtok() divise une chaîne en "tokens" (morceaux)
     * selon un ou plusieurs délimiteurs.
     *
     * ATTENTION : strtok() MODIFIE la chaîne originale
     *             en remplaçant les délimiteurs par '\0'.
     *             Ne jamais utiliser sur une chaîne constante !
     *
     * Premier appel : strtok(chaine, delimiteurs)
     * Appels suivants : strtok(NULL, delimiteurs)
     *                   (NULL = continuer sur la même chaîne)
     * ---------------------------------------------------------- */
    afficher_separateur("4. strtok() : decouper une chaine");

    /* Découper par espaces */
    char phrase[] = "Alice Bob Charlie Diana Eva";
    printf("Chaine : \"%s\"\n", phrase);
    printf("Tokens (delimiteur espace) :\n");

    char *token = strtok(phrase, " ");
    int   idx   = 0;
    while (token != NULL) {
        printf("  [%d] \"%s\"\n", idx++, token);
        token = strtok(NULL, " ");   /* NULL = continuer */
    }
    printf("\n");

    /* Découper un CSV (plusieurs délimiteurs possibles) */
    char csv[] = "Alice,25,Paris,Informatique";
    printf("CSV : \"%s\"\n", csv);
    printf("Champs (delimiteur virgule) :\n");

    char *champs[] = {"Nom", "Age", "Ville", "Filiere"};
    token = strtok(csv, ",");
    idx   = 0;
    while (token != NULL && idx < 4) {
        printf("  %s : \"%s\"\n", champs[idx++], token);
        token = strtok(NULL, ",");
    }
    printf("\n");

    /* Découper avec plusieurs délimiteurs différents */
    char mixte[] = "un;deux,trois:quatre cinq";
    printf("Chaine mixte : \"%s\"\n", mixte);
    printf("Tokens (delimiteurs : ; , : espace) :\n");

    token = strtok(mixte, ";,: ");
    while (token != NULL) {
        printf("  \"%s\"\n", token);
        token = strtok(NULL, ";,: ");
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 5 — CONVERTIR CHAÎNE ↔ NOMBRE
     *
     * atoi(s)          → chaîne vers int (simple, pas de gestion d'erreur)
     * atof(s)          → chaîne vers double
     * strtol(s, &end, base) → chaîne vers long (gestion d'erreur possible)
     * strtod(s, &end)       → chaîne vers double (gestion d'erreur possible)
     *
     * sprintf(buf, "%d", n) → int vers chaîne (vu en partie 1)
     *
     * Préférer strtol/strtod à atoi/atof car ils permettent
     * de détecter les erreurs de conversion.
     * ---------------------------------------------------------- */
    afficher_separateur("5. Conversions chaine <-> nombre");

    /* atoi : simple mais sans gestion d'erreur */
    char str_entier[] = "42";
    char str_float[]  = "3.14";
    char str_neg[]    = "-128";
    char str_hex[]    = "0xFF";   /* atoi ne comprend pas l'hexa */

    printf("atoi(\"%s\")  = %d\n", str_entier, atoi(str_entier));
    printf("atof(\"%s\") = %.2f\n", str_float,  atof(str_float));
    printf("atoi(\"%s\") = %d\n\n",  str_neg,    atoi(str_neg));

    /* strtol : plus robuste, détecte les erreurs */
    char *endptr;
    char str_hex2[] = "FF";

    long val_dec = strtol("12345", &endptr, 10);   /* base 10 */
    printf("strtol(\"12345\", base 10) = %ld\n", val_dec);

    long val_hex = strtol("FF", &endptr, 16);      /* base 16 */
    printf("strtol(\"FF\",    base 16) = %ld\n", val_hex);

    long val_bin = strtol("1010", &endptr, 2);     /* base 2 */
    printf("strtol(\"1010\",  base  2) = %ld\n\n", val_bin);

    /* Détecter une erreur de conversion avec strtol */
    char invalide[] = "abc123";
    long val_invalide = strtol(invalide, &endptr, 10);
    if (endptr == invalide) {
        printf("strtol(\"%s\") → echec : pas de chiffre en debut\n", invalide);
    } else {
        printf("strtol(\"%s\") → %ld (s'est arrete a '%s')\n",
               invalide, val_invalide, endptr);
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 6 — TABLEAUX DE CHAÎNES (char *tab[])
     *
     * Un tableau de chaînes est un tableau de pointeurs,
     * chaque pointeur pointant vers une chaîne différente.
     *
     * Deux formes :
     *   char *tab[]    → tableau de pointeurs (chaînes en lecture seule)
     *   char tab[][N]  → tableau de tableaux  (chaînes modifiables)
     * ---------------------------------------------------------- */
    afficher_separateur("6. Tableaux de chaines");

    /* Tableau de pointeurs vers des chaînes littérales */
    const char *jours[] = {
        "Lundi", "Mardi", "Mercredi", "Jeudi",
        "Vendredi", "Samedi", "Dimanche"
    };
    int nb_jours = sizeof(jours) / sizeof(jours[0]);

    printf("Jours de la semaine :\n");
    for (int i = 0; i < nb_jours; i++) {
        printf("  jours[%d] = \"%s\" (longueur %lu)\n",
               i, jours[i], strlen(jours[i]));
    }

    /* Recherche dans un tableau de chaînes */
    printf("\nRecherche de \"Vendredi\" :\n");
    int trouve = 0;
    for (int i = 0; i < nb_jours; i++) {
        if (strcmp(jours[i], "Vendredi") == 0) {
            printf("  Trouve a l'index %d\n", i);
            trouve = 1;
            break;
        }
    }
    if (!trouve) printf("  Non trouve.\n");

    /* Tableau de chaînes modifiables (char[][N]) */
    char fruits[4][20] = {"pomme", "banane", "cerise", "datte"};
    printf("\nFruits (modifiables) :\n");
    for (int i = 0; i < 4; i++) {
        /* Convertir en majuscules */
        for (int j = 0; fruits[i][j]; j++) {
            fruits[i][j] = (char)toupper((unsigned char)fruits[i][j]);
        }
        printf("  fruits[%d] = \"%s\"\n", i, fruits[i]);
    }
    printf("\n");


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    afficher_separateur("RECAPITULATIF");
    printf("  sprintf(buf, fmt, ...)       → printf dans une chaine\n");
    printf("  sscanf(str, fmt, ...)        → scanf depuis une chaine\n");
    printf("  strncpy(dst, src, n)         → copie securisee\n");
    printf("  strncat(dst, src, n)         → concat securisee\n");
    printf("  strncmp(s1, s2, n)           → compare n chars\n");
    printf("  strchr(s, c)                 → cherche un char\n");
    printf("  strstr(s, sub)               → cherche une sous-chaine\n");
    printf("  strtok(s, delim)             → decoupe en tokens\n");
    printf("  atoi/atof                    → chaine → int/double\n");
    printf("  strtol(s, &end, base)        → chaine → long (robust)\n");
    printf("  const char *tab[]            → tableau de chaines\n");
    printf("\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS
 * ============================================================ */
void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}