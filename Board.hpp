// id:322530080 mail:avishb1213@gmail.com
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <ctime>
#include <algorithm>
#include "Land.hpp"
using namespace std;

namespace catan_game
{
    class Board
    {
    private:
        Forest forest1;
        Forest forest2;
        Forest forest3;
        Forest forest4;
        Hill hill1;
        Hill hill2;
        Hill hill3;
        Mountain mountain1;
        Mountain mountain2;
        Mountain mountain3;
        Pasture pasture1;
        Pasture pasture2;
        Pasture pasture3;
        Pasture pasture4;
        Field field1;
        Field field2;
        Field field3;
        Field field4;
        Desert desert;
        map<int, vector<Land *>> _lands_dice_number;
        map<int, vector<Land *>> _lands_nodes;
        vector<Edge *> _edges;
        vector<Node *> _nodes;
        vector<Land *> _lands;
        void set_nodes();

        vector<int> generateRandomNumbers();

        void add_land(Land &land, int n1, int n2);

        void set_edges();

        void set_lands_dice_number();

        void put_edge(int i, int j)
        {
            _edges.push_back(new Edge(_nodes[i], _nodes[j]));
        }

    public:
        Board(bool randomize_board);

        bool random_board;

        ~Board()
        {
            for (auto node : _nodes)
            {
                delete node;
            }
            for (auto edge : _edges)
            {
                delete edge;
            }
        }

        vector<Land *> get_land(int i)
        {
            return this->_lands_dice_number[i];
        }

        Node *get_node(int i)
        {
            return this->_nodes[i];
        }

        Edge *get_edge(int n1, int ni);
    };
}