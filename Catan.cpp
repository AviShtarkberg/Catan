// id:322530080 mail:avishb1213@gmail.com
#include <iostream>
#include "Catan.hpp"

using namespace std;
using namespace catan_game;

/**
 * Prompts the player to enter a node to build a settlement and adds initial resources to the player.
 */
void Catan::build_s_before_start(Player &p)
{
    int n1;
    cout << p.get_name() << " please enter the node in which you want to build a settlement: ";
    cin >> n1;
    if (n1 < 0 || n1 > 53)
    {
        __throw_runtime_error("enter a valid number!!!");
    }
    p.build_settlement(n1);
    add_resorces_to_player(n1, &p);
}

/**
 * Prompts the player to enter the starting and ending nodes to build a road.
 */
void Catan::build_r_before_start(Player &p)
{
    int n1, n2;
    cout << p.get_name() << " please enter the starting node in which you want to build the road: ";
    cin >> n1;
    cout << p.get_name() << " please enter the end node in which you want to build the road: ";
    cin >> n2;
    if (n1 < 0 || n1 > 53 || n2 < 0 || n2 > 53)
    {
        __throw_runtime_error("enter a valid number!!!");
    }
    p.build_road(n1, n2);
}

/**
 * Adds resources to the player based on the lands adjacent to the given node.
 */
void Catan::add_resorces_to_player(int n1, Player *player)
{
    vector<Land *> re = _board->get_node(n1)->get_lands();
    for (size_t i = 0; i < re.size(); i++)
    {
        player->add_resourse(re[i]->get_resource());
        player->set_number_of_resource();
    }
}

/**
 * Starts the player's turn and performs initial building actions.
 */
void Catan::start_player(Player &p)
{
    p.active_turn();
    build_s_before_start(p);
    build_s_before_start(p);
    build_r_before_start(p);
    build_r_before_start(p);
    p.set_game_started();
    p.end_turn();
}

/**
 * Initializes the Catan game with three players and sets up the board and player turns.
 */
Catan::Catan(Player &p1, Player &p2, Player &p3, bool random_game) : _p1(p1), _p2(p2), _p3(p3)
{
    this->_board = new Board(random_game);
    p1.set_board(_board);
    p2.set_board(_board);
    p3.set_board(_board);

    p1.set_game(this);
    p2.set_game(this);
    p3.set_game(this);

    _p1.set_next_player(&p2);
    _p2.set_next_player(&p3);
    _p3.set_next_player(&p1);

    vector<Player *> other_players1 = {&p2, &p3};
    vector<Player *> other_players2 = {&p1, &p3};
    vector<Player *> other_players3 = {&p1, &p2};

    p1.set_other_players(other_players1);
    p2.set_other_players(other_players2);
    p3.set_other_players(other_players3);

    start_the_game();
    set_deck();

    _p1.set_deck(this->_deck);
    _p2.set_deck(this->_deck);
    _p3.set_deck(this->_deck);

    _p1.active_turn();
}

/**
 * Sets up and shuffles the deck of development cards.
 */
void Catan::set_deck()
{
    for (size_t j = 0; j < 6; j++)
    {
        this->_deck.push_back(new MonopolCard());
        this->_deck.push_back(new RoadBuilderCard());
        this->_deck.push_back(new YearOfPlentyCard());
    }

    for (size_t j = 0; j < 3; j++)
    {
        this->_deck.push_back(new Knight());
    }

    for (size_t j = 0; j < 4; j++)
    {
        this->_deck.push_back(new WinningPoint());
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(this->_deck.begin(), this->_deck.end(), g);
}

/**
 * Destructor for the Catan game, deallocates the board and deck of cards.
 */
Catan::~Catan()
{
    delete this->_board;
    for (auto card : _deck)
    {
        delete card;
    }
}
