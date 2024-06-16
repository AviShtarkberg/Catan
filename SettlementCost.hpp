// id:322530080 mail:avishb1213@gmail.com
#ifndef SETTLEMENT_COST_HPP
#define SETTLEMENT_COST_HPP

#include "Cost.hpp"
#include <map>

//this class will represent the cost of a settlement in the game.
//will have a functuion that detectes of a player have enough resorces to build one.
namespace catan_game
{
    class Settlement_cost : public cost
    {
    public:
        static std::map<Resource, int> get_cost()
        {
            std::map<Resource, int> s_cost;
            s_cost[BRICK] = 1;
            s_cost[LUMBER] = 1;
            s_cost[WOOL] = 1;
            s_cost[GRAIN] = 1;
            return s_cost;
        }

        static bool check_if_fits(const std::map<Resource, int> &map)
        {
            int b = map.at(BRICK);
            int l = map.at(LUMBER);
            int w = map.at(WOOL);
            int g = map.at(GRAIN);
            return !(b < 1 || l < 1 || w < 1 || g < 1);
        }
    };
}

#endif // SETTLEMENT_COST_HPP
