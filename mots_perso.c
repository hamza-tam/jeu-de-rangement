#include "mots_perso.h"

const char delimiteurs[49] = " ,;/!?*%µ?./§²&\"(-_)=1234567890°+¹~#{[|`^@]}";

int i = 0;

char** saisie_mots() {	
	//char *mots = charger_mots_perso();
	char *mots = malloc(201*sizeof(char));

	erase();
	refresh();

	mvprintw(5, 5, "ENTREZ LES MOTS QUE VOUS SOUHAITEZ ECRIRE (CLIQUEZ SUR ENTREE POUR TERMINER)");
	refresh();

	echo();

	WINDOW *champs_conteneur = newwin(2*HAUTEUR, 5*LARGEUR, 7,5);
	WINDOW *champs = newwin(2*HAUTEUR-2, 5*LARGEUR-2, 8,6);

	curs_set(1);
	wmove(champs, 1,1);
	box(champs_conteneur, 0, 0);
	wrefresh(champs_conteneur);
	wrefresh(champs);
	leaveok(champs, FALSE);
	wgetnstr(champs, mots, 200);
	curs_set(0);

	noecho();

	char** tableau_mots = parcer(mots);

	return tableau_mots;
}

char *charger_mots_perso() {
	char *str = malloc(200*sizeof(char));

	FILE *fic = fopen("test.txt","r");
	
	fgets(str, 200, fic);

   	fclose(fic);

	return str;
}


char** parcer(char* mot){   
	char** tableau_mots_utilisateur = malloc(16*sizeof(char*));
   	char *token;
   	token = strtok(mot, delimiteurs);
	
	for (i = 0; i < 16; i++) {
		tableau_mots_utilisateur[i] = NULL;
	}

	i = 0;

  	 while( token != NULL && i < 16) {    	
			//Stoquage des mots dans un tableau
		tableau_mots_utilisateur[i]=(char*)malloc(10*sizeof(char));
		strcpy(tableau_mots_utilisateur[i],token);
		i++;
		token = strtok(NULL, delimiteurs); 
   	}

	return tableau_mots_utilisateur;
}
