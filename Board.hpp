#pragma once
#include <string>
#include "City.hpp"

namespace pandemic
{
    class Board
    {
        int n_1; // broad with 48 city
      
      
        public:
            int& operator[](City city); // City ID >> Read + Update disease level
            bool is_clean();  
            void remove_cures(); // removal of detected drugs so far
            friend std::ostream& operator<< (std::ostream& os, const Board& b); // broad status << disease level - medications - research stations
    };
}
