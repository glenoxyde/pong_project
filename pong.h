//pong.h avec les protoypes et types définis

#define C 48 //colonnes
#define L 30 //lignes
#define S 9 //platform size

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
void move_player1(char ** , joueur, int);
void move_player2(char ** , joueur, ball);
void move_player3(char ** , joueur, ball);
void init(char **, joueur, joueur, ball, FILE*, bool*, bool*);
void dir_ball(char **, ball, bool *, bool*, joueur, joueur);
void freemap(char**);
