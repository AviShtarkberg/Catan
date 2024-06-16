// id:322530080 mail:avishb1213@gmail.com
#include <iostream>
#include "Node_Edge.hpp"
using namespace std;

namespace catan_game
{
    class Resourse;
    class Land
    {
    protected:
        string _type;
        const Resource _recource;
        vector<Node *> _nodes;
        int _dice_number;

    public:
        Land(const string &type, const Resource recource)
            : _type(type), _recource(recource)
        {
        }

        void set_dice_number(int n)
        {
            this->_dice_number = n;
        }
        // Getters
        string get_type() const
        {
            return _type;
        }

        const Resource get_resource() const
        {
            return _recource;
        }
        vector<Node *> get_nodes()
        {
            return this->_nodes;
        }
        void add_node(Node *node)
        {
            _nodes.push_back(node);
            node->set_land(this);
        }
        int get_dice_number()
        {
            return this->_dice_number;
        }
    };

    class Forest : public Land
    {
    public:
        Forest()
            : Land("forest", LUMBER) {}
    };

    class Hill : public Land
    {
    public:
        Hill()
            : Land("hill", BRICK) {}
    };

    class Field : public Land
    {
    public:
        Field()
            : Land("field", GRAIN) {}
    };

    class Mountain : public Land
    {
    public:
        Mountain()
            : Land("mountain", ORE) {}
    };

    class Pasture : public Land
    {
    public:
        Pasture()
            : Land("pasture", WOOL) {}
    };

    class Desert : public Land
    {
    public:
        Desert()
            : Land("desert", NO_RESOURCE) {}
    };
}