// id:322530080 mail:avishb1213@gmail.com
#include "Resource.hpp"

namespace catan_game {
    Resource res_from_string(const string &s) {
        if (s == "wool") {
            return WOOL;
        } else if (s == "grain") {
            return GRAIN;
        } else if (s == "ore") {
            return ORE;
        } else if (s == "brick") {
            return BRICK;
        } else if (s == "lumber") {
            return LUMBER;
        }
        return NO_RESOURCE;
    }
}
