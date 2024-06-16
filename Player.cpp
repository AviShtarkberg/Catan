// id:322530080 mail:avishb1213@gmail.com
#include "Player.hpp"
using namespace std;
using namespace catan_game;

// Initializes the player's resource map with zero values for all resources.
void Player::set_res_map()
{
    _resources[BRICK] = 0;
    _resources[LUMBER] = 0;
    _resources[GRAIN] = 0;
    _resources[ORE] = 0;
    _resources[WOOL] = 0;
}

// Initializes the player's development cards with zero counts for all card types.
void Player::set_my_cards()
{
    this->_myCards["monopol"] = 0;
    this->_myCards["road builder"] = 0;
    this->_myCards["year of plenty"] = 0;
    this->_myCards["knight"] = 0;
    this->_myCards["winning point"] = 0;
}

// Builds a settlement at the specified node if the game has not started or if conditions are met.
void Player::build_settlement(int n1)
{
    if (n1 < 0 || n1 > 53)
    {
        __throw_runtime_error("enter valid numbers!");
    }
    if (!game_started && _turn && _board->get_node(n1)->get_builder() == nullptr)
    {
        _board->get_node(n1)->build_settlement();
        _board->get_node(n1)->get_builder()->set_owner(this);
        this->_points++;
        cout << "-" << this->_name << " built a settlement in " << n1 << endl;
    }
    else if (game_started && can_build_s(n1))
    {
        _board->get_node(n1)->build_settlement();
        _board->get_node(n1)->get_builder()->set_owner(this);
        this->_points++;
        cout << "-" << this->_name << " built a settlement in " << n1 << endl;
        check_if_game_ended();
    }
    else
    {
        __throw_runtime_error("you cant build here!!");
    }
}

// Upgrades a settlement to a city at the specified node and deducts resources accordingly.
void Player::build_city(int n1)
{
    if (n1 < 0 || n1 > 53)
    {
        __throw_runtime_error("enter valid numbers!");
    }
    can_build_city(n1);
    _board->get_node(n1)->build_city();
    _board->get_node(n1)->get_builder()->set_owner(this);
    this->_points++;
    pay(City_cost::get_cost());
    cout << "-" << this->_name << " built a city in " << n1 << endl;
    check_if_game_ended();
}

// Builds a road between two nodes if conditions are met and deducts resources if required.
void Player::build_road(int n1, int n2)
{
    if (n1 < 0 || n1 > 53 || n2 < 0 || n2 > 53)
    {
        __throw_runtime_error("enter valid numbers!");
    }
    if (can_build_road(n1, n2))
    {
        _board->get_edge(n1, n2)->build_road();
        _board->get_edge(n1, n2)->get_road()->set_owner(this);
        if (this->br_falg == 0 && game_started)
        {
            pay(Road_cost::get_cost());
        }
        else
        {
            br_falg--;
        }
        cout << "-" << this->_name << " built a road in " << n1 << "," << n2 << endl;
    }
    else
    {
        __throw_runtime_error("unvalid call for build raod!!");
    }
}

// Rolls two dice, calculates the total, and handles resource distribution or special actions based on the roll.
void Player::roll_the_dice()
{
    if (!this->_turn)
    {
        __throw_runtime_error("you cant roll not in your turn!!!");
    }
    if (!this->_dice_rolled)
    {
        int diceRoll1 = (std::rand() % 6) + 1;
        int diceRoll2 = (std::rand() % 6) + 1;
        int totalRoll = diceRoll1 + diceRoll2;
        cout << "-" << "the dice number in this turn is: " << totalRoll << endl;
        this->_dice_rolled = true;
        if (totalRoll != 7)
        {
            add_resources_to_players(totalRoll);
        }
        else
        {
            total_dice_was_7();
        }
    }
    else
    {
        __throw_runtime_error("you cant roll twice !!!");
    }
}

// Handles the scenario when the dice roll is 7 by reducing resources for all players.
void Player::total_dice_was_7()
{
    decrease_resources(this);
    decrease_resources(this->_other_players[0]);
    decrease_resources(this->_other_players[1]);
}

// Reduces a player's resources by half if they have more than 7 resources.
void Player::decrease_resources(Player *p)
{
    if (p->_number_of_resource >= 7)
    {
        int temp = p->_number_of_resource / 2;
        for (int i = 0; i < temp; i++)
        {
            string s;
            cout << "-" << p->get_name() << " please enter a card that you want to return" << endl;
            cin >> s;
            if (res_from_string(s) == NO_RESOURCE)
            {
                __throw_runtime_error("you must enter a valid resource");
            }

            if (p->get_resourses()[res_from_string(s)] < 1)
            {
                __throw_runtime_error("you must enter a valid resource");
            }
            p->get_resourses()[res_from_string(s)]--;
            p->_number_of_resource--;
        }
    }
}

// Allocates resources to players based on the total dice roll by checking the corresponding lands and nodes.
void Player::add_resources_to_players(int totalRoll)
{
    vector<Land *> lands = _board->get_land(totalRoll); // will return the lands vector that has total roll number
    for (size_t i = 0; i < lands.size(); i++)
    {
        vector<Node *> nodes = lands[i]->get_nodes();
        for (size_t j = 0; j < nodes.size(); j++)
        {
            Builder *builder = nodes[j]->get_builder();
            if (builder != nullptr)
            {
                add_the_res(builder, lands, i);
            }
        }
    }
}

// Adds resources to the specified builder's owner based on the builder type.
void Player::add_the_res(Builder *builder, vector<Land *> lands, int i)
{
    Player *p = builder->get_owner();
    if (builder->get_type() == "settlement")
    {
        p->_resources[lands[i]->get_resource()]++;
        p->_number_of_resource++;
    }
    if (builder->get_type() == "city")
    {
        p->_resources[lands[i]->get_resource()] += 2;
        this->_number_of_resource += 2;
    }
}

// Checks if a road can be built between two nodes based on turn, resource availability, and edge occupancy.
bool Player::can_build_road(int n1, int n2)
{
    if (!_turn)
    {
        __throw_runtime_error("you cant build not in your turn!!!");
    }
    if (_board->get_edge(n1, n2)->get_road() != nullptr)
    {
        __throw_runtime_error("this edge is not empty!!!");
    }
    if (game_started && !Road_cost::check_if_fits(_resources))
    {
        __throw_runtime_error("you dont have enough resources to build the road!");
    }
    Node *no1 = _board->get_node(n1);
    Node *no2 = _board->get_node(n2);
    const Player *p1 = nullptr;
    const Player *p2 = nullptr;
    return check_valid_for_road_edges(no1, no2) ||
           check_valid_for_road_builder(no1, no2, p1, p2);
}

// Checks if the road can be built based on the builders at the specified nodes.
bool Player::check_valid_for_road_builder(Node *node1, Node *node2, const Player *p1, const Player *p2)
{
    if (node1->get_builder() != nullptr)
        p1 = node1->get_builder()->get_owner();
    if (node2->get_builder() != nullptr)
        p2 = node2->get_builder()->get_owner();
    if (p1 == this || p2 == this)
    {
        return true;
    }
    return false;
}

// Checks if the road can be built based on the presence of adjacent roads owned by the player.
bool Player::check_valid_for_road_edges(Node *node1, Node *node2)
{
    vector<Edge *> n1_edges = node1->get_edges();
    vector<Edge *> n2_edges = node2->get_edges();
    for (size_t i = 0; i < n1_edges.size(); i++)
    {
        if (n1_edges[i]->get_road() != nullptr && n1_edges[i]->get_road()->get_owner() == this)
        {
            return true;
        }
    }
    for (size_t i = 0; i < n2_edges.size(); i++)
    {
        if (n2_edges[i]->get_road() != nullptr && n2_edges[i]->get_road()->get_owner() == this)
        {
            return true;
        }
    }
    return false;
}

// Checks if a settlement can be built at the specified node based on turn, resource availability, and edge occupancy.
bool Player::can_build_s(int n1)
{
    if (!_turn)
    {
        __throw_runtime_error("you cant build not in your turn!!!");
    }

    if (game_started && !Settlement_cost::check_if_fits(_resources))
    {
        __throw_runtime_error("Not enough resources !!!");
    }
    Node *node1 = _board->get_node(n1);

    if (node1->get_builder() != nullptr)
    {
        __throw_runtime_error("this place is not empty");
    }
    vector<Edge *> n1_edges = node1->get_edges();
    return aux_can_build_set(n1_edges, n1);
}

// Checks if a settlement can be built at the specified node based on the presence of adjacent roads owned by the player.
bool Player::aux_can_build_set(vector<Edge *> n1_edges, int n1)
{
    for (size_t i = 0; i < n1_edges.size(); i++)
    {
        vector<Node *> nodes = n1_edges[i]->get_nodes();
        int n2 = 0;
        if (nodes[0]->get_number() != n1)
        {
            n2 = nodes[0]->get_number();
        }
        else
        {
            n2 = nodes[1]->get_number();
        }
        Node *node1 = _board->get_node(n2);
        if (n1_edges[i]->get_road() != nullptr &&
            n1_edges[i]->get_road()->get_owner() == this && node1->get_builder() == nullptr)
        {
            return true;
        }
    }
    return false;
}

// Checks if a city can be built at the specified node based on turn, resource availability, and builder type.
void Player::can_build_city(int n1)
{
    if (!_turn)
    {
        __throw_runtime_error("you cant build not in your turn!!!");
    }
    if (game_started && !City_cost::check_if_fits(_resources))
    {
        __throw_runtime_error("Not enough resources !!!");
    }
    Node *node1 = _board->get_node(n1);
    if (node1->get_builder() == nullptr)
    {
        __throw_runtime_error("this place is empty!!!");
    }
    string type = node1->get_builder()->get_type();
    const Player *p1 = node1->get_builder()->get_owner();
    if (p1 != this || type != "settlement")
    {
        __throw_runtime_error("You dont have settlement here !!!");
    }
}

// Allows the player to buy a development card if conditions are met and deducts resources accordingly.
void Player::buy_dev_card()
{
    if (!this->_turn)
    {
        __throw_runtime_error("you cant buy cards not in your turn!");
    }
    if (!Development_cost::check_if_fits(_resources))
    {
        __throw_runtime_error("dont have enough resources to buy a dev card!");
    }
    DevCards *dev = _deck.back();
    _deck.pop_back();
    cout << dev->get_type() << endl;
    this->_myCards[dev->get_type()]++;
    pay(Development_cost::get_cost());
    cout << "-" << this->_name << " has new development card !!!" << endl;
    check_if_game_ended();
}

// Checks if the player has the specified development card, otherwise throws an error.
void Player::dev_card_exe(string type)
{
    if (this->_myCards[type] < 1)
    {
        __throw_runtime_error("you dont have that card!!!");
    }
    if (!this->_turn)
    {
        __throw_runtime_error("you cant use dev cards not in your turn!");
    }
}

void Player::check_dice_dev()
{
    if (this->_dice_rolled)
    {
        end_turn();
    }
}

// Uses the monopol card to take all of a specified resource from other players.
void Player::use_monopol(string res)
{
    dev_card_exe("monopol");
    Resource rs = res_from_string(res);
    if (rs == NO_RESOURCE)
    {
        __throw_runtime_error("You cant ask for this!!!");
    }
    cout << "-" << this->_name << " used monopol card and asked for " << res << endl;
    reduce_increase(0, rs);
    reduce_increase(1, rs);
    check_dice_dev();
}

// Reduces a specified resource from other players and adds it to the current player.
void Player::reduce_increase(int i, Resource res)
{
    if (this->_other_players[i]->get_resourses()[res] > 0)
    {
        this->_resources[res]++;
        this->_other_players[i]->get_resourses()[res]--;
    }
}

// Uses the road builder card to build roads without resource cost for the next two roads.
void Player::use_road_builder()
{
    dev_card_exe("road builder");
    cout << "-" << this->_name << " used road builder " << endl;
    this->br_falg = 2;
    check_dice_dev();
}

// Uses the year of plenty card to gain two specified resources.
void Player::use_year_of_planty(Resource r1, Resource r2)
{
    dev_card_exe("year of plenty");
    cout << "-" << this->_name << " used year of plenty " << endl;
    year_of_planty_falg = true;
    this->currenet_res1 = r1;
    this->currenet_res2 = r2;
    this->amount_current_res1 = this->_resources[r1];
    this->amount_current_res2 = this->_resources[r2];
    this->_resources[r1]++;
    this->_resources[r2]++;
    check_dice_dev();
}

// Uses the winning point card to gain an additional victory point.
void Player::use_winning_point()
{
    dev_card_exe("winning point");
    cout << "-" << this->_name << " used winning point " << endl;
    this->_points++;
    check_if_game_ended();
    check_dice_dev();
}

// Ends the effects of the year of plenty card by adjusting resource counts if necessary.
void Player::end_yop()
{
    if (year_of_planty_falg == true)
    {
        if (this->amount_current_res1 < this->_resources[currenet_res1])
        {
            this->_resources[currenet_res1]--;
        }
        if (this->amount_current_res2 < this->_resources[currenet_res2])
        {
            this->_resources[currenet_res2]--;
        }
    }
}

// Activates the player's turn, allowing them to perform actions.
void Player::active_turn()
{
    this->_turn = true;
}

// Ends the player's turn, resets flags, and activates the next player's turn.
void Player::end_turn()
{
    end_yop();
    this->br_falg = 0;
    this->_turn = false;
    this->_dice_rolled = false;
    cout << "-" << this->_name << " ended his turn, now its " << this->_next_player->_name << " turn" << endl;
    this->_next_player->active_turn();
    this->year_of_planty_falg = false;
}

// Trades resources or development cards with another player based on specified amounts.
void Player::trade(string s1, int amount1, string s2, int amount2, Player *trader)
{
    if (!this->_turn)
    {
        __throw_runtime_error("you cant trade not in your turn!!!");
    }
    bool s1r = res_from_string(s1) == NO_RESOURCE;
    bool s1d = s1 != "monopol" && s1 != "road builder" && s1 != "road builder" && s1 != "year of plenty" && s1 != "knight" && s1 != "winning point";
    bool s2r = res_from_string(s2) == NO_RESOURCE;
    bool s2d = s2 != "monopol" && s2 != "road builder" && s2 != "road builder" && s2 != "year of plenty" && s2 != "knight" && s2 != "winning point";
    if ((s1r && s1d) || (s2r && s2d))
    {
        __throw_runtime_error("enter a valid card to trade");
    }
    trade_resource(s1, amount1, s2, amount2, trader);
    trade_devCards(s1, amount1, s2, amount2, trader);
    cout << "-trede was done between " << this->_name << " and " << trader->_name << endl;
}

// Trades resources with another player, adjusting resource counts accordingly.
void Player::trade_resource(string s1, int amount1, string s2, int amount2, Player *trader)
{
    if (res_from_string(s1) != NO_RESOURCE)
    {
        if (trader->_resources[res_from_string(s1)] - amount1 < 0)
        {
            __throw_runtime_error("you dont have enough resources to do that trade!!!");
        }
        this->_resources[res_from_string(s1)] += amount1;
        trader->_resources[res_from_string(s1)] -= amount1;
    }

    if (res_from_string(s2) != NO_RESOURCE)
    {
        if (this->_resources[res_from_string(s2)] - amount2 < 0)
        {
            __throw_runtime_error("you dont have enough resources to do that trade!!!");
        }
        trader->_resources[res_from_string(s2)] += amount2;
        this->_resources[res_from_string(s2)] -= amount2;
    }
}

// Trades development cards with another player, adjusting card counts accordingly.
void Player::trade_devCards(string s1, int amount1, string s2, int amount2, Player *trader)
{
    if (this->_myCards[s1]) // detect if its a devcard
    {
        if (trader->_myCards[s1] - amount1 < 0)
        {
            __throw_runtime_error("you dont have enough devcards to do that trade!!!");
        }
        this->_myCards[s1] += amount1;
        trader->_myCards[s1] -= amount1;
    }
    if (trader->_myCards[s2]) // detect if its a devcard
    {
        if (this->_myCards[s2] - amount2 < 0)
        {
            __throw_runtime_error("you dont have enough devcards to do that trade!!!");
        }
        trader->_myCards[s1] += amount2;
        this->_myCards[s1] -= amount2;
    }
}

// Deducts the specified resource cost from the player's resources.
void Player::pay(map<Resource, int> cost)
{
    map<Resource, int>::iterator it;
    for (it = cost.begin(); it != cost.end(); it++)
    {
        _resources[it->first] -= it->second;
    }
}

// Checks if the game has ended by verifying if the player has met the winning conditions.
void Player::check_if_game_ended()
{
    bool check = (this->_myCards["knight"] == 3 && this->_points > 7);
    if (this->_points >= 10 || check)
    {
        cout << "-" << "the game is ended " << this->_name << " won this game !!!" << endl;
        this->_game->set_game_was_ended();
    }
}
