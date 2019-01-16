#include <stdio.h>
#include <stdlib.h>

int main () {

    char mots[260][10] = {
"achat",
"alarme",
"alphabet",
"an",
"ange",
"animal",
"annee",
"arbre",
"argent",
"aussi",
"banane",
"bande",
"baleine",
"barbre",
"bateau",
"beau",
"boisson",
"bol",
"bonheur",
"bonjour",
"cahier",
"camion",
"canard",
"cent",
"chaise",
"chat",
"chatte",
"cheval",
"chevre",
"chien",
"dame",
"damier",
"dauphin",
"dessin",
"dessiner",
"dinde",
"disque",
"docteur",
"dos",
"dossier",
"ecrire",
"ecriture",
"elephant",
"eleve",
"enfant",
"enigme",
"epaisseur",
"episode",
"epee",
"epaule",
"facteur",
"facture",
"farine",
"ferme",
"fermier",
"fleur",
"fauteuil",
"frais",
"fraise",
"fraisier",
"gadien",
"garage",
"garcon",
"garde",
"gare",
"general",
"gentil",
"girafe",
"gorge",
"gomme",
"habille",
"habile",
"habitat",
"harpe",
"hibou",
"harry",
"histoire",
"hero",
"homme",
"hopital",
"ideal",
"idee",
"identique",
"ile",
"image",
"imaginer",
"infirmier",
"infini",
"institut",
"instant",
"jardin",
"jaune",
"jeux",
"jour",
"journee",
"journal",
"jumeau",
"jumelle",
"jupe",
"jeudi",
"kaki",
"kangourou",
"kilo",
"kermes",
"karma",
"karate",
"kholle",
"klaxon",
"kippa",
"karaoke",
"lac",
"lapin",
"lame",
"lampe",
"larme",
"lime",
"lion",
"lionne",
"livre",
"livret",
"maison",
"mal",
"maman",
"mandarine",
"mangue",
"medicament",
"mille",
"moins",
"mois",
"mouton", 
"nom",
"nez",
"nocture",
"nausee",
"naitre",
"naissance",
"narite",
"nefaste",
"normal",
"norme",
"ordinaire",
"orange",
"osature",
"oiseau",
"ossement",
"osculter",
"ordonner",
"obscure",
"objet",
"oser",
"page",
"papa",
"patte",
"pois",
"pomme",
"pommier",
"porte",
"poussin",
"poule",
"poisson",
"quatre",
"quart",
"quartier",
"question",
"quiche",
"quitter",
"quinze",
"quitter",
"quiche",
"quotidien",
"racine",
"radio",
"radis",
"ranger",
"rat",
"requin",
"rond",
"rose",
"roue",
"rouge",
"salade",
"salle",
"salon",
"scorpion",
"semaine",
"serpent",
"serviette",
"soleil",
"somme",
"souris",
"tarte",
"taride",
"tartine",
"terrain",
"terrasse",
"terre",
"toit",
"tortus",
"touche",
"tracteur",
"un",
"une",
"union",
"unique",
"unisson",
"unir",
"urne",
"usine",
"utile",
"utiliser",
"vacance",
"vache",
"vague",
"vendre",
"vent",
"ver",
"verre",
"vert",
"vide",
"ville",
"wagon",
"wagonnet",
"wali",
"watts",
"wiki",
"wifi",
"wharf",
"wallon",
"western",
"whig",
"xenophobe",
"xerces",
"xeres",
"xylophone",
"xieme",
"xerus",
"xhosa",
"xipho",
"xylol",
"xyste",
"yacht",
"yack",
"yaourt",
"yard",
"yeux",
"yoga",
"yole",
"youyou",
"yoyo",
"yucca",
"zapper",
"zebre",
"zero",
"zeste",
"zigzag",
"zinc",
"zodiaque",
"zone",
"zoo",
"zoologie"};

    FILE *f = fopen("dict.jdr", "w");

    fwrite(mots, 260*10*sizeof(char), 1, f);

    fclose(f);
}