
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

void printmap(char ** map_array){
    //on lit le tableau
    for (int i=0;i<L;++i){
        for (int j=0;j<C;++j){
            printw("%c", map_array[i][j]);
        }
    }
    printf("\n");
}


void move_ball(char ** map_array, ball ball){
    //on update la position de la balle        
    map_array[ball->pos_y][ball->pos_x]=' '; 
        
    ball->pos_x=(ball->pos_x)+ball->dir_x;
    ball->pos_y=(ball->pos_y)+ball->dir_y;
        
    map_array[ball->pos_y][ball->pos_x]='O';
}

void move_player1(char ** map_array, joueur player1){
    //on met la position du joueur à jour 
    char d_player = 's';
    scanf(" %c", &d_player);
    if (d_player=='a'){
        if (player1->left>2){
            map_array[L-2][player1->left-1]='n';
            map_array[L-2][player1->right]=' ';
            player1->left-=1;
            player1->right-=1;
        } else {
            printf("ne peut pas aller plus loin à droite");
        }
    }
    if (d_player=='d'){
        if (player1->right<C-1){
            map_array[L-2][player1->left-1]=' ';
            map_array[L-2][player1->right]='n';
            player1->left+=1;
            player1->right+=1;
        } else {
            printf("ne peut pas aller plus loin à gauche");
        }
    } 
	if (d_player=='s') printf("ne se passe rien");
}



void init(char ** map_array, joueur player1, ball ball, FILE* map, bool * lost){

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

    player1->left =C-8; //indice de la colonne avec l'extrémité gauche de la plateforme du bas
    player1->right =C-2; //idem pour l'extrémité droite

    lost = false;

}


void dir_ball(char ** map_array, ball ball, bool * lost){ 
        //on regarde autour de la balle
        ball->right=map_array[ball->pos_y][ball->pos_x+1];
        ball->left=map_array[ball->pos_y][ball->pos_x-1];
        ball->down=map_array[ball->pos_y+1][ball->pos_x];
        ball->up=map_array[ball->pos_y-1][ball->pos_x];
        
        //on change la direction 
        if (ball->down==PLAYER1){
            ball->dir_y=-1;
        } else if (ball->down==FRONTWALL) *lost=true;
        if (ball->up==FRONTWALL || ball->up==PLAYER1){
            ball->dir_y=1;
        }
        if (ball->left==SIDEWALL){
            ball->dir_x=1;
        } 
        if (ball->right==SIDEWALL){
            ball->dir_x=-1;
        }
}

void freemap(char ** map_array){
    //on libère le tableau (quand on a fini seulment)
    for(int i = 0; i < L; i++){
	   free(map_array[i]); 
	}
	free(map_array);
}