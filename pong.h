//pong.h avec les protoypes et types définis

#define C 47 //colonnes
#define L 30 //lignes
#define S 7 //platform size


//structure qui représente un joueur (plateforme, score?, bonus?)
struct joueur {
    int left;
    int right;
};

typedef struct platform * joueur;

//structure qui définit la balle
struct ball {
    int pos_x;
    int pos_y;
    int dir_x;
    int dir_y;
    char up;
    char down;
    char left;
    char right;
};

typedef struct ball * ball;







//fonction qui renverra au main la direction que le joueur à choisi. 
char direction();
//void fill_map_array(char*** , FILE*);
//void print_map_array(char**);
//void clear_map_array(char***);