#pragma once

#include "..\players\pokerplayergroup.h"
#include "..\cards\deck.h"


class BaseGame
{
public:
    PokerPlayerGroup m_players;
    PokerPlayer* &m_action_player;
    PokerPlayer* &m_aggressor;
    Deck m_deck;
    int m_num_of_folded_players = 0;
    int m_num_of_all_in_players = 0;
    double m_last_raise;
    double m_highest_bet;

    BaseGame(std::vector<PokerPlayer> &players, Deck& deck);
    void raise(double ammount);
    void call();
    void fold();
    void deal_hands(int num_of_cards);
    void post_blinds(double sb, double bb);
    bool is_valid_raise(double ammount_raised_to);
    void all_in();
    bool all_in_to_raise();
    bool all_in_to_call();
    bool all_but_one_players_folded();
    bool all_but_one_players_folded_or_all_in();
    bool all_players_folded_or_all_in();
};