// Librairie
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// VARIABLR
# define NBRE_VILLE 1
# define NBRE_SOLDAT 15
// definition des couleurs
#define couleur(param) printf("\033[%sm",param)
#define clrscr() printf("\033[H\033[2J")

// FONCTION D'ERREUR
enum{	 
	NO_ERROR,
	ERROR_OUVERTURE,
	ERROR_FERMETURE,
	
};
 enum joueur{	 
		ROUGE=1, // joueur 1
		NOIR=2, // joueur 2
};
enum contenu{
	VIDE,
	SOLDAT_ROUGE,
	SOLDAT_NOIR,
	VILLE_ROUGE,
	VILLE_NOIR,
};
enum direction
{
	HAUT,
	HAUT_GAUCHE,
	HAUT_DROITE,
	GAUCHE,
	DROITE,
	BAS,
	BAS_GAUCHE,
	BAS_DROITE
};
enum resultat_mouvement
{
	MOUVEMENT_INVALIDE,
	MOUVEMENT_VALIDE,
	VICTOIRE,
	NO_VICTOIRE
};

// Prototype
// mouvement.c

int det_offset(int joueur_courant);
void donne_ville_amie_ennemie(int *ville_amie,int *ville_ennemie,int joueur_courant);
int verification_mouvement(int x,int y,int ville_ennemie ,int joueur_courant,int ville_amie);
int verification_destination(int y,int x,int x_dest,int y_dest, int joueur_courant);
int victoire_ville(int x_dest,int y_dest,int ville_ennemie);
int victoire_pion(int x_dest,int y_dest,int pion_ennemi);
int mouvement_pion(int y, int x,int x_dest,int y_dest,int dir);
int deplacer_pion(int x, int y,int dir,int joueur_courant);
int tir_canon(int x, int y ,int dir,int joueur_courant);
int deplacer_canon(int x,int y, int dir ,int joueur_courant);
// interface_utilisateur.c
int choix_nbre_joueur();
int joueur_commence_partie();
// partie catalogue
void catalogue_type_de_coup();
void catalogue_choix_deplacement();
void catalogue_avancer();
void catalogue_retraite();
void catalogue_capturer();
// choix du deplacement
int choix_deplacement();
int choix_avance();
int choix_retraite();
int choix_type_coup();
// Affichage plateau
void display_plateau();
int choix_capture();



// Main
int duel_joueur_vs_joueur(int joueur);
int joueur_vs_ordinateur(int joueur);



