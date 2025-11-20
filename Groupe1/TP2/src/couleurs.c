#include <stdio.h>
#include <stdbool.h>

struct color {
    int R;
    int G;
    int B;
    float A;
};

struct color colors[100] = {
    // C1 — 8 fois
    {255, 0, 0, 1.0},{255, 0, 0, 1.0},{255, 0, 0, 1.0},{255, 0, 0, 1.0},
    {255, 0, 0, 1.0},{255, 0, 0, 1.0},{255, 0, 0, 1.0},{255, 0, 0, 1.0},

    // C2 — 7 fois
    {200, 0, 0, 1.0},{200, 0, 0, 1.0},{200, 0, 0, 1.0},{200, 0, 0, 1.0},
    {200, 0, 0, 1.0},{200, 0, 0, 1.0},{200, 0, 0, 1.0},

    // C3 — 9 fois
    {0, 255, 0, 1.0},{0, 255, 0, 1.0},{0, 255, 0, 1.0},{0, 255, 0, 1.0},
    {0, 255, 0, 1.0},{0, 255, 0, 1.0},{0, 255, 0, 1.0},{0, 255, 0, 1.0},
    {0, 255, 0, 1.0},

    // C4 — 5 fois
    {0, 200, 0, 1.0},{0, 200, 0, 1.0},{0, 200, 0, 1.0},{0, 200, 0, 1.0},
    {0, 200, 0, 1.0},

    // C5 — 6 fois
    {0, 0, 255, 1.0},{0, 0, 255, 1.0},{0, 0, 255, 1.0},
    {0, 0, 255, 1.0},{0, 0, 255, 1.0},{0, 0, 255, 1.0},

    // C6 — 4 fois
    {0, 0, 200, 1.0},{0, 0, 200, 1.0},{0, 0, 200, 1.0},{0, 0, 200, 1.0},

    // C7 — 10 fois
    {255, 255, 0, 1.0},{255, 255, 0, 1.0},{255, 255, 0, 1.0},{255, 255, 0, 1.0},
    {255, 255, 0, 1.0},{255, 255, 0, 1.0},{255, 255, 0, 1.0},{255, 255, 0, 1.0},
    {255, 255, 0, 1.0},{255, 255, 0, 1.0},

    // C8 — 3 fois
    {200, 200, 0, 1.0},{200, 200, 0, 1.0},{200, 200, 0, 1.0},

    // C9 — 12 fois
    {255, 165, 0, 1.0},{255, 165, 0, 1.0},{255, 165, 0, 1.0},{255, 165, 0, 1.0},
    {255, 165, 0, 1.0},{255, 165, 0, 1.0},{255, 165, 0, 1.0},{255, 165, 0, 1.0},
    {255, 165, 0, 1.0},{255, 165, 0, 1.0},{255, 165, 0, 1.0},{255, 165, 0, 1.0},

    // C10 — 2 fois
    {200, 130, 0, 1.0},{200, 130, 0, 1.0},

    // C11 — 11 fois
    {255, 0, 255, 1.0},{255, 0, 255, 1.0},{255, 0, 255, 1.0},{255, 0, 255, 1.0},
    {255, 0, 255, 1.0},{255, 0, 255, 1.0},{255, 0, 255, 1.0},{255, 0, 255, 1.0},
    {255, 0, 255, 1.0},{255, 0, 255, 1.0},{255, 0, 255, 1.0},

    // C12 — 6 fois
    {200, 0, 200, 1.0},{200, 0, 200, 1.0},{200, 0, 200, 1.0},
    {200, 0, 200, 1.0},{200, 0, 200, 1.0},{200, 0, 200, 1.0},

    // C13 — 9 fois
    {0, 255, 255, 1.0},{0, 255, 255, 1.0},{0, 255, 255, 1.0},{0, 255, 255, 1.0},
    {0, 255, 255, 1.0},{0, 255, 255, 1.0},{0, 255, 255, 1.0},{0, 255, 255, 1.0},
    {0, 255, 255, 1.0},

    // C14 — 4 fois
    {0, 200, 200, 1.0},{0, 200, 200, 1.0},{0, 200, 200, 1.0},{0, 200, 200, 1.0},

    // C15 — 4 fois
    {128, 128, 128, 1.0},{128, 128, 128, 1.0},{128, 128, 128, 1.0},{128, 128, 128, 1.0}
};

bool colors_equal(struct color c1, struct color c2) {
    return c1.R == c2.R && c1.G == c2.G && c1.B == c2.B && c1.A == c2.A;
}

int main() {
    // on va maintenant compter le nombre d'occurence de chaque couleur differente
    // pour se faire je vais créer un tableau comme en python avec les dictionnaires
    struct color_occurence_object { // structure similaire au dictionnaire avec couleur:nb_occurence
        struct color color;
        int nb_occurence;
    };

	struct color_occurence_object color_occurence_list[100] = {0}; // liste d'occurence de couleurs
	int indexColorOccurenceList = 0; // pour gerer l'ajout dans le tableau

	// on boucle sur toutes les couleurs
    for (int ii = 0; ii < 100; ii++) {
        // on va d'abord regarder si la couleur est deja dans notre liste d'occurence de couleur

		bool isPresentInList = false;
		for (int jj = 0; jj < indexColorOccurenceList; jj++) {
			if (colors_equal(colors[ii], color_occurence_list[jj].color)) {
				// s'il est present on met le flag a true et on incrémente l'occurence
				isPresentInList = true;
				color_occurence_list[jj].nb_occurence++;
			}
		}
		// si la couleur n'est pas presente alors on l'ajoute
		if (!isPresentInList) {
			color_occurence_list[indexColorOccurenceList].color = colors[ii];
			color_occurence_list[indexColorOccurenceList].nb_occurence = 1;
			indexColorOccurenceList++;
		}
    }

	printf("Voici les couleurs et leur nombre d'occurence : \n");
	for (int kk = 0; kk < indexColorOccurenceList; kk++) {
		printf("Couleur N°%d : rgba: %d/%d/%d/%.2f -> %d fois\n", kk+1,
	 color_occurence_list[kk].color.R,
	 color_occurence_list[kk].color.G,
	 color_occurence_list[kk].color.B,
	 color_occurence_list[kk].color.A,
	 color_occurence_list[kk].nb_occurence);
	}

	return 0;
}