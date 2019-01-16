#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "constantes.h"

// DEFINITION DES TOUCHES DE JEU:
#define SELECTION 's'

// DEFINITION DE LA STRUCTURE PLATEAU:
typedef struct plateau {
	int    nombre_mots;
	char   *mots[32];
	int    curseur;
	int    selectionne;
	int    parties;
	WINDOW **win;
	WINDOW *select;
	WINDOW *valider;
	WINDOW *quitter;
	WINDOW *corriger_bouton;
	int    *correction;
} plateau;

// PROTOTYPES DES FONCTIONS:

plateau initialiser_plateau(int, char**);
plateau actualiser_box(plateau);
plateau deplacer_box(plateau, int);
plateau afficher_plateau(plateau);
plateau selectionner_mot(plateau);
plateau permuter(plateau, int, int);
plateau vider_plateau(plateau);
plateau ecrire_mots(plateau);
plateau incrementer_parties();
//plateau corriger_plateau(plateau, char**);

char *generer_vide();
int reporter_case(plateau, MEVENT);
int corriger_plateau(plateau);

#endif
