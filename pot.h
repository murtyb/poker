#pragma once

#include <vector>
#include <algorithm>
#include "player.h"


class Pot
{
    public:
        Pot(std::vector<Player*> possible_winners);
        double calculate_contribution();
        void gather_chips();
        Hand find_winning_hand(std::vector<Player*>& non_folded_players);
        std::vector<Player*> find_winners(std::vector<Player*>& non_folded_players);
        void find_and_pay_winners_of_pot();
        void divide_up_chips(std::vector<Player*> &winners);
        std::vector<Player*> find_non_folded_players();

        std::vector<Player*> m_possible_winners;
        double m_contribution;
        double m_pot_total;
};

class PotArray
{
    public :
    PotArray(std::vector<Player*> players);
    void find_and_pay_winners();
    void create_side_pots(std::vector<Player*> &players);
    void order_players_by_decreasing_bet(std::vector<Player*>& players);
    std::vector<Pot> m_side_pots;
};