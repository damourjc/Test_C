/*
 * ============================================================
 *  FICHIER  : preprocesseur.c
 *  SUJET    : Le préprocesseur avancé en C
 *  NIVEAU   : Intermédiaire — Leçon 10
 *  COMPILE  : gcc -Wall -Wextra preprocesseur.c -o preprocesseur
 *  EXECUTE  : ./preprocesseur
 *
 *  Pour voir le résultat du préprocesseur AVANT compilation :
 *    gcc -E preprocesseur.c -o preprocesseur.i
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

/* ============================================================
 * PARTIE 1 — MACROS AVEC PARAMÈTRES
 *
 * Contrairement aux macros simples (#define PI 3.14),
 * les macros avec paramètres ressemblent à des fonctions
 * mais sont traitées par le préprocesseur (substitution textuelle).
 *
 * RÈGLES IMPORTANTES :
 *   1. Toujours mettre les paramètres entre parenthèses
 *   2. Toujours mettre l'expression entière entre parenthèses
 *   3. Attention aux effets de bord (ex: i++ dans une macro)
 * ============================================================ */

/* Macro simple */
#define CARRE(x)        ((x) * (x))
#define CUBE(x)         ((x) * (x) * (x))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define ABS(x)          ((x) < 0 ? -(x) : (x))
#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : (v) > (hi) ? (hi) : (v))

/* Macro de swap (échange deux valeurs) */
#define SWAP(type, a, b) do { type _tmp = (a); (a) = (b); (b) = _tmp; } while(0)

/* Macro de vérification avec retour */
#define CHECK_NULL(ptr, msg) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "ERREUR: %s\n", msg); \
            return -1; \
        } \
    } while(0)

/* ============================================================
 * PARTIE 2 — MACROS MULTI-LIGNES AVEC BACKSLASH
 *
 * Une macro peut s'étendre sur plusieurs lignes avec \.
 * Le do { ... } while(0) est le pattern recommandé pour
 * les macros à instructions multiples :
 *   - permet le point-virgule final
 *   - fonctionne dans tous les contextes if/else
 * ============================================================ */

#define LOG_INFO(msg) \
    do { \
        printf("[INFO]  %s:%d : %s\n", __FILE__, __LINE__, msg); \
    } while(0)

#define LOG_ERROR(msg) \
    do { \
        fprintf(stderr, "[ERROR] %s:%d : %s\n", \
                __FILE__, __LINE__, msg); \
    } while(0)

/* Macro d'assertion personnalisée */
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "ASSERTION ECHOUEE : %s\n" \
                            "  Fichier : %s\n" \
                            "  Ligne   : %d\n", \
                    #condition, __FILE__, __LINE__); \
        } else { \
            printf("ASSERT OK : %s\n", #condition); \
        } \
    } while(0)

/* ============================================================
 * PARTIE 3 — #undef : ANNULER UNE DÉFINITION
 *
 * #undef supprime une définition existante.
 * Permet de redéfinir une macro ou de limiter sa portée.
 * ============================================================ */

#define TAILLE_BUFFER 256

/* Usage de TAILLE_BUFFER... */

#undef TAILLE_BUFFER   /* on annule */
#define TAILLE_BUFFER 512   /* et on redéfinit avec une nouvelle valeur */

/* ============================================================
 * PARTIE 4 — #error : PROVOQUER UNE ERREUR À LA COMPILATION
 *
 * #error arrête la compilation avec un message personnalisé.
 * Très utile pour vérifier des prérequis à la compilation
 * (version du compilateur, plateforme, configuration...).
 * ============================================================ */

/* Exemple : vérifier qu'une configuration est cohérente */
/* Ces vérifications sont commentées pour permettre la compilation */

/*
#define MODE_DEBUG
#define MODE_RELEASE
#if defined(MODE_DEBUG) && defined(MODE_RELEASE)
    #error "Impossible d'activer DEBUG et RELEASE en meme temps !"
#endif
*/

/* Vérification de la taille des types */
/* #if sizeof(int) < 4
    #error "Ce programme requiert un int d'au moins 4 octets"
   #endif */

/* ============================================================
 * PARTIE 5 — MACROS PRÉDÉFINIES : __FILE__, __LINE__, etc.
 *
 * Le compilateur C fournit plusieurs macros prédéfinies :
 *   __FILE__    → nom du fichier source (chaîne)
 *   __LINE__    → numéro de la ligne courante (entier)
 *   __DATE__    → date de compilation ("Jan 01 2025")
 *   __TIME__    → heure de compilation ("12:34:56")
 *   __func__    → nom de la fonction courante (C99)
 *   __STDC__    → 1 si compilateur standard C
 * ============================================================ */

/* Macro de débogage utilisant les macros prédéfinies */
#define DEBUG_PRINT(fmt, ...) \
    printf("[DEBUG] %s:%d (%s) : " fmt "\n", \
           __FILE__, __LINE__, __func__, ##__VA_ARGS__)

/* ============================================================
 * PARTIE 6 — OPÉRATEURS # ET ## (STRINGIFICATION ET COLLAGE)
 *
 * # (stringification) : transforme un argument en chaîne
 *   STRINGIFY(hello) → "hello"
 *
 * ## (concaténation de tokens) : colle deux tokens ensemble
 *   CONCAT(var, 1) → var1
 * ============================================================ */

/* Opérateur # : stringification */
#define STRINGIFY(x)    #x
#define TO_STRING(x)    STRINGIFY(x)   /* nécessaire pour développer les macros */

/* Opérateur ## : concaténation de tokens */
#define MAKE_VAR(prefix, num)   prefix##num
#define MAKE_FUNC(name)         do_##name

/* Macro utilisant les deux opérateurs */
#define DECLARE_COMPTEUR(nom) \
    static int compteur_##nom = 0; \

#define AFFICHER_ENUM(e) printf("  " #e " = %d\n", e)

/* ============================================================
 * PARTIE 7 — COMPILATION CONDITIONNELLE
 *
 * #ifdef, #ifndef, #if, #elif, #else, #endif
 * permettent d'inclure ou d'exclure du code selon des conditions
 * évaluées à la compilation.
 * ============================================================ */

/* Activer/désactiver le mode debug */
#define MODE_DEBUG   /* commenter pour désactiver */

#ifdef MODE_DEBUG
    #define TRACE(msg) printf("[TRACE] %s\n", msg)
    #define DBG_VAL(var) printf("[DBG] " #var " = %d\n", var)
#else
    #define TRACE(msg)    /* rien en mode release */
    #define DBG_VAL(var)  /* rien en mode release */
#endif

/* Détecter la plateforme */
#if defined(_WIN32)
    #define PLATEFORME "Windows"
    #define SEP_CHEMIN '\\'
#elif defined(__APPLE__)
    #define PLATEFORME "macOS"
    #define SEP_CHEMIN '/'
#elif defined(__linux__)
    #define PLATEFORME "Linux"
    #define SEP_CHEMIN '/'
#else
    #define PLATEFORME "Inconnue"
    #define SEP_CHEMIN '/'
#endif

/* Versionning */
#define VERSION_MAJEURE 1
#define VERSION_MINEURE 2
#define VERSION_PATCH   3
#define VERSION_STR     TO_STRING(VERSION_MAJEURE) "." \
                        TO_STRING(VERSION_MINEURE) "." \
                        TO_STRING(VERSION_PATCH)

/* ============================================================
 * PROTOTYPES
 * ============================================================ */
void afficher_separateur(char *titre);
void demo_macros_parametres();
void demo_macros_multilignes();
void demo_undef();
void demo_error();
void demo_macros_predefinies();
void demo_stringification();
void demo_compilation_conditionnelle();


/* ============================================================
 * PROGRAMME PRINCIPAL
 * ============================================================ */
int main() {

    printf("==============================================\n");
    printf("  INTERMEDIAIRE - LECON 10 : Preprocesseur\n");
    printf("==============================================\n\n");

    demo_macros_parametres();
    demo_macros_multilignes();
    demo_undef();
    demo_error();
    demo_macros_predefinies();
    demo_stringification();
    demo_compilation_conditionnelle();

    printf("==============================================\n");
    printf("  Toutes les demos completees !\n");
    printf("==============================================\n\n");

    return 0;
}


/* ============================================================
 * DÉFINITIONS DES FONCTIONS DE DÉMONSTRATION
 * ============================================================ */

void afficher_separateur(char *titre) {
    printf("--- %s ---\n", titre);
}


void demo_macros_parametres() {
    afficher_separateur("1. Macros avec parametres");

    /* Macros arithmétiques */
    printf("CARRE(5)      = %d\n",  CARRE(5));
    printf("CUBE(3)       = %d\n",  CUBE(3));
    printf("MAX(7, 12)    = %d\n",  MAX(7, 12));
    printf("MIN(7, 12)    = %d\n",  MIN(7, 12));
    printf("ABS(-42)      = %d\n",  ABS(-42));
    printf("CLAMP(15,0,10)= %d\n",  CLAMP(15, 0, 10));
    printf("CLAMP(-5,0,10)= %d\n",  CLAMP(-5, 0, 10));
    printf("CLAMP(5, 0,10)= %d\n\n",CLAMP(5,  0, 10));

    /* PIÈGE : sans parenthèses, les macros peuvent donner des résultats inattendus */
    /* CARRE_MAUVAIS(x) = x * x  → CARRE_MAUVAIS(2+3) = 2+3*2+3 = 11 (faux !) */
    /* CARRE(2+3) = ((2+3)*(2+3)) = 25 (correct) */
    printf("CARRE(2+3)    = %d  (correct avec parentheses)\n\n", CARRE(2+3));

    /* SWAP */
    int a = 10, b = 20;
    printf("Avant SWAP : a=%d, b=%d\n", a, b);
    SWAP(int, a, b);
    printf("Apres SWAP : a=%d, b=%d\n\n", a, b);

    /* Effet de bord dangereux */
    int n = 5;
    printf("ATTENTION aux effets de bord !\n");
    printf("n = %d\n", n);
    /* MAX(n++, 3) → ((n++) > (3) ? (n++) : (3)) → n++ evalué DEUX fois ! */
    printf("Utiliser MAX(n, 3) sans effets de bord.\n\n");
}


void demo_macros_multilignes() {
    afficher_separateur("2. Macros multi-lignes et do-while(0)");

    /* Macros de log */
    LOG_INFO("Demarrage de l'application");
    LOG_INFO("Connexion etablie");
    LOG_ERROR("Fichier de config introuvable");

    printf("\n");

    /* Macros d'assertion */
    ASSERT(1 + 1 == 2);
    ASSERT(CARRE(4) == 16);
    ASSERT(MAX(3, 7) == 7);
    ASSERT(1 == 2);   /* volontairement faux */

    printf("\n");

    /* Pourquoi do { } while(0) est important */
    printf("do { } while(0) : permet d'utiliser la macro\n");
    printf("comme une instruction normale avec ;\n");
    printf("  if (cond) LOG_INFO(\"ok\");  ← fonctionne\n");
    printf("  else LOG_ERROR(\"ko\");      ← fonctionne\n\n");
}


void demo_undef() {
    afficher_separateur("3. #undef : annuler une definition");

    /* Utiliser la version redéfinie de TAILLE_BUFFER */
    printf("TAILLE_BUFFER = %d\n", TAILLE_BUFFER);
    printf("(undef puis redefini de 256 a %d)\n\n", TAILLE_BUFFER);

    /* Démonstration de portée locale à un bloc */
    #define CONSTANTE_LOCALE 42
    printf("CONSTANTE_LOCALE = %d\n", CONSTANTE_LOCALE);
    #undef CONSTANTE_LOCALE
    /* printf("%d", CONSTANTE_LOCALE);  ← ERREUR après undef */
    printf("CONSTANTE_LOCALE : indisponible apres #undef\n\n");

    /* Undef pour éviter les conflits */
    printf("Cas d'usage d'#undef :\n");
    printf("  1. Redefinir une macro avec une nouvelle valeur\n");
    printf("  2. Limiter la portee d'une macro\n");
    printf("  3. Eviter les conflits entre headers\n\n");
}


void demo_error() {
    afficher_separateur("4. #error : erreur a la compilation");

    printf("Les directives #error sont commentees pour\n");
    printf("permettre la compilation de ce fichier.\n\n");

    printf("Exemples d'utilisation :\n\n");

    printf("  /* Verifier configuration */\n");
    printf("  #if defined(DEBUG) && defined(RELEASE)\n");
    printf("  #  error \"DEBUG et RELEASE incompatibles\"\n");
    printf("  #endif\n\n");

    printf("  /* Verifier le compilateur */\n");
    printf("  #ifndef __STDC_VERSION__\n");
    printf("  #  error \"Compilateur C standard requis\"\n");
    printf("  #endif\n\n");

    printf("  /* Verifier la plateforme */\n");
    printf("  #if !defined(__linux__) && !defined(_WIN32)\n");
    printf("  #  error \"Plateforme non supportee\"\n");
    printf("  #endif\n\n");

    /* #warning : avertissement sans arrêt (extension GCC) */
    printf("  /* Avertissement sans erreur (GCC) */\n");
    printf("  #warning \"Cette fonctionnalite est obsolete\"\n\n");
}


void demo_macros_predefinies() {
    afficher_separateur("5. Macros predefinies");

    printf("__FILE__ = \"%s\"\n",   __FILE__);
    printf("__LINE__ = %d\n",       __LINE__);
    printf("__DATE__ = \"%s\"\n",   __DATE__);
    printf("__TIME__ = \"%s\"\n",   __TIME__);
    printf("__func__ = \"%s\"\n\n", __func__);

    /* Utilisation dans les logs de debug */
    printf("Usage dans DEBUG_PRINT :\n");
    int valeur = 42;
    DEBUG_PRINT("valeur = %d", valeur);
    DEBUG_PRINT("pi approx = %.4f", 3.1416);

    printf("\nUsage de TRACE et DBG_VAL (mode DEBUG actif) :\n");
    int x = 10;
    TRACE("entree dans la fonction");
    DBG_VAL(x);
    TRACE("sortie de la fonction");

    printf("\nVersion : %s\n", VERSION_STR);
    printf("Compile le %s a %s\n\n", __DATE__, __TIME__);
}


void demo_stringification() {
    afficher_separateur("6. Operateurs # et ##");

    /* Opérateur # : stringification */
    printf("Operateur # (stringification) :\n");
    printf("  STRINGIFY(hello)      = \"%s\"\n", STRINGIFY(hello));
    printf("  STRINGIFY(42)         = \"%s\"\n", STRINGIFY(42));
    printf("  STRINGIFY(1 + 2)      = \"%s\"\n", STRINGIFY(1 + 2));

    /* Important : # stringifie AVANT l'expansion des macros */
    /* TO_STRING développe d'abord la macro puis stringify */
    printf("  TO_STRING(VERSION_MAJEURE) = \"%s\"\n\n",
           TO_STRING(VERSION_MAJEURE));

    /* Opérateur ## : concaténation de tokens */
    printf("Operateur ## (concatenation de tokens) :\n");

    /* Crée des variables var1, var2, var3 */
    int MAKE_VAR(var, 1) = 10;
    int MAKE_VAR(var, 2) = 20;
    int MAKE_VAR(var, 3) = 30;
    /* Équivalent à : int var1 = 10; int var2 = 20; int var3 = 30; */

    printf("  var1 = %d, var2 = %d, var3 = %d\n", var1, var2, var3);
    printf("  (crees par MAKE_VAR(var, 1/2/3))\n\n");

    /* Macro AFFICHER_ENUM : stringifie le nom de la constante */
    printf("AFFICHER_ENUM pour des constantes :\n");
    enum { VALEUR_A = 1, VALEUR_B = 42, VALEUR_C = 100 };
    AFFICHER_ENUM(VALEUR_A);
    AFFICHER_ENUM(VALEUR_B);
    AFFICHER_ENUM(VALEUR_C);

    printf("\n");
}


void demo_compilation_conditionnelle() {
    afficher_separateur("7. Compilation conditionnelle");

    /* Plateforme détectée */
    printf("Plateforme detectee : %s\n", PLATEFORME);
    printf("Separateur de chemin : '%c'\n\n", SEP_CHEMIN);

    /* Mode debug */
    #ifdef MODE_DEBUG
    printf("Mode DEBUG actif :\n");
    printf("  Les macros TRACE et DBG_VAL produisent du code.\n");
    printf("  Desactiver en commentant #define MODE_DEBUG\n");
    #else
    printf("Mode RELEASE :\n");
    printf("  TRACE et DBG_VAL sont des macros vides.\n");
    printf("  Zero overhead en production.\n");
    #endif

    printf("\n");

    /* Versionning conditionnel */
    printf("Version : %s\n", VERSION_STR);

    #if VERSION_MAJEURE >= 1
    printf("Version majeure >= 1 : fonctionnalites completes\n");
    #endif

    #if VERSION_MINEURE == 0
    printf("Version mineure 0 : premiere release\n");
    #else
    printf("Version mineure %d : mise a jour\n", VERSION_MINEURE);
    #endif

    printf("\n");

    /* Exemple de code conditionnel par plateforme */
    printf("Code specifique a la plateforme :\n");
    #if defined(__linux__)
    printf("  → Sur Linux : utiliser syscall, epoll...\n");
    #elif defined(_WIN32)
    printf("  → Sur Windows : utiliser WinAPI, IOCP...\n");
    #elif defined(__APPLE__)
    printf("  → Sur macOS : utiliser kqueue...\n");
    #else
    printf("  → Plateforme inconnue : code generique\n");
    #endif

    printf("\n");

    /* Récapitulatif des directives */
    printf("Directives de compilation conditionnelle :\n");
    printf("  #ifdef MACRO      → si MACRO est definie\n");
    printf("  #ifndef MACRO     → si MACRO n'est PAS definie\n");
    printf("  #if expr          → si expression vraie\n");
    printf("  #elif expr        → sinon si expression vraie\n");
    printf("  #else             → sinon\n");
    printf("  #endif            → fin du bloc conditionnel\n");
    printf("  #defined(MACRO)   → test dans #if\n\n");
}