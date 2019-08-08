#include "splashkit.h"
#include "fruit_play.h"



void load_resources()
{
    load_resource_bundle("game_bundle", "fruit_play.txt");
    load_font("font1","font.ttf");
}


int main()
{
    open_window("2048- Fruit version",600,600);
    load_resources();
   
    fruit_game_data game;
    game = new_game();
    int high_score = 0;
    while (not quit_requested())
    {
        process_events();
        check_quit_game(game);
        if ((game.win) || (game.lose))
        {
            draw_finish_box(game.win,game.lose,game.score,high_score);
            if (key_typed(ESCAPE_KEY)) break;
            if (key_typed(S_KEY))  game= new_game();   
        }
        else
        {
            handle_input(game);
            draw_game(game,high_score);
        }

    }
    return 0;
}