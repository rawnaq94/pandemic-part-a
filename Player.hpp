#pragma once
#include "Board.hpp"
#include "Color.hpp"
#include "City.hpp"



namespace pandemic
{
    class Player
    {
        
      public:
            Player();
            Player(Board board,City c);
            Player& drive(City c);
            Player& fly_direct(City c);
            Player& fly_charter(City c);
            Player& fly_shuttle(City c);
            Player& build();
            bool discover_cure(Color c);
            Player& treat(City c);
            std::string role();
            Player& take_card(City c);
    

    };
}
