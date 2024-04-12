#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"
#include "hands.h"
#include "deck.h"
#include "preflopgame.h"

using std::string;



int main()
{
    try
    {
        Card::card_initialization();
        std::vector<string> card_symbols = {"A", "A", "K" ,"10", "10", "9", "9", "7", "J", "Q"};
        Deck deck(card_symbols);
        std::vector<PokerPlayer> players = {PokerPlayer(100), PokerPlayer(100), PokerPlayer(100)};
        PreFlopGame Game1(players, deck, 0.5 , 1);
        Game1.run();

    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -1;
    }
    return 0;
}