#include "splashkit.h"
#include <vector>

#define SIZE 4
#define BOX_SIZE 100
#define MAXFRUIT 13
#define FINISH_BOX 150


using namespace std;

enum fruit_kind
{
    NONE,
    CHERRY, 
    GOOSEBERRY, 
    BLUEBERRY, 
    POMEGRANATE, 
    APRICOT, 
    RASPBERRY, 
    BLACKBERRY, 
    STRAWBERRY, 
    CURRANT,
    APPLE,
    ORANGE,
    LEMON,
    MELON
};



struct fruit_game_data
{
    int fruits[4][4];
    int score;
    bool win;
    bool lose;
};

//fruit.cpp
bitmap fruit_bitmap(fruit_kind kind);
void draw_box(const fruit_game_data &game, double x, double y);
void draw_fruit(int value, double xx, double yy);
void random_add_fruit(fruit_game_data &game, int count);

//fruit_game.cpp
fruit_game_data new_game();
void draw_game(const fruit_game_data &game, int high_score);

double calculate(string s);
void draw_line(string s1, string s2, string s3,string s4, double x, double y);
void draw_finish_box(bool win, bool lose, int score, int &high_score);
void check_quit_game(fruit_game_data &game);

void  merge_2_fruits(int &tmp_value,vector <int> &tmp, int &score);
void  Update_array_LeftUp(int fruits[][SIZE],int i,const vector <int> &tmp,char key);
void  Update_array_RightDown(int fruits[][SIZE],int i,const vector <int> &tmp,char key);

void handle_input(fruit_game_data &game);

void reset_vector(vector<int> &tmp);
void add_value(int fruits[][SIZE],int i, int j, int value, char key);
int assign_value(int fruits[][SIZE],int i, int j,  char key);
void presskeyLeftUp_call(fruit_game_data &game, char key);
void presskeyRightDown_call(fruit_game_data &game, char key);