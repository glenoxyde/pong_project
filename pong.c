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

    //déclaration des objets utilisés
    joueur player1 = (joueur)malloc(sizeof(struct platform)); //raquette joueur1
    joueur player2 = (joueur)malloc(sizeof(struct platform)); //raquette joueur2 robot

    ball ball = (struct ball *)malloc(sizeof(struct ball)); //la balle donc

    initscr();
    cbreak();

    clear();

    //ouverture du fichier contentant la map
    FILE * map;
    map = fopen("map.txt", "r");
    
    //création de la map exploitable
    char ** map_array;

    //on alloue un espace mémoire pour stocker les pointeurs sur chaque lignes (il y en a L)
    map_array = malloc(L*sizeof(map_array));
	
    for (int i=0 ; i<L ; ++i){
    //on alloue un espace mémoire de taille C colonnes pour chaque ligne
        map_array[i]=malloc(C*sizeof(char));
    }
    
    //booléens de la victoire
    bool lost1;
    bool lost2;

    //valeur de timeout (décrémentée à chanque round)
    int t=1000;

    //initialisation de la balle et des joueurs
    init(map_array, player1, player2, ball, map, &lost1, &lost2);

    while(1){

        clear();
        t-=1;

        printmap(map_array);

        //gère la direction de la balle
        dir_ball(map_array, ball, &lost1, &lost2, player1, player2);  
    
        //lost flags
        if (lost1==true || lost2==true) break; 

        move_ball(map_array, ball);
        
        timeout(t/10);
        char input = getch();

        move_player1(map_array, player1, input);
        move_player2(map_array, player2, ball);
        //move_player3(map_array, player1, ball);

        refresh();

    }

    endwin();
    clear();
    fclose(map);
    if (lost2) printf("\n\n\n\n*******J1 GAGNE*******\n\n\n\n");
    if (lost1) printf("\n\n\n\n*******J2 GAGNE*******\n\n\n\n");
    return 0;

}