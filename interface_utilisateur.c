// **********************************************************
// Fichier interface avec l'utilisateur
// **********************************************************
// LIBRAIRIE
# include "couleur.h"
# include "mouvement.c"
// Fonction

//Extension Choix de plateau non classique par l'utilisateur
int choix_plateau(){
	int dim_plateau;
	printf("Rentrer les dimensions du plateau que vous souhaitez.\n");
	scanf("%d",&dim_plateau);
	return dim_plateau;
}

// L'utilisateur choisit son mode de jeux
int choix_nbre_joueur(){
	int nbre_joueur = 0;
	do{
		printf("Bienvenue, A combien de personnes voulez vous jouer\n");
		scanf("%d",&nbre_joueur);
	}while(nbre_joueur <= 0 || nbre_joueur > 2);
    if(nbre_joueur == 1 ){
        printf("Vous jouez contre l'ordinateur.\n");
    }else{
        printf("Vous faites un duel un contre un.\n");
    }
	return nbre_joueur;
}
// L'utilisateur choisit qui veut commencer la partie
int joueur_commence_partie(){
    int joueur;
    printf("Qui veux commencer la partie \n");
    scanf("%d",&joueur);
            
    switch(joueur){
        case 1: 
            printf("Le joueur 1 commence la partie.\n");
            break;
        case 2:
            printf("Le joueur 2 commence la partie\n");
            break;
        default:
            printf("Le numero rentrée estmauvais par défault: le joueur 1 commence la partie\n");
            joueur = 1;
            break;
    }
    return joueur;
}

// Type de coup réalisable dans le jeux
void catalogue_type_de_coup(){
    printf("\n");
    printf("******** Catalogue type de coup ******\n");
    printf("0:\n");
    printf("Vous voulez deplacer un pion.\n");

    printf("1:\n");
    printf("Vous voulez tirer au canon.\n");

    printf("2:\n");
    printf("Vous voulez deplacer un canon.\n");
    printf("***************************************\n");
    printf("\n");
}

// Les placements possiblent à partir d'une pièce
void catalogue_choix_deplacement(){
    printf("\n");
    printf("****** Catalogue choix de deplacement ******\n");
    printf("0:\n");
    printf("Deplacement pion : Pour avancer le pion.\n");
    printf("Tirer au canon : Pour tirer devant .\n");
    printf("Deplacement Canon : Pour avancer le canon.\n");

    printf("1:\n");
    printf("deplacer pion : Battre en retraite.\n");
    printf("Tirer au canon : Pour tirer deriere .\n");
    printf("Deplacement Canon : Pour reculer le canon.(!= retraite)\n");

    printf("2:\n");
    printf(" Deplacer pion :capturer un pion ennemi.\n");
    printf(" Tirer au canon :capturer des pions ennemis.\n");
    printf("**********************************************\n");
    printf("\n");
}

// Manuel avancer un pion
void catalogue_avancer(){
    printf("\n");
    printf("****** Catalogue direction possible pour avancer un pion ******\n");
    printf("0:\n");
    printf("deplacement haut.\n");

    printf("1:\n");
    printf("deplacement haut gauche.\n");

    printf("2:\n");
    printf("deplacement haut droite.\n");
    printf("****************************************************************\n");
    printf("\n");

}

// Manuel reculer une pièce
void catalogue_retraite(){
    printf("\n");
    printf("****** Catalogue direction possible pour reculer un pion ******\n");
    printf("5:\n");
    printf("deplacement bas.\n");

    printf("6:\n");
    printf("deplacement bas gauche.\n");
           
    printf("7\n");
    printf("deplacement bas droite.\n");
    printf("****************************************************************\n");
    printf("\n");

}

// Manuel capturer un pion
void catalogue_capturer(){
    printf("\n");
    printf("****** Catalogue direction possible pour attaquer un pion /canon ******\n");
    printf("0:\n");
    printf("deplacement haut.\n");

    printf("1:\n");
    printf("deplacement haut gauche.\n");

    printf("2\n");
    printf("deplacement haut droite.\n");

    printf("3:\n");
    printf("deplacement gauche.\n");

    printf("4:\n");
    printf("deplacement droite.\n");
    printf("****************************************************************\n");
    printf("\n");
}

// Choix du déplacement par l'utilisateur
int choix_deplacement(){
    int dep;
    do{
        catalogue_choix_deplacement();
        printf("Choisissez votre déplacement.\n");
        scanf("%d",&dep);

    } while(dep < 0 || dep > 2);
    return dep;
}

// Choix de l'avancé du pion par l'utilisateur
int choix_avance(){
    int dir;
    do{
        catalogue_avancer();
        printf("Dans quel direction voulez vous bouger le pion ? \n");
        scanf("%d",&dir);
    }while(dir <0 || dir > 2);
    return dir;
}

// Choix du retrait du pion par l'utilisateur
int choix_retraite(){
    int dir;
    do{
        catalogue_retraite();
        printf("Dans quel direction voulez vous bouger le pion ? \n");
        scanf("%d",&dir);
    }while(dir <5 || dir > 7);
    return dir;
}

// Choix du mode capture  de pion par l'utilisateur
int choix_capture(){
    int dir;      
    do{
        catalogue_capturer(); 
        printf("Dans quel direction voulez vous bouger le pion ? \n");
        scanf("%d",&dir);
    }while(dir <0 || dir >4);
    return dir;
}


// Choix du type de coup par le joueur
int choix_type_coup(){
    int type_coup;
    do{
        
        catalogue_type_de_coup();
        printf("Quel type de coup voulez vous jouer?\n");
        scanf("%d",&type_coup);
    }while(type_coup < 0 || type_coup > 2);
    return type_coup;
}

// Affichage du plateau
void display_plateau(){
	int x,y;
    printf("*******************\n");
    printf("joueur 1= Rouge\n");
    printf("joueur 2= Noir\n");
     printf("*******************\n");
    printf("x-0 1 2 3 4 5 6 7 8 9  y \n"); 
    printf("  _ _ _ _ _ _ _ _ _ _  | \n");
	for(y=0;y < DIM_PLATEAU;y++){ 
        printf("%d|",y);
		for (x=0; x < DIM_PLATEAU;x++){
			
            if(plateau[y][x]== VIDE )
				printf(" |");
			else if (plateau[y][x] == SOLDAT_ROUGE)
			{
				couleur("31");
				printf("%d|",plateau[y][x]);
				couleur("0");
			}
			else if (plateau[y][x] == SOLDAT_NOIR ){
				couleur("30");
				printf("%d|",plateau[y][x]);
				couleur("0");
			}
            else if (plateau[y][x] == VILLE_ROUGE ){
                couleur("32");
				printf("%d|",plateau[y][x]);
				couleur("0");
			}
            else{	
                couleur("33");
				printf("%d|",plateau[y][x]);
				couleur("0");
            }		
 		}
 		printf("|%d\n",y);
	}
    printf("x-0 1 2 3 4 5 6 7 8 9  y \n"); 
    printf("  _ _ _ _ _ _ _ _ _ _  | \n");
} 

// joueur contre ordinateur Ordinateur choisit aléatoirement sa pièce
int aleatoire_entre(int min,int max){
   
    srand(time(NULL));
    return rand() % (max-min)+min;

}
void choix_position_ville(int joueur){
    int y;
    int x;
    
    if (joueur == 1){
        do{
        y=0;
        printf("Joueur %d :Choisissez la position x de la ville.\n",joueur);
        scanf("%d",&x);
        }while(y<0 && y >= DIM_PLATEAU);
        plateau[y][x]=VILLE_ROUGE;

    }else{
        do{
            y=9;
            printf("Joueur %d:Choisissez la position x de la ville.\n",joueur);
            scanf("%d",&x);
        }while(y<0 && y >= DIM_PLATEAU);
        plateau[y][x]=VILLE_NOIR;
    }
}
