// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Board.hpp"
#include "DevCards.hpp"
#include "Catan.hpp"
/*this is the main and most important class of the project, will hold
all the functionallity that a player in a catan game will need.
*/
namespace catan_game
{
    class Catan;
    class Player
    {
    public:
        // player constructor:
        Player(std::string name)
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            this->_name = name;
            set_res_map();
        }

        // getters:
        void set_next_player(Player *player)
        {
            this->_next_player = player;
        }
        void add_resourse(Resource resource)
        {
            _resources[resource]++;
        }

        // inline setters:
        void set_board(Board *board)
        {
            this->_board = board;
        }
        void set_game_started()
        {
            this->game_started = true;
        }

        std::string get_name()
        {
            return this->_name;
        }
        std::map<Resource, int> &get_resourses()
        {
            return this->_resources;
        }

        void set_other_players(std::vector<Player *> other_players)
        {
            this->_other_players = other_players;
        }

        void set_number_of_resource()
        {
            this->_number_of_resource++;
        }

        int get_number_of_resource()
        {
            return this->_number_of_resource;
        }

        std::map<std::string, int> get_cards()
        {
            return this->_myCards;
        }

        void set_deck(std::vector<DevCards *> deck)
        {
            this->_deck = deck;
        }

        int get_wp()
        {
            return this->_points;
        }

        void set_game(Catan *game)
        {
            this->_game = game;
        }

        // outline functions:
        void build_settlement(int n1);
        void build_city(int n1);
        void build_road(int n1, int n2);
        void roll_the_dice();
        void buy_dev_card();
        void use_monopol(std::string res);
        void use_road_builder();
        void use_winning_point();
        void use_year_of_planty(Resource r1, Resource r2);
        void active_turn();
        void end_turn();
        void trade(std::string s1, int amount1, std::string s2, int amount2, Player *trader);
        void check_if_game_ended();

    protected:
        std::string _name;
        Board *_board;
        std::map<Resource, int> _resources;
        bool game_started = false;
        int _points = 0;
        bool _turn = false;
        Player *_next_player;
        std::vector<Player *> _other_players;
        bool _dice_rolled = false;
        int _number_of_resource = 0;
        std::vector<DevCards *> _deck;
        std::map<std::string, int> _myCards;
        bool year_of_planty_falg = false;
        int br_falg = 0;
        Catan *_game = nullptr;

        // for yop:
        int amount_current_res1 = 0;
        int amount_current_res2 = 0;
        Resource currenet_res1 = NO_RESOURCE;
        Resource currenet_res2 = NO_RESOURCE;

        // for a turn to check if
        bool _dev_used = false;

        void set_res_map();
        bool can_build_road(int n1, int n2);
        bool can_build_s(int n1);
        void can_build_city(int n1);
        void pay(std::map<Resource, int> cost);
        bool check_valid_for_road_builder(Node *node1, Node *node2, const Player *p1, const Player *p2);
        bool check_valid_for_road_edges(Node *node1, Node *node2);
        bool aux_can_build_set(std::vector<Edge *> n1_edges, int n1);
        void add_resources_to_players(int totalRoll);
        void total_dice_was_7();
        void decrease_resources(Player *p);
        void set_my_cards();
        void dev_card_exe(std::string type);
        void reduce_increase(int i, Resource res);
        void end_yop();
        void trade_resource(std::string s1, int amount1, std::string s2, int amount2, Player *trader);
        void trade_devCards(std::string s1, int amount1, std::string s2, int amount2, Player *trader);
        void add_the_res(Builder *builder, std::vector<Land *> lands, int i);
        void check_dice_dev();
    };
}

#endif // PLAYER_HPP
