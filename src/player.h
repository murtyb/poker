#pragma once

#include "hands.h"


class Player
{
    public:
    Player();
    Hand m_hand;
    int m_position; //0 position is button.
    int m_id;

    static bool compare_player_positions(const Player &p1, const Player &p2); //returns true if p1 is positioned before p2.

    private:
    static int s_number_of_players;
};

