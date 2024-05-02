#include "..\..\include\players\pokerplayer.h"
#include "pokerplayer.h"

PokerPlayer::PokerPlayer(const Chips& starting_stack)
    : m_stack(starting_stack),
      Player()
{
}

PokerPlayer::PokerPlayer(int starting_stack) : PokerPlayer(Chips(starting_stack, 'b')){}

void PokerPlayer::bet(Chips ammount)
{
    m_stack -= ammount;
    m_ammount_bet += ammount;
}

bool PokerPlayer::compare_player_bets(const PokerPlayer &p1, const PokerPlayer &p2)
{
    return p1.m_ammount_bet <= p2.m_ammount_bet;
}
