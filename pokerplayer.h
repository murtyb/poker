#pragma once
#include "player.h"

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
    float m_ammount_bet;
    double m_stack;

    PokerPlayer(const float& starting_stack);
    void bet(const float& ammount);
    
    static bool compare_player_hands(const PokerPlayer &p1, const PokerPlayer &p2); //returns true if p2's hand beats or draws p1's hand
    static bool compare_player_bets(const PokerPlayer &p1, const PokerPlayer &p2);
};

std::vector<PokerPlayer*> pointer_copy(std::vector<PokerPlayer>& vect);
