#include <stdio.h> //printf, fopen
#include <math.h>
#include <stdlib.h> //malloc
#include <time.h> //time_t, timediff 
#include <string.h> //manipulation des chaines
//#include <ctype.h> pour identifier un élément 
#include <unistd.h> //misc
#include <stdbool.h> //bool
#include <ncurses.h> //printw, initscr, cbreak, noecho, endwin
#include "pong.h"



int main(void){

    struct joueur * player = (struct joueur *)malloc(sizeof(struct joueur)); //raquette joueur1
    //struct joueur * IA = (struct joueur *)malloc(sizeof(struct joueur)); //raquette IA/joueur2
    struct ball * ball = (struct ball *)malloc(sizeof(struct ball)); //la balle donc

    char d_player = 's';
    //int d_IA;

    initscr();
    cbreak();
    //noecho();

    clear();

    //le fichier map sera à transférer dans la mémoire du mC
    FILE * map;
    map = fopen("map.txt", "r");


    
    
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
    ball->dir_x=1;
    ball->dir_y=1;

    int V = 1; //multiplieur pour la vitesse

    

    
    player->left =C-8; //indice de la colonne avec l'extrémité gauche de la plateforme du bas
    player->right =C-2; //idem pour l'extrémité droite





    int k=0;



   while(d_player!='o'){



    clear();
	k++;
        //on lit le tableau
        for (int i=0;i<L;++i){
            for (int j=0;j<C;++j){
                printw("%c", map_array[i][j]);
            }
        }
        printf("\n");


        if (k>30) V=2;

        
        //on regarde autour de la balle
        ball->right=map_array[ball->pos_y][ball->pos_x+1];
        ball->left=map_array[ball->pos_y][ball->pos_x-1];
        ball->down=map_array[ball->pos_y+1][ball->pos_x];
        ball->up=map_array[ball->pos_y-1][ball->pos_x];
        
        
        printw("down %c\n", map_array[ball->pos_y+1][ball->pos_x]);
        printw("up %c\n", map_array[ball->pos_y-1][ball->pos_x]);
        printw("left %c\n", map_array[ball->pos_y][ball->pos_x+1]);
        printw("right %c\n", map_array[ball->pos_y][ball->pos_x-1]);

        //on change la direction 
        if (ball->down==PLAYER1){
            ball->dir_y=-1*V;
        } else if (ball->down==FRONTWALL) break;
        if (ball->up==FRONTWALL || ball->up==PLAYER1){
            ball->dir_y=1*V;
        }
        if (ball->left==SIDEWALL){
            ball->dir_x=1*V;
        } 
        if (ball->right==SIDEWALL){
            ball->dir_x=-1*V;
        }
        



        //on update la position de la balle        
        map_array[ball->pos_y][ball->pos_x]=' '; 

        ball->pos_x=(ball->pos_x)+ball->dir_x;
        ball->pos_y=(ball->pos_y)+ball->dir_y;
        
        map_array[ball->pos_y][ball->pos_x]='O';



        //refresh();

        

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
	
    


	
	printw("je suis passé %d fois dans le while 1\n", k);



    refresh();

    } 

    



    
    
    endwin();




    

    printf("\n");
    //on libère le tableau (quand on a fini seulment)
    for(int i = 0; i < L; i++){
	   free(map_array[i]); 
	}
	free(map_array);
    fclose(map);
    return 0;
}



