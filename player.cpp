#include "player.h"


Player::Player(const float& starting_stack)
    : m_stack(starting_stack), m_ammount_bet(0)
{
}

void Player::bet(const float& ammount)
{
    m_stack - ammount;
    m_ammount_bet + ammount;
}

bool Player::compare_player_positions(Player p1, Player p2)
{
    return p1.m_position < p2.m_position;
}
