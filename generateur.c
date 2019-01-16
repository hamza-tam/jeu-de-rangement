#include "generateur.h"

int* tableau_repetitions = NULL;
int taille_tableau=0;
int indice_courant=0;

int verifier_r(int r){
	int i;
	// 0 : r existe
	// 1 : r n'existe pas
	
	if(tableau_repetitions==NULL){	    
		tableau_repetitions=(int*)malloc(taille_tableau*sizeof(int));			
		tableau_repetitions[indice_courant] = r;
		return 1;
	}
	
	else  {
		
		for(i=0; i< indice_courant; i++) {
			if ( tableau_repetitions[i]==r) return 0;
		}
		indice_courant++;
		tableau_repetitions[indice_courant] = r;
		return 1;
	}

	
			
}

char** generer_mots ( int nombre_mots, int difficulte ) {
	
	taille_tableau = nombre_mots;

    FILE *fic = fopen(DICTIONNAIRE,"rb");	

    char mot[10];
   
	int i,j,r,p;
	
	char** tableau_mots;
	tableau_mots=(char**)malloc(nombre_mots*sizeof(char*));

	srand(time(0));

	for(i=0 ; i< nombre_mots ; i++) {
        tableau_mots[i]=(char*)malloc(10*sizeof(char));
    }
	
	if(difficulte==FACILE){
		for(i=0 ; i< nombre_mots ; i++) {
			//fseek( fic, 0, SEEK_SET );
			
			do{
	        r=rand()%26;
			p=rand()%10;		        
	       
	        r*=10;
	        r+=p;
	    	} while (verifier_r(r) == 0);

			fseek(fic, r*10*sizeof(char), SEEK_SET);
			fread(mot, 10*sizeof(char), 1, fic);
				
/*
	        while(r>=0){
	        	fgets(mot,10,fic);
	        	r--;
			}
*/
			
			if(mot!=NULL){
	        	strcpy(tableau_mots[i],mot);
	        }
	        else printf("Erreur de lecture d'un mot");
	    }
	}
	
	else if(difficulte==DIFFICILE){
		for(i=0 ,j=0 ; j< nombre_mots/2 ; j++) {

					//fseek( fic, 0, SEEK_SET );
					
			        r=rand()%26;
			        p=rand()%10;
				if (r == 25) p = rand()%8;
			        r*=10; 
			        r+=p;
			        
					/*while(r>=0){
			        	fgets(mot,10,fic);
			        	r--;
					}*/

				fseek(fic, r*10*sizeof(char), SEEK_SET);
				fread(mot, 10*sizeof(char), 1, fic);
					
				if(mot!=NULL){
			        	strcpy(tableau_mots[i],mot);
			        	i++;
				}
			        
			        
			        fread(mot,10*sizeof(char), 1, fic);
			        if(mot!=NULL){
			        	strcpy(tableau_mots[i],mot);
			        	i++;
				}
			        
		}
		if((nombre_mots%2)!=0) {
			        fread(mot,10*sizeof(char), 1, fic);
			        if(mot!=NULL){
			        	strcpy(tableau_mots[i],mot);
			        	i++;
				}
			        
		}
		
	    }
	
	
    fclose(fic);

    return tableau_mots;
}
