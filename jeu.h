#ifndef JEU_H
#define JEU_H

#include "generateur.h"
#include "plateau.h"
#include "menu.h"
#include "administration.h"
#include "utilisateur.h"
#include "niveau.h"
#include "mots_perso.h"

static int difficulte  = FACILE;
static int nombre_mots = MOTS_5;

int jouer();
int lancer();
int niveau();
int initialiser();
int administration();
int instructions();
int mots_personnalises();

int changer_difficulte(int);
int changer_nombre_mots(int);
void recompenser_joueur(int);
void message(char*);
void acceuil();
void donner_correction(char**, plateau*);

#endif
