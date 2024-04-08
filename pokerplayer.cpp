#include "pokerplayer.h"

PokerPlayer::PokerPlayer(const float& starting_stack)
    : m_stack(starting_stack), 
      m_ammount_bet(0.0)
{
}

void PokerPlayer::bet(const float& ammount)
{
    m_stack -= ammount;
    m_ammount_bet += ammount;
}

bool PokerPlayer::compare_player_hands(const PokerPlayer &p1, const PokerPlayer &p2)
{
    return p1.m_hand <= p2.m_hand;
}

bool PokerPlayer::compare_player_bets(const PokerPlayer &p1, const PokerPlayer &p2)
{
    return p1.m_ammount_bet <= p2.m_ammount_bet;
}

std::vector<PokerPlayer*> pointer_copy(std::vector<PokerPlayer>& vect)
{
    std::vector<PokerPlayer*> output;
    for (PokerPlayer& element : vect)
    {
        output.push_back(&element);
    }
    return output;
}