// id:322530080 mail:avishb1213@gmail.com
#include "Board.hpp"
using namespace std;
using namespace catan_game;

//funciton that will set the numbers of each land on the board
vector<int> Board::generateRandomNumbers()
{
    vector<int> numbers;

    // Add the number 2 and 12 one time each
    numbers.push_back(10);
    numbers.push_back(2);
    numbers.push_back(9);
    numbers.push_back(12);
    numbers.push_back(6);
    numbers.push_back(4);
    numbers.push_back(10);
    numbers.push_back(9);
    numbers.push_back(11);
    numbers.push_back(3);
    numbers.push_back(8);
    numbers.push_back(8);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.push_back(5);
    numbers.push_back(6);
    numbers.push_back(11);
    if (this->random_board)
    {
        // Shuffle the numbers vector
        random_device rd;
        mt19937 g(rd());
        shuffle(numbers.begin(), numbers.end(), g);
    }
    return numbers;
}

//the board construcor- will set the lands with respect to randomization that the players
//will detect
Board::Board(bool randomized_board)
{
    this->random_board = randomized_board;
    _lands.push_back(&mountain1);
    _lands.push_back(&pasture1);
    _lands.push_back(&forest1);
    _lands.push_back(&field1);
    _lands.push_back(&hill1);
    _lands.push_back(&pasture2);
    _lands.push_back(&hill3);
    _lands.push_back(&field2);
    _lands.push_back(&forest2);
    _lands.push_back(&forest3);
    _lands.push_back(&mountain2);
    _lands.push_back(&forest4);
    _lands.push_back(&mountain3);
    _lands.push_back(&field3);
    _lands.push_back(&pasture3);
    _lands.push_back(&hill2);
    _lands.push_back(&field4);
    _lands.push_back(&pasture4);
    if (randomized_board)
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(_lands.begin(), _lands.end(), g);
    }
    set_lands_dice_number();
    set_nodes();
    set_edges();
}

//will set the nodes to each land will be set as in the pdf file that represent the board.
void Board::set_nodes()
{
    for (int i = 0; i < 54; i++)
    {
        _nodes.push_back(new Node(i));
    }
    add_land(*_lands[0], 0, 8);
    cout << "land 1:" << _lands[0]->get_type() << " ,dice number: " << _lands[0]->get_dice_number() << endl;
    add_land(*_lands[1], 2, 10);
    cout << "land 2:" << _lands[1]->get_type() << " ,dice number: " << _lands[1]->get_dice_number() << endl;
    add_land(*_lands[2], 4, 12);
    cout << "land 3:" << _lands[2]->get_type() << " ,dice number: " << _lands[2]->get_dice_number() << endl;
    add_land(*_lands[3], 7, 17);
    cout << "land 4:" << _lands[3]->get_type() << " ,dice number: " << _lands[3]->get_dice_number() << endl;
    add_land(*_lands[4], 9, 19);
    cout << "land 5:" << _lands[4]->get_type() << " ,dice number: " << _lands[4]->get_dice_number() << endl;
    add_land(*_lands[5], 11, 21);
    cout << "land 6:" << _lands[5]->get_type() << " ,dice number: " << _lands[5]->get_dice_number() << endl;
    add_land(*_lands[6], 13, 23);
    cout << "land 7:" << _lands[6]->get_type() << " ,dice number: " << _lands[6]->get_dice_number() << endl;
    add_land(*_lands[7], 16, 27);
    cout << "land 8:" << _lands[7]->get_type() << " ,dice number: " << _lands[7]->get_dice_number() << endl;
    add_land(*_lands[8], 18, 29);
    cout << "land 9:" << _lands[8]->get_type() << " ,dice number: " << _lands[8]->get_dice_number() << endl;
    add_land(desert, 20, 31);
    cout << "land 10:" << "desert" << endl;
    add_land(*_lands[9], 22, 33);
    cout << "land 11:" << _lands[9]->get_type() << " ,dice number: " << _lands[9]->get_dice_number() << endl;
    add_land(*_lands[10], 24, 35);
    cout << "land 12:" << _lands[10]->get_type() << " ,dice number: " << _lands[10]->get_dice_number() << endl;
    add_land(*_lands[11], 28, 38);
    cout << "land 13:" << _lands[11]->get_type() << " ,dice number: " << _lands[11]->get_dice_number() << endl;
    add_land(*_lands[12], 30, 40);
    cout << "land 14:" << _lands[12]->get_type() << " ,dice number: " << _lands[12]->get_dice_number() << endl;
    add_land(*_lands[13], 32, 42);
    cout << "land 15:" << _lands[13]->get_type() << " ,dice number: " << _lands[13]->get_dice_number() << endl;
    add_land(*_lands[14], 34, 44);
    cout << "land 16:" << _lands[14]->get_type() << " ,dice number: " << _lands[14]->get_dice_number() << endl;
    add_land(*_lands[15], 39, 47);
    cout << "land 17:" << _lands[15]->get_type() << " ,dice number: " << _lands[15]->get_dice_number() << endl;
    add_land(*_lands[16], 41, 49);
    cout << "land 18:" << _lands[16]->get_type() << " ,dice number: " << _lands[16]->get_dice_number() << endl;
    add_land(*_lands[17], 43, 51);
    cout << "land 19:" << _lands[17]->get_type() << " ,dice number: " << _lands[17]->get_dice_number() << endl;
}

//auxilliry function to the function that is above.
void Board::add_land(Land &land, int n1, int n2)
{
    land.add_node(_nodes[n1]);
    land.add_node(_nodes[n1 + 1]);
    land.add_node(_nodes[n1 + 2]);

    land.add_node(_nodes[n2]);
    land.add_node(_nodes[n2 + 1]);
    land.add_node(_nodes[n2 + 2]);
}

//will set the edges of the game will be set with respect to the 
//nodes that the edge is connected to.
void Board::set_edges()
{
    for (int i = 0; i < 6; i++)
    {
        put_edge(i, i + 1);
    }
    for (int i = 7; i < 15; i++)
    {
        put_edge(i, i + 1);
    }

    for (int i = 16; i < 26; i++)
    {
        put_edge(i, i + 1);
    }

    for (int i = 27; i < 37; i++)
    {
        put_edge(i, i + 1);
    }

    for (int i = 38; i < 46; i++)
    {
        put_edge(i, i + 1);
    }

    for (int i = 47; i < 53; i++)
    {
        put_edge(i, i + 1);
    }

    for (int i = 0; i < 7; i += 2)
    {
        put_edge(i, i + 8);
    }

    for (int i = 7; i < 16; i += 2)
    {
        put_edge(i, i + 10);
    }

    for (int i = 16; i < 27; i += 2)
    {
        put_edge(i, i + 11);
    }

    for (int i = 28; i < 37; i += 2)
    {
        put_edge(i, i + 10);
    }

    for (int i = 39; i < 46; i += 2)
    {
        put_edge(i, i + 8);
    }
}

//will use the randomaizer from the above to set all the numbers to each land.
void Board::set_lands_dice_number()
{
    vector<int> ids = generateRandomNumbers();
    for (size_t i = 0; i < _lands.size(); i++)
    {
        _lands_dice_number[ids[i]].push_back(_lands[i]);
        _lands[i]->set_dice_number(ids[i]);
    }
}

//this functiuon will return the edge with the respect to the nodes that are given.
Edge *Board::get_edge(int n1, int ni)
{
    vector<Edge *> edges = _nodes[n1]->get_edges();
    for (size_t i = 0; i < edges.size(); i++)
    {
        int m1 = edges[i]->get_nodes()[0]->get_number();
        int m2 = edges[i]->get_nodes()[1]->get_number();
        if (m1 == ni || m2 == ni)
        {
            return edges[i];
        }
    }
    return nullptr;
}