# MAKEFILE POUR LA COMPILATION DU JEU DE RANGEMENT

# Les drapeaux de compilation:
FLAGS = -lncurses -g
GDB   = -g

# Les regles de compilation:
jeu : jeu.o plateau.o menu.o generateur.o utilisateur.o niveau.o administration.o mots_perso.o
	gcc $(GDB) jeu.o plateau.o menu.o generateur.o utilisateur.o niveau.o administration.o mots_perso.o -o jeu $(FLAGS)

plateau.o : plateau.c plateau.h constantes.h
	gcc -c plateau.c -o plateau.o $(FLAGS)

jeu.o : plateau.h menu.h constantes.h generateur.h utilisateur.h niveau.h jeu.h administration.h mots_perso.h jeu.c
	gcc -c jeu.c -o jeu.o $(FLAGS)

menu.o : menu.h menu.c constantes.h utilisateur.h
	gcc -c menu.c -o menu.o $(FLAGS)

generateur.o : generateur.c generateur.h constantes.h
	gcc -c generateur.c -o generateur.o $(FLAGS)

utilisateur.o : utilisateur.h utilisateur.c constantes.h
	gcc -c utilisateur.c -o utilisateur.o $(FLAGS)

niveau.o : constantes.h niveau.h niveau.c utilisateur.h jeu.h
	gcc -c niveau.c -o niveau.o $(FLAGS)

administration.o : administration.h administration.c menu.h
	gcc -c administration.c -o administration.o $(FLAGS)

mots_perso.o : mots_perso.c mots_perso.h constantes.h
	gcc -c mots_perso.c -o mots_perso.o $(FLAGS)

#correcteur.o : correcteur.c correcteur.h constantes.h
#	gcc -c correcteur.c -o correcteur.o $(FLAGS)

# commande pour le nettoyage du projet
clean : 
	rm -f *.o
