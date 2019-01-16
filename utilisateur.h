#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include "constantes.h"

static int pos_utilisateur;

typedef struct _utilisateur {
	char pseudo[MAX_CHAR];
	char mdp[MAX_CHAR];
	int niveau;
	int score;
} Utilisateur;

typedef struct _noeud {
	Utilisateur *u;
	struct _noeud *suivant;
} noeud;

Utilisateur *creer_utilisateur(char*, char*);
Utilisateur *utilisateur_connexion();

void afficher_choix_utilisateur();
int reporter_choix_utilisateur(MEVENT*);
void mettre_a_jour_utilisateur();
void afficher_joueurs();

noeud* ajouter_noeud(noeud*, Utilisateur*);
void afficher_noeud(noeud*, int);

void reinitialiser_joueurs();

#endif
