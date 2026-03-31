/*
 * ============================================================
 *  FICHIER  : chaines.c
 *  SUJET    : Les chaînes de caractères en C
 *  NIVEAU   : Débutant — Leçon 7
 *  COMPILE  : gcc chaines.c -o chaines
 *  EXECUTE  : ./chaines
 * ============================================================
 */

#include <stdio.h>
#include <string.h>   /* strlen, strcpy, strcat, strcmp */

int main() {

    printf("==============================================\n");
    printf("  LECON 7 : Chaines de caracteres\n");
    printf("==============================================\n\n");


    /* ----------------------------------------------------------
     * PARTIE 1 — UNE CHAÎNE EST UN TABLEAU DE char + '\0'
     *
     * En C, il n'existe pas de type "string" natif.
     * Une chaîne de caractères est simplement un tableau de
     * char qui se termine OBLIGATOIREMENT par '\0' (zéro ASCII).
     * Ce caractère nul invisible marque la fin de la chaîne.
     *
     * "Bonjour" occupe 8 cases : B o n j o u r \0
     * ---------------------------------------------------------- */
    printf("--- 1. Une chaine = tableau de char + '\\0' ---\n");

    /* Les deux déclarations suivantes sont équivalentes */
    char mot1[] = "Bonjour";               /* Forme raccourcie */
    char mot2[] = {'B','o','n','j','o','u','r','\0'}; /* Forme longue */

    printf("mot1 : %s\n", mot1);
    printf("mot2 : %s\n", mot2);

    /* Afficher caractère par caractère avec leur code ASCII */
    printf("\nDétail de \"%s\" :\n", mot1);
    for (int i = 0; mot1[i] != '\0'; i++) {
        printf("  mot1[%d] = '%c'  (ASCII %d)\n", i, mot1[i], mot1[i]);
    }
    printf("  mot1[7] = '\\0' (ASCII 0) ← terminateur\n\n");


    /* ----------------------------------------------------------
     * PARTIE 2 — DÉCLARER ET INITIALISER UNE CHAÎNE
     *
     * Toujours prévoir assez de place pour les caractères
     * ET pour le '\0' final.
     * Ex : "Alice" a 5 lettres → il faut au moins char[6]
     * ---------------------------------------------------------- */
    printf("--- 2. Declarer et initialiser ---\n");

    /* Taille déduite automatiquement (= 6 : 5 lettres + '\0') */
    char prenom[] = "Alice";

    /* Taille fixée manuellement (assez grande pour futures modifs) */
    char nom[50] = "Dupont";

    /* Chaîne vide : juste le terminateur */
    char vide[100] = "";

    /* Chaîne non initialisée : DANGEREUSE sans '\0' */
    char buffer[100];
    buffer[0] = '\0';   /* On force la chaîne vide manuellement */

    printf("prenom   : \"%s\"  (taille tableau : %lu)\n",
           prenom, sizeof(prenom));
    printf("nom      : \"%s\"  (taille tableau : %lu)\n",
           nom, sizeof(nom));
    printf("vide     : \"%s\"  (longueur : %lu)\n",
           vide, strlen(vide));
    printf("buffer   : \"%s\"  (longueur : %lu)\n\n",
           buffer, strlen(buffer));


    /* ----------------------------------------------------------
     * PARTIE 3 — AFFICHER UNE CHAÎNE AVEC printf("%s")
     *
     * %s dans printf attend un tableau de char terminé par '\0'.
     * On peut contrôler la largeur d'affichage comme pour %d.
     * ---------------------------------------------------------- */
    printf("--- 3. Afficher avec printf(\"%%s\") ---\n");

    char ville[] = "Paris";

    printf("Simple       : %s\n",    ville);
    printf("Largeur 15   : [%15s]\n", ville);   /* Aligné à droite */
    printf("Larg 15 gche : [%-15s]\n", ville);  /* Aligné à gauche */
    printf("Précision 3  : %.3s\n",  ville);    /* 3 premiers chars seulement */
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 4 — LIRE UNE CHAÎNE AVEC scanf() ET fgets()
     *
     * scanf("%s") : lit jusqu'à l'espace → un seul mot
     * fgets()     : lit toute la ligne (espaces inclus)
     * ---------------------------------------------------------- */
    printf("--- 4. Lire avec scanf et fgets ---\n");

    char saisie_mot[50];
    char saisie_phrase[100];

    /* scanf : lit un seul mot (s'arrête à l'espace) */
    printf("Entrez votre prenom : ");
    scanf("%49s", saisie_mot);          /* 49 = taille - 1 */
    printf("Prenom saisi : %s\n", saisie_mot);

    /* Vider le buffer clavier avant fgets */
    while (getchar() != '\n');

    /* fgets : lit toute la ligne, espaces inclus */
    printf("Entrez une phrase : ");
    fgets(saisie_phrase, sizeof(saisie_phrase), stdin);

    /* Enlever le '\n' que fgets laisse à la fin */
    int i = 0;
    while (saisie_phrase[i] != '\n' && saisie_phrase[i] != '\0') i++;
    saisie_phrase[i] = '\0';

    printf("Phrase saisie : \"%s\"\n\n", saisie_phrase);


    /* ----------------------------------------------------------
     * PARTIE 5 — strlen() : LONGUEUR D'UNE CHAÎNE
     *
     * strlen() retourne le nombre de caractères SANS compter '\0'.
     * C'est différent de sizeof() qui retourne la taille du tableau.
     * ---------------------------------------------------------- */
    printf("--- 5. strlen() : longueur ---\n");

    char a[] = "Bonjour";
    char b[50] = "Bonjour";

    printf("strlen(\"%s\")  = %lu  (nb de caracteres)\n", a, strlen(a));
    printf("sizeof(a)     = %lu  (taille du tableau en octets)\n", sizeof(a));
    printf("sizeof(b)     = %lu  (taille du tableau en octets)\n", sizeof(b));

    /* Chaîne vide */
    char vide2[] = "";
    printf("strlen(\"\")    = %lu  (chaine vide)\n\n", strlen(vide2));


    /* ----------------------------------------------------------
     * PARTIE 6 — strcpy() : COPIER UNE CHAÎNE
     *
     * On NE peut PAS faire : chaine1 = chaine2  (interdit en C !)
     * Il faut utiliser strcpy() pour copier le contenu.
     * Toujours s'assurer que la destination est assez grande.
     * ---------------------------------------------------------- */
    printf("--- 6. strcpy() : copier ---\n");

    char source[]   = "Programmation";
    char destination[50];

    strcpy(destination, source);   /* copie source → destination */

    printf("source      : \"%s\"\n", source);
    printf("destination : \"%s\"\n", destination);

    /* Modifier la destination ne modifie pas la source */
    destination[0] = 'p';   /* Minuscule */
    printf("Apres modif → source : \"%s\", dest : \"%s\"\n\n",
           source, destination);


    /* ----------------------------------------------------------
     * PARTIE 7 — strcat() : CONCATÉNER DEUX CHAÎNES
     *
     * strcat() ajoute la deuxième chaîne à la fin de la première.
     * La première doit avoir assez de place pour contenir les deux !
     * ---------------------------------------------------------- */
    printf("--- 7. strcat() : concatener ---\n");

    char complet[100] = "Bonjour";
    char espace[]     = " ";
    char monde[]      = "le monde";

    printf("Avant : \"%s\"\n", complet);
    strcat(complet, espace);   /* "Bonjour" + " " → "Bonjour " */
    strcat(complet, monde);    /* "Bonjour " + "le monde" */
    printf("Apres : \"%s\"\n", complet);

    /* Construire un nom complet */
    char prenom2[100] = "Jean";
    char nom2[]       = "Dupont";

    strcat(prenom2, " ");
    strcat(prenom2, nom2);
    printf("Nom complet : \"%s\"\n\n", prenom2);


    /* ----------------------------------------------------------
     * PARTIE 8 — strcmp() : COMPARER DEUX CHAÎNES
     *
     * On NE peut PAS faire : if (chaine1 == chaine2)  (compare des adresses !)
     * strcmp() compare le CONTENU des chaînes.
     *
     * Retourne :
     *   0   si les chaînes sont ÉGALES
     *   < 0 si chaine1 vient AVANT chaine2 (ordre alphabétique)
     *   > 0 si chaine1 vient APRÈS chaine2
     * ---------------------------------------------------------- */
    printf("--- 8. strcmp() : comparer ---\n");

    char s1[] = "pomme";
    char s2[] = "pomme";
    char s3[] = "Pomme";    /* Majuscule : code ASCII différent */
    char s4[] = "poire";

    printf("strcmp(\"%s\", \"%s\") = %d  → egales\n",
           s1, s2, strcmp(s1, s2));

    printf("strcmp(\"%s\", \"%s\") = %d  → differentes (casse)\n",
           s1, s3, strcmp(s1, s3));

    printf("strcmp(\"%s\", \"%s\") = %d  → pomme > poire\n",
           s1, s4, strcmp(s1, s4));

    /* Utilisation dans une condition */
    char mot_secret[] = "azerty";
    char tentative[]  = "azerty";

    if (strcmp(tentative, mot_secret) == 0) {
        printf("Mot de passe correct !\n");
    } else {
        printf("Mot de passe incorrect.\n");
    }
    printf("\n");


    /* ----------------------------------------------------------
     * PARTIE 9 — PARCOURIR CARACTÈRE PAR CARACTÈRE
     *
     * Une chaîne étant un tableau, on peut la parcourir
     * comme n'importe quel tableau, jusqu'au '\0' final.
     * ---------------------------------------------------------- */
    printf("--- 9. Parcourir caractere par caractere ---\n");

    char texte[] = "Bonjour C !";

    /* Méthode 1 : boucle while jusqu'à '\0' */
    printf("Méthode while  : ");
    int j = 0;
    while (texte[j] != '\0') {
        putchar(texte[j]);
        j++;
    }
    printf("\n");

    /* Méthode 2 : boucle for avec strlen */
    printf("Methode for    : ");
    for (int k = 0; k < (int)strlen(texte); k++) {
        putchar(texte[k]);
    }
    printf("\n");

    /* Compter les espaces */
    int nb_espaces = 0;
    for (int k = 0; texte[k] != '\0'; k++) {
        if (texte[k] == ' ') nb_espaces++;
    }
    printf("Nb d'espaces   : %d\n", nb_espaces);

    /* Compter les voyelles */
    int nb_voyelles = 0;
    char voyelles[] = "aeiouAEIOU";
    for (int k = 0; texte[k] != '\0'; k++) {
        for (int v = 0; voyelles[v] != '\0'; v++) {
            if (texte[k] == voyelles[v]) {
                nb_voyelles++;
                break;
            }
        }
    }
    printf("Nb de voyelles : %d\n\n", nb_voyelles);


    /* ----------------------------------------------------------
     * RÉCAPITULATIF
     * ---------------------------------------------------------- */
    printf("==============================================\n");
    printf("  RECAPITULATIF\n");
    printf("==============================================\n");
    printf("  char s[] = \"texte\";    → declaration\n");
    printf("  printf(\"%%s\", s);       → afficher\n");
    printf("  scanf(\"%%49s\", s);      → lire un mot\n");
    printf("  fgets(s, taille, stdin) → lire une ligne\n");
    printf("  strlen(s)              → longueur\n");
    printf("  strcpy(dest, src)      → copier\n");
    printf("  strcat(dest, src)      → concatener\n");
    printf("  strcmp(s1, s2) == 0    → comparer\n");
    printf("  while(s[i] != '\\0')    → parcourir\n");
    printf("\n");

    return 0;
}