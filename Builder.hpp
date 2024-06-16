// id:322530080 mail:avishb1213@gmail.com
#include <iostream>
#include <vector>
#include <map>
#include "Resource.hpp"
#include "Cost.hpp"
#include "RoadCost.hpp"
#include "CityCost.hpp"
#include "SettlementCost.hpp"
using namespace std;

/*This class will be responsible to build each type of piece that you can
build in a regular catan game -road, city, settelment
*/
namespace catan_game
{
    class Player;
    class Builder
    {
    public:
        Builder(const std::map<Resource, int> &cost)
            : _cost(cost), _owner(nullptr)
        {
        }

        virtual ~Builder() {}


        void set_owner(Player *owner)
        {
            this->_owner = owner;
        }

        Player *get_owner()
        {
            return _owner;
        }
        
        virtual string get_type()
        {
            return ("");
        }

    protected:
        std::map<Resource, int> _cost;
        Player *_owner;
    };

    class Settlement : public Builder
    {
    public:
        Settlement() : Builder(Settlement_cost::get_cost())
        {
        }
        string get_type()
        {
            return "settlement";
        }
    };

    class City : public Builder
    {
    public:
        City() : Builder(City_cost::get_cost())
        {
        }

        string get_type()
        {
            return "city";
        }
    };

    class Road : public Builder
    {
    public:
        Road() : Builder(Road_cost::get_cost()) {}
    };
}
