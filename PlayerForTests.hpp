#include "Player.hpp"
#include <iostream>
using namespace std;

/*this class will be responsible to represent a player that have
more functionallity than a regular player, we dont want to allow to a regular
player to increase his points for example.
*/
namespace catan_game
{
    class PlayerForTest : public Player
    {
    public:
        PlayerForTest(string name) : Player(name)
        {
            this->_resources[WOOL] = 100;
            this->_resources[BRICK] = 100;
            this->_resources[LUMBER] = 100;
            this->_resources[ORE] = 100;
            this->_resources[GRAIN] = 100;
            this->_myCards["monopol"] = 3;
            this->_myCards["knight"] = 1;
            this->_myCards["year of plenty"] = 3;
            this->_myCards["winning point"] = 3;
            this->_myCards["road builder"] = 3;
        }

        void add_knights()
        {
            this->_points = 8;
            this->_myCards["knight"] = 3;
            check_if_game_ended();
        }

        void set_res_to_0()
        {
            this->_resources[WOOL] = 0;
            this->_resources[BRICK] = 0;
            this->_resources[LUMBER] = 0;
            this->_resources[ORE] = 0;
            this->_resources[GRAIN] = 0;
        }

        void set_res_to_100()
        {
            this->_resources[WOOL] = 100;
            this->_resources[BRICK] = 100;
            this->_resources[LUMBER] = 100;
            this->_resources[ORE] = 100;
            this->_resources[GRAIN] = 100;
        }

        void roll_number(int n)
        {
            add_resources_to_players(n);
        }

        void roll_7()
        {
            total_dice_was_7();
        }

        void set_number_of_res(int n)
        {
            this->_number_of_resource = n;
        }

        bool get_turn()
        {
            return this->_turn;
        }

        void set_points()
        {
            this->_points = 9;
        }
    };
}
