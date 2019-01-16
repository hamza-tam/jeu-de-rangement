#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "constantes.h"
#include "utilisateur.h"

typedef struct _option {
	char *nom;
	int nbr_choix;
	char **choix;
	int actif;
} option;

typedef struct _menu {
	int nbr_entrees;
	int nbr_options;
	char **modes;
	WINDOW **modes_win;
	option *options;
} menu;

menu* initialiser_menu();
menu* afficher_menu(menu*);
int reporter_case_menu(menu*, MEVENT*);

void menu_initialiser_joueur(Utilisateur*);
void afficher_menu_haut();
Utilisateur* menu_actualiser_score(int);
int menu_retourner_niveau();
Utilisateur* menu_actualiser_niveau(int);

#endif
