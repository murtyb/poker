#include "..\..\include\holdem\preflopgame.h" 

int main()
{
    try
    {
        Card::card_initialization();
        std::vector<string> card_symbols = {"A", "K", "10", "9", "8", "7", "6", "5", "4", "3", "2",
                                            "A", "K", "10", "9", "8", "7", "6", "5", "4", "3", "2",
                                            "A", "K", "10", "9", "8", "7", "6", "5", "4", "3", "2",
                                            "A", "K", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
        Deck deck(card_symbols);
        deck.shuffle_deck();
        std::cout << "Please enter the number of players:" << std::endl;
        int num_of_players;
        std::cin >> num_of_players;
        PokerPlayerGroup players(num_of_players);
        PreFlopGame Game1(players, deck, Chips(0.5, 'b') , Chips(1, 'b'));
        Game1.run();

    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -1;
    }
    return 0;
}