#include "player.h"


Player::Player(const float& starting_stack)
    : m_stack(starting_stack), 
      m_ammount_bet(0.0f)
{
    s_number_of_players++;
    m_id = s_number_of_players;
}

void Player::bet(const float& ammount)
{
    m_stack -= ammount;
    m_ammount_bet += ammount;
}

bool Player::compare_player_positions(const Player &p1, const Player &p2)
{
    return p1.m_position < p2.m_position;
}

bool Player::compare_player_hands(const Player &p1, const Player &p2)
{
    return p1.m_hand <= p2.m_hand;
}

bool Player::compare_player_bets(const Player &p1, const Player &p2)
{
    return p1.m_ammount_bet <= p2.m_ammount_bet;
}

int Player::s_number_of_players = 0; 


std::vector<Player*> pointer_copy(std::vector<Player>& vect)
{
    std::vector<Player*> output;
    for (Player& element : vect)
    {
        output.push_back(&element);
    }
    return output;
}