//pong.h avec les protoypes et types définis

#define C 47 //colonnes
#define L 30 //lignes
#define S 7 //platform size

#define PLAYER1 'n'
#define PLAYER2 'u'
#define SIDEWALL '*'
#define FRONTWALL '-'


//structure qui représente un joueur (plateforme, score?, bonus?)
struct platform {
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


void printmap(char **);
void move_ball(char **, ball);
void move_player1(char ** , joueur);
void init(char **, joueur, ball, FILE*, bool*);
void dir_ball(char **, ball, bool *);
void freemap(char**);