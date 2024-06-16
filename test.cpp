// id:322530080 mail:avishb1213@gmail.com
#include "doctest.h"
#include "Catan.hpp"
#include <stdio.h>
#include "PlayerForTests.hpp"
using namespace catan_game;
using namespace std;
using namespace doctest;
// to run this code you should run: ./test < input.txt

// will test the startinh proces of the game
TEST_CASE("Start and end of the game")
{
    PlayerForTest p1("p1");
    PlayerForTest p2("p2");
    PlayerForTest p3("p3");
    Catan game(p1, p2, p3, false);
    Board *board = game.get_board();

    // start of the game:
    //  p1 after the game is starting
    CHECK(board->get_node(1)->get_builder()->get_owner()->get_name() == "p1");
    CHECK(board->get_node(2)->get_builder()->get_owner()->get_name() == "p1");
    CHECK(board->get_edge(1, 2)->get_road()->get_owner()->get_name() == "p1");
    CHECK(board->get_edge(2, 3)->get_road()->get_owner()->get_name() == "p1");

    // p2 after the game is starting
    CHECK(board->get_node(7)->get_builder()->get_owner()->get_name() == "p2");
    CHECK(board->get_node(8)->get_builder()->get_owner()->get_name() == "p2");
    CHECK(board->get_edge(7, 8)->get_road()->get_owner()->get_name() == "p2");
    CHECK(board->get_edge(8, 9)->get_road()->get_owner()->get_name() == "p2");

    // p3 after the game is starting
    CHECK(board->get_node(16)->get_builder()->get_owner()->get_name() == "p3");
    CHECK(board->get_node(17)->get_builder()->get_owner()->get_name() == "p3");
    CHECK(board->get_edge(16, 17)->get_road()->get_owner()->get_name() == "p3");
    CHECK(board->get_edge(17, 18)->get_road()->get_owner()->get_name() == "p3");

    // end of the game:
    p1.set_points();
    p1.build_road(3, 4);
    p1.build_settlement(4);
    CHECK(game.game_was_ended());
}

// will test all the builders that used in this projecet - road, settelment,city
TEST_CASE("Builders tests")
{
    PlayerForTest p1("p1");
    PlayerForTest p2("p2");
    PlayerForTest p3("p3");
    Catan game(p1, p2, p3, false);

    // test the build_settlement method:

    // check that a palyer cant builed settlement in a node that contain one:
    CHECK_THROWS(p1.build_settlement(1));

    // will check that if player dont have 2 roads path this functuion will throw an error
    CHECK_THROWS(p1.build_settlement(3));  // have one road
    CHECK_THROWS(p1.build_settlement(23)); // have no raods at all

    // will check that legal call not throwing an error
    p1.build_road(3, 4);
    CHECK_NOTHROW(p1.build_settlement(4));
    // will check that the settlment was set well on the board.
    CHECK(game.get_board()->get_node(4)->get_builder()->get_owner()->get_name() == "p1");
    CHECK_FALSE(game.get_board()->get_node(4)->get_builder()->get_owner()->get_name() == "p2");

    // will raise an error becuase its not p2 and p3 turn
    CHECK_THROWS(p2.build_settlement(9));
    CHECK_THROWS(p3.build_settlement(18));

    // will check that if player dont have enough resources and tries to build a
    // settlement the function will throw an exception.
    p1.build_road(4, 5);
    p1.build_road(5, 6);
    p1.set_res_to_0();
    CHECK_THROWS(p1.build_settlement(6));

    // will check that unvalid nodes number throws
    CHECK_THROWS(p1.build_settlement(100));
    CHECK_THROWS(p1.build_settlement(-1));

    // check the build city method:

    // will check that after a legal build the baord is updated correctly
    p1.end_turn();
    p2.build_city(7);
    CHECK(game.get_board()->get_node(7)->get_builder()->get_type() == "city");
    CHECK(game.get_board()->get_node(7)->get_builder()->get_owner()->get_name() == "p2");
    CHECK_FALSE(game.get_board()->get_node(7)->get_builder()->get_owner()->get_name() == "p3");

    // will check that a player cant build city not in his turn
    CHECK_THROWS(p1.build_city(1));

    // will check that a player cant build a city in a node that dont have his settelment
    CHECK_THROWS(p2.build_city(44));

    // will check that if a player dont have enought res the build city method will throw
    p2.set_res_to_0();
    CHECK_THROWS(p2.build_city(8));

    // will check the build city function for a node that already has a city
    CHECK_THROWS(p2.build_city(7));

    // will check that unvalid nodes number throws
    CHECK_THROWS(p2.build_city(100));
    CHECK_THROWS(p2.build_city(-1));

    p2.end_turn();

    // check the build road method:

    // will check a vaild build raod call.
    CHECK_NOTHROW(p3.build_road(18, 19)); // smaller than bigger
    CHECK_NOTHROW(p3.build_road(19, 20)); // bigger than smaller
    CHECK(game.get_board()->get_edge(18, 19)->get_road()->get_owner()->get_name() == "p3");
    CHECK(game.get_board()->get_edge(19, 18)->get_road()->get_owner()->get_name() == "p3");
    CHECK(game.get_board()->get_edge(19, 20)->get_road()->get_owner()->get_name() == "p3");
    CHECK(game.get_board()->get_edge(20, 19)->get_road()->get_owner()->get_name() == "p3");
    CHECK_FALSE(game.get_board()->get_edge(20, 19)->get_road()->get_owner()->get_name() == "p2");

    // will check that if a player tries to build a road but dont have a settelment or a
    // road that is connected to this 2 nodes the build road method will throw.
    CHECK_THROWS(p3.build_road(22, 33));

    // will check that unvalid nodes number throws
    CHECK_THROWS(p3.build_road(100, 101));

    // will check that players cant build roads not in thier turns
    CHECK_THROWS(p1.build_road(6, 7));
    CHECK_THROWS(p2.build_road(9, 10));
}

// will test the dice functionalliny - will be checked that each player
// get resorces based on the total dice number. will also check the
// total_dice_is_7 function.
TEST_CASE("Dice tests")
{
    PlayerForTest p1("p1");
    PlayerForTest p2("p2");
    PlayerForTest p3("p3");
    Catan game(p1, p2, p3, false);

    // will check that after rolling the dice with a result in which
    // the players has settelments the players got 1 point for each settelment.
    CHECK(p1.get_resourses()[ORE] == 102);
    p1.roll_number(10);
    CHECK(p1.get_resourses()[ORE] == 104);
    CHECK(p2.get_resourses()[GRAIN] == 102);
    p1.roll_number(12);
    CHECK(p2.get_resourses()[GRAIN] == 104);
    CHECK(p3.get_resourses()[GRAIN] == 104);
    p1.roll_number(9);
    CHECK(p3.get_resourses()[GRAIN] == 106);

    // will check that if a player has a city in the node he will get 2 points
    p1.build_city(1);
    p1.roll_number(10);
    CHECK(p1.get_resourses()[ORE] == 104); // note that p1 paid the city building cost!!

    /* will check that after 7 is the sum of the dice,
        eah player with more than 7 resources will forced to
        return half of the card. also will be checked that
        if a player has less than 7 card the function wont ask his anything.
    */
    p1.set_number_of_res(15);
    p2.set_number_of_res(15);
    p3.set_number_of_res(6);
    p1.roll_7();
    CHECK(p1.get_number_of_resource() == 8); // works with input.txt
    CHECK(p2.get_number_of_resource() == 8); // works with input.txt
    CHECK(p3.get_number_of_resource() == 6); // works with input.txt

    // will check that a player cant roll the dice not in his turn
    CHECK_THROWS(p2.roll_the_dice());
}
// in this part i tested the trades part of the code
TEST_CASE("Trades tests")
{
    PlayerForTest p1("p1");
    p1.active_turn();
    PlayerForTest p2("p2");
    PlayerForTest p3("p3");

    // will check a legal trade of res with res"
    p1.trade("wool", 3, "brick", 2, &p3);
    CHECK(p1.get_resourses()[WOOL] == 103);
    CHECK(p3.get_resourses()[WOOL] == 97);
    CHECK(p1.get_resourses()[BRICK] == 98);
    CHECK(p3.get_resourses()[BRICK] == 102);

    // will check that if one of the players dont have the amount that is asked
    // for a trade the method will throw
    CHECK_THROWS(p1.trade("wool", 3, "brick", 200, &p3));

    // will check a legal trade of devcard with res"
    p1.trade("monopol", 1, "brick", 3, &p3);
    CHECK(p1.get_cards()["monopol"] == 4);
    CHECK(p3.get_cards()["monopol"] == 2);
    CHECK(p1.get_resourses()[BRICK] == 95);
    CHECK(p3.get_resourses()[BRICK] == 105);

    // will check that a player cant trade not in his turn
    CHECK_THROWS(p3.trade("monopol", 1, "brick", 3, &p2));

    // will check that a player cant trade something that is not a card
    CHECK_THROWS(p1.trade("mono", 1, "brick", 3, &p2));
    CHECK_THROWS(p1.trade("monopol", 1, "bri", 3, &p2));
}

// each type of the devcards will be checked
TEST_CASE("Devcards tests")
{
    PlayerForTest p1("p1");
    PlayerForTest p2("p2");
    PlayerForTest p3("p3");
    Catan game(p1, p2, p3, false);
    p1.buy_dev_card();
    map<string, int> p1_cards = p1.get_cards();
    // will check that the player got the card from the deck
    map<Resource, int> res = p1.get_resourses();
    bool got_card = (p1_cards["monopol"] == 4 || p1_cards["road builder"] == 4 || p1_cards["year of plenty"] == 4 || p1_cards["knight"] == 2 || p1_cards["winning point"] == 4);
    CHECK(got_card);
    bool check_if_player_payed = res[WOOL] == 100 && res[ORE] == 101 && res[GRAIN] == 99;
    CHECK(check_if_player_payed);

    // wil test that after using a monopol the player got the right resources from the
    // other players.
    p1.use_monopol("wool");
    CHECK(p1.get_resourses()[WOOL] == 102);
    CHECK(p2.get_resourses()[WOOL] == 99);
    CHECK(p3.get_resourses()[WOOL] == 99);
    p1.use_year_of_planty(BRICK, WOOL);
    CHECK(p1.get_resourses()[BRICK] == 101);
    CHECK(p1.get_resourses()[WOOL] == 103);
    p1.end_turn();
    // will check that if a player didnt used the resource at the end of the turn
    // the amount of this resource wil get back to the original.
    CHECK(p1.get_resourses()[BRICK] == 100);

    // will check the road builder card, will check that if used, the player
    // wont pay for building a road.
    p2.build_road(9, 10);
    CHECK(p2.get_resourses()[BRICK] == 99);
    CHECK(p2.get_resourses()[LUMBER] == 99);
    p2.use_road_builder();
    p2.build_road(10, 11);
    CHECK(p2.get_resourses()[BRICK] == 99);
    CHECK(p2.get_resourses()[LUMBER] == 99);
    p2.build_road(11, 12);
    CHECK(p2.get_resourses()[BRICK] == 99);
    CHECK(p2.get_resourses()[LUMBER] == 99);
    p2.build_road(12, 13);
    CHECK(p2.get_resourses()[BRICK] == 98);
    CHECK(p2.get_resourses()[LUMBER] == 98);

    // will check that if the turn ended and the player didnt build the
    // roads, in his next turn he will pay for the road.
    p2.use_road_builder();
    p2.end_turn();
    p3.end_turn();
    p1.end_turn();
    p2.build_road(13, 14);
    CHECK(p2.get_resourses()[BRICK] == 97);
    CHECK(p2.get_resourses()[LUMBER] == 97);

    // will check the winning point card.
    int wp = p2.get_wp();
    p2.use_winning_point();
    CHECK(wp + 1 == p2.get_wp());

    // will check that if a player roll the dice than after he user a dev card card
    // the turn will be passed to the next player.
    p2.roll_the_dice();
    p2.use_winning_point();
    CHECK_FALSE(p2.get_turn());
    CHECK(p3.get_turn());

    // will check cases in which the player dond have the dev card and tries to use it:
    Player p5("p5");
    CHECK_THROWS(p5.use_monopol("wool"));
    CHECK_THROWS(p5.use_road_builder());
    CHECK_THROWS(p5.use_winning_point());
    CHECK_THROWS(p5.use_year_of_planty(WOOL, BRICK));

    p3.add_knights();
    // will check the knight card - will check that player with 8 points and
    // 3 knights in his turn will win the game and the program will exit.
    CHECK(game.game_was_ended());
}
