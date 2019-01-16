#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INCLUSION DES FICHIER ENTETE:
#include "jeu.h"


int main (int argc, char *argv[]) {
	int i;
	char **tableau_mots;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	// Initialisation des variables de position:
	posX = COLS / 2;
	posY = LINES / 2;

	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);

	mousemask(ALL_MOUSE_EVENTS, NULL);

	printw("F1 to exit");
	refresh();

	/*tableau_mots = malloc(difficulte*sizeof(char*));
	
	for (i = 0; i < difficulte; i++) {
		tableau_mots[i] = malloc(20*sizeof(char));
		strcpy(tableau_mots[i], "test");
	}*/

	/*
	tableau_mots = generer_mots(3, FACILE);
	
	for (i = 0; i < 3; i++) {
		printf("%s", tableau_mots[i]);
	}
	*/

	initialiser();

	//mots_personnalises();

	//lancer();

	//jouer();
	
	/*
	nombre_mots = BEAUCOUP;
	difficulte  = FACILE;	

	tableau_mots = generer_mots(nombre_mots, difficulte);

	for (i = 0; i < nombre_mots; i++) {
		printf("%s \n", tableau_mots[i]);
	}
	*/
	
	endwin();

	return 0;
}


// FONCTION QUI GERE LA PARTIE DE JEU:
int jouer(char** tab) {
	plateau p;
	MEVENT e;
	int press, est_correct;
	int temps = 0;

	char **tableau_mots;

	if (tab == NULL) tableau_mots = generer_mots(nombre_mots, difficulte);
	else { tableau_mots = tab; }
	
	p = initialiser_plateau(nombre_mots, tableau_mots);

	do {
		erase();
		refresh();

		press = 0;

		p = afficher_plateau(p);
		refresh();
		// Lecture d'un evenement:
		mvprintw(0, COLS/2 - 9,  "TEMPS RESTANT : %2i", TEMPS - temps);
		refresh();
		timeout(1000);
		press = getch();
		// Incrementation du temps:
		temps++;


		if (temps == TEMPS) {
			p = vider_plateau(p);
			message("TEMPS ECOULE !");
			timeout(-1);
			return -1;
		}
		
		if (press == KEY_MOUSE) {
			if (getmouse(&e) == OK) {
				if (e.bstate & BUTTON1_CLICKED) {
					p.curseur = reporter_case(p, e);
					if ( p.curseur == CORRECTION ) {
						timeout(-1);
						donner_correction(tableau_mots, &p);
						p = vider_plateau(p);
						return -1;
					}
					if ( p.curseur == -2 ) {
						p = incrementer_parties(p);
						est_correct = corriger_plateau(p);
						if (est_correct == 1) {
							recompenser_joueur(p.parties);
							p = vider_plateau(p);
							timeout(-1);
							return 0;
						} else {
							message("ERRONE");
						}
						p.curseur = -1;
					} else if (p.curseur == -3) {
						press = KEY_F(1);
						p.curseur = -1;
						p = vider_plateau(p);
						timeout(-1);
						return -1;
					} else {
						p = selectionner_mot(p);
						p.curseur = -1;
					} 
				}
			}
			continue;
		}
		
		switch (press) {
			case KEY_RIGHT : p = deplacer_box(p, nombre_mots); break;
			case KEY_LEFT  : p = deplacer_box(p,(-1)*nombre_mots); break;
			case KEY_UP    : p = deplacer_box(p,-1); break;
			case KEY_DOWN  : p = deplacer_box(p, 1); break;
			case SELECTION : p = selectionner_mot(p); break;
		} 
		refresh();
	} while (press != KEY_F(1));

	timeout(-1);	
	p = vider_plateau(p);

	return 0;
}

// FONCTION QUI GERE LE MENU:
int lancer() {
	menu *m;
	MEVENT e;
	int ch;
	int choix;
	m = initialiser_menu();

	do {
		erase();
		refresh();

		afficher_menu_haut();

		m = afficher_menu(m);
		
		ch = getch();
		
		if (ch == KEY_MOUSE) {
			if (getmouse(&e) == OK) {
				if (e.bstate & BUTTON1_CLICKED) {
					choix = reporter_case_menu(m, &e);
					erase();
					refresh();
					switch (choix) {
						// Les entrees du menu:
						case JOUER        : jouer(NULL);          break;
						case QUITTER      : ch = KEY_F(1);        break;
						case NIVEAU       : niveau();             break;
						case INSTRUCTIONS : instructions();       break;
						case MOTS_PERSO   : mots_personnalises(); break;

						// Les options de jeu:
						case OPTION_DIFFICULTE+FACILE    : difficulte = FACILE;
											break;
						case OPTION_DIFFICULTE+DIFFICILE : difficulte = DIFFICILE;
											break;

						case OPTION_MOT+OPTION_5  : nombre_mots = MOTS_5;
											break;
						case OPTION_MOT+OPTION_8  : nombre_mots = MOTS_8;
											break;
						case OPTION_MOT+OPTION_12 : nombre_mots = MOTS_12;
											break;
						case OPTION_MOT+OPTION_16 : nombre_mots = MOTS_16;
											break;
					}
				}
			} continue;
		}
		
	} while (ch != KEY_F(1));
}

// LA FONCTION QUI GERE LES STATISTIQUES DES JOUEURS
int niveau() {
	int ch;
	MEVENT e;
	int niveau;

	do {
		if (ch = KEY_MOUSE) {
			if (getmouse(&e) == OK) {
				if (e.bstate & BUTTON1_CLICKED) {
					niveau = reporter_niveau(&e);
					if (niveau == RETOUR) {
						ch = KEY_F(1);
						continue;
					} else if (niveau == A_DEBLOQUE) {
						message("A DEBLOQUER");
					} else if (niveau != -1) {
						message("CHARGEMENT");
						niveau = generer_niveau(niveau);
					}
				}
			}
		}		

		afficher_menu_niveau();

		ch = getch();
	} while(ch != KEY_F(1));

	return 0;
}

// LA FONCTION QUI INITIALISE LES PARAMETRES DU JEU
int initialiser() {
	int ch;
	int choix_u = -1;
	MEVENT e;
	Utilisateur *u = NULL;

	acceuil();

	do {
		refresh();

		afficher_choix_utilisateur();
	
		ch = getch();
		if (ch = KEY_MOUSE) {
			if (getmouse(&e) == OK) {
				if (e.bstate & BUTTON1_CLICKED) {
					choix_u = reporter_choix_utilisateur(&e);
					switch (choix_u) {
						case JOUEUR: 
							u = utilisateur_connexion(FALSE); 
							menu_initialiser_joueur(u);
							lancer();
							break;
						case ADMIN : 
							u = utilisateur_connexion(TRUE);
							administration();
							break;
					}
				}
			}	
		}

	} while(ch != KEY_F(1) && choix_u == -1);
}

// LA FONCTION QUI GERE LA PARTIE ADMIN
int administration() {
	int ch, choix;
	MEVENT e;

	erase();
	refresh();
	message("ADMINISTRATION");

	do {
		erase();
		refresh();
		
		menu* m = initialiser_menu_administration();
		afficher_menu_administration(m);

		ch = getch();
		
		if (ch == KEY_MOUSE) {
			if (getmouse(&e) == OK) {
				if (e.bstate & BUTTON1_CLICKED) {
					choix = reporter_case_menu_administration(m, &e);
					erase();
					refresh();
					switch (choix) {
						// Les entrees du menu:
						case ADMIN_JOUEUR        : afficher_joueurs();      break;
						case ADMIN_REINITIALISER : reinitialiser_joueurs(); break;
						case ADMIN_QUITTER       : ch = KEY_F(1);           break;
					}
				}
			} continue;
		}

	} while (ch != KEY_F(1));
}

// LA FONCTION QUI PERMET DE CHANGER LA DIFFICULTE:
int changer_difficulte(int nouvelle_difficulte) {
	difficulte = nouvelle_difficulte;

	return 0;
}

int changer_nombre_mots(int nouveau_nombre_mots) {
	nombre_mots = nouveau_nombre_mots;

	return 0;
}

void recompenser_joueur(int coeff) {
	Utilisateur *u;

	erase();
	refresh();
	
	message("CORRECT");

	u = menu_actualiser_score( ( nombre_mots * difficulte * 100 ) / coeff);
	mettre_a_jour_utilisateur(u);
}

void message(char *m) {
	erase();	
	refresh();

	WINDOW *message = newwin(HAUTEUR, LARGEUR, posY-HAUTEUR/2, posX-LARGEUR/2);
	box(message, 0, 0);
	mvwprintw(message, 1,1, m);
	wrefresh(message);
	sleep(1);
	delwin(message);
}

// FONCTION QUI PERMET D'AFFICHER LES INSTRUCTIONS:
int instructions() {
	// Texte des instruction:
	char *texte = "Dans ce jeu, vous devrez ordoner les mots par ordre alphabetique.\n Pour ce faire, vous deverez selectionner un premier mot, puis selectionner un second pour\n le permutter avec.\n\n\n Appuyez sur n'importe quelle touche pour sortir";
	
	// Vidage de l'ecran:
	erase();
	refresh();

	// Affichage d'une fenetre a l'ecran:
	WINDOW *fenetre = newwin(LINES - 2, COLS - 2, 1, 1);

	mvwprintw(fenetre, 2,1, texte);
	box(fenetre, 0,0);
	mvwprintw(fenetre, 0, (COLS-2)/2 - 8, "[ INSTRUCTIONS ]");
	
	wrefresh(fenetre);
	delwin(fenetre);

	getch();

	return 0;
}

int mots_personnalises() {
	// Demande de saisie des mots:
	char** mots = saisie_mots();
	int* choisi;
	
	int i = 0, taille, k, j;

	erase();
	refresh();

	while (mots[i] != NULL) {
		i++;
	}
	
	taille = i;

	if (taille < nombre_mots) {
		message("INSUFFISANT");
		return -1;
	}

	char** tableau_genere = malloc(nombre_mots*sizeof(char*));
	choisi = malloc(nombre_mots*sizeof(int));

	do {
		for (i = 0; i < nombre_mots; i++) {
			tableau_genere[i] = malloc(10*sizeof(char));
			k = rand()%taille;
			for (j = 0; j < taille; j++) {
				if (choisi[j] == k) { k = rand()%taille; j = 0; }
			}
			choisi[i] = k;
			tableau_genere[i] = mots[k];
		}
		
		k = jouer(tableau_genere);
	} while (k > -1);

	erase();
	refresh();
	
	return 0;
}

// FONCTION POUR MONTRER LE LOGO DU JEU:
void acceuil() {
	erase();
	refresh();
	move(LINES/2 - 2, (COLS-102)/2);
	addstr("   __  _____  _____    ____   _____    _____  _____  _____  _____  _____  _____  _____  _____  _____  \n");
	move(LINES/2 - 1, (COLS-102)/2);
	addstr(" __|  ||   __||  |  |  |    \\ |   __|  | __  ||  _  ||   | ||   __||   __||     ||   __||   | ||_   _|\n");
	move(LINES/2 - 0, (COLS-102)/2);
	addstr("|  |  ||   __||  |  |  |  |  ||   __|  |    -||     || | | ||  |  ||   __|| | | ||   __|| | | |  | |  \n");	
	move(LINES/2 +1, (COLS-102)/2);
	addstr("|_____||_____||_____|  |____/ |_____|  |__|__||__|__||_|___||_____||_____||_|_|_||_____||_|___|  |_|  \n");
	refresh();	
	sleep(2);
	
	erase();
	refresh();
}

// LA FONCTION QUI DONNE LA CORRECTION D'UN PLATEAU:
void donner_correction(char** tableau_mots, plateau* p) {
	int i, k = 0, j;
	int X,Y;
	char** tableau_trie = malloc(2 * nombre_mots * sizeof(char*));

	for (i = 0; i < nombre_mots; i++) {
		tableau_trie[k] = malloc(10*sizeof(char));
		j = k;
		while( j > 0 && strcmp(tableau_trie[j-1], tableau_mots[i]) > 0 ) {
			strcpy(tableau_trie[j], tableau_trie[j-1]);
			j--;
		}
		strcpy(tableau_trie[j], tableau_mots[i]);
		k++;
	}

	for (i = 0; i < nombre_mots; i++) {
		tableau_trie[nombre_mots+i] = malloc(10*sizeof(char));
		strcpy(tableau_trie[i+nombre_mots], p->mots[i]);
	}

	erase();
	refresh();

	/*
	X = COLS/2; - LARGEUR/2;
	for (i = 0; i < nombre_mots; i++) {
		Y = LINES/2 - (nombre_mots*HAUTEUR)/2 + HAUTEUR*i;
	}
	*/

	X = COLS/2-LARGEUR;
	Y = LINES/2 - (HAUTEUR * (2+nombre_mots/2));	
	mvprintw(Y,X, "CORRECTION");

	X = COLS/2+1;
	Y = LINES/2 - (HAUTEUR * (2+nombre_mots/2));	
	mvprintw(Y,X, "VOTRE REPONSE");
	
	for (i = 0; i < 2; i++) {
		X = COLS/2 - LARGEUR + ((LARGEUR+1) * i);
		for (j = 0; j < nombre_mots; j++) {
			Y = LINES/2 + (HAUTEUR * (j - 1 - (nombre_mots / 2)));
			mvprintw(Y, X, tableau_trie[j+(nombre_mots*i)]);
		}
	}
	
	X = COLS/2 - 28;
	Y += HAUTEUR;
	mvprintw(Y,X,"APPUYEZ SUR N'IMPORTE QUELLE TOUCHE POUR SORTIR");
	refresh();

	getch();
} 
