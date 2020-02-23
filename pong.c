#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h> 
#include <unistd.h>
#include <stdbool.h>
#include <ncurses.h>
#include "pong.h"

//---------------constantes globales
//const int L = 47; //nombre de lignes
//const int C = 30; //nombre de colonnes
//---------------variables globales


int main(int argc, char * argv[]){

    struct joueur * player = (struct joueur *)malloc(sizeof(struct joueur)); //raquette joueur1
    //struct joueur * IA = (struct joueur *)malloc(sizeof(struct joueur)); //raquette IA/joueur2
    struct ball * ball = (struct ball *)malloc(sizeof(struct ball)); //la balle donc

    int n=argc;
	n+=1;


    char d_player;
    //int d_IA;

    //le fichier map sera à transférer dans la mémoire du mC
    FILE * map;
    map = fopen(argv[1], "r");

 
    
    
    //création du tableau
    char ** map_array;
    //on alloue un espace mémoire pour stocker les pointeurs sur chaque lignes (il y en a L)
    map_array = malloc(L*sizeof(map_array));
	
    for (int i=0 ; i<L ; ++i){
        //on alloue un espace mémoire de taille C pour chque ligne
        map_array[i]=malloc(C*sizeof(char));
    }
    

    //on remplit le tableau
    for (int i=0;i<L;++i){
        for (int j=0;j<C;++j){
            map_array[i][j] = fgetc(map);
        }
    }
    

	//on initialise la position et vitesse de la balle
    ball->pos_x=3;
    ball->pos_y=4;
    ball->dir_x=2;
    ball->dir_y=1;



    

    
    player->left =C-8; //indice de la colonne avec l'extrémité gauche de la plateforme du bas
    player->right =C-2; //idem pour l'extrémité droite



	        printf("0/!|/!|/!|/!|/!|/!|/!|/!|/!|\n");

    int k=0;
   while(d_player!='o'){
	k++;
        //on lit le tableau
        for (int i=0;i<L;++i){
            for (int j=0;j<C;++j){
                printf("%c", map_array[i][j]);
            }
        }
        printf("\n");


        
        //on regarde autour de la balle
        ball->right=map_array[ball->pos_y][ball->pos_x+1];
        ball->left=map_array[ball->pos_y][ball->pos_x-1];
        ball->down=map_array[ball->pos_y+1][ball->pos_x];
        ball->up=map_array[ball->pos_y-1][ball->pos_x];
        
        
        printf("down %c\n", map_array[ball->pos_y+1][ball->pos_x]);
        printf("up %c\n", map_array[ball->pos_y-1][ball->pos_x]);
        printf("left %c\n", map_array[ball->pos_y][ball->pos_x+1]);
        printf("right %c\n", map_array[ball->pos_y][ball->pos_x-1]);

        //on change la direction 
        if (ball->down=='n'){
            ball->dir_y=-1;
        } else if (ball->down=='-') break;
        if (ball->up=='-' || ball->up=='n'){
            ball->dir_y=1;
        }
        if (ball->left=='*'){
            ball->dir_x=1;
        } 
        if (ball->right=='*'){
            ball->dir_x=-1;
        }
        
        printf("1/!|/!|/!|/!|/!|/!|/!|/!|/!|");
        printf("\ndir_x %d\n", ball->dir_x);
        printf("dir_y %d\n", ball->dir_y);


        //on update la position de la balle
        
        map_array[ball->pos_y][ball->pos_x]=' '; 

        ball->pos_x=(ball->pos_x)+ball->dir_x;
        ball->pos_y=(ball->pos_y)+ball->dir_y;
        
        map_array[ball->pos_y][ball->pos_x]='O';

        printf("2/!|/!|/!|/!|/!|/!|/!|/!|/!|");

        printf("\npos_x %d\n", ball->pos_x);
        printf("pos_y %d\n", ball->pos_y);




        

        //on met la position du joueur à jour 
        scanf(" %c", &d_player);
        if (d_player=='a'){
            if (player->left>2){
                map_array[L-2][player->left-1]='n';
                map_array[L-2][player->right]=' ';
                player->left-=1;
                player->right-=1;
            } else {
                printf("ne peut pas aller plus loin à droite");
            }
        }
        if (d_player=='d'){
            if (player->right<C-1){
                map_array[L-2][player->left-1]=' ';
                map_array[L-2][player->right]='n';
                player->left+=1;
                player->right+=1;
            } else {
                printf("ne peut pas aller plus loin à gauche");
            }
        } 
	if (d_player=='q') break;
	if (d_player=='s') printf("ne se passe rien");
	
	//sleep(1);
	
	printf("je suis passé %d fois dans le while 1\n", k);
	
        } 

    
        printf("3/!|/!|/!|/!|/!|/!|/!|/!|/!|\n");


    
    





    

    printf("\n");
    //on libère le tableau (quand on a fini seulment)
    for(int i = 0; i < L; i++){
	   free(map_array[i]); 
	}
	free(map_array);
    fclose(map);
    return 0;
}







char direction(){
    //fonction qui va recueillir les données transmises par le module bluetooth depuis le tel
    char d='\0';
    //ici c'est scanf, mais il s'agira d'une entrée GPIO
    scanf("%c", &d);

    return d;
}

