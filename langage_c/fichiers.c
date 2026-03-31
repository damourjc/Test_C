/*
 * ============================================================
 *  FICHIER  : fichiers.c
 *  SUJET    : Les fichiers en C
 *  NIVEAU   : Intermédiaire — Leçon 5
 *  COMPILE  : gcc -Wall -Wextra fichiers.c -o fichiers
 *  EXECUTE  : ./fichiers
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * STRUCTURES ET CONSTANTES
 * ============================================================ */
#define NOM_FICHIER_TEXTE   "notes.txt"
#define NOM_FICHIER_BINAIRE "etudiants.bin"
#define NOM_FICHIER_CSV     "data.csv"
#define TAILLE_LIGNE        256

typedef struct {
    char  nom[50];
    int   age;
    float note;
} Etudiant;


/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);
void demo_ecriture_texte();
void demo_lecture_texte();
void demo_fgets_lecture();
void demo_ecriture_binaire();
void demo_lecture_binaire();
void demo_deplacement_fseek();
void demo_feof_ferror();
void demo_modes_ouverture();
void nettoyer_fichiers();


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 5 : Les fichiers\n");
    printf("==============================================\n\n");

    demo_ecriture_texte();
    demo_lecture_texte();
    demo_fgets_lecture();
    demo_ecriture_binaire();
    demo_lecture_binaire();
    demo_deplacement_fseek();
    demo_feof_ferror();
    demo_modes_ouverture();
    nettoyer_fichiers();

    printf("==============================================\n");
    printf("  Tous les exemples executes avec succes !\n");
    printf("==============================================\n\n");

    return 0;
}


/* ----------------------------------------------------------
 * PARTIE 1 — OUVRIR ET FERMER : fopen / fclose
 *
 * fopen() ouvre (ou crée) un fichier.
 * Retourne un pointeur FILE* ou NULL si échec.
 * TOUJOURS vérifier le retour de fopen !
 * TOUJOURS appeler fclose() après utilisation.
 *
 * Syntaxe : FILE *fopen(const char *chemin, const char *mode);
 *
 * Modes texte :
 *   "r"  → lecture seule (fichier doit exister)
 *   "w"  → écriture (crée ou écrase)
 *   "a"  → ajout en fin de fichier
 *   "r+" → lecture + écriture
 *   "w+" → lecture + écriture (crée ou écrase)
 *   "a+" → lecture + ajout
 *
 * Modes binaires : idem avec 'b' ajouté : "rb", "wb", "ab"
 * ---------------------------------------------------------- */
void demo_ecriture_texte() {
    afficher_separateur("1. fopen / fclose + ecriture texte (fprintf, fputs)");

    /* Ouverture en écriture : crée ou écrase le fichier */
    FILE *f = fopen(NOM_FICHIER_TEXTE, "w");
    if (f == NULL) {
        perror("Erreur fopen");   /* perror affiche le message d'erreur système */
        return;
    }

    printf("Fichier '%s' ouvert en mode ecriture.\n", NOM_FICHIER_TEXTE);

    /* fprintf : comme printf mais vers un fichier */
    fprintf(f, "=== Notes des etudiants ===\n");
    fprintf(f, "Nom           Age   Note\n");
    fprintf(f, "--------------------------\n");

    /* Écrire des données formatées */
    fprintf(f, "%-14s %3d   %.1f\n", "Alice Martin",  22, 15.5f);
    fprintf(f, "%-14s %3d   %.1f\n", "Bob Dupont",    20, 12.0f);
    fprintf(f, "%-14s %3d   %.1f\n", "Charlie Rey",   25, 18.5f);
    fprintf(f, "%-14s %3d   %.1f\n", "Diana Blanc",   21, 14.0f);
    fprintf(f, "%-14s %3d   %.1f\n", "Eva Noir",      23, 16.5f);

    /* fputs : écrire une chaîne sans formatage */
    fputs("\n--- Fin du rapport ---\n", f);

    /* TOUJOURS fermer le fichier */
    fclose(f);
    printf("Fichier ecrit et ferme.\n\n");
}


/* ----------------------------------------------------------
 * PARTIE 2 — LIRE UN FICHIER TEXTE : fscanf
 *
 * fscanf() lit des données formatées depuis un fichier.
 * Fonctionne comme scanf() mais sur un FILE*.
 * Retourne le nombre d'éléments lus avec succès,
 * ou EOF (-1) en fin de fichier ou erreur.
 * ---------------------------------------------------------- */
void demo_lecture_texte() {
    afficher_separateur("2. Lecture texte avec fscanf");

    FILE *f = fopen(NOM_FICHIER_TEXTE, "r");
    if (f == NULL) {
        perror("Erreur fopen lecture");
        return;
    }

    printf("Contenu brut de '%s' :\n", NOM_FICHIER_TEXTE);
    printf("---\n");

    /* Lire caractère par caractère avec fgetc */
    int c;
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }
    printf("---\n\n");

    fclose(f);
}


/* ----------------------------------------------------------
 * PARTIE 3 — LIRE LIGNE PAR LIGNE : fgets
 *
 * fgets() lit une ligne complète (jusqu'au \n ou EOF).
 * Plus sûre que fscanf pour les chaînes.
 * Retourne NULL en fin de fichier ou erreur.
 *
 * Syntaxe : char *fgets(char *buf, int taille, FILE *f);
 * ---------------------------------------------------------- */
void demo_fgets_lecture() {
    afficher_separateur("3. Lecture ligne par ligne avec fgets");

    FILE *f = fopen(NOM_FICHIER_TEXTE, "r");
    if (f == NULL) {
        perror("Erreur fopen");
        return;
    }

    char ligne[TAILLE_LIGNE];
    int  num_ligne = 0;
    int  nb_etudiants = 0;
    float somme_notes = 0.0f;

    printf("Lecture et analyse du fichier :\n");

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        num_ligne++;

        /* Enlever le \n de fin si présent */
        int len = strlen(ligne);
        if (len > 0 && ligne[len-1] == '\n') {
            ligne[len-1] = '\0';
        }

        /* Analyser les lignes contenant des données */
        char nom[50];
        int  age;
        float note;

        /* sscanf lit depuis une chaîne (comme fscanf depuis un fichier) */
        if (sscanf(ligne, "%49s %d %f", nom, &age, &note) == 3) {
            printf("  Etudiant : %-15s age=%d note=%.1f\n",
                   nom, age, note);
            somme_notes += note;
            nb_etudiants++;
        }
    }

    if (nb_etudiants > 0) {
        printf("\nStatistiques :\n");
        printf("  Nb etudiants : %d\n", nb_etudiants);
        printf("  Moyenne      : %.2f\n", somme_notes / nb_etudiants);
    }

    fclose(f);
    printf("\n");
}


/* ----------------------------------------------------------
 * PARTIE 4 — ÉCRITURE BINAIRE : fwrite
 *
 * fwrite() écrit des données binaires brutes dans un fichier.
 * Plus compact et plus rapide que le texte pour les structures.
 * Les données ne sont PAS lisibles par un éditeur de texte.
 *
 * Syntaxe : size_t fwrite(const void *ptr, size_t taille,
 *                         size_t nb, FILE *f);
 * Retourne le nombre d'éléments écrits.
 * ---------------------------------------------------------- */
void demo_ecriture_binaire() {
    afficher_separateur("4. Ecriture binaire avec fwrite");

    Etudiant etudiants[] = {
        {"Alice Martin",  22, 15.5f},
        {"Bob Dupont",    20, 12.0f},
        {"Charlie Rey",   25, 18.5f},
        {"Diana Blanc",   21, 14.0f},
        {"Eva Noir",      23, 16.5f}
    };
    int nb = sizeof(etudiants) / sizeof(etudiants[0]);

    FILE *f = fopen(NOM_FICHIER_BINAIRE, "wb");  /* mode binaire ! */
    if (f == NULL) {
        perror("Erreur fopen binaire");
        return;
    }

    /* Écrire d'abord le nombre d'étudiants */
    fwrite(&nb, sizeof(int), 1, f);

    /* Écrire tous les étudiants en une seule opération */
    size_t ecrits = fwrite(etudiants, sizeof(Etudiant), nb, f);

    printf("Ecriture binaire : %zu/%d etudiants ecrits\n", ecrits, nb);
    printf("Taille fichier   : %zu octets\n",
           sizeof(int) + nb * sizeof(Etudiant));

    fclose(f);
    printf("Fichier binaire '%s' cree.\n\n", NOM_FICHIER_BINAIRE);
}


/* ----------------------------------------------------------
 * PARTIE 5 — LECTURE BINAIRE : fread
 *
 * fread() lit des données binaires brutes depuis un fichier.
 * La structure doit être identique à celle utilisée pour écrire.
 *
 * Syntaxe : size_t fread(void *ptr, size_t taille,
 *                        size_t nb, FILE *f);
 * Retourne le nombre d'éléments lus.
 * ---------------------------------------------------------- */
void demo_lecture_binaire() {
    afficher_separateur("5. Lecture binaire avec fread");

    FILE *f = fopen(NOM_FICHIER_BINAIRE, "rb");
    if (f == NULL) {
        perror("Erreur fopen binaire lecture");
        return;
    }

    /* Lire le nombre d'étudiants */
    int nb;
    fread(&nb, sizeof(int), 1, f);
    printf("Nombre d'etudiants stockes : %d\n\n", nb);

    /* Allouer et lire tous les étudiants */
    Etudiant *tab = (Etudiant*)malloc(nb * sizeof(Etudiant));
    if (tab == NULL) {
        fclose(f);
        return;
    }

    size_t lus = fread(tab, sizeof(Etudiant), nb, f);
    printf("Lus : %zu etudiants\n\n", lus);

    printf("%-16s %4s %6s\n", "Nom", "Age", "Note");
    printf("---------------------------\n");
    for (int i = 0; i < (int)lus; i++) {
        printf("%-16s %4d %6.1f\n",
               tab[i].nom, tab[i].age, tab[i].note);
    }

    free(tab);
    fclose(f);
    printf("\n");
}


/* ----------------------------------------------------------
 * PARTIE 6 — SE DÉPLACER DANS UN FICHIER : fseek, ftell, rewind
 *
 * fseek() déplace le curseur de lecture/écriture.
 * ftell() retourne la position courante du curseur.
 * rewind() remet le curseur au début du fichier.
 *
 * fseek(f, offset, origine) :
 *   origine :
 *     SEEK_SET → depuis le début du fichier
 *     SEEK_CUR → depuis la position courante
 *     SEEK_END → depuis la fin du fichier
 * ---------------------------------------------------------- */
void demo_deplacement_fseek() {
    afficher_separateur("6. fseek / ftell / rewind");

    FILE *f = fopen(NOM_FICHIER_BINAIRE, "rb");
    if (f == NULL) {
        perror("Erreur fopen");
        return;
    }

    /* Sauter le compteur initial (int) */
    fseek(f, sizeof(int), SEEK_SET);

    /* Connaître la taille totale */
    fseek(f, 0, SEEK_END);
    long taille = ftell(f);
    printf("Taille du fichier : %ld octets\n", taille);

    /* Revenir au début */
    rewind(f);
    printf("Apres rewind : position = %ld\n", ftell(f));

    /* Sauter au 3e étudiant (index 2) */
    long offset = sizeof(int) + 2 * sizeof(Etudiant);
    fseek(f, offset, SEEK_SET);
    printf("Apres fseek vers etudiant[2] : position = %ld\n", ftell(f));

    /* Lire uniquement le 3e étudiant */
    Etudiant e;
    fread(&e, sizeof(Etudiant), 1, f);
    printf("Etudiant[2] : %s, %d ans, %.1f\n\n",
           e.nom, e.age, e.note);

    /* Lire le dernier étudiant en partant de la fin */
    fseek(f, -(long)sizeof(Etudiant), SEEK_END);
    fread(&e, sizeof(Etudiant), 1, f);
    printf("Dernier etudiant : %s, %d ans, %.1f\n\n",
           e.nom, e.age, e.note);

    fclose(f);
}


/* ----------------------------------------------------------
 * PARTIE 7 — TESTER FIN DE FICHIER ET ERREURS : feof, ferror
 *
 * feof(f)   → retourne vrai si la fin du fichier est atteinte
 * ferror(f) → retourne vrai si une erreur s'est produite
 * clearerr(f) → remet les indicateurs d'erreur/EOF à zéro
 *
 * IMPORTANT : ne pas tester feof() en condition de boucle !
 * Tester plutôt le retour de fread/fgets/fscanf.
 * feof() est vrai APRÈS avoir essayé de lire au-delà de la fin.
 * ---------------------------------------------------------- */
void demo_feof_ferror() {
    afficher_separateur("7. feof et ferror");

    FILE *f = fopen(NOM_FICHIER_TEXTE, "r");
    if (f == NULL) {
        perror("Erreur fopen");
        return;
    }

    /* Bonne pratique : tester le retour de la fonction de lecture */
    char ligne[TAILLE_LIGNE];
    int nb_lignes = 0;

    printf("Bonne pratique (tester retour fgets) :\n");
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        nb_lignes++;
    }

    /* feof est vrai maintenant (après la dernière lecture) */
    if (feof(f)) {
        printf("  Fin de fichier atteinte apres %d lignes\n", nb_lignes);
    }

    /* ferror vérifie si une erreur de lecture s'est produite */
    if (ferror(f)) {
        printf("  Une erreur de lecture s'est produite !\n");
    } else {
        printf("  Aucune erreur de lecture.\n");
    }

    printf("\n  ATTENTION : ne jamais ecrire :\n");
    printf("  while (!feof(f)) { fgets(...) }  <- MAUVAISE PRATIQUE\n");
    printf("  car feof est vrai apres la derniere lecture\n\n");

    fclose(f);
}


/* ----------------------------------------------------------
 * PARTIE 8 — MODES D'OUVERTURE COMPLETS
 * ---------------------------------------------------------- */
void demo_modes_ouverture() {
    afficher_separateur("8. Modes d'ouverture");

    printf("Modes texte :\n");
    printf("  \"r\"  → lecture seule (fichier doit exister)\n");
    printf("  \"w\"  → ecriture (cree ou ecrase)\n");
    printf("  \"a\"  → ajout en fin de fichier\n");
    printf("  \"r+\" → lecture + ecriture (fichier doit exister)\n");
    printf("  \"w+\" → lecture + ecriture (cree ou ecrase)\n");
    printf("  \"a+\" → lecture + ajout\n\n");

    printf("Modes binaires (ajouter 'b') :\n");
    printf("  \"rb\" \"wb\" \"ab\" \"r+b\" \"w+b\" \"a+b\"\n\n");

    /* Démonstration du mode "a" (append) */
    FILE *f = fopen(NOM_FICHIER_TEXTE, "a");
    if (f == NULL) { perror("append"); return; }
    fprintf(f, "\n[Ligne ajoutee en mode \"a\"]\n");
    fclose(f);
    printf("Mode \"a\" : ligne ajoutee a la fin du fichier.\n");

    /* Lire la dernière ligne pour vérifier */
    f = fopen(NOM_FICHIER_TEXTE, "r");
    if (f == NULL) { return; }
    char ligne[TAILLE_LIGNE];
    char derniere[TAILLE_LIGNE] = "";
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (strlen(ligne) > 1)
            strncpy(derniere, ligne, sizeof(derniere) - 1);
    }
    /* Enlever \n */
    int len = strlen(derniere);
    if (len > 0 && derniere[len-1] == '\n') derniere[len-1] = '\0';
    printf("Derniere ligne non vide : \"%s\"\n\n", derniere);
    fclose(f);

    /* Récapitulatif des fonctions */
    printf("Recap des fonctions :\n");
    printf("  fopen / fclose      → ouvrir / fermer\n");
    printf("  fprintf / fputs     → ecrire texte formate / chaine\n");
    printf("  fscanf / fgetc      → lire texte formate / char\n");
    printf("  fgets               → lire une ligne entiere\n");
    printf("  fwrite / fread      → lire/ecrire binaire\n");
    printf("  fseek / ftell       → deplacer / lire curseur\n");
    printf("  rewind              → revenir au debut\n");
    printf("  feof / ferror       → tester fin / erreur\n\n");
}

void nettoyer_fichiers() {
    remove(NOM_FICHIER_TEXTE);
    remove(NOM_FICHIER_BINAIRE);
    remove(NOM_FICHIER_CSV);
    printf("Fichiers temporaires supprimes.\n\n");
}

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}