#include "Board.hpp"
#include "doctest.h"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Scientist.hpp"
#include "Researcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "GeneSplicer.hpp"
#include "FieldDoctor.hpp"


using namespace std;
using namespace pandemic;


TEST_CASE("check if the board is_clean") // Check if the board is clear of disease cubes
{
    Board board;
    CHECK_FALSE(!board.is_clean());
	board[City::NewYork] = 3;  // update 3 disease cubes in New York city
    CHECK_FALSE(board.is_clean());
}

// ------------------------------ OperationsExpert  ----------------------------------
TEST_CASE("check OperationsExpert player") // Performs a construction operation for any city he is in without throwing card
{
    Board board;
    OperationsExpert player{board, City::NewYork};
    CHECK_THROWS(player.drive(City::Khartoum)); 
    player.take_card(City::NewYork); 
    player.fly_charter(City::Moscow); // because he has the card of the same city he is in
    CHECK_THROWS(player.fly_direct(City::Milan)); 
    CHECK_THROWS(player.treat(City::Delhi)); //no cure was found
    player.take_card(City::London); 
    player.fly_direct(City::London); 
    player.build(); 

}
 


// -------------------------------- Dispatcher -------------------------------------------
TEST_CASE("check Dispatcher player") // can perform a direct flight without throwing a card if it is at a research station
{
    Board board;
    Dispatcher player{board,City::Paris};
    CHECK_THROWS(player.drive(City::Moscow)); // they are not adjacent
    CHECK_THROWS(player.fly_direct(City::Tokyo)); // he does not have a card
    Dispatcher player{board,City::Mumbai};
    CHECK_THROWS(player.drive(City::Madrid)); // they are not adjacent
    CHECK_THROWS(player.treat(City::Mumbai)); // no cure was found
    player.take_card(City::Paris);
    player.fly_charter(City::Milan); // has a card of the city that is in it (paris)
    CHECK_THROWS(player.fly_direct(City::Milan)); 
    CHECK_THROWS(player.build());
    CHECK_THROWS(player.fly_direct(City::Miami));//  he does not have a card 
    player.take_card(City::Milan);
    player.build(); // has already flown there
    CHECK_THROWS(player.treat(City::Miami));
}



// ----------------------------------- Scientist -----------------------------------
TEST_CASE("check Scientist player") // can perform a "drug discovery" operation with only n cards
{
    Board board;
    Scientist player{board, City::Delhi,4}; 
    CHECK_THROWS(player.drive(City::Cairo)); // they are not adjacent
    CHECK_THROWS(player.fly_direct(City::Istanbul)); // does not have a card
    player.take_card(City::London);
    CHECK_THROWS(player.fly_direct(City::Milan));
    CHECK_THROWS(player.fly_charter(City::Milan)); // has not delhi card
    player.take_card(City::MexicoCity);
    CHECK_THROWS(player.build()); // has not MexicoCity card
    player.take_card(City::Delhi); 
    player.build();
    CHECK_THROWS(player.fly_charter(City::Milan)); // has not card to the same city
    player.take_card(City::Delhi);
    player.fly_charter(City::Milan);
    CHECK_THROWS(player.build()); 
    player.take_card(City::Milan);
    player.build(); 
    player.fly_shuttle(City::Delhi); // build was done in delhi
    CHECK_THROWS(player.treat(City::Mumbai));
    player.take_card(City::Madrid);
    player.take_card(City::Milan);
    player.take_card(City::Paris);
    CHECK_THROWS(player.discover_cure(Color::Blue));
    player.take_card(City::Delhi); // build was done in delhi
    player.discover_cure(Color::Blue);
}


// ------------------------------ Researcher ---------------------------------------------
TEST_CASE("check Researcher player") // can perform a "drug discovery" operation in any city - does not have to be at a research station.
{
    Board board;
    Researcher player{board, City::Tokyo};
    CHECK_THROWS(player.drive(City::Delhi));
    CHECK_THROWS(player.drive(City::Mumbai));
    CHECK_THROWS(player.drive(City::Moscow));
    CHECK_THROWS(player.fly_direct(City::Paris));
    CHECK_THROWS(player.fly_direct(City::Washington));
    CHECK_THROWS(player.fly_direct(City::HongKong));
    CHECK_THROWS(player.fly_charter(City::Milan));
    CHECK_THROWS(player.fly_charter(City::Delhi));
    CHECK_THROWS(player.fly_charter(City::Baghdad));
    player.take_card(City::Istanbul);
    player.take_card(City::Milan);
    player.take_card(City::Paris);
    player.take_card(City::Istanbul);
    CHECK_THROWS(player.discover_cure(Color::Blue));
    CHECK_THROWS(player.discover_cure(Color::Red));
    CHECK_THROWS(player.discover_cure(Color::Black));
    CHECK_THROWS(player.discover_cure(Color::Yellow));

    player.take_card(City::Montreal);
    player.discover_cure(Color::Blue);
    CHECK_THROWS(player.treat(City::Miami));    
}

















