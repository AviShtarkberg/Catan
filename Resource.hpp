// id:322530080 mail:avishb1213@gmail.com
#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <iostream>
using namespace std;

namespace catan_game {
    enum Resource {
        BRICK,
        LUMBER,
        WOOL,
        GRAIN,
        ORE,
        NO_RESOURCE
    };

    Resource res_from_string(const string &s);
}

#endif // RESOURCE_HPP
