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

    joueur player1 = (joueur)malloc(sizeof(struct platform)); //raquette joueur1

    ball ball = (struct ball *)malloc(sizeof(struct ball)); //la balle donc

    initscr();
    cbreak();

    clear();

    //le fichier map sera à transférer dans la mémoire du mC
    FILE * map;
    map = fopen("map.txt", "r");
    
    //création de la map exploitable
    char ** map_array;


    //on alloue un espace mémoire pour stocker les pointeurs sur chaque lignes (il y en a L)
    map_array = malloc(L*sizeof(map_array));
	
    for (int i=0 ; i<L ; ++i){
    //on alloue un espace mémoire de taille C pour chque ligne
        map_array[i]=malloc(C*sizeof(char));
    }
    
    bool lost;

    //initialisation de la balle et des joueurs
    init(map_array, player1, ball, map, &lost);



    while(1){
    
        clear();
    
        printmap(map_array);

        dir_ball(map_array, ball, &lost); //gère la direction de la balle 
    
        if (lost==true) break; //lost flag

        move_ball(map_array, ball);

        move_player1(map_array, player1);

        refresh();

    }

    endwin();
    clear();
    fclose(map);
    printf("\n\n\n\n*******PERDU*******\n\n\n\n");
    
    return 0;

}