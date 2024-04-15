#pragma once

#include "..\game_logic\basegame.h"
#include "..\game_logic\pot.h"


class HoldEmPreFlopLogic:virtual public BaseGame
{
public:
    double m_small_blind;
    double m_big_blind;
    bool m_limped_to_big_blind = false;

    HoldEmPreFlopLogic(std::vector<PokerPlayer>& players, Deck& deck, double small_blind, double big_blind);
    void pre_flop_setup();
    bool in_betting_phase();
    void check_if_limped_to_big_blind();
    void allocate_winnings();
    void end_round();
    void calculate_valid_options();
};