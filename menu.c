#include "menu.h"

static Utilisateur *u = NULL;

menu* initialiser_menu() {
	int i,j;
	// Creation d'un menu:
	menu *m;
	m = malloc(sizeof(menu));

	m->nbr_entrees = 5;
	m->nbr_options = 2;

	// Creation des modes du menu:
	m->modes = (char**)malloc(m->nbr_entrees*sizeof(char*));

	m->modes[0] = (char*)malloc(10*sizeof(char));
	m->modes[1] = (char*)malloc(10*sizeof(char));
	m->modes[2] = (char*)malloc(10*sizeof(char));
	m->modes[3] = (char*)malloc(10*sizeof(char));
	m->modes[4] = (char*)malloc(10*sizeof(char));
	
	strcpy(m->modes[0], "ENTRAINEMENT");
	strcpy(m->modes[1], "PARCOURS");
	strcpy(m->modes[2], "INSTRUCTIONS");
	strcpy(m->modes[3], "MOTS PERSONNALISES");
	strcpy(m->modes[4], "QUITTER");
	
	// Initialisation des options du jeu:
	m->options = malloc(m->nbr_options * sizeof(option));
		// Creation de l'option nombre de mots:
	m->options[0].nom       = "Nombre de mots";
	m->options[0].nbr_choix = 4;
	m->options[0].actif     = 0;

		// Creation de l'option difficulte:
	m->options[1].nom       = "  Difficulte  ";
	m->options[1].nbr_choix = 2;
	m->options[1].actif     = 0;

	for (i = 0; i < m->nbr_options; i++) {
		m->options[i].choix = malloc(m->options[i].nbr_choix * sizeof(char*));
		for (j = 0; j < m->options[i].nbr_choix; j++) {
			m->options[i].choix[j] = malloc(MAX_CHAR*sizeof(char));
		}
	}

		// Nommination des options de nombre de mots:
	strcpy(m->options[0].choix[0], " 5 MOTS");
	strcpy(m->options[0].choix[1], " 8 MOTS");
	strcpy(m->options[0].choix[2], "12 MOTS");
	strcpy(m->options[0].choix[3], "16 MOTS");
		// Nommination des options de difficulte::
	strcpy(m->options[1].choix[0], "FACILE");
	strcpy(m->options[1].choix[1], "DIFFICILE");
	
	// Iniialisation des cases du menu:
	m->modes_win = malloc(m->nbr_entrees*sizeof(WINDOW*));

	for (i = 0; i < m->nbr_entrees; i++) {
		j = i - ((m->nbr_entrees/2) + 1);
		m->modes_win[i] = newwin(HAUTEUR,LARGEUR + 5,posY + HAUTEUR*j, posX/2-LARGEUR/2);
	}

	return m;
}

menu *afficher_menu(menu *m) {
	int i,j;

	// Affichage des entrees du menu:
	for (i = 0; i < m->nbr_entrees; i++) {
		box(m->modes_win[i], 0, 0);
		mvwprintw(m->modes_win[i], 1, 1, m->modes[i]);
		wrefresh(m->modes_win[i]);
	}

	refresh();

	WINDOW *option_win;

	// On recupere la hauteur des options:
	int hauteur = 0;
	char ch;
	for (i = 0; i < m->nbr_options; i++) {
		hauteur += m->options[i].nbr_choix;
	}

	// On initialise la position ou on va le mettre:
	hauteur = (LINES - hauteur*HAUTEUR)/2;
	

	// affichage des options:
		// affichage de l'option nombre de mots
	for (i = 0; i < m->nbr_options; i++) {
			option_win = newwin(HAUTEUR*(m->options[i].nbr_choix),LARGEUR_OPTION,hauteur,3*posX/2-LARGEUR_OPTION/2);
			box(option_win, 0,0);
			mvwprintw(option_win, 0,1, "[ %s ]",m->options[i].nom);
			
			for (j = 0; j < m->options[i].nbr_choix; j++) {
				if (m->options[i].actif == j) ch = '*';
				else ch = ' ';
				mvwprintw(option_win, 2 + (HAUTEUR-1)*j, 1, "[%c] %s", ch, m->options[i].choix[j]);
			}
			
			wrefresh(option_win);
			delwin(option_win);

			hauteur += HAUTEUR*m->options[i].nbr_choix + 1;
	} 

	return m;
}

int reporter_case_menu(menu *m, MEVENT *e) {
    int i,j;

	// Detecter le click sur une case du menu:
    if ((e->x >= posX/2 - LARGEUR/2) && (e->x <= posX/2 + LARGEUR/2)) {
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

// FONCTION QUI AFFICHE LE MENU HAUT:
void afficher_menu_haut() {
	WINDOW *menu_haut = newwin(5, COLS, 0 , 0);

	mvwprintw(menu_haut, 1,1, "JOUEUR : %s", u->pseudo);
	mvwprintw(menu_haut, 2,1, "SCORE  : %i", u->score);
	mvwprintw(menu_haut, 3,1, "NIVEAU : %i", u->niveau);

	box(menu_haut, 0, 0);
	wrefresh(menu_haut);

	delwin(menu_haut);
}

// FONCTION QUI PERMET D'INITIALISER LE JOUEUR:
void menu_initialiser_joueur(Utilisateur *joueur) {
	u = joueur;
}

// FONCTION QUI PERMET D'ACTUALISER LE SCORE DU JOUEUR:
Utilisateur* menu_actualiser_score(int nouveau_score) {
	u->score += nouveau_score;

	return u;
}

// FONCTION QUI NOUS PERMET DE RECUPERER LE NIVEAU DU JOUEUR
int menu_retourner_niveau() {
	return u->niveau;
}

// FONCTION QUI MET A JOUR LE NIVEAU DU JOUEUR:
Utilisateur* menu_actualiser_niveau(int n) {
	if (n > u->niveau) u->niveau = n;

	return u;
}
