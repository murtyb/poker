#pragma once
#include "player.h"
#include "../chips/chips.h"

class PokerPlayer: public Player
{
    public:
    bool m_can_fold = true;
    bool m_can_check;
    bool m_can_call;
    bool m_can_raise;
    bool m_can_go_all_in;
    bool m_folded = false;
    bool m_is_all_in = false;
    bool m_on_button = false;
    Chips m_amount_bet;
    Chips m_stack;

    PokerPlayer(const Chips& starting_stack);
    PokerPlayer(int starting_stack);
    void bet(Chips amount);

    static bool compare_player_bets(const PokerPlayer &p1, const PokerPlayer &p2);
};
