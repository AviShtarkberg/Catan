// id:322530080 mail:avishb1213@gmail.com
#ifndef COST_HPP
#define COST_HPP
#include <map>
#include "Resource.hpp"
using namespace std;

//this class will be an abstruct class that represents cost of anything
// class that will inharnce from this class:
// city cost, devcard cost, road cost, settelment cost
namespace catan_game
{
    class cost
    {
    public:
        static map<Resource, int> get_cost()
        {
            map<Resource, int> re;
            return re;
        }
    };
}

#endif // COST_HPP
