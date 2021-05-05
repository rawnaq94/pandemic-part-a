#include "Player.hpp"


namespace pandemic
{
            Player::Player()
            {
                
            }
            
            Player::Player(Board board,City city)
            {

            }
            
            Player& Player::drive(City city)
            {
                return *this;
            }
            
            Player& Player::fly_direct(City city)
            {
                return *this;
            }
            
            Player& Player::fly_charter(City city)
            {
                return *this;
            }
            
            Player& Player::fly_shuttle(City city)
            {
                return *this;
            }
            
            Player& Player::build()
            {
                return *this;
            }
            
            bool Player::discover_cure(Color city)
            {
                return true;
            }
            
            Player& Player::treat(City city)
            {
                return *this;
            }
            
            std::string Player::role()
            {
                return "";
            }
            
            Player& Player::take_card(City city)
            {
                return *this;
            }

}
