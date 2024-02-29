#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"
#include "hands.h"

using std::string;



int main()
{
    try
    {
        Card::card_initialization();
        Card Ace("A");
        Card Six("6");
        Card Seven("7");
        Hand Hand_1(Ace, Six);
        Hand Hand_2(Ace, Seven);
        Hand Hand_3(Six, Six);
        std::cout << (Hand_2 <= Hand_1) << std::endl;
        std::cout << (Hand_3 <= Hand_2) << std::endl;
        std::cout << (Hand_2 <= Hand_3) << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -1;
    }

    return 0;
}