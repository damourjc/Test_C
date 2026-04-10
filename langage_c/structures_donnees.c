/*
 * ============================================================
 *  FICHIER  : structures_donnees.c
 *  SUJET    : Structures de données avancées en C
 *  NIVEAU   : Avancé — Leçon 1
 *  COMPILE  : gcc -Wall -Wextra structures_donnees.c -o sda
 *  EXECUTE  : ./sda
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * PARTIE 1 — LISTE CHAÎNÉE SIMPLE
 *
 * Chaque nœud contient une donnée et un pointeur vers le suivant.
 * Le dernier nœud pointe vers NULL.
 *
 * [val|next] → [val|next] → [val|next] → NULL
 *
 * Avantages : insertion/suppression O(1) en tête
 * Inconvénients : accès indexé O(n), pas de retour en arrière
 * ============================================================ */

typedef struct NoeudListe {
    int               valeur;
    struct NoeudListe *suivant;
} NoeudListe;

typedef struct {
    NoeudListe *tete;
    int         taille;
} ListeSimple;

void liste_init(ListeSimple *l) {
    l->tete   = NULL;
    l->taille = 0;
}

/* Insérer en tête : O(1) */
void liste_inserer_tete(ListeSimple *l, int val) {
    NoeudListe *n = (NoeudListe*)malloc(sizeof(NoeudListe));
    if (!n) return;
    n->valeur  = val;
    n->suivant = l->tete;
    l->tete    = n;
    l->taille++;
}

/* Insérer en queue : O(n) */
void liste_inserer_queue(ListeSimple *l, int val) {
    NoeudListe *n = (NoeudListe*)malloc(sizeof(NoeudListe));
    if (!n) return;
    n->valeur  = val;
    n->suivant = NULL;
    if (!l->tete) {
        l->tete = n;
    } else {
        NoeudListe *cur = l->tete;
        while (cur->suivant) cur = cur->suivant;
        cur->suivant = n;
    }
    l->taille++;
}

/* Supprimer par valeur : O(n) */
int liste_supprimer(ListeSimple *l, int val) {
    NoeudListe *cur = l->tete, *prev = NULL;
    while (cur) {
        if (cur->valeur == val) {
            if (prev) prev->suivant = cur->suivant;
            else      l->tete       = cur->suivant;
            free(cur);
            l->taille--;
            return 1;
        }
        prev = cur;
        cur  = cur->suivant;
    }
    return 0;
}

void liste_afficher(ListeSimple *l) {
    NoeudListe *cur = l->tete;
    printf("Liste(%d) : ", l->taille);
    while (cur) {
        printf("[%d]%s", cur->valeur, cur->suivant ? " -> " : "");
        cur = cur->suivant;
    }
    printf(" -> NULL\n");
}

void liste_liberer(ListeSimple *l) {
    NoeudListe *cur = l->tete, *tmp;
    while (cur) { tmp = cur->suivant; free(cur); cur = tmp; }
    l->tete   = NULL;
    l->taille = 0;
}


/* ============================================================
 * PARTIE 2 — LISTE DOUBLEMENT CHAÎNÉE
 *
 * Chaque nœud a un pointeur vers le suivant ET le précédent.
 * Permet le parcours dans les deux directions.
 *
 * NULL <- [prev|val|next] <-> [prev|val|next] -> NULL
 *
 * Avantages : parcours bidirectionnel, suppression O(1) si nœud connu
 * Inconvénients : plus de mémoire (2 pointeurs par nœud)
 * ============================================================ */

typedef struct NoeudDouble {
    int                valeur;
    struct NoeudDouble *suivant;
    struct NoeudDouble *precedent;
} NoeudDouble;

typedef struct {
    NoeudDouble *tete;
    NoeudDouble *queue;
    int          taille;
} ListeDouble;

void liste_double_init(ListeDouble *l) {
    l->tete = l->queue = NULL;
    l->taille = 0;
}

void liste_double_inserer_fin(ListeDouble *l, int val) {
    NoeudDouble *n = (NoeudDouble*)malloc(sizeof(NoeudDouble));
    if (!n) return;
    n->valeur    = val;
    n->suivant   = NULL;
    n->precedent = l->queue;
    if (l->queue) l->queue->suivant = n;
    else          l->tete = n;
    l->queue = n;
    l->taille++;
}

void liste_double_afficher(ListeDouble *l) {
    NoeudDouble *cur = l->tete;
    printf("Double(%d) : NULL <-> ", l->taille);
    while (cur) {
        printf("[%d]%s", cur->valeur, cur->suivant ? " <-> " : "");
        cur = cur->suivant;
    }
    printf(" <-> NULL\n");
}

void liste_double_afficher_inverse(ListeDouble *l) {
    NoeudDouble *cur = l->queue;
    printf("Inverse    : NULL <-> ");
    while (cur) {
        printf("[%d]%s", cur->valeur, cur->precedent ? " <-> " : "");
        cur = cur->precedent;
    }
    printf(" <-> NULL\n");
}

void liste_double_liberer(ListeDouble *l) {
    NoeudDouble *cur = l->tete, *tmp;
    while (cur) { tmp = cur->suivant; free(cur); cur = tmp; }
    l->tete = l->queue = NULL;
    l->taille = 0;
}


/* ============================================================
 * PARTIE 3 — PILE (STACK)
 *
 * Structure LIFO : Last In, First Out.
 * Le dernier élément ajouté est le premier retiré.
 * Cas d'usage : appels de fonctions, undo/redo, vérification
 * de parenthèses, évaluation d'expressions.
 *
 * push(10) push(20) push(30)
 * Sommet → [30][20][10] ← Base
 * pop() → 30 (puis 20 puis 10)
 * ============================================================ */

#define PILE_MAX 64

typedef struct {
    int donnees[PILE_MAX];
    int sommet;
} Pile;

void pile_init(Pile *p)        { p->sommet = 0; }
int  pile_est_vide(Pile *p)    { return p->sommet == 0; }
int  pile_est_pleine(Pile *p)  { return p->sommet == PILE_MAX; }

int pile_push(Pile *p, int val) {
    if (pile_est_pleine(p)) return 0;
    p->donnees[p->sommet++] = val;
    return 1;
}

int pile_pop(Pile *p, int *val) {
    if (pile_est_vide(p)) return 0;
    *val = p->donnees[--p->sommet];
    return 1;
}

int pile_peek(Pile *p, int *val) {
    if (pile_est_vide(p)) return 0;
    *val = p->donnees[p->sommet - 1];
    return 1;
}

void pile_afficher(Pile *p) {
    printf("Pile(sommet->bas) : [");
    for (int i = p->sommet - 1; i >= 0; i--)
        printf("%d%s", p->donnees[i], i > 0 ? ", " : "");
    printf("] (taille=%d)\n", p->sommet);
}


/* ============================================================
 * PARTIE 4 — FILE (QUEUE)
 *
 * Structure FIFO : First In, First Out.
 * Le premier élément ajouté est le premier retiré.
 * Implémentée avec un tableau circulaire.
 *
 * Cas d'usage : gestion de tâches, BFS, buffers réseau.
 *
 * enfiler(1) enfiler(2) enfiler(3)
 * Debut → [1][2][3] ← Fin
 * defiler() → 1 (puis 2 puis 3)
 * ============================================================ */

#define FILE_MAX 8

typedef struct {
    int donnees[FILE_MAX];
    int debut;
    int fin;
    int taille;
} File;

void file_init(File *f)       { f->debut = f->fin = f->taille = 0; }
int  file_est_vide(File *f)   { return f->taille == 0; }
int  file_est_pleine(File *f) { return f->taille == FILE_MAX; }

int file_enfiler(File *f, int val) {
    if (file_est_pleine(f)) return 0;
    f->donnees[f->fin] = val;
    f->fin = (f->fin + 1) % FILE_MAX;   /* tableau circulaire */
    f->taille++;
    return 1;
}

int file_defiler(File *f, int *val) {
    if (file_est_vide(f)) return 0;
    *val = f->donnees[f->debut];
    f->debut = (f->debut + 1) % FILE_MAX;
    f->taille--;
    return 1;
}

void file_afficher(File *f) {
    printf("File(debut->fin) : [");
    for (int i = 0; i < f->taille; i++) {
        int idx = (f->debut + i) % FILE_MAX;
        printf("%d%s", f->donnees[idx], i < f->taille - 1 ? ", " : "");
    }
    printf("] (taille=%d)\n", f->taille);
}


/* ============================================================
 * PARTIE 5 — ARBRE BINAIRE DE RECHERCHE (BST)
 *
 * Propriété BST : pour chaque nœud N :
 *   - Sous-arbre gauche : toutes valeurs < N.valeur
 *   - Sous-arbre droit  : toutes valeurs > N.valeur
 *
 * Recherche, insertion, suppression : O(log n) équilibré, O(n) pire cas.
 * ============================================================ */

typedef struct NoeudArbre {
    int                valeur;
    struct NoeudArbre *gauche;
    struct NoeudArbre *droite;
} NoeudArbre;

NoeudArbre *bst_creer_noeud(int val) {
    NoeudArbre *n = (NoeudArbre*)malloc(sizeof(NoeudArbre));
    if (!n) return NULL;
    n->valeur = val;
    n->gauche = n->droite = NULL;
    return n;
}

/* Insertion récursive : O(h) où h = hauteur */
NoeudArbre *bst_inserer(NoeudArbre *racine, int val) {
    if (!racine)              return bst_creer_noeud(val);
    if (val < racine->valeur) racine->gauche = bst_inserer(racine->gauche, val);
    else if (val > racine->valeur) racine->droite = bst_inserer(racine->droite, val);
    return racine;
}

/* Recherche récursive : O(h) */
int bst_rechercher(NoeudArbre *racine, int val) {
    if (!racine)               return 0;
    if (val == racine->valeur) return 1;
    if (val < racine->valeur)  return bst_rechercher(racine->gauche, val);
    return                            bst_rechercher(racine->droite, val);
}

/* Trouver le nœud minimum d'un sous-arbre */
NoeudArbre *bst_min(NoeudArbre *n) {
    while (n && n->gauche) n = n->gauche;
    return n;
}

/* Suppression : 3 cas (feuille, 1 enfant, 2 enfants) */
NoeudArbre *bst_supprimer(NoeudArbre *racine, int val) {
    if (!racine) return NULL;
    if (val < racine->valeur)
        racine->gauche = bst_supprimer(racine->gauche, val);
    else if (val > racine->valeur)
        racine->droite = bst_supprimer(racine->droite, val);
    else {
        /* Cas 1 : feuille ou 1 seul enfant */
        if (!racine->gauche) {
            NoeudArbre *tmp = racine->droite;
            free(racine); return tmp;
        }
        if (!racine->droite) {
            NoeudArbre *tmp = racine->gauche;
            free(racine); return tmp;
        }
        /* Cas 2 : 2 enfants → remplacer par le successeur inorder */
        NoeudArbre *succ = bst_min(racine->droite);
        racine->valeur   = succ->valeur;
        racine->droite   = bst_supprimer(racine->droite, succ->valeur);
    }
    return racine;
}

/* Hauteur de l'arbre */
int bst_hauteur(NoeudArbre *racine) {
    if (!racine) return 0;
    int hg = bst_hauteur(racine->gauche);
    int hd = bst_hauteur(racine->droite);
    return 1 + (hg > hd ? hg : hd);
}

/* Parcours in-order (gauche-racine-droite) : donne l'ordre trié */
void bst_inorder(NoeudArbre *racine) {
    if (!racine) return;
    bst_inorder(racine->gauche);
    printf("%d ", racine->valeur);
    bst_inorder(racine->droite);
}

/* Affichage visuel (arbre tourné 90°) */
void bst_afficher(NoeudArbre *racine, int niveau) {
    if (!racine) return;
    bst_afficher(racine->droite, niveau + 1);
    for (int i = 0; i < niveau; i++) printf("    ");
    printf("[%d]\n", racine->valeur);
    bst_afficher(racine->gauche, niveau + 1);
}

void bst_liberer(NoeudArbre *racine) {
    if (!racine) return;
    bst_liberer(racine->gauche);
    bst_liberer(racine->droite);
    free(racine);
}


/* ============================================================
 * PARTIE 6 — TABLE DE HACHAGE
 *
 * Associe des clés (chaînes) à des valeurs (entiers).
 * Fonction de hachage → index dans le tableau de buckets.
 * Collisions gérées par chaînage (liste dans chaque bucket).
 *
 * hash("alice") → 7 → bucket[7] → [("alice":25)] → NULL
 * Complexité : O(1) en moyenne, O(n) au pire (toutes collisions)
 * ============================================================ */

#define HASH_TAILLE 16

typedef struct NoeudHash {
    char              cle[64];
    int               valeur;
    struct NoeudHash *suivant;
} NoeudHash;

typedef struct {
    NoeudHash *buckets[HASH_TAILLE];
    int        nb_elements;
} TableHash;

/* Fonction de hachage djb2 */
unsigned int hash_fn(const char *cle) {
    unsigned int h = 5381;
    int c;
    while ((c = *cle++)) h = ((h << 5) + h) + c;
    return h % HASH_TAILLE;
}

void hash_init(TableHash *t) {
    for (int i = 0; i < HASH_TAILLE; i++) t->buckets[i] = NULL;
    t->nb_elements = 0;
}

void hash_inserer(TableHash *t, const char *cle, int val) {
    unsigned int idx = hash_fn(cle);
    /* Mise à jour si clé existante */
    for (NoeudHash *cur = t->buckets[idx]; cur; cur = cur->suivant) {
        if (strcmp(cur->cle, cle) == 0) { cur->valeur = val; return; }
    }
    /* Nouveau nœud en tête de bucket */
    NoeudHash *n = (NoeudHash*)malloc(sizeof(NoeudHash));
    if (!n) return;
    strncpy(n->cle, cle, 63); n->cle[63] = '\0';
    n->valeur       = val;
    n->suivant      = t->buckets[idx];
    t->buckets[idx] = n;
    t->nb_elements++;
}

int hash_rechercher(TableHash *t, const char *cle, int *val) {
    unsigned int idx = hash_fn(cle);
    for (NoeudHash *cur = t->buckets[idx]; cur; cur = cur->suivant) {
        if (strcmp(cur->cle, cle) == 0) { *val = cur->valeur; return 1; }
    }
    return 0;
}

void hash_afficher(TableHash *t) {
    printf("Table de hachage (%d elems, %d buckets) :\n",
           t->nb_elements, HASH_TAILLE);
    for (int i = 0; i < HASH_TAILLE; i++) {
        if (!t->buckets[i]) continue;
        printf("  bucket[%2d] : ", i);
        for (NoeudHash *cur = t->buckets[i]; cur; cur = cur->suivant)
            printf("(\"%s\":%d)%s", cur->cle, cur->valeur,
                   cur->suivant ? " -> " : "");
        printf("\n");
    }
}

void hash_liberer(TableHash *t) {
    for (int i = 0; i < HASH_TAILLE; i++) {
        NoeudHash *cur = t->buckets[i], *tmp;
        while (cur) { tmp = cur->suivant; free(cur); cur = tmp; }
        t->buckets[i] = NULL;
    }
    t->nb_elements = 0;
}


/* ============================================================
 * PARTIE 7 — GRAPHE (liste d'adjacence)
 *
 * Ensemble de sommets reliés par des arêtes/arcs.
 * Représentation par liste d'adjacence :
 *   adjacence[i] = liste des voisins du sommet i
 *
 * Complexité spatiale : O(V + E)
 * Inclut BFS (niveau par niveau) et DFS (récursif en profondeur)
 * ============================================================ */

#define GRAPH_MAX 8

typedef struct NoeudArete {
    int               dest;
    int               poids;
    struct NoeudArete *suivant;
} NoeudArete;

typedef struct {
    NoeudArete *adjacence[GRAPH_MAX];
    int         nb_sommets;
    int         oriente;
} Graphe;

void graphe_init(Graphe *g, int nb, int oriente) {
    g->nb_sommets = nb;
    g->oriente    = oriente;
    for (int i = 0; i < nb; i++) g->adjacence[i] = NULL;
}

void graphe_ajouter_arete(Graphe *g, int src, int dst, int poids) {
    NoeudArete *n = (NoeudArete*)malloc(sizeof(NoeudArete));
    if (!n) return;
    n->dest    = dst; n->poids = poids;
    n->suivant = g->adjacence[src];
    g->adjacence[src] = n;

    if (!g->oriente) {
        NoeudArete *m = (NoeudArete*)malloc(sizeof(NoeudArete));
        if (!m) return;
        m->dest    = src; m->poids = poids;
        m->suivant = g->adjacence[dst];
        g->adjacence[dst] = m;
    }
}

void graphe_afficher(Graphe *g) {
    printf("Graphe %s (%d sommets) :\n",
           g->oriente ? "oriente" : "non oriente", g->nb_sommets);
    for (int i = 0; i < g->nb_sommets; i++) {
        printf("  %d : ", i);
        for (NoeudArete *cur = g->adjacence[i]; cur; cur = cur->suivant)
            printf("[->%d(p=%d)] ", cur->dest, cur->poids);
        printf("\n");
    }
}

/* BFS : parcours niveau par niveau, garantit le chemin le plus court */
void graphe_bfs(Graphe *g, int depart) {
    int visite[GRAPH_MAX] = {0};
    int file[GRAPH_MAX];
    int debut = 0, fin = 0;

    printf("BFS depuis sommet %d : ", depart);
    visite[depart] = 1;
    file[fin++]    = depart;

    while (debut < fin) {
        int courant = file[debut++];
        printf("%d ", courant);
        for (NoeudArete *cur = g->adjacence[courant]; cur; cur = cur->suivant) {
            if (!visite[cur->dest]) {
                visite[cur->dest] = 1;
                file[fin++]       = cur->dest;
            }
        }
    }
    printf("\n");
}

/* DFS : parcours récursif en profondeur */
void graphe_dfs_rec(Graphe *g, int courant, int visite[]) {
    visite[courant] = 1;
    printf("%d ", courant);
    for (NoeudArete *cur = g->adjacence[courant]; cur; cur = cur->suivant)
        if (!visite[cur->dest])
            graphe_dfs_rec(g, cur->dest, visite);
}

void graphe_dfs(Graphe *g, int depart) {
    int visite[GRAPH_MAX] = {0};
    printf("DFS depuis sommet %d : ", depart);
    graphe_dfs_rec(g, depart, visite);
    printf("\n");
}

void graphe_liberer(Graphe *g) {
    for (int i = 0; i < g->nb_sommets; i++) {
        NoeudArete *cur = g->adjacence[i], *tmp;
        while (cur) { tmp = cur->suivant; free(cur); cur = tmp; }
        g->adjacence[i] = NULL;
    }
}


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("\n=== %s ===\n", titre);
}

int main() {

    printf("==============================================\n");
    printf("  AVANCE - LECON 1 : Structures de donnees\n");
    printf("==============================================\n");

    /* ---- 1. LISTE CHAÎNÉE SIMPLE ---- */
    afficher_separateur("1. Liste chainee simple");
    ListeSimple liste;
    liste_init(&liste);

    int vals_ins[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) liste_inserer_tete(&liste, vals_ins[i]);
    liste_inserer_queue(&liste, 40);
    liste_inserer_queue(&liste, 50);
    liste_afficher(&liste);

    printf("Suppression de 30 : ");
    liste_supprimer(&liste, 30);
    liste_afficher(&liste);
    liste_liberer(&liste);


    /* ---- 2. LISTE DOUBLEMENT CHAÎNÉE ---- */
    afficher_separateur("2. Liste doublement chainee");
    ListeDouble listeD;
    liste_double_init(&listeD);

    int vals_d[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) liste_double_inserer_fin(&listeD, vals_d[i]);
    liste_double_afficher(&listeD);
    liste_double_afficher_inverse(&listeD);
    liste_double_liberer(&listeD);


    /* ---- 3. PILE (STACK) ---- */
    afficher_separateur("3. Pile (Stack - LIFO)");
    Pile pile;
    pile_init(&pile);

    int vals_pile[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        pile_push(&pile, vals_pile[i]);
        printf("push(%2d) : ", vals_pile[i]);
        pile_afficher(&pile);
    }
    printf("--- Pop ---\n");
    int v;
    while (!pile_est_vide(&pile)) {
        pile_pop(&pile, &v);
        printf("pop() -> %d\n", v);
    }


    /* ---- 4. FILE (QUEUE) ---- */
    afficher_separateur("4. File (Queue - FIFO)");
    File file;
    file_init(&file);

    int vals_file[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        file_enfiler(&file, vals_file[i]);
        printf("enfiler(%d) : ", vals_file[i]);
        file_afficher(&file);
    }
    printf("--- Defiler ---\n");
    while (!file_est_vide(&file)) {
        file_defiler(&file, &v);
        printf("defiler() -> %d\n", v);
    }


    /* ---- 5. ARBRE BINAIRE DE RECHERCHE ---- */
    afficher_separateur("5. Arbre Binaire de Recherche (BST)");
    NoeudArbre *bst = NULL;
    int bst_vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) bst = bst_inserer(bst, bst_vals[i]);

    printf("Arbre visuel (droite=haut, gauche=bas) :\n");
    bst_afficher(bst, 0);

    printf("Parcours in-order (trié) : ");
    bst_inorder(bst);
    printf("\nHauteur : %d\n", bst_hauteur(bst));

    printf("Recherche 40 : %s\n", bst_rechercher(bst, 40) ? "trouve" : "absent");
    printf("Recherche 99 : %s\n", bst_rechercher(bst, 99) ? "trouve" : "absent");

    bst = bst_supprimer(bst, 30);
    printf("Apres suppression de 30 : ");
    bst_inorder(bst);
    printf("\n");
    bst_liberer(bst);


    /* ---- 6. TABLE DE HACHAGE ---- */
    afficher_separateur("6. Table de hachage");
    TableHash ht;
    hash_init(&ht);

    hash_inserer(&ht, "alice",   25);
    hash_inserer(&ht, "bob",     30);
    hash_inserer(&ht, "charlie", 22);
    hash_inserer(&ht, "diana",   28);
    hash_inserer(&ht, "eve",     35);
    hash_afficher(&ht);

    int age;
    printf("Recherche \"charlie\" : ");
    printf(hash_rechercher(&ht, "charlie", &age) ? "%d ans\n" : "non trouve\n", age);

    printf("Recherche \"inconnu\" : ");
    printf(hash_rechercher(&ht, "inconnu", &age) ? "trouve\n" : "non trouve\n");

    hash_inserer(&ht, "alice", 26);
    hash_rechercher(&ht, "alice", &age);
    printf("Mise a jour alice : %d ans\n", age);
    hash_liberer(&ht);


    /* ---- 7. GRAPHE ---- */
    afficher_separateur("7. Graphe (liste d'adjacence + BFS + DFS)");
    Graphe g;
    graphe_init(&g, 6, 0);   /* 6 sommets, non orienté */
    /*
     * Structure du graphe :
     *    0 --- 1 --- 3
     *    |           |
     *    2 --- 4 --- 5
     */
    graphe_ajouter_arete(&g, 0, 1, 1);
    graphe_ajouter_arete(&g, 0, 2, 1);
    graphe_ajouter_arete(&g, 1, 3, 1);
    graphe_ajouter_arete(&g, 2, 4, 1);
    graphe_ajouter_arete(&g, 3, 5, 1);
    graphe_ajouter_arete(&g, 4, 5, 1);
    graphe_afficher(&g);
    graphe_bfs(&g, 0);
    graphe_dfs(&g, 0);
    graphe_liberer(&g);


    printf("\n==============================================\n");
    printf("  7 structures de donnees implementees !\n");
    printf("==============================================\n\n");

    return 0;
}