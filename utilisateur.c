#include "utilisateur.h"


Utilisateur* creer_joueur(char *nom, char *mdp) {
	Utilisateur *u = malloc(sizeof(Utilisateur));
	int trouve = FALSE;

	FILE *f = fopen(FICHIERJOUEURS, "rb");

	pos_utilisateur = -1;

	while ( trouve == FALSE && fread(u, sizeof(Utilisateur), 1, f) ) {

		pos_utilisateur++;

		if (strcmp(u->pseudo, nom) == 0) {
			if (strcmp(u->mdp, mdp) == 0) trouve = TRUE;
		 	else {		
				erase();	
				refresh();
		
				WINDOW *message = newwin(HAUTEUR, LARGEUR+7, posY-HAUTEUR/2, posX-(LARGEUR+10)/2);
				box(message, 0, 0);
				mvwprintw(message, 1,1, " DONNEES INCORRECTES");
				wrefresh(message);
				sleep(1);
				delwin(message);

				return utilisateur_connexion();
			}
		}
	}
	
	fclose(f);

	WINDOW *message = newwin(3,21,posY-1,posX-10);
	
	if (trouve == FALSE) {
		pos_utilisateur++;
		u = malloc(sizeof(Utilisateur));
		strcpy(u->pseudo, nom);
		strcpy(u->mdp, mdp);
		u->niveau = NIVEAU_1;
		u->score = 0;
		
		mvwprintw(message, 1,4,"Joueur cree !");
		
		f = fopen(FICHIERJOUEURS, "ab");
		fwrite(u, sizeof(Utilisateur), 1, f);
		fclose(f);
	} else {
		mvwprintw(message, 1,3,"Joueur trouve !");
	}

	box(message, 0,0);
	erase();
	refresh();
	wrefresh(message);
	sleep(1);

	delwin(message);

	return u;
}

void afficher_choix_utilisateur() {	
	// Affichage des boutons de choix:
	WINDOW *admin, *joueur; 

	admin = newwin(HAUTEUR, LARGEUR, posY-1, posX-LARGEUR);
	joueur = newwin(HAUTEUR, LARGEUR, posY-1, posX+1);

	mvwprintw(admin, 1, 1, " ADMIN");
	mvwprintw(joueur, 1, 1, " JOUEUR");

	box(admin, 0, 0);
	box(joueur, 0, 0);

	wrefresh(admin);
	wrefresh(joueur);
}

Utilisateur* utilisateur_connexion(int est_admin) {
	int admin_connecte = TRUE;
	char nom[10], mdp[10];
	
	do {
		// Reinitialisation de l'ecran:
		erase();

	// Affichage des labels :
	mvprintw(posY-1, posX-7, "PSEUDO : ");
	mvprintw(posY+1, posX-13, "MOT DE PASSE : ");
	echo();

	refresh();

	// Attente d'entree des donnees:
	curs_set(1);
	move(posY-1, posX+2);
	getnstr(nom, 9);
	move(posY+1, posX+2);
	getnstr(mdp, 9);
	noecho();
	curs_set(0);

	if (est_admin == TRUE) {
		if (strcmp(nom, ADMIN_PSEUDO) == 0 && strcmp(mdp, ADMIN_MDP) == 0) 
			return NULL;
		else admin_connecte = FALSE;
	}

	} while (admin_connecte == FALSE);

	return creer_joueur(nom, mdp);
}

// FONCTION QUI DONNE LE CLICK DE L'UTILISATEUR:
int reporter_choix_utilisateur(MEVENT* e) {
	// Recuperation du bouton clique:
	if ((e->y >= posY-1) && (e->y <= posY-1+HAUTEUR)) {
		if ((e->x >= posX-LARGEUR) && (e->x <= posX-1)) {
			return ADMIN;
		} else if ((e->x >= posX+1) && (e->x <= posX+LARGEUR)) {
			return JOUEUR;
		}
	}
	
	return -1;
}

// FONCTION QUI SAUVEGARDE LES NOUVELLES DONNEES DE L'UTILISATEUR
void mettre_a_jour_utilisateur(Utilisateur *u) {
	FILE *f = fopen(FICHIERJOUEURS, "r+b");

	fseek(f, pos_utilisateur * sizeof(Utilisateur), SEEK_SET);
	fwrite(u, sizeof(Utilisateur), 1, f);

	fclose(f);	
}

// LA FONCTION QUI GERE LE LISTING DES JOUEURS
void afficher_joueurs() {
	// Chargement des utilisateurs:
	noeud *n;
	Utilisateur *u = malloc(sizeof(Utilisateur));

	FILE *f = fopen(FICHIERJOUEURS, "rb");
	while(fread(u, sizeof(Utilisateur),1,f)) {
		n = ajouter_noeud(n,u);
	}

	fclose(f);
	
	// Affichage des utilisateurs:
	WINDOW *tableau = newwin(HAUTEUR, LARGEUR*3, posY/4,  COLS/2 - (3*LARGEUR)/2);
	box(tableau, 0,0);
	mvwprintw(tableau, 1, 2, "     NOM      ");
	mvwprintw(tableau, 1, LARGEUR, "|");
	mvwprintw(tableau, 1, LARGEUR+2, "   NIVEAU");
	mvwprintw(tableau, 1, 2*LARGEUR, "|");
	mvwprintw(tableau, 1, 2*LARGEUR+2, "   SCORE");
	wrefresh(tableau);
	delwin(tableau);

	afficher_noeud(n,1);

	getch();
}

noeud* ajouter_noeud(noeud* n, Utilisateur* u) {
	noeud *nouveau_n = malloc(sizeof(noeud));

	nouveau_n->suivant = n;

	nouveau_n->u = malloc(sizeof(Utilisateur));
	strcpy(nouveau_n->u->pseudo, u->pseudo);
	strcpy(nouveau_n->u->mdp, u->mdp);
	nouveau_n->u->score  = u->score;
	nouveau_n->u->niveau = u->niveau;

	return nouveau_n;
}

// FONCTION D'AFFICHAGE DE CHAQUE NOEUD:
void afficher_noeud(noeud* n, int indice) {
	if (n != NULL) {
		WINDOW *ligne = newwin(HAUTEUR, LARGEUR*3, posY/4 + (HAUTEUR-1)*indice,  COLS/2-(3*LARGEUR)/2);
		box(ligne, 0,0);
		mvwprintw(ligne, 1, 2, n->u->pseudo);
		mvwprintw(ligne, 1, LARGEUR, "|");
		mvwprintw(ligne, 1, LARGEUR+2, " %i", n->u->niveau);
		mvwprintw(ligne, 1, 2*LARGEUR, "|");
		mvwprintw(ligne, 1, 2*LARGEUR+2, " %i", n->u->score);
		wrefresh(ligne);
		delwin(ligne);

		afficher_noeud(n->suivant, ++indice);	
	}
}

// FONCTION POUR REINITIALISER TOUT LES JOUEURS:
void reinitialiser_joueurs() {
	FILE *f = fopen(FICHIERJOUEURS, "w");
	fclose(f);
	
	erase();	
	refresh();

	WINDOW *message = newwin(HAUTEUR, LARGEUR+2, posY-HAUTEUR/2, posX-LARGEUR/2);
	box(message, 0, 0);
	mvwprintw(message, 1,1, "REINITIALISATION");
	wrefresh(message);
	sleep(1);
	delwin(message);
}
