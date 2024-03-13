#include "player.h"


Player::Player(const float& starting_stack)
    : m_stack(starting_stack), m_ammount_bet(0)
{
    s_number_of_players++;
    m_id = s_number_of_players;
}

void Player::bet(const float& ammount)
{
    m_stack - ammount;
    m_ammount_bet + ammount;
}

bool Player::compare_player_positions(const Player &p1, const Player &p2)
{
    return p1.m_position < p2.m_position;
}

bool Player::compare_player_hands(const Player &p1, const Player &p2)
{
    return p1.m_hand <= p2.m_hand;
}

bool Player::compare_player_stacks(const Player &p1, const Player &p2)
{
    return p1.m_stack <= p2.m_stack;
}

void Player::transfer(Player losing_player, double ammount_owed)
{
    losing_player.m_ammount_bet - ammount_owed;
    m_stack + ammount_owed;
}

int Player::s_number_of_players = 0; 
