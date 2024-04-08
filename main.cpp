#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"
#include "hands.h"
#include "deck.h"
#include "simple_game.h"

using std::string;



int main()
{
    try
    {
        Card::card_initialization();
        std::vector<string> card_symbols = {"A", "A", "K" ,"10", "10", "9", "9", "7", "J", "Q"};
        Deck deck(card_symbols);
        std::vector<Player> players = {Player(100), Player(100), Player(100)};

        //std::string m_action = "";
        //if (!(std::cin >> m_action))
        //{
          //  std::cout << "invalid input\n";
        //} 
        SimpleGame Game1(players, deck, 0.5 , 1);
        Game1.run();

    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -1;
    }

    return 0;
}