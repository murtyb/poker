#pragma once

#include <vector>
#include <algorithm>
#include "pokerplayer.h"


class Pot
{
    public:
        Pot(std::vector<PokerPlayer*> possible_winners);
        double calculate_contribution();
        void gather_chips();
        Hand find_winning_hand(std::vector<PokerPlayer*>& non_folded_players);
        std::vector<PokerPlayer*> find_winners(std::vector<PokerPlayer*>& non_folded_players);
        void find_and_pay_winners_of_pot();
        void divide_up_chips(std::vector<PokerPlayer*> &winners);
        std::vector<PokerPlayer*> find_non_folded_players();

        std::vector<PokerPlayer*> m_possible_winners;
        double m_contribution;
        double m_pot_total;
};

class PotArray
{
    public :
    PotArray(std::vector<PokerPlayer*> players);
    void find_and_pay_winners();
    void create_side_pots(std::vector<PokerPlayer*> &players);
    void order_players_by_decreasing_bet(std::vector<PokerPlayer*>& players);
    std::vector<Pot> m_side_pots;
};