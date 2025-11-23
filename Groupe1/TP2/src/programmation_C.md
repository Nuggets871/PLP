# Programmation en C

## Débogage avec GDB

GDB est un programme qui sert à trouver des erreurs dans un programme en C. On peut lancer le programme dans GDB, mettre des points d’arrêt et exécuter le code pas à pas. Par exemple on peut utiliser les commandes `run`, `break`, `next` et `print` pour voir les valeurs des variables pendant l’exécution

## Chaîne de compilation avec gcc

Gcc est le compilateur que nous avons utilisé pour transformer un fichier `.c` en programme exécutable. Par exemple on peut utiliser `gcc fichier.c -o fichier` pour créer un binaire. On peut aussi ajouter des options comme `-Wall` pour afficher plus d’avertissements et corriger plus facilement les erreurs dans le code

## Manipulation de chaînes de caractères

En C, une chaîne de caractères est un tableau de `char` terminé par `\0`. On peut utiliser `printf` pour afficher une chaîne et `scanf` ou `fgets` pour lire une chaîne au clavier. La bibliothèque `<string.h>` fournit des fonctions utiles comme `strlen` pour la longueur et `strcpy` pour copier une chaîne dans une autre

## Structures et recherche dans les fichiers

Les structures (`struct`) permettent de regrouper plusieurs champs dans un même type, par exemple pour représenter un étudiant avec son nom, son prénom et ses notes. C’est pratique pour organiser les données. On peut aussi lire et écrire des informations dans des fichiers avec `fopen`, `fgets`, `fprintf` et `fclose`, ce qui permet de sauvegarder des phrases ou des données et de les rechercher plus tard

## Conclusion

Avec ces exercices, j’ai vu comment déboguer un programme avec GDB, comment compiler un programme en C avec gcc, comment travailler avec des chaînes de caractères et comment utiliser des structures et des fichiers pour gérer des données. J’avais déjà un peu vu tout ça en BUT informatique, mais il ne me restait que de légers souvenirs.
