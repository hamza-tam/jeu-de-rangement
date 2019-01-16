#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifndef CONSTANTES_H
#define CONSTANTES_H

// LE NOM DU FICHIER
#define FICHIERJOUEURS 		"joueurs.jdr"
#define DICTIONNAIRE		"dict.jdr"

// LES CONSTANTES DU JEU
#define HAUTEUR 	3
#define LARGEUR 	21
#define LARGEUR_OPTION	20
#define RETOUR		-3
#define CORRECTION 	-4
#define TEMPS		120

// LES TYPES D'UTILISATEURS
#define JOUEUR	0
#define ADMIN	1

// LES ENTREES DU MENU
#define JOUER   	0
#define NIVEAU		1
#define INSTRUCTIONS	2
#define MOTS_PERSO	3
#define QUITTER 	4

// NOMBRE DE MOTS:
#define MOTS_5	  5
#define MOTS_8	  8
#define MOTS_12	  12
#define MOTS_16   16

// NIVEAUX DE DIFFICULTE:
#define FACILE		1
#define DIFFICILE	2

// LES NIVEAU DE JEU:
#define A_DEBLOQUE	-2
#define NIVEAU_1	1
#define NIVEAU_2	2
#define NIVEAU_3	3
#define NIVEAU_4	4
#define NIVEAU_5	5
#define NIVEAU_6	6
#define NIVEAU_7	7
#define NIVEAU_8	8

// LES CONSTANTES D'OPTIONS
#define OPTION_MOT		100
#define OPTION_DIFFICULTE	200

#define OPTION_5		1
#define OPTION_8		2
#define OPTION_12		3
#define OPTION_16		4

// CONSTANTES POUR LE PROGRAMM
#define MAX_CHAR    10
#define TAILLE_BLOC 5
#define NBR_NIVEAUX 8

// DONNEES DE L'ADMINSTRATEUR
#define ADMIN_PSEUDO	"admin"
#define ADMIN_MDP	"admin"

// LES ENTREES DU MENU D'ADMINISTRATION
#define ADMIN_JOUEUR		0
#define ADMIN_REINITIALISER	1
#define ADMIN_QUITTER		2

// VARIABLES DE POSITION
int posX;
int posY;

#endif // CONSTANTES_H
