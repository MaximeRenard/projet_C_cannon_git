// ***********************************************
// Autheur: Fabien Genty RENARD Maxime M1IB
// Date : 30/12/16
// ***********************************************
// Librairie
# include "interface_utilisateur.c"


// ************************************************
// FONCTION
// ************************************************

// UTILISATEUR VS UTILISATEUR
int duel_joueur_vs_joueur(int joueur){
    int x,y,dir;
    //int tour = 0;  extension tour besoin de faire pour 2 joueur
    int canon_tir;
    int pion_dep;
    int canon_dep;
    int deplacement;
    int type;
    do{
        printf("Joueur %d:\n", joueur);
        display_plateau(plateau);
                
        printf("Donnez les coordonnées x,y du pion que vous voulez déplacer.\n");
        printf("x=");                
        scanf("%d",&x);
        printf("y=");
        scanf("%d",&y);
        printf("*******************************************************************\n");
        printf("x=%d,y=%d\n",x,y);
        printf("*******************************************************************\n");
        printf("\n");
        type=choix_type_coup();  
        deplacement=choix_deplacement();
                    
        // avancer le pion
        if (deplacement == 0){
            dir=choix_avance();           
        }
        // Battre en retraite
        else if (deplacement == 1){
            dir=choix_retraite();
        }
        // capturer un pion ennemie
        else{
            dir=choix_capture();
        }
            // deplacement pion
        if (type==0){
            pion_dep=deplacer_pion(x,y,dir,joueur);
        }
            // tirer au canon
        else if (type == 1){
            canon_tir=tir_canon(x, y ,dir,joueur);
        }
        // deplacement canon
        else{
            canon_dep=deplacer_canon(x, y ,dir,joueur);
        }
                   
        if (((pion_dep == MOUVEMENT_VALIDE) || (canon_dep == MOUVEMENT_VALIDE) || (canon_tir == MOUVEMENT_VALIDE))\
           && (pion_dep != VICTOIRE || canon_tir != VICTOIRE || canon_dep != VICTOIRE)){
            joueur=3-joueur;
        }
            
    }while(pion_dep != VICTOIRE || canon_tir != VICTOIRE || canon_dep != VICTOIRE);
        
    return joueur;

}
int choix_ordinateur(int canon_tir,int pion_dep,int canon_dep\
    ,int deplacement,int type,int x,int y,int dir,int joueur){
    do{
                printf("*******************************************\n");
                printf("Joueur %d\n",joueur);
                printf("*******************************************\n");
                display_plateau(plateau);
                x = aleatoire_entre(0,DIM_PLATEAU-1);
                y = aleatoire_entre(0,DIM_PLATEAU-1);
                printf("x=%d , y=%d\n",x,y);
                type = aleatoire_entre(0,2);
                printf("type=%d,dep %d\n",type,deplacement);
                deplacement = aleatoire_entre(0,2);
                if(deplacement == 0){
                    dir = aleatoire_entre(0,2);
                    printf("dir=%d\n",dir); 
                }else if(deplacement == 1){
                    dir = aleatoire_entre(5,7);
                    printf("dir=%d\n",dir);
                }else{
                    dir = aleatoire_entre(0,4);
                    printf("dir=%d\n",dir);
                }
                if (type==0){
                    pion_dep=deplacer_pion(x,y,dir,joueur);
                }
                // tirer au canon
                else if (type == 1){
                    canon_tir=tir_canon(x, y ,dir,joueur);
                }
                // deplacement canon
                else{
                    canon_dep=deplacer_canon(x, y ,dir,joueur);
                }
       }while((pion_dep == MOUVEMENT_VALIDE) || (canon_dep == MOUVEMENT_VALIDE) || (canon_tir == MOUVEMENT_VALIDE));
        return 3-joueur;
}

// JOUEUR CONTRE ORDINATEUR
int joueur_vs_ordinateur(int joueur){
    int x,y,dir;
    //int tour = 0;  extension tour besoin de faire pour 2 joueur
    int canon_tir;
    int pion_dep;
    int canon_dep;
    int deplacement;
    int type;
    
        
    do{
        printf("Joueur 1= joueur, Joueur 2 = ordinateur \n");
        printf("Joueur %d:\n", joueur);

        display_plateau(plateau);
        // l'ordinateur
        if(joueur == 2){
            joueur = choix_ordinateur(canon_tir,pion_dep,canon_dep,\
            deplacement,type,x,y,dir,joueur);
            
            
         }
         // le joueur 
         else{
            printf("Donnez les coordonnées x,y du pion que vous voulez déplacer.\n");
            printf("x=");                
            scanf("%d",&x);
            printf("y=");
            scanf("%d",&y);
            printf("*******************************************************************\n");
            printf("x=%d,y=%d\n",x,y);
            printf("*******************************************************************\n");
            printf("\n");
            type=choix_type_coup();  
            deplacement=choix_deplacement();
                            
            // avancer le pion
            if (deplacement == 0){
                dir=choix_avance();           
            }
            // Battre en retraite
            else if (deplacement == 1){
                dir=choix_retraite();
            }
            // capturer un pion ennemie
            else{
                dir=choix_capture();
            }
            // deplacement pion
            if (type==0){
                pion_dep=deplacer_pion(x,y,dir,joueur);
            }
            // tirer au canon
            else if (type == 1){
                canon_tir=tir_canon(x, y ,dir,joueur);
            }
            // deplacement canon
            else{
                canon_dep=deplacer_canon(x, y ,dir,joueur);
            }
            if (((pion_dep == MOUVEMENT_VALIDE) || (canon_dep == MOUVEMENT_VALIDE) || (canon_tir == MOUVEMENT_VALIDE))\
                && (pion_dep != VICTOIRE || canon_tir != VICTOIRE || canon_dep != VICTOIRE)){
                joueur=3-joueur;
            }
            printf("joueur:%d\n",joueur );
        }
    }while((pion_dep != VICTOIRE) || (canon_dep == VICTOIRE) || (canon_tir == VICTOIRE));
    printf("%d\n",joueur );
    return joueur;
}

// ***********************************************
// MAIN
// ***********************************************

int 
main()
{
    // initialisation des variables
	int debut,fin;
	int joueur=0;

	debut=time(NULL);
    int victorieux;
    int nombre_joueur=0;
    
    // joueur qui commence la partie
    joueur=choix_nbre_joueur();
      // pour le joueur 1
    choix_position_ville(1);

    // pour le joueur 2
    choix_position_ville(2);
    joueur=joueur_commence_partie();

    display_plateau();

    // JOUEUR VS ORDINATEUR
    if (nombre_joueur == 1){
        victorieux = joueur_vs_ordinateur(joueur);     
    }
    // C'est un duel un contre un
    else{
    	victorieux = duel_joueur_vs_joueur(joueur);    
    }    
	fin=time(NULL);
	printf(" Bravo joueur %d!Vous avez gagné en %d time\n",victorieux,fin-debut);

	return 0;
}
