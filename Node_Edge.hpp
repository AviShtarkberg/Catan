// id:322530080 mail:avishb1213@gmail.com
#include "Builder.hpp"
#include <iostream>
#include <vector>
using namespace std;


/* in this file you will find the implmention of the edge and the node that will be set in the
board of the game
*/
namespace catan_game
{
    class Edge;
    class Land;
    class Node
    {
    private:
        int _number;
        Builder *_builder;
        vector<Edge *> _edges;
        vector<Land *> _lands;

    public:
        Node(int number) : _number(number), _builder(nullptr) {}

        int get_number() const
        {
            return _number;
        }

        void add_edge(Edge *edge)
        {
            _edges.push_back(edge);
        }

        vector<Edge *> get_edges() const
        {
            return _edges;
        }

        void build_settlement()
        {
            _builder = new Settlement();
        }

        void build_city()
        {
            delete this->_builder;
            this->_builder = new City();
        }

        Builder *get_builder()
        {
            return _builder;
        }
        void set_land(Land *land)
        {
            _lands.push_back(land);
        }
        vector<Land *> get_lands() const
        {
            return this->_lands;
        }

        ~Node()
        {
            delete this->_builder;
        }
    };

    class Edge
    {
    private:
        Node *_node1;
        Node *_node2;
        Builder *_road;

    public:
        Edge(Node *node1, Node *node2)
            : _node1(node1), _node2(node2), _road(nullptr)
        {
            node1->add_edge(this);
            node2->add_edge(this);
        }

        vector<Node *> get_nodes() const
        {
            return {_node1, _node2};
        }

        void build_road()
        {
            _road = new Road();
        }

        Builder *get_road()
        {
            return this->_road;
        }

        ~Edge()
        {
            delete this->_road;
        }
    };
}
