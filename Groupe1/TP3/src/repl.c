#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char version[] = "1.0.0";


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

int main()
{
    int continuer = 1; // Variable pour contrôler la boucle principale

    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer)
    {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];

        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        // Traite la commande en fonction de son contenu
        if (strcmp(commande, "quit") == 0 || strcmp(commande, "quitter") == 0)
        {
            // Quitte le programme si la commande est "quit"
            continuer = exe_quit();
        }
        else if (strncmp(commande, "echo ", 5) == 0 ||strncmp(commande, "afficher ", 5) == 0)
        {
            // Traite la commande "echo" pour afficher du texte
            show_echo(commande); 
        }
        else if(strcmp(commande, "date") == 0)
        {
            //traite la commande date
            show_date();
        }
        else if(strcmp(commande, "version") == 0)
        {
            //traite la commande version
            show_version();
        }   
        else if(strcmp(commande, "help") == 0)
        {
            //traite la commande version
            show_help();
        }   
        else if(strcmp(commande, "aide") == 0)
        {
            //traite la commande version
            show_aide();
        }  
        else
        {
            // Affiche un message d'erreur si la commande est inconnue
            printf("Commande non reconnue. Essayez 'echo <text>' pour afficher du texte, 'date' pour afficher la date ou tapez 'quit' pour quitter.\n");
        }

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}


