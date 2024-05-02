#pragma once

#include "..\players\pokerplayergroup.h"
#include "..\cards\deck.h"


class BaseGame
{
public:
    PokerPlayerGroup& m_players;
    PokerPlayer* &m_action_player;
    PokerPlayer* &m_aggressor;
    Deck& m_deck;
    int m_num_of_folded_players = 0;
    int m_num_of_all_in_players = 0;
    Chips m_last_raise;
    Chips m_highest_bet;

    BaseGame(PokerPlayerGroup& players, Deck& deck);
    void raise(Chips amount);
    void call();
    void fold();
    void deal_hands(int num_of_cards);
    void post_blinds(Chips sb, Chips bb);
    bool is_valid_raise(Chips amount_raised_to);
    void all_in();
    bool all_in_to_raise();
    bool all_in_to_call();
    bool all_but_one_players_folded();
    bool all_but_one_players_folded_or_all_in();
    bool all_players_folded_or_all_in();
};