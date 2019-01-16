#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INCLUSION DU FICHIER D'ENTETE:
#include "plateau.h"

static int X,Y;

// INITIALISATION DES VARAIBLES DU PLATEAU DE JEU:
plateau initialiser_plateau (int nombre_mots, char **tableau_mots) {
	plateau p;
	int i = 0, j = 0;

	// Initialisation du plateau:
	p.nombre_mots = nombre_mots;
	p.curseur     = 0;
	p.selectionne = -1;
	p.parties     = 0;
	for (i = 0; i < 32; i++) {
		p.mots[i] = NULL;
	}
	//p.mots        = malloc(2*nombre_mots*sizeof(char*));
	p.select      = newwin(HAUTEUR, LARGEUR, 0, 0);

	box(p.select, 0, 0);


	// Chargement des mots:
	for (i = 0; i < nombre_mots; i++) {
		p.mots[i]             = malloc(20*sizeof(char));
		p.mots[i+nombre_mots] = malloc(20*sizeof(char));

		strcpy(p.mots[i+nombre_mots], tableau_mots[i]);
		strcpy(p.mots[i], "(vide)");
	}

	// Initialisation des cases:
	p.win = malloc(2 * nombre_mots * sizeof(WINDOW*));

	for (i = 0; i < 2; i++) {
		X = posX - LARGEUR - 1 + ((LARGEUR+1) * i);
		for (j = 0; j < nombre_mots; j++) {
			Y = posY + (HAUTEUR * (j - 1 - (p.nombre_mots / 2)));
			p.win[j+(nombre_mots*i)] = newwin(HAUTEUR, LARGEUR, Y, X);
		}
	}

	// Ecriture des mots:
	p = ecrire_mots(p);

	// Affichage du bouton valider:
	p.valider = newwin(HAUTEUR, LARGEUR, Y+HAUTEUR, X-LARGEUR-1);
	mvwprintw(p.valider, 1,1, "VALIDER");

	// Affichage du bouton quitter:
	p.quitter = newwin(HAUTEUR, LARGEUR, Y+HAUTEUR, X);
	mvwprintw(p.quitter, 1,1,"QUITTER");

	// Affichage du bouton quitter:
	p.corriger_bouton = newwin(HAUTEUR, 2*LARGEUR+1, Y+2*HAUTEUR, X-LARGEUR-1);
	mvwprintw(p.corriger_bouton, 1,1,"CORRECTION");
	
	// Initialisation du tableau de verification de correction:
	p.correction = malloc(2*p.nombre_mots*sizeof(int));	

	// p = actualiser_box(p);

	return p;
}

/*
// GESTION DU BOX DE SELECTION:
plateau actualiser_box(plateau p) {
	int i, j,
	    posX = 10,
	    posY = 3;
	i = p.selectionne / 3;
	j = p.selectionne % 3;

	mvwin(p.select, posY + (HAUTEUR*j), posX + (20*i));
	mvwprintw(p.select, 1, 1 , "        ");
	mvwprintw(p.select, 1, 1, p.mots[p.selectionne]);

	return p;
}*/

// DEPLACEMENT DU CURSEUR DE SELECTION:
plateau deplacer_box(plateau p, int dep) {
	if ((p.curseur + dep > -1) && (p.curseur + dep < 2*p.nombre_mots)) {
		p.curseur = p.curseur + dep;
		//wborder(p.select)
	}

	//p = actualiser_box(p);

	return p;
}

// GENERER UN CHAINE VIDE POUR INITIALISER LES CASES:
char *generer_vide() {
	char *vide;

	vide = malloc((LARGEUR - 2) * sizeof(char));

	int i;
	for (i = 0; i < LARGEUR - 2; i++)
		vide[i] = ' ';

	return vide;
}

// ECRIRE LES MOTS DANS LES CASES:
plateau ecrire_mots(plateau p) {
	int i;
	char *vide = generer_vide();

	for (i = 0; i < 2*p.nombre_mots; i++) {
		mvwprintw(p.win[i], 1, 1, vide);
		mvwprintw(p.win[i], 1, 1, p.mots[i]);
	}

	return p;
}

//SELECTIONNER UN MOT DU PLATEAU:
plateau selectionner_mot(plateau p) {
	// Si rien n'est selectionne:
	if (p.curseur == -1) {
		p.selectionne = -1;
		return p;
	}
	// On annule la selection si le mot selectionné est deja selectionné
	else if (p.selectionne == p.curseur) {
		p.selectionne = -1;
	} else if (p.selectionne != -1) {
		p = permuter(p, p.curseur, p.selectionne);
		p = ecrire_mots(p);
		p.selectionne = -1;
	} else {
		p.selectionne = p.curseur;
	}

	/*
	int k = p.selectionne / 3;
	int l = p.selectionne % 3;
	mvwin(p.win[mot], posY+((HAUTEUR+1)*l)-1, posX + (20*k-1));
	*/
	box(p.win[p.curseur], 0, 0);

	return p;
}

// AFFICHAGE DU PLATEAU:
plateau afficher_plateau(plateau p) {
	int i, x, y;

	Y = posY - (HAUTEUR * (p.nombre_mots/2)) - HAUTEUR - 2;
	X = posX - LARGEUR - 1;
	mvprintw(Y,X, "     [ REPONSE ]");
	mvprintw(Y,posX, "   [ MOTS A TRIER ]");
	
	for (i = 0; i < 2*p.nombre_mots; i++) {
		if ( i == p.curseur || i== p.selectionne) {
			box(p.win[i], 0, 0);
		} else if(i != p.selectionne) {
			wborder(p.win[i], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		}
		wrefresh(p.win[i]);
	}

	box(p.valider, 0,0);
	box(p.quitter, 0,0);
	box(p.corriger_bouton, 0,0);
	wrefresh(p.corriger_bouton);
	wrefresh(p.quitter);
	wrefresh(p.valider);

	return p;
}

// PERMUTATION DES MOTS:
plateau permuter(plateau p, int mot1, int mot2) {
	char *tampon;

	tampon = p.mots[mot1];
	p.mots[mot1] = p.mots[mot2];
	p.mots[mot2] = tampon;

	return p;
}

// LIBERATION DE LA MEMOIRE:
plateau vider_plateau(plateau p) {
	int i;

	for (i = 0; i < 2*p.nombre_mots; i++) {
		delwin(p.win[i]);
	}

	free(p.win);
	delwin(p.select);
	delwin(p.quitter);
	delwin(p.valider);	

	return p;
}

// DETECTER QUELLE CASE A ETE CLIQUEE:
int reporter_case(plateau p, MEVENT e) {
	int i,j;

	for (i = 0; i < 2; i++) {
		X = posX - LARGEUR - 1 + (12 * i);
		if ((e.x >= X) && (e.x < X + LARGEUR)) {
			for (j = 0; j < p.nombre_mots; j++) {
				Y = posY + (HAUTEUR * (j - 1 - (p.nombre_mots / 2)));
				if ((e.y >= Y)
					&& (e.y <= Y+HAUTEUR)) {
					return j + (p.nombre_mots*i);
				}
			}
		}

			//p.win[j+(nombre_mots*i)] = newwin(HAUTEUR, LARGEUR, posY + ((HAUTEUR+1)*j), posX + (20*i));
	}

	X = COLS/2;

	// Detecter le click sur valider
	if ((e.x >= X-LARGEUR-1) && (e.x <= X-1)) {
		if ( (e.y >= Y+HAUTEUR) && (e.y < Y+2*HAUTEUR) ) {
			return -2;
		}
	}

	// detecter le click sur quitter
	if ((e.x >= X+1) && (e.x < X+1+LARGEUR)) {
		if ( (e.y >= Y+HAUTEUR) && (e.y < Y+2*HAUTEUR) ) {
			return -3;
		}
	}

	// Detecter le click sur corriger:
	if ( (e.x >= X-LARGEUR - 1) && (e.x < X+LARGEUR+1) ) {
		if ( (e.y >= Y+2*HAUTEUR) && (e.y < Y+3*HAUTEUR) ) {
			return -4;
		}
	}
	p.corriger_bouton = newwin(HAUTEUR, 2*LARGEUR+1, Y+2*HAUTEUR, X-LARGEUR-1);

	return -1;
}

// CORRECTION DES ENTREES DU JOUEUR:
int corriger_plateau(plateau p) {
	int i;

	for (i = 0; i < p.nombre_mots; i++) 
		if (strcmp(p.mots[i], "(vide)") == 0) return 0;

	for (i = 0; i < p.nombre_mots - 1; i++) 
		if (strcmp(p.mots[i], p.mots[i+1]) > 0) return 0;

	return 1;
}

// FONCTION POUR INCREMENTER LE NOMBRE DE PARTIES JOUEE:
plateau incrementer_parties(plateau p) {
	p.parties++;
	
	return p;
}
