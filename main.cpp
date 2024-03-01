#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"
#include "hands.h"
#include "deck.h"

using std::string;



int main()
{
    try
    {
        Card::card_initialization();
        std::vector<string> card_symbols = {"A", "A", "K" , "10"};
        Deck deck(card_symbols);
        Hand hand1 = deck.deal_hand();
        Hand hand2 = deck.deal_hand();
        std::cout << hand1 << hand2;
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -1;
    }

    return 0;
}