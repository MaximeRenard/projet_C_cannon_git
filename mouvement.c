// BIBLIOTHEQUE
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
// IMPORTATION
# include "plateau.c"
# include "cannon.h"


// ****************************************************************** 
// Fonction 
// ******************************************************************
// determine le sens du jeu selon le joueur
int det_offset(int joueur_courant){
	int offset=0;
	if (joueur_courant==NOIR){
        offset=-1;
    }
	else{
        offset = 1;
    }
    return offset;
} 

// fonction qui donne le sens du jeu selon le joueur evite verifier ville à chaque tour
void donne_ville_amie_ennemie(int *ville_amie,int *ville_ennemie,int joueur_courant){
	if(joueur_courant == NOIR)
	{
		*ville_amie=VILLE_NOIR;
		*ville_ennemie=VILLE_ROUGE;
	}
	else
	{
		*ville_amie=VILLE_ROUGE;
		*ville_ennemie=VILLE_NOIR;
	}
}

// verification du pion choisi par l'utilisateur
int verification_mouvement(int x,int y,int ville_ennemie ,int joueur_courant,int ville_amie){
	if(plateau[y][x]== VIDE || plateau[y][x] == ville_ennemie ||plateau[y][x]== ville_amie || plateau[y][x] != joueur_courant ||
		x < 0 || y < 0 || x >= DIM_PLATEAU || y >= DIM_PLATEAU){
		printf("selection d'une mauvaise case, x= %d y=%d, piece choisie =%d \n ", x,y,plateau[y][x]);
		return MOUVEMENT_INVALIDE;
	}
	return MOUVEMENT_VALIDE;
}

// verification du coup : hors plateau
int verification_destination(int y,int x,int x_dest,int y_dest, int joueur_courant){
 	if(x_dest >= DIM_PLATEAU || x_dest < 0 || y_dest >= DIM_PLATEAU || y_dest < 0 || plateau[y_dest][x_dest]==joueur_courant )
 	{
 		printf("MOUVEMENT HORS LIMITE \n");
 		printf("selection d'une mauvaise destination d'un pion/canon , x= %d y=%d piece, %d X_dest= %d y_dest= %d %d \n "\
 			, x,y,plateau[y][x],x_dest,y_dest,plateau[y_dest][x_dest]);
 		return MOUVEMENT_INVALIDE;
 	}
 	return MOUVEMENT_VALIDE;
}

// 1 ere fonction de victoire
int victoire_ville(int x_dest,int y_dest,int ville_ennemie){	
	if(plateau[y_dest][x_dest] == ville_ennemie){
		printf(" mouvement valide : ville conquise \n");
		printf("x _dest :%d,y_dest:%d\n",x_dest,y_dest);
		return VICTOIRE; // while( != victoire)
	}
	return NO_VICTOIRE;	
}

// 2 eme fonction de victoire
int victoire_pion(int x_dest,int y_dest,int pion_ennemi){
	int x,y;
	for (y=0;y < DIM_PLATEAU;y++){
		for (x=0;x < DIM_PLATEAU;x++){
			if (plateau[y][x]==pion_ennemi){
				return NO_VICTOIRE;
			}
		}
	}
	return VICTOIRE;
}
// realise le mouvement d'un pion si possible
int mouvement_pion(int y, int x,int x_dest,int y_dest,int dir){
		if(plateau[y_dest][x_dest] == VIDE &&( dir == HAUT_GAUCHE || dir == HAUT || dir == HAUT_DROITE ))
		{
            // mouvement normale : avancer
			plateau[y_dest][x_dest] = plateau[y][x];
			plateau[y][x] = VIDE;
			printf(" mouvement valide \n");
			printf("x _dest : %d ,y_dest: %d\n",x_dest,y_dest);
			return MOUVEMENT_VALIDE;
		}
		else
		{
            //else if(plateau[y_dest][x_dest] == pion_ami)
			printf(" mouvement invalide \n");
			printf("x= %d y=%d, piece: %d, X_dest= %d, y_dest= %d piece_dest : %d \n ", x,y,plateau[y][x],x_dest,y_dest,plateau[y_dest][x_dest]);
			return MOUVEMENT_INVALIDE;
		} 
}	
// Fonction de deplacement d'un pion : avancer, retrait, capture
int deplacer_pion(int x, int y,int dir,int joueur_courant){

	int x_dest = 0;
	int y_dest = 0;
	int offset = 0;
	int ville_amie,ville_ennemie;
	donne_ville_amie_ennemie(&ville_amie,&ville_ennemie,joueur_courant);
	int pion_ennemi =(joueur_courant == 1?2:1);

	offset = det_offset(joueur_courant);
  
	if(verification_mouvement(x,y,ville_ennemie,joueur_courant,ville_amie) == MOUVEMENT_INVALIDE){
		return MOUVEMENT_INVALIDE;
	}
    // appeler fonction
 	switch(dir)
 	{
 		case HAUT_GAUCHE:
 			x_dest = x + offset;
 			y_dest = y + offset;
 			break;

 		case HAUT:
 			x_dest = x;
 			y_dest = y + offset;
 			break;

 		case HAUT_DROITE:
 			x_dest = x - offset;
 			y_dest = y + offset;
 			break;
 			
 		case GAUCHE :
 			x_dest = x + offset;
 			y_dest = y;
 			break;
 			
 		case DROITE :
 			x_dest = x - offset;
 			y_dest = y ;
 			break;
 			
 		case BAS :
			x_dest=x;
			y_dest = y - 2*offset;
			break;

		case BAS_DROITE :
			x_dest = x - 2*offset;
			y_dest = y - 2*offset;
			break;

		case BAS_GAUCHE :
			x_dest = x + 2*offset;
			y_dest = y - 2*offset;  
			break;	
 	}
    //return coord;
    // verification si la destination est bonne 0 ok 1 bon verif_destination
    
 	if(verification_destination(y,x,x_dest,y_dest,joueur_courant) == MOUVEMENT_INVALIDE){
 		return MOUVEMENT_INVALIDE;
 	}
    // DEPLACEMENT mouvement Bas bas droit ou bas gauche
 	if(dir >=BAS)// mode retraite
 	{	
 		//verification presence de pions ennemies

		if(plateau[y][x + offset] != pion_ennemi
			&& plateau[y + offset][x + offset]!= pion_ennemi
		 && plateau[y + offset][x] != pion_ennemi
		 && plateau[y + offset][x - offset]  != pion_ennemi
		 && plateau[y][x -offset] != pion_ennemi)
		{
			printf("On ne peut pas battre en retraite sans ennemi adjacent.\n");
			printf("selection de la mauvaise piece pour battre en retraite\
				x= %d, y=%d, piece : %d, X_dest= %d, y_dest= %d,piece_dest : %d \n "\
				,x,y,plateau[y][x],x_dest,y_dest,plateau[y_dest][x_dest]);
            
			return MOUVEMENT_INVALIDE;	
		}
        // Il y a un ennemi
		else 
		{
			// la retraite est possible
			if(plateau[(y_dest+y)/2][(x+x_dest)/2] == VIDE && plateau[y_dest][x_dest] == VIDE)
			{
                // quand recule on fait deux pas 
				plateau[y_dest][x_dest] = plateau[y][x]; // transfere
				plateau[y][x]= VIDE; // position iniiale vide
				
				return MOUVEMENT_VALIDE;
			}
			// la retraite est impossible
			else
			{
                // 
				printf(" Retrait impossible:à cause des pions de derrières bloquent le passage\n");
				printf("selection de la mauvaise piece pour battre en retraite\
				x= %d, y=%d, piece : %d, X_dest= %d, y_dest= %d,piece_dest : %d \n "\
				,x,y,plateau[y][x],x_dest,y_dest,plateau[y_dest][x_dest]);
				return MOUVEMENT_INVALIDE;
			} 
			
	 	}	
	}
 	else{
        // 	 DEPACEMENT HAUT,HAUT_GAUCHE,HAUT_DROITE,GAUCHE,DROITE,

		if(plateau[y_dest][x_dest] == pion_ennemi){
            //mode avance capture
			plateau[y_dest][x_dest] = plateau[y][x];
			plateau[y][x] = VIDE;
			printf(" mouvement valide \n");
			printf("x _dest :%d ,y_dest:%d.\n",x_dest,y_dest);
			if(victoire_pion(x_dest,y_dest,pion_ennemi) == VICTOIRE){
					return VICTOIRE;
			}
			return MOUVEMENT_VALIDE;
		}
        else if(victoire_ville(x_dest,y_dest,ville_ennemie) == VICTOIRE){
        	return VICTOIRE;
        }else{
			if(mouvement_pion(y,x,x_dest,y_dest,dir) == MOUVEMENT_INVALIDE){
				return MOUVEMENT_INVALIDE;
			}
		}
 	}
 	return MOUVEMENT_VALIDE;
}




// Fonction Canon tirer au canon
// NOTICE:la piece indiquée en entrée est celle ou le cannon doit tirer
int tir_canon(int x, int y ,int dir,int joueur_courant)
{

	int offset = 0;
	int x_offset;
	int y_offset;
	
	int ville_amie,ville_ennemie;
	donne_ville_amie_ennemie(&ville_amie,&ville_ennemie,joueur_courant);
	int pion_ennemi =(joueur_courant == 1?2:1);

	offset = det_offset(joueur_courant);

	if(verification_mouvement(x,y,ville_ennemie,joueur_courant,ville_amie) == MOUVEMENT_INVALIDE){
		return 1;}

//test existence canon 
    // sens_canon()
	switch(dir)
 	{
 		case HAUT_GAUCHE:
 			x_offset = offset;
 			y_offset = offset;
 	 
 			break;

 		case HAUT:
 			x_offset = 0;
 			y_offset = offset;
 			break;

 		case HAUT_DROITE:
 			x_offset = -offset;
 			y_offset =  offset;
 			break;
 			
 		case GAUCHE :
 			x_offset = offset;
 			y_offset = 0;
 			break;
 			
 		case DROITE :
 			x_offset = - offset;
 			y_offset = 0;
 			break;
 			
 		case BAS :
			x_offset= 0;
			y_offset = - offset;
			break;

		case BAS_DROITE :
			x_offset =  - offset;
			y_offset =  - offset;
			break;

		case BAS_GAUCHE :
			x_offset =   offset;
			y_offset =  - offset;
			break;	
 	}
 	// FONCTION TEST CANNON
 
 	if( (y + y_offset >= 0) && (y + y_offset < DIM_PLATEAU) && (x + x_offset >= 0 && x + x_offset < DIM_PLATEAU &&
 		y - y_offset >= 0 && y - y_offset <DIM_PLATEAU && x - x_offset >= 0 && x - x_offset < DIM_PLATEAU &&
 	 	plateau[y + y_offset][x + x_offset ] == joueur_courant && (plateau[y - y_offset][x - x_offset ] == joueur_courant)))
 	{ 
 		if( y + 2*y_offset >= 0 && y + 2*y_offset < DIM_PLATEAU && x + 2*x_offset >=0 && x + 2*x_offset <= DIM_PLATEAU &&
 			plateau[y + 2*y_offset][x + 2*x_offset]== VIDE){
            //  test_canon_actif 
 			if( y + 3*y_offset >= 0 && y + 3*y_offset < DIM_PLATEAU && 
				x + 3*x_offset >=0 && x + 3*x_offset  < DIM_PLATEAU &&
				plateau[y + 3*y_offset][x + 3*x_offset] == pion_ennemi &&
				plateau[y + 3*y_offset][x + 3*x_offset] == ville_ennemie &&
				y + 4*y_offset >= 0 && y + 4*y_offset < DIM_PLATEAU && x + 4*x_offset >= 0 && x + 4*x_offset < DIM_PLATEAU &&
				plateau[y + 4*y_offset][x + 4*x_offset] == pion_ennemi &&
				plateau[y + 4*y_offset][x + 4*x_offset] ==  ville_ennemie )
			{	
			    // BOULET ENVOYE
			    
				if(plateau[y + 3*y_offset][x + 3*x_offset] == ville_ennemie || plateau[y + 4*y_offset][x + 4*x_offset] == ville_ennemie)
				{
					printf("Vous avez conquis la ville, gagné \n");
					return VICTOIRE;
				}
            	plateau[y + 3*y_offset][x + 3*x_offset] = VIDE;
				plateau[y + 4*y_offset][x + 4*x_offset] = VIDE;
				printf(" x= %d y=%d %d \n ", x,y,plateau[y][x]);
				printf("On a tirer sur deux pions ennemis \n");
				return MOUVEMENT_VALIDE; 
				
			}// on peut tirer sur 1 pion enemmi avec un case 
			else if ( y + 3*y_offset >= 0 && y + 3*y_offset < DIM_PLATEAU && 
				x + 3*x_offset >=0 && x + 3*x_offset  < DIM_PLATEAU &&
				plateau[y + 3*y_offset][x + 3*x_offset] == pion_ennemi)
			{	
				if(plateau[y + 3*y_offset][x + 3*x_offset] == ville_ennemie)
				{
					printf("Vous avez conquis la ville, gagné \n");
					return VICTOIRE;
				}

				plateau[y + 3*y_offset][x + 3*x_offset] = VIDE;
				printf("On a tirer sur un pion ennemi \n");
				return MOUVEMENT_VALIDE; 	
			}else{
				printf("On ne peut pas tirer au canon da\n");
				return MOUVEMENT_INVALIDE;
			}
        // test canon_actif ==0	
 		}else{
 			
 				printf("case adjacente non vide: le canon est bloqué.\n");
 				return MOUVEMENT_INVALIDE;
 			}
    // test_canon== 0
 	}else{
 		printf("La piece sélectionné n'est pas un canon.\n");
 		return MOUVEMENT_INVALIDE;
 	}	
}
// Deplacement du cannon
int deplacer_canon(int x,int y, int dir ,int joueur_courant)
{
	int offset = 0;
	int x_offset;
	int y_offset;
	
	int ville_amie,ville_ennemie;
	donne_ville_amie_ennemie(&ville_amie,&ville_ennemie,joueur_courant);
	

	offset = det_offset(joueur_courant);

	//test l'existance d'une la piece selectionnée appel verification_mouvement
	if(verification_mouvement(x,y,ville_ennemie,joueur_courant,ville_amie) == MOUVEMENT_INVALIDE){
		return MOUVEMENT_INVALIDE;
	}

//test existence canon 

	switch(dir)
 	{
 		case HAUT_GAUCHE:
 			x_offset = offset;
 			y_offset = offset;
 	 
 			break;

 		case HAUT:
 			x_offset = 0;
 			y_offset = offset;
 			break;

 		case HAUT_DROITE:
 			x_offset = - offset;
 			y_offset =  offset;
 			break;
 			
 		case GAUCHE :
 			x_offset = offset;
 			y_offset = 0;
 			break;
 			
 		case DROITE :
 			x_offset = - offset;
 			y_offset = 0;
 			break;
 			
 		case BAS :
			x_offset= 0;
			y_offset = - offset;
			break;

		case BAS_DROITE :
			x_offset =  - offset;
			y_offset =  - offset;
			break;

		case BAS_GAUCHE :
			x_offset = offset;
			y_offset = - offset;
			break;	
 	}
 	
 	//test de l'existance d'un cannon DOUBLE ???? test_canon
 	if( y + y_offset >= 0 && y + y_offset <DIM_PLATEAU && x + x_offset >= 0 && x + x_offset < DIM_PLATEAU &&
 		y - y_offset >= 0 && y - y_offset <DIM_PLATEAU && x - x_offset >= 0 && x - x_offset < DIM_PLATEAU &&
 	 	plateau[y + y_offset][x + x_offset ] == joueur_courant && (plateau[y - y_offset][x - x_offset ] == joueur_courant))
 	{
 		//portée pacifique test_canon_actif()
 		if( y + 2*y_offset >= 0 && y + 2*y_offset < DIM_PLATEAU && x + 2*x_offset >=0 && x + 2*x_offset <= DIM_PLATEAU &&
 			plateau[y + 2*y_offset][x + 2*x_offset]== VIDE)
 		{	//deplacement du canon dans la direction choisit appel fonction deplacement_canon_actif 
 			plateau[y + 2*y_offset][x + 2*x_offset] = plateau[y - y_offset][x - x_offset];
 			plateau[y - y_offset][x - x_offset] = VIDE;
 			printf("Deplacement du cannon avec succès\n");
 			printf("x _dest :%d,y_dest:%d\n",x + 2*x_offset,y + 2*y_offset);
 			return MOUVEMENT_VALIDE;
 		}
        // test_canon actif == 0
 		else
 		{
 			printf("Deplacement du cannon, impossible: la case n'est pas libre.\n");
 			return MOUVEMENT_INVALIDE;
 		}
	}
    // test cannon == 0 
	printf("La piece sélectionnée n'est pas un canon.\n");
	return MOUVEMENT_INVALIDE;
}
	
