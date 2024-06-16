// id:322530080 mail:avishb1213@gmail.com
#include "Cost.hpp"
#include <map>

// this class will represent the cost of a dev card.
// will have a functuion that will check if a player
//  have enoght resorces to buy a dev card
namespace catan_game
{
    class Development_cost : public cost
    {
    public:
        static map<Resource, int> get_cost()
        {
            map<Resource, int> d_cost;
            d_cost[ORE] = 1;
            d_cost[WOOL] = 1;
            d_cost[GRAIN] = 1;
            return d_cost;
        }

        static bool check_if_fits(map<Resource, int> map)
        {
            int o = map[ORE];
            int w = map[WOOL];
            int g = map[GRAIN];
            if (o < 1 || w < 1 || g < 1)
            {
                return false;
            }
            return true;
        }
    };
}