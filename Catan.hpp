// id:322530080 mail:avishb1213@gmail.com
#ifndef CATAN_HPP
#define CATAN_HPP
#include <iostream>
#include "Player.hpp"
using namespace std;

/*This class will be responsible to do the connection between each
player in the game. The class will force the players to add thier first settelments and roads.
Will set the other and next turn of each player and will set the deck of each of them.
*/
namespace catan_game
{
    class Catan
    {
    public:
        Catan(Player &p1, Player &p2, Player &p3, bool random_game);

        void start_player(Player &p);

        void build_s_before_start(Player &p);

        void build_r_before_start(Player &p);

        void start_the_game()
        {
            start_player(_p1);
            start_player(_p2);
            start_player(_p3);
        }

        Board *get_board()
        {
            return this->_board;
        }

        // will be seted by the player that finish the game
        void set_game_was_ended()
        {
            this->_game_was_ended = true;
        }

        bool game_was_ended()
        {
            if (_game_was_ended)
            {
                cout << "The game was ended !!!" << endl;
                return true;
            }
            else
            {
                cout << "the game didnt ended yet!!!";
            }
            return false;
        }

        ~Catan();

    private:
        Player &_p1;
        Player &_p2;
        Player &_p3;
        Board *_board;
        void add_resorces_to_player(int n1, Player *player);
        vector<DevCards *> _deck;
        void set_deck();
        bool _game_was_ended = false;
    };
}

#endif // CATAN_HPP