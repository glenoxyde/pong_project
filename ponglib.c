
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

void move_player1(char ** map_array, joueur player1, int d_player1){
    //on met la position du joueur à jour 
    
    
    if (d_player1=='a'){
        if (player1->left>2){

            map_array[L-2][player1->right]=' ';
            map_array[L-2][player1->right-1]=' ';
            map_array[L-2][player1->left-1]='n';
            map_array[L-2][player1->left-2]='n';

            player1->left-=2;
            player1->right-=2;
        } else {

        }
    }
    if (d_player1=='d'){
        if (player1->right<C-3){
            
            map_array[L-2][player1->left]=' ';
            map_array[L-2][player1->left+1]=' ';
            map_array[L-2][player1->right+1]='n';
            map_array[L-2][player1->right+2]='n';


            player1->left+=2;
            player1->right+=2;
        } else {

        }
    } 
}

void move_player2(char ** map_array, joueur player2, ball ball){
    
    int middle = (player2->left)+4;
    //on met la position du joueur à jour 
    if (ball->pos_x < middle){
        if (player2->left>1){
            map_array[1][player2->left-1]='u';
            //map_array[1][player2->left-2]='u';
            map_array[1][player2->right]=' ';
            //map_array[1][player2->right-1]=' ';

            player2->left-=1;
            player2->right-=1;
        } else {

        }
    }
    if (ball->pos_x > middle){
        if (player2->right<C-3){

            map_array[1][player2->left]=' ';
            //map_array[1][player2->left+1]=' ';
            map_array[1][player2->right+1]='u';
            //map_array[1][player2->right+2]='u';


            player2->left+=1;
            player2->right+=1;
        } else {

        }
    } 
}
/*
void move_player3(char ** map_array, joueur player1, ball ball){
    
    int middle = (player1->left)+4;
    //on met la position du joueur à jour 
    if (ball->pos_x < middle){
        if (player1->left>2){
            map_array[L-2][player1->left-1]='n';
            //map_array[1][player1->left-2]='u';
            map_array[L-2][player1->right]=' ';
            //map_array[1][player1->right-1]=' ';

            player1->left-=1;
            player1->right-=1;
        } else {

        }
    }
    if (ball->pos_x > middle){
        if (player1->right<C-3){

            map_array[L-2][player1->left]=' ';
            //map_array[1][player1->left+1]=' ';
            map_array[L-2][player1->right+1]='n';
            //map_array[1][player1->right+2]='u';


            player1->left+=1;
            player1->right+=1;
        } else {

        }
    } 
}
*/



void init(char ** map_array, joueur player1, joueur player2, ball ball, FILE* map, bool * lost1, bool * lost2){

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

    player1->left =19; //indice de la colonne avec l'extrémité gauche de la plateforme du bas
    player1->right =27; //idem pour l'extrémité droite

    player2->left =19;
    player2->right =27;

    *lost1 = false;
    *lost2 = false;

}


void dir_ball(char ** map_array, ball ball, bool * lost1, bool * lost2, joueur player1, joueur player2){ 
        
        int middle1 = (player1->left)+4;
        int middle2 = (player2->left)+4;
        
        //on regarde autour de la balle
        ball->right=map_array[ball->pos_y][ball->pos_x+1];
        ball->left=map_array[ball->pos_y][ball->pos_x-1];
        ball->down=map_array[ball->pos_y+1][ball->pos_x];
        ball->up=map_array[ball->pos_y-1][ball->pos_x];
        
        //on change la direction 
        if (ball->down==PLAYER1){
            ball->dir_y=-1;
            if (ball->dir_x==1){
                if (ball->pos_x < middle1){
                    ball->dir_x=-1;
                } else ball->dir_x=1;
            } else if (ball->dir_x==-1){
                if (ball->pos_x < middle1){
                    ball->dir_x=-1;
                } else ball->dir_x=1;
            }
        } else if (ball->down==FRONTWALL) *lost1=true;
        
        /*
        if (ball->up==PLAYER2){
            ball->dir_y=1;
            if (ball->dir_x==1){
                if (ball->pos_x < middle2){
                    ball->dir_x=-1;
                } else ball->dir_x=1;
            } else if (ball->dir_x==-1){
                if (ball->pos_x < middle2){
                    ball->dir_x=-1;
                } else ball->dir_x=1;
            }
        } else if (ball->up==FRONTWALL) *lost2=true;
        */
        if (ball->up==PLAYER2){
            ball->dir_y=1;
        } else if (ball->up==FRONTWALL) *lost2=true;
        
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