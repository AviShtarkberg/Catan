// id:322530080 mail:avishb1213@gmail.com
#include <iostream>
#include "Catan.hpp"
using namespace std;
using namespace catan_game;

// player 1 settelments - 40 , 11. raods - 40,41 11,12.
// player 2 settelments - 36 ,17. rods -  36,35 17,18.
// player 3 settelments - 20 ,21. rods -  20,21 21,22.
// demo file to run the code and demonstrate a game that is running.
int main()
{
    Player a("a");
    Player b("b");
    Player c("c");
    Catan game(a, b, c, false);

    // a turn:
    a.roll_the_dice();
    a.build_road(41, 42);
    a.end_turn();

    // b turn:
    try
    {
        b.roll_the_dice();
    }
    catch (const exception &e)
    {
    }
    b.buy_dev_card();
    b.end_turn();

    // c turn
    try
    {
        c.roll_the_dice();
    }
    catch (const exception &e)
    {
    }
    c.end_turn();

    for (size_t i = 0; i < 70; i++)
    {
        try
        {
            a.roll_the_dice();
        }
        catch (const exception &e)
        {
        }
        a.end_turn();
        try
        {
            b.roll_the_dice();
        }
        catch (const exception &e)
        {
        }
        b.end_turn();
        try
        {
            c.roll_the_dice();
        }
        catch (const exception &e)
        {
        }
        c.end_turn();
    }

    // a turn
    try
    {
        a.roll_the_dice();
    }
    catch (const exception &e)
    {
    }

    a.trade("grain", 3, "ore", 1, &b);
    a.build_settlement(42);
    a.build_city(42);
    a.end_turn();

    // b turn:
    try
    {
        b.roll_the_dice();
    }
    catch (const exception &e)
    {
    }
    for (int i = 0; i < 5; i++)
    {
        try
        {
            b.buy_dev_card();
        }
        catch (const exception &e)
        {
        }
    }
    b.end_turn();

    // c turn
    try
    {
        c.roll_the_dice();
    }
    catch (const exception &e)
    {
    }
    try
    {
        c.trade("monopol", 1, "wool", 1, &b);
    }
    catch (const exception &e)
    {
    }

    c.end_turn();

    game.game_was_ended();
    return 0;
}