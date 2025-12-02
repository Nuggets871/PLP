#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char version[] = "1.0.0";


int equals_ignore_case(const char *a, const char *b)
{
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return (*a == '\0' && *b == '\0');
}

int starts_with_ignore_case(const char *str, const char *prefix)
{
    size_t i = 0;
    while (prefix[i] != '\0') {
        if (str[i] == '\0') return 0;
        if (tolower((unsigned char)str[i]) != tolower((unsigned char)prefix[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

int min3(int a, int b, int c)
{
    int m = (a < b) ? a : b;
    return (m < c) ? m : c;
}

int levenshtein(const char *s1, const char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    int dp[len1 + 1][len2 + 1];

    for (size_t i = 0; i <= len1; i++) dp[i][0] = (int)i;
    for (size_t j = 0; j <= len2; j++) dp[0][j] = (int)j;

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (tolower((unsigned char)s1[i - 1]) ==
                        tolower((unsigned char)s2[j - 1])) ? 0 : 1;
            dp[i][j] = min3(
                dp[i - 1][j] + 1,        // suppression
                dp[i][j - 1] + 1,        // insertion
                dp[i - 1][j - 1] + cost  // substitution
            );
        }
    }
    return dp[len1][len2];
}

const char *known_commands[] = {
    "help", "aide",
    "echo", "afficher",
    "version",
    "date",
    "quit", "quitter"
};

int known_count = sizeof(known_commands) / sizeof(known_commands[0]);

const char *suggest_command(const char *input)
{
    int best_dist = 999;
    const char *best_name = NULL;

    for (int i = 0; i < known_count; i++) {
        int d = levenshtein(input, known_commands[i]);
        if (d < best_dist) {
            best_dist = d;
            best_name = known_commands[i];
        }
    }

    if (best_dist <= 2) {
        return best_name;
    }
    return NULL;
}


void show_version(void)
{
    printf("Version de l'interpreteur de commande: %s\n", version);
}

void show_help(void)
{
    printf(
        "help : montre toutes les commandes disponibles\n"
        "echo : affiche du texte\n"
        "version : affiche la version actuelle de l'interpréteur de commande\n"
        "date : affiche la date actuelle\n"
        "quit : quitte l'interpréteur de commande\n"
    );
}

void show_aide(void)
{
    printf(
        "aide : montre toutes les commandes disponibles\n"
        "afficher : affiche du texte\n"
        "version : affiche la version actuelle de l'interpréteur de commande\n"
        "date : affiche la date actuelle\n"
        "quitter : quitte l'interpréteur de commande\n"
    );
}

void show_echo(char commande[1024])
{
    int first_space = 1;
    for (int i = 0; commande[i] != '\0'; i++) {
        char c = commande[i];
        if (i == 0) {
            c = (char)toupper((unsigned char)c);
        }
        if (c == ' ' && first_space) {
            printf(": ");
            first_space = 0;
            continue;
        }
        printf("%c", c);
    }

    printf("\n");
}

void show_date(void)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("date: %d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int exe_quit(void)
{
    printf("Arrêt...\n");
    return 0;
}


typedef int  (*cmd_int_noarg_t)(void);
typedef void (*cmd_void_noarg_t)(void);
typedef void (*cmd_void_str_t)(char *);

typedef enum {
    CMD_INT_NOARG,
    CMD_VOID_NOARG,
    CMD_VOID_STR
} cmd_type_t;

typedef struct {
    const char *name;
    cmd_type_t  type;
    union {
        cmd_int_noarg_t   int_noarg;
        cmd_void_noarg_t  void_noarg;
        cmd_void_str_t    void_str;
    } func;
} command_t;

command_t commands[] = {
    { "quit", CMD_INT_NOARG,  .func.int_noarg  = exe_quit  },
    { "version", CMD_VOID_NOARG, .func.void_noarg = show_version },
    { "date", CMD_VOID_NOARG, .func.void_noarg = show_date },
    { "help", CMD_VOID_NOARG, .func.void_noarg = show_help },
    { "echo", CMD_VOID_STR,   .func.void_str   = show_echo },
};


/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

int main(void)
{
    int continuer = 1;

    while (continuer)
    {
        printf("> ");

        char commande[1024];

        if (fgets(commande, sizeof(commande), stdin) == NULL) {
            break;
        }

        commande[strcspn(commande, "\n")] = 0;

        if (equals_ignore_case(commande, "quit") ||
            equals_ignore_case(commande, "quitter"))
        {
            continuer = exe_quit();
        }
        else if (starts_with_ignore_case(commande, "echo ") ||
                 starts_with_ignore_case(commande, "afficher "))
        {
            show_echo(commande);
        }
        else if (equals_ignore_case(commande, "date"))
        {
            show_date();
        }
        else if (equals_ignore_case(commande, "version"))
        {
            show_version();
        }
        else if (equals_ignore_case(commande, "help"))
        {
            show_help();
        }
        else if (equals_ignore_case(commande, "aide"))
        {
            show_aide();
        }
        else
        {
            const char *suggest = suggest_command(commande);

            if (suggest != NULL) {
                printf(
                    "Commande non reconnue: \"%s\".\n"
                    "Suggestion: avez-vous voulu taper \"%s\" ?\n",
                    commande, suggest
                );
            } else {
                printf(
                    "Commande non reconnue: \"%s\".\n"
                    "Commandes disponibles (FR/EN) : help/aide, echo/afficher, "
                    "version, date, quit/quitter.\n",
                    commande
                );
            }
        }

        printf("\n");
    }

    return 0;
}


