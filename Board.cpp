#include "Board.hpp"


using namespace pandemic;


namespace pandemic{
       int& Board::operator[](City city)
       {
           return n_1;
       }
  
       std::ostream& operator<< (std::ostream& os, const Board& b)
       {
           return os;
       } 
  
       bool Board::is_clean()
       {
           return true;
       }
  
       void Board::remove_cures()
       {

       }
}



