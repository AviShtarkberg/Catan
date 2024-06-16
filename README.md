# ~Catan Game~ #

## Project Description
This C++ project is an implementation of the popular board game Catan. The game features a  game board where players collect and trade resources to build roads, settlements, and cities aiming to be the first to reach 10 victory points.


## Features
- Implementation of a hexagonal game board with randomized tiles.
- Support for three players.
- Basic gameplay mechanics such as building roads, settlements, and cities.
- Resource management and trading between players.
- Development cards including knights, road building, and more.


## The bord
- The board of the game has 19 lands to which assiged a number between 2 and 12.
- The lands and the resorces that they provide: 
                            *forests that provides lumber
                            *hills that provides brick
                            *mountains that provides ore
                            *fields that provides grain
                            *pasture that provides wool
                            *deseret that provides nothing
- a board can be randomized (dice numbers and lands) or can be set fixed as in the picture 
  in this project (board_with_nodes.jpeg).


## How to build
- In this game you can build:
                             *roads- from your settlement or from another your road
                             *settlement- you can build one if you have 2 roads from another one and not next to another one of yours.
                             *citys- you can upgrade your settlement to city.
- You can build only in your turn.
- Settelment will give you 1 winning point and their cost is brick, lumber, wool, grain.
- City will give you 2 winning points and their cost is 3 ore and 2 grain.
- Roads dont give you winning point and their cost is brick and lumber.


## Development card
- The game holds a deck of cards from which the players will draw if they
  want to get a development card.
- The cost of a development card is 1 ore 1 wool 1 grain.
- Inside that dech that is: 
                            * 3 knighs cards. 
                            * 4 winning points cards. 
                            * 6 monopols cards. 
                            * 6 road builders cards. 
                            * 6 year of plantys cards. 
- knighs: if you have 3 knights in your hand you have addtional 2 points.
- winning points: gives you one winning point.
- monopols: when you use that card you ask for a resorce and the other players need to give
  you that resource.
- road builder: you can build 2 roads in this turn and you dont have to pay for tham.
- year of plantys: you ask for 2 resources from the bank and you can use tham in that turn.
                            

## Game Rules
The game follows the standard rules of Catan:
- At the begining of the game each player will be forced to build 2 settelments and 2 roads,
  p1 firstly than p2 than p3.
- I assume that the players decides by themself the turns and p1 is always first, 
  then p2 then p3.
- Each player in his turn need to role the dice.
- After the dice is rolled the players that have settelments or citys in the
  nodes that are on the land with the dice number that was rolled will get 
  resorces based on the land that they have a building.
- In this game settelment will give the player one resource from the land and city
  will give 2.
- After the dice was rolled in his turn the player may build settelments, 
  upgrade them to citys, build roads, buy development cards and use one of them, trade.
- If a player dicides to use a development card his turn is ended, exept if he uses it before
  he rolls the dice.
- The trades can be done with resources and development cards between 2 players.


## Important functions to play this game:
- Firstly you will need to construct the 3 players of the game like that:
    Player a("a")
    Player b("b")
    Player c("c")
- Then you will have to innit the catan game like that:
    Catan(a, b, c, false) or Catan(a, b, c, true)
    the boolean value is responsible to detect if the game is random or not.
- Then in each turn you can use this functuions with respect to your resorces ans dev cards:
- build_settlement(int n1) - will build a settlment in the node with the number that you pass.
- build_city(int n1) - will build the city in the node with the number that you pass.
- build_road(int n1, int n2) - will build the road in the nodes with the numbers that you pass.
- roll_the_dice() - will roll the dice in this player turn.
- buy_dev_card() - will add a development card to the players hand.
- use_monopol(std::string res)- will get as arg the resources that the player wants to get.
- use_road_builder() - to use the road builder card in this turn.
- use_winning_point() - to use the winning point card.
- use_year_of_planty(Resource r1, Resource r2) - will get as arg the resources that the
  player want for this turn.
- trade(std::string s1, int amount1, std::string s2, int amount2, Player *trader) - will
  be responsible for the trades between player, you will need to pass first what you want
  then the amount of it, then what you will give and the amount of it and than the player that
  you want to trade with.I assume that the player and you talked and the player agrees to the
  trade always.
- end_turn()- will end the players turn and pass it to the next one.


## Project Structure
- Board.cpp & Board.hpp: Implementation of the game board, including the randomization and setting up of lands, nodes, and edges.
- Land.hpp: Representation of different types of lands on the game board.
- Resource.cpp & Resource.hpp: Implementation of game resources and utility functions.
- Node_Edge.hpp: Implementation of nodes and edges on the game board.
- Builder.hpp: Classes representing different types of builders (settlement, city, road).
- CityCost.hpp, RoadCost.hpp, SettlementCost.hpp: Classes representing the cost of building different game components.
- Catan.cpp & Catan.hpp: start the game, set the relation between the players, the deck   and  detectes if the game is finished.
- Player.cpp & Player.hpp: Player class containing all functionalities a player needs in the game.
- DevCards.hpp, DevCost.hpp: Implementation of development cards and their costs.
- PlayerForTests.hpp: Extended player class used for testing purposes.
- test.cpp: Tests for validating game functionalities.
- demo.cpp: Demo file to run the game.
- makefile: Makefile for compiling the project and running tests.


## Running commands:
# To run the test you should run : 
"make run_test"  or "make test->./test < input_test.txt"

# To run the demo you should run : 
"make catan" command or "make demo->./demo < input_demo.txt"

# To run valgrind you should run :
  "make valgrind_test" - to detect memory leacks in the test file.
  "make valgrind_demo" - to detect memory leacks in the demo file.

## Used libraries
  - iostream - was used for the inputs and outputs in this project.
  - vector - as a contiener. 
  - map - as a contiener.
  - random - to allow a random game do be played.
  - ctime - to detrimne the random seed.
  - algorithm - was used with shuffle algorithm.
  - doctest.h - to test the code.
