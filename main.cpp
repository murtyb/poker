#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"

using std::string;


int main()
{
    try
    {
        std::cout << 1;
        Card::card_initialization();
        Card Ace("87");
        std::cout << 4;
        std::cout << Ace.get_value() << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -1;
    }

    return 0;
}