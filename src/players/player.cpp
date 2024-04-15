#include "..\..\include\players\player.h"


Player::Player()
{
    s_number_of_players++;
    m_id = s_number_of_players;
}

bool Player::compare_player_positions(const Player &p1, const Player &p2)
{
    return p1.m_position < p2.m_position;
}


int Player::s_number_of_players = 0; 

