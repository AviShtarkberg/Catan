// id:322530080 mail:avishb1213@gmail.com
#include <iostream>
#include <vector>
#include <map>
#include "DevCost.hpp"


//this file will be resposible for all the development card that will be used in a game.
//from the abc 5 classes will inherited.
namespace catan_game
{
    class DevCards
    {
    public:
        DevCards() {}
        DevCards(const std::map<Resource, int> &cost) : _cost(cost) {}
        virtual ~DevCards(){}

        std::map<Resource, int> get_cost() const
        {
            return _cost;
        }
        
        virtual std::string get_type() const
        {
            return "";
        }

    protected:
        std::map<Resource, int> _cost;
    };

    class MonopolCard : public DevCards
    {
    public:
        MonopolCard() : DevCards(Development_cost::get_cost()) {}
        std::string get_type() const override
        {
            return "monopol";
        }
    };

    class RoadBuilderCard : public DevCards
    {
    public:
        RoadBuilderCard() : DevCards(Development_cost::get_cost()) {}
        std::string get_type() const override
        {
            return "road builder";
        }
    };

    class YearOfPlentyCard : public DevCards
    {
    public:
        YearOfPlentyCard() : DevCards(Development_cost::get_cost()) {}
        std::string get_type() const override
        {
            return "year of plenty";
        }
    };

    class Knight : public DevCards
    {
    public:
        Knight() : DevCards(Development_cost::get_cost()) {}
        std::string get_type() const override
        {
            return "knight"; 
        }
    };

    class WinningPoint : public DevCards
    {
    public:
        WinningPoint() : DevCards(Development_cost::get_cost()) {}
        std::string get_type() const override
        {
            return "winning point";
        }
    };
}