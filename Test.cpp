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
    player.take_card(City::Mumbai); 
    player.discover_cure(Color::Blue); // can perform a "drug discovery" operation in any city
    CHECK_THROWS(player.treat(City::Paris));   
    CHECK_THROWS(player.treat(City::HongKong)); 

}


// ------------------------------- Medic ---------------------------------------------------
TEST_CASE("check Medic player") // when he performs a "disease treatment" operation, he removes all the disease cubes from the city he is in, and not just one.
{
    Board board;
    Medic player{board,City::Paris};
    CHECK_THROWS(player.drive(City::Cairo));
    CHECK_THROWS(player.drive(City::Istanbul));
    CHECK_THROWS(player.drive(City::Mumbai));	
    CHECK_THROWS(player.fly_direct(City::Madrid)); // has not card of madrid
    CHECK_THROWS(player.fly_direct(City::HongKong)); // has not card of HongKong
    CHECK_THROWS(player.fly_charter(City::Milan)); // has not card of paris
    CHECK_THROWS(player.fly_shuttle(City::Istanbul)); // there is no research station from Istanbul and paris
    CHECK_THROWS(player.build()); // has not card of paris
    player.take_card(City::Paris);
    player.build(); // now we can build
    CHECK_THROWS(player.fly_shuttle(City::NewYork)); // discarded the paris card during the build
    board[City::Paris]=2;
    player.treat(City::Miami);
    CHECK_THROWS(player.treat(City::Miami));

}



// ------------------------------- Virologist -------------------------------------------
TEST_CASE("check Virologist player") // Can perform a "disease treatment" operation, not only in the city in which it is located, but in any city in the world - by throwing a card of that city.
{
    Board board;
    Virologist player{board,City::Paris};
    CHECK_THROWS(player.drive(City::Cairo));
    CHECK_THROWS(player.drive(City::Istanbul));
    CHECK_THROWS(player.drive(City::Mumbai));	
    CHECK_THROWS(player.fly_direct(City::Madrid)); // has not card of madrid
    CHECK_THROWS(player.fly_direct(City::HongKong)); // has not card of HongKong
    CHECK_THROWS(player.fly_charter(City::Milan)); // has not card of paris
    CHECK_THROWS(player.fly_shuttle(City::Istanbul));
    CHECK_THROWS(player.treat(City::Milan));
    board[City::Paris]=2;
    player.take_card(City::Paris);
    player.fly_charter(City::NewYork);
    player.treat(City::Paris);
    CHECK_THROWS(player.treat(City::Paris));
    CHECK_THROWS(player.build());
    
}



// --------------------------------------- GeneSplicer --------------------------------------
TEST_CASE("check GeneSplicer player") // can perform a "drug discovery" operation with the help of 5 cards - not necessarily from the color of the disease.
{
    Board board;
    GeneSplicer player{board,City::Paris};
    CHECK_THROWS(player.drive(City::Cairo));
    CHECK_THROWS(player.drive(City::Istanbul));
    CHECK_THROWS(player.drive(City::Mumbai));	
    CHECK_THROWS(player.fly_direct(City::Madrid)); // has not card of madrid
    CHECK_THROWS(player.fly_direct(City::HongKong)); // has not card of HongKong
    CHECK_THROWS(player.fly_charter(City::Milan)); // has not card of paris
    CHECK_THROWS(player.fly_shuttle(City::Istanbul));
    CHECK_THROWS(player.treat(City::Milan));
    player.take_card(City::Delhi);
    player.take_card(City::Paris);
    player.take_card(City::Mumbai);
    player.take_card(City::Madrid);
    player.take_card(City::Miami);
    player.discover_cure(Color::Red); // have 5 cards
    CHECK_THROWS(player.discover_cure(Color::Red));
    CHECK_THROWS(player.build());
}


// -------------------------------------- FieldDoctor ----------------------------------------------
TEST_CASE("check FieldDoctor player") // can perform a "disease treatment" operation not only in the city he is in but in any city near the city he is in, without throwing a city card. 
{
    Board board;
    FieldDoctor player{board,City::Paris};
    CHECK_THROWS(player.drive(City::Cairo));
    CHECK_THROWS(player.drive(City::Istanbul));
    CHECK_THROWS(player.drive(City::Mumbai));	
    CHECK_THROWS(player.fly_direct(City::Madrid)); // has not card of madrid
    CHECK_THROWS(player.fly_direct(City::HongKong)); // has not card of HongKong
    CHECK_THROWS(player.fly_charter(City::Milan)); // has not card of paris
    CHECK_THROWS(player.fly_shuttle(City::Istanbul));
    CHECK_THROWS(player.treat(City::Milan));
    board[City::Paris]=1;
    player.treat(City::Paris);
    CHECK_THROWS(player.treat(City::Paris));
    CHECK_THROWS(player.build());
}

