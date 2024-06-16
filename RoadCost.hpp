// id:322530080 mail:avishb1213@gmail.com
#ifndef ROAD_COST_HPP
#define ROAD_COST_HPP

#include "Cost.hpp"
#include <map>

//this class will represent the cost of a road in the game.
//will have a functuion that detectes of a player have enough resorces to build one.
namespace catan_game
{
    class Road_cost : public cost
    {
    public:
        static std::map<Resource, int> get_cost()
        {
            std::map<Resource, int> r_cost;
            r_cost[BRICK] = 1;
            r_cost[LUMBER] = 1;
            return r_cost;
        }

        static bool check_if_fits(const std::map<Resource, int> &map)
        {
            int b = map.at(BRICK);
            int l = map.at(LUMBER);
            return !(b < 1 || l < 1);
        }
    };
}

#endif // ROAD_COST_HPP
