#pragma once

#include "hands.h"


class Player
{
    public:
    Hand m_hand;
    int m_position; //0 position is button.
    float m_ammount_bet;
    double m_stack;
    int m_id;
    bool m_can_fold = true;
    bool m_can_check;
    bool m_can_call;
    bool m_can_raise;
    bool m_can_go_all_in;
    bool m_folded = false;

    Player(const float& starting_stack);
    void bet(const float& ammount);
    static bool compare_player_positions(const Player &p1, const Player &p2); //returns true if p1 is positioned before p2.
    static bool compare_player_hands(const Player &p1, const Player &p2); //returns true if p2's hand beats or draws p1's hand
    static bool compare_player_bets(const Player &p1, const Player &p2);

private:
    static int s_number_of_players;
};

std::vector<Player*> pointer_copy(std::vector<Player>& vect);