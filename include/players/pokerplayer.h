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
    float m_ammount_bet;
    double m_stack;

    PokerPlayer(const float& starting_stack);
    void bet(const float& ammount);

    static bool compare_player_bets(const PokerPlayer &p1, const PokerPlayer &p2);
};