#pragma once

#include <vector>
#include <algorithm>
#include "..\players\pokerplayergroup.h"
#include "winrules.h"


class Pot
{
public:
    Pot(std::vector<PokerPlayer*> possible_winners);
    void find_and_pay_winners_of_pot(const WinRules& win_rules);

private:
    std::vector<PokerPlayer*> m_possible_winners;
    Chips m_contribution;
    Chips m_pot_total = Chips(0, 'c');


    Chips calculate_contribution();
    void allocate_remaining_chips(std::vector<PokerPlayer*> &winners);
    void divide_up_chips(std::vector<PokerPlayer*> &winners);
    void gather_chips();
    std::vector<PokerPlayer*> find_winners(std::vector<PokerPlayer*>& non_folded_players, const WinRules& win_rules);
    std::vector<PokerPlayer*> find_non_folded_players();
};

class PotArray
{
public :
    PotArray(PokerPlayerGroup& players);
    void find_and_pay_winners(const WinRules& win_rules);

private:
    std::vector<Pot> m_side_pots;
    
    void create_side_pots(std::vector<PokerPlayer*> players);
};