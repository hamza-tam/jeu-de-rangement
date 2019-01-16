#include "administration.h"

menu* initialiser_menu_administration() {
	int i,j;
	// Creation d'un menu:
	menu *m;
	m = malloc(sizeof(menu));

	m->nbr_entrees = 3;
	m->nbr_options = 0;

	// Creation des modes du menu:
	m->modes = (char**)malloc(m->nbr_entrees*sizeof(char*));

	m->modes[0] = (char*)malloc(10*sizeof(char));
	m->modes[1] = (char*)malloc(10*sizeof(char));
	m->modes[2] = (char*)malloc(10*sizeof(char));

	strcpy(m->modes[0], "JOUEURS");
	strcpy(m->modes[1], "REINITIALISER");
	strcpy(m->modes[2], "QUITTER");
	
	// Iniialisation des cases du menu:
	m->modes_win = malloc(m->nbr_entrees*sizeof(WINDOW*));

	for (i = 0; i < m->nbr_entrees; i++) {
		j = i - ((m->nbr_entrees/2) + 1);
		m->modes_win[i] = newwin(HAUTEUR,LARGEUR,posY + HAUTEUR*j, posX/2-LARGEUR/2);
	}

	return m;
}

menu *afficher_menu_administration(menu *m) {
	int i,j;

	// Affichage des entrees du menu:
	for (i = 0; i < m->nbr_entrees; i++) {
		box(m->modes_win[i], 0, 0);
		mvwprintw(m->modes_win[i], 1, 1, m->modes[i]);
		wrefresh(m->modes_win[i]);
	}

	refresh();

	return m;
}

int reporter_case_menu_administration(menu *m, MEVENT *e) {
    int i,j;

	// Detecter le click sur une case du menu:
    if ((e->x >= posX/2 - LARGEUR/2) && (e->x < posX/2 + LARGEUR/2)) {
        for (i = 0; i < m->nbr_entrees; i++) {
	    j = i - ((m->nbr_entrees/2) + 1);
            if ((e->y >= posY + HAUTEUR*j)&& (e->y < posY + HAUTEUR*j + HAUTEUR)) {
                return i;
            }
        }
    }

	// Detecter le click sur une option:
		// initialiser les donnees:
	int hauteur = 0;
	char ch;
	for (i = 0; i < m->nbr_options; i++) {
		hauteur += m->options[i].nbr_choix;
	}
	hauteur = (LINES - hauteur*HAUTEUR)/2;

		// detecter l'option choisie:
	if ( (e->x >= 3*posX/2 - LARGEUR_OPTION/2) && (e->x < 3*posX/2 + LARGEUR_OPTION/2) ) {
		for (i = 0; i < m->nbr_options; i++) {
			for (j = 0; j < m->options[i].nbr_choix; j++) {
				if (e->y == hauteur + 2 + (HAUTEUR-1)*j) {
					m->options[i].actif = j;
					return (i+1)*100+(j+1);
				}
			}
			hauteur += HAUTEUR*m->options[i].nbr_choix + 1;
		}
	}

	//option_win = newwin(HAUTEUR*(m->options[i].nbr_choix),LARGEUR_OPTION,hauteur,3*posX/2-LARGEUR_OPTION/2);
	return -1;
}
