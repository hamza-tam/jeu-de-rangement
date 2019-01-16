#include "niveau.h"

static int hauteur;
static int largeur;
static int centrer;

void afficher_menu_niveau() {
	// Initialiser l'ecran:
	erase();
	refresh();

	// Initialisation des variables:
	hauteur = posY;
	largeur = posX;
	centrer = (largeur - 24) / 2 ;

	// DECLARATION DES VARIABLES:
	int i, niveau_joueur = menu_retourner_niveau();

	// Initialisation de la fenetre:
	WINDOW *menu = newwin(hauteur, largeur, (int)(posY/2), (int)(posX/2));
	box(menu, 0,0);
	mvwprintw(menu, 0, centrer, "[ Choisissez le niveau ]");
	wrefresh(menu);

	WINDOW *niveaux[NBR_NIVEAUX];

	for (i = 0; i < NBR_NIVEAUX; i++) {
		niveaux[i] = newwin(3,5,posY/2 + 2, posX/2 + 2 + 5 * i);
		if (niveau_joueur < i + 1) wborder(niveaux[i], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		else box(niveaux[i],0,0);
		mvwprintw(niveaux[i], 1,2, "%i", i+1);
		wrefresh(niveaux[i]);

		delwin(niveaux[i]);
	}

	WINDOW *quitter = newwin(HAUTEUR, LARGEUR, 3*posY/2 - HAUTEUR - 1, 3*posX/2 - LARGEUR - 2);
	box(quitter, 0, 0);
	mvwprintw(quitter, 1, 1, "RETOUR");
	wrefresh(quitter);
	delwin(quitter);

	delwin(menu);
}

int reporter_niveau(MEVENT *e) {
	int i, niveau_joueur = menu_retourner_niveau();

	if ( (e->y >= posY/2 + 2) && (e->y < posY/2 + 2+3) ) {
		for (i = 0; i < NBR_NIVEAUX; i++) {
			if ( (e->x >= posX/2 + 2 + 5*i) && (e->x < posX/2 + 2 + 5*(i+1)) ) {
				if (niveau_joueur < i +1) return -2;
				return i+1;
			}
		}
	}
	
	WINDOW *quitter = newwin(HAUTEUR, LARGEUR, 3*posY/2 - 2*HAUTEUR , 3*posX/2 - LARGEUR + 2);
	if ( (e->y >= 3*posY/2 - HAUTEUR - 1) && (e->y < 3*posY/2 - 1) ) {
		if ( (e->x >= 3*posX/2 - LARGEUR - 2) && (e->x < 3*posX/2 - 2) ) {
			return RETOUR;
		}
	}

	return -1;
}

int generer_niveau(int niveau) {
	int ret;
	Utilisateur *u;

	switch(niveau) {
		case NIVEAU_1:
			changer_difficulte(FACILE);
			changer_nombre_mots(MOTS_5);
			if ( jouer(NULL) > -1 ) {
				u = menu_actualiser_niveau(NIVEAU_2);
			}
			mettre_a_jour_utilisateur(u);
			break;

		case NIVEAU_2:
			changer_difficulte(DIFFICILE);
			changer_nombre_mots(MOTS_5);
			if ( jouer(NULL) > -1 ) {
				u = menu_actualiser_niveau(NIVEAU_3);
			}
			mettre_a_jour_utilisateur(u);
			break;

		case NIVEAU_3:
			changer_difficulte(FACILE);
			changer_nombre_mots(MOTS_8);
			if ( jouer(NULL) > -1 ) {
				u = menu_actualiser_niveau(NIVEAU_4);
			}
			mettre_a_jour_utilisateur(u);
			break;

		case NIVEAU_4:
			changer_difficulte(DIFFICILE);
			changer_nombre_mots(MOTS_8);
			if ( jouer(NULL) > -1 ) {
				u = menu_actualiser_niveau(NIVEAU_5);
			}
			mettre_a_jour_utilisateur(u);
			break;

		case NIVEAU_5:
			changer_difficulte(FACILE);
			changer_nombre_mots(MOTS_12);
			if ( jouer(NULL) > -1 ) {
				u = menu_actualiser_niveau(NIVEAU_6);
			}
			mettre_a_jour_utilisateur(u);
			break;

		case NIVEAU_6:
			changer_difficulte(DIFFICILE);
			changer_nombre_mots(MOTS_12);
			if ( jouer(NULL) > -1 ) {
				u = menu_actualiser_niveau(NIVEAU_7);
			}
			mettre_a_jour_utilisateur(u);
			break;
		
		case NIVEAU_7:
			changer_difficulte(FACILE);
			changer_nombre_mots(MOTS_16);
			if ( jouer(NULL) > -1 ) {
				u = menu_actualiser_niveau(NIVEAU_8);
			}
			mettre_a_jour_utilisateur(u);
			break;
		
		case NIVEAU_8:
			changer_difficulte(DIFFICILE);
			changer_nombre_mots(MOTS_16);
			jouer(NULL);
			break;
	}

	return 0;
}
