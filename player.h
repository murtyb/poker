#pragma once

#include "hands.h"


class Player
{
    public:
    Hand hand;
    int m_position; //0 position is button.
    float m_ammount_bet;
    static bool compare_player_positions(const Player &p1, const Player &p2); //returns true if p1 is positioned before p2.

    Player(const float& starting_stack);
    void bet(const float& ammount);

    
    private:
    double m_stack;
};