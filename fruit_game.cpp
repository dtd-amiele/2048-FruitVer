#include "fruit_play.h"
#include "splashkit.h"


using namespace std;


/**
 * Return data of a new game, include:
 * Data of fruits
 * Assign value for first fruit
 * assign Score value
 * assign win value
 * assign lose value 
 * @returns     New game  
**/
fruit_game_data new_game()
{
    fruit_game_data result;
    for (int i=0; i< SIZE; i++){
        for (int j=0; j<SIZE; j++){
            result.fruits[i][j]=0;
        }
    }
    result.fruits[rnd(3)][rnd(3)] = 1; //random position for the first fruit
    result.score = 0;
    result.win = false;
    result.lose = false;
    return result;
}

/**
 * Procedure to draw a game, include:
 * Draw game frame
 * Draw boxex of fruit
 * Draw score
 * Draw high score
 * @params game         Value represents game to draw. Pass as reference. Use as constant
 *         high_score   Value store the highest score of previous games
**/
void draw_game(const fruit_game_data &game, int high_score)
{
        double y = screen_height()/2-(SIZE*BOX_SIZE)/2;
        double x = screen_width()/2-(SIZE*BOX_SIZE)/2;
        clear_screen(COLOR_WHITE);
        fill_rectangle(COLOR_AQUA,x,y,SIZE*BOX_SIZE,SIZE*BOX_SIZE);
        draw_rectangle(COLOR_BLACK,x,y,SIZE*BOX_SIZE,SIZE*BOX_SIZE);
        draw_box(game,x,y);
        
        draw_text("SCORE: "+to_string(game.score),COLOR_BLACK,"font1",10,0,0);
        draw_text("HIGH SCORE: "+to_string(high_score),COLOR_BLACK,"font1",10,100,0);
        
        refresh_screen();
}

/**
 * procedure to reset vector
 * @params      tmp     vector need to reset. Pass by reference
 */
void reset_vector(vector<int> &tmp)
{
        while (tmp.size()>0) tmp.pop_back();
}

/**
 * procedure to addvalue to array
 * @params  
 *          fruits      2-dimension array need to add value. Pass by reference
 *          i,j         indexes show the position in array to add value
 *          value       value need to add
 *          key         char represent the action of users

*/
void add_value(int fruits[][SIZE],int i, int j, int value, char key)
{
    if ((key == 'L') or (key=='R')) fruits[i][j]= value;
    else fruits[j][i]= value;
}


/**
 * function return a value from 2-dimension array
 * @params  
 *          fruits      2-dimension array need to take value from . Pass by reference
 *          i,j         indexes show the position in array to take value
 *          key         char represent the action of users

*/
int assign_value(int fruits[][SIZE],int i, int j,  char key)
{
    if ((key == 'L') or (key=='R')) return(fruits[i][j]);
    else return(fruits[j][i]);    
}
/**
 * procedur to merge tosame fruits
 * @params
 *          tmp_value       value represent the higher fruit. Pass by reference
 *          tmp             vector contains fruits to merge. Pass by reference
 *          score           value of game score. Pass by reference
 */
void  merge_2_fruits(int &tmp_value,vector <int> &tmp, int &score)
{
    tmp_value +=1;
    tmp.pop_back();
    tmp.push_back(tmp_value);
    score +=1;
}

/**
 * Procedure to update array when press Left or Up arrow key
 * @params
 *          fruits      2-dimension array to update. Pass by reference
 *          i           value usedfor position in array
 *          tmp         vector contains values to update. pass by reference. use as constant
 *          char        char represent the action of users
 */
void  Update_array_LeftUp(int fruits[][SIZE],int i,const vector <int> &tmp,char key)
{
    for (int j=0; j< tmp.size();j++)
    {
        add_value(fruits,i,j,tmp[j],key);
    }
    for (int j=tmp.size() ; j<SIZE;j++)
    {
        add_value(fruits,i,j,0,key);
    } 
}

/**
 * Procedure to update array when press Right or Down arrow key
 * @params
 *          fruits      2-dimension array to update. Pass by reference
 *          i           value usedfor position in array
 *          tmp         vector contains values to update. pass by reference. use as constant
 *          char        char represent the action of users
 */
void  Update_array_RightDown(int fruits[][SIZE],int i,const vector <int> &tmp,char key)
{
    for (int j=0; j< tmp.size();j++)
    {
        add_value(fruits,i,SIZE-1-j,tmp[j],key);
    }

    for (int j=0 ; j<SIZE-tmp.size();j++)
    {
        add_value(fruits,i,j,0,key);
    }
}

/**
 * procedure represent actions when user press Left or Up narrow key, include:
 * move in all fruits of box to the Left or go up based on user's action
 * Merge if 2 same fruit touch
 * @params 
 *          game      Value represents game to draw. Pass as reference. Use as constant 
 *          key       Char represent the action of users   
 *          
 */
void presskeyLeftUp_call(fruit_game_data &game, char key)
{
    vector<int> tmp;
    int tmp_value,i,j;
    int count=0;
    i=0;
    while (i<SIZE)
    {
        reset_vector(tmp);
        j=0;
        while (j<SIZE)
        {
            tmp_value =assign_value(game.fruits,i,j,key);
            if (tmp_value>0 ) 
            {
                if ((tmp.size()>0) and (tmp_value==tmp[tmp.size()-1])) 
                {
                    merge_2_fruits(tmp_value, tmp,game.score);

                    if (j<SIZE-1)
                    {
                        j=j+1;
                        tmp_value = assign_value(game.fruits,i,j,key);
                        tmp.push_back(tmp_value);
                    }
                }
            else
                tmp.push_back(tmp_value);
            }
        j=j+1;   
        }
        count = count + tmp.size();
        Update_array_LeftUp(game.fruits,i,tmp,key);
    
    i = i+1;
    }
    random_add_fruit(game,count);
}


/**
 * procedure represent actions when user press Right or Down narrow key, include:
 * move in all fruits of box to the Left or go up based on user's action
 * Merge if 2 same fruits touch
 * @params 
 *          game      Value represents game to draw. Pass as reference. Use as constant 
 *          key       Char represent the action of users   
 *          
 */
void presskeyRightDown_call(fruit_game_data &game, char key)
{
    vector<int> tmp;
    int tmp_value,i,j;
    int count=0;
    i=0;
    while (i<SIZE)
    {
        reset_vector(tmp);

        j=SIZE-1;
        while (j>=0)
        {
            tmp_value =assign_value(game.fruits,i,j,key);
      
            if (tmp_value>0 ) 
            {
            if ((tmp.size()>0) and (tmp_value==tmp[tmp.size()-1])) 
                {
                    merge_2_fruits(tmp_value, tmp,game.score);
                    if (j>0)
                    {
                        j=j-1;
                        tmp_value = assign_value(game.fruits,i,j,key);
                        tmp.push_back(tmp_value);
                    }
                }
            else
                tmp.push_back(tmp_value);
            }   
        j = j-1;
        }
        count = count + tmp.size();
        Update_array_RightDown(game.fruits,i,tmp,key);

    i = i+1;    
    }
    random_add_fruit(game,count);
}

/**
 * Procedure to check handle input from user, and call procedure to execute actions
 * @params         
            game       Value represents the playing game. Pass as reference.

**/
void handle_input(fruit_game_data &game)
{
       if (key_typed(LEFT_KEY)) presskeyLeftUp_call(game,'L');
       if (key_typed(RIGHT_KEY)) presskeyRightDown_call(game,'R');
       if (key_typed(UP_KEY)) presskeyLeftUp_call(game,'U');
       if (key_typed(DOWN_KEY)) presskeyRightDown_call(game,'D');
}

/**
 * Procedure to check whether game quit, include:
 * Check whether the highest fruit appears
 * Check whether moves can made
 * @params         
            game       Value represents the playing game. Pass as reference.

**/
void check_quit_game(fruit_game_data &game)
{
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE;j++)
        {
            if (game.fruits[i][j]==MAXFRUIT)
            {    
                game.win = true;
                return;
            }
        }
    }
    
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE;j++)
        {
            if (game.fruits[i][j]==0)
            {    
                return;
            }
        }
    }
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE;j++)
        {
            if (j==SIZE-1)
            {
                if ((game.fruits[i][j]==game.fruits[i+1][j]))
                    return;
            }
            else
            if (j==SIZE-1)
            {
                if ((game.fruits[i][j]==game.fruits[i][j+1]))
                    return;  
            }
            else
            if ((game.fruits[i][j]==game.fruits[i][j+1]) ||  (game.fruits[i][j]==game.fruits[i+1][j])) 
            {    
                return;
            }
        }
    }
    game.lose = true;
}

/**
 * function to return value to draw line
 * @params s    string to draw
 */
double calculate(string s)
{
    return (FINISH_BOX/2 - s.length()*4);
}

/**
 * Procedure to draw line inform of finish game

 * @params         
            s1,s2,s3,s4    string include information to inform
            x,y         position to draw string

**/
void draw_line(string s1, string s2, string s3,string s4, double x, double y)
{
    draw_text(s1,COLOR_BLACK,"font1",15,x+calculate(s1),y+20);   
    draw_text(s2,COLOR_BLACK,"font1",15,x+calculate(s2),y+40);   
    draw_text(s3,COLOR_BLACK,"font1",15,x+calculate(s3),y+60);  
    draw_text(s4,COLOR_BLACK,"font1",15,x+calculate(s4)-10,y+80);   
    draw_text("Press S to start new game",COLOR_BLACK,"font1",9,x+3,y+110); 
    draw_text("Press ESC to close game",COLOR_BLACK,"font1",9,x+7,y+125); 
}

/**
 * Procedure to draw finish box

 * @params         
 *          win         value to check whether user win the game
 *          lose        value to check whether user lose the game
 *          score       value of score 
 *          high_score  value of highest score. Pass by reference
**/
void draw_finish_box(bool win, bool lose, int score, int &high_score)
{
    double x = screen_width()/2-FINISH_BOX/2;
    double y = screen_height()/2-FINISH_BOX/2;
    fill_rectangle(COLOR_PINK,x,y,FINISH_BOX, FINISH_BOX);
    draw_rectangle(COLOR_WHITE,x,y,FINISH_BOX, FINISH_BOX);
    if (high_score <score) high_score = score;
    if (win)
    {
        draw_line(" Hooray! ^_^ ","YOU WIN!!","SCORE: "+to_string(score),"High score: "+to_string(high_score),x,y);
    }
    else
    {
        draw_line(" Out of moves!  ","GAME OVER!!","SCORE: "+to_string(score),"High score: "+to_string(high_score),x,y);
    }
    refresh_screen();    
}

