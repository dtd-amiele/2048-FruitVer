#include "fruit_play.h"
#include "splashkit.h"

/**
 * Return the required fruit bitmap
 * 
 * @params kind     Value which  represents the kind of fruit
 * @returns         The required bitmap based on the kind of fruit
 **/
bitmap fruit_bitmap(fruit_kind kind)
{
    switch(kind)
    {
        case NONE:          return bitmap_named("None");
        case CHERRY:	    return bitmap_named("Cherry");
		case GOOSEBERRY:	return bitmap_named("Gooseberry");
		case BLUEBERRY:		return bitmap_named("Blueberry");
        case POMEGRANATE:	return bitmap_named("Pomegranate");
        case APRICOT:       return bitmap_named("Apricot");
        case RASPBERRY: 	return bitmap_named("Raspberry");
        case BLACKBERRY:    return bitmap_named("Blackberry"); 
        case STRAWBERRY:    return bitmap_named("Strawberry"); 
        case CURRANT:       return bitmap_named("Currant");
        case APPLE:         return bitmap_named("Apple");
        case ORANGE:        return bitmap_named("Orange");
        case LEMON:         return bitmap_named("Lemon");
        case MELON:         return bitmap_named("Melon");
        default:            return bitmap_named("None");
    }
}

/**
 * Procedure to draw a fruit
 * @params
 *          value       value used to take bitmap 
 *          xx, yy      position to draw bitmap
**/
void draw_fruit(int value, double xx, double yy)
{
    bitmap to_draw;
    to_draw = fruit_bitmap(static_cast<fruit_kind>(value));
    draw_rectangle(COLOR_BLACK, xx, yy ,BOX_SIZE,BOX_SIZE);
    draw_bitmap(to_draw, xx+(BOX_SIZE - bitmap_width(to_draw))/2, yy + (BOX_SIZE- bitmap_height(to_draw))/2);
}

/**
 * Procedure use 2 loop to draw boxes of fruit
 * @params
 *          game        current playing game. Pass by reference
 *          x, y        position to draw first bitmap, change through loops
**/
void draw_box(const fruit_game_data &game, double x, double y)
{
    bitmap to_draw;
    double xx,yy;
    xx = x;
    yy = y;
    for (int i=0; i< SIZE; i++)
    {
        for (int j=0; j< SIZE; j++)
        {
            draw_fruit(game.fruits[i][j],xx,yy);
            xx = xx + BOX_SIZE;
        }
        yy = yy + BOX_SIZE;
        xx = x;
    }
}

/**
 * Procedure use 2 loop to draw boxes of fruit
 * @params
 *          game        current playing game, Pass by reference
 *          count       number of current fruits 
**/
void random_add_fruit(fruit_game_data &game, int count)
{
    int tmp, tmp_current;
    if ((SIZE*SIZE-count-1)>0)
        tmp = rnd(SIZE*SIZE -count-1)+1;
    else tmp=1;
    tmp_current=0;
    for (int i=0; i< SIZE; i++)
    {
        for (int j=0; j< SIZE; j++)
        {
            if (game.fruits[i][j]==0)
            {
                tmp_current +=1;
                if (tmp_current == tmp)
                 {
                    game.fruits[i][j]=1;
                    return;
                 }
            }
        }
    }  
}