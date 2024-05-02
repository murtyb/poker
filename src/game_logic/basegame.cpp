#include "..\..\include\game_logic\basegame.h"


BaseGame::BaseGame(PokerPlayerGroup& players, Deck& deck)
    : m_players(players), 
      m_action_player(m_players.m_action_player),
      m_aggressor(m_players.m_aggressor),
      m_deck(deck)
{
}

bool BaseGame::all_in_to_raise()
{
    return m_action_player->m_ammount_bet + m_action_player->m_stack - m_highest_bet <= m_last_raise;
}

bool BaseGame::all_in_to_call()
{
    return  m_action_player->m_ammount_bet + m_action_player->m_stack <= m_highest_bet;
}

bool BaseGame::all_but_one_players_folded()//checks if all but one player has folded.
{
    return m_players.size() - m_num_of_folded_players == 1;
}

bool BaseGame::all_but_one_players_folded_or_all_in()//checks if all but one player has folded.
{
    return m_players.size() - m_num_of_folded_players - m_num_of_all_in_players == 1;
}

bool BaseGame::all_players_folded_or_all_in()//checks if all but one player has folded.
{
    return m_players.size() == m_num_of_folded_players + m_num_of_all_in_players;
}

void BaseGame::raise(Chips ammount_raised_to)
{
    if (m_action_player->m_stack <= ammount_raised_to) {all_in(); return;}
    Chips ammount_extra = ammount_raised_to - m_action_player->m_ammount_bet; 
    m_action_player->bet(ammount_extra);
    m_aggressor = m_action_player;
    m_last_raise = ammount_raised_to - m_highest_bet;
    m_highest_bet = ammount_raised_to;
}

void BaseGame::call()
{
    Chips ammount_extra = m_highest_bet - m_action_player->m_ammount_bet;
    m_action_player->bet(ammount_extra); 
}

void BaseGame::fold()
{
    m_action_player->m_folded = true;
    m_num_of_folded_players++;
}

void BaseGame::all_in()
{
    m_action_player->bet(m_action_player->m_stack);
    m_action_player->m_is_all_in = true;
    m_num_of_all_in_players++;
    if (!(m_action_player->m_ammount_bet <= m_highest_bet))
    {
        m_highest_bet = m_action_player->m_ammount_bet;
        m_aggressor = m_action_player;
    }  
}

bool BaseGame::is_valid_raise(Chips desired_raise)
{
    if (desired_raise <= m_last_raise){return false;}
    return m_last_raise <= desired_raise - m_highest_bet;
}

void BaseGame::deal_hands(int num_of_cards)
{
    for (int i = 0; i < m_players.size(); i++)
    {
        m_players.position(i)->m_hand = m_deck.deal_hand(num_of_cards);
    }
}

void BaseGame::post_blinds(Chips sb, Chips bb)
{
    m_players.sb_player()->bet(sb);
    m_players.bb_player()->bet(bb);
    m_highest_bet = bb;
}