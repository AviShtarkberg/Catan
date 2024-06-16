// id:322530080 mail:avishb1213@gmail.com
#ifndef CITY_COST_HPP
#define CITY_COST_HPP

#include "Cost.hpp"
#include <map>
//this class will represent a cost of a city, will have a function to check if a player 
//have enoght resorces to build a new city
namespace catan_game
{
    class City_cost : public cost
    {
    public:
        static std::map<Resource, int> get_cost()
        {
            std::map<Resource, int> c_cost;
            c_cost[GRAIN] = 2;
            c_cost[ORE] = 3;
            return c_cost;
        }

        static bool check_if_fits(const std::map<Resource, int> &map)
        {
            int g = map.at(GRAIN);
            int o = map.at(ORE);
            return !(g < 2 || o < 3);
        }
    };
}

#endif // CITY_COST_HPP
