
#include "game.h"
#include "player.h"
#include <vector>
#include <algorithm>


Game::Game(std::vector<Player>& players, Deck deck)
    :m_players(players), m_number_of_players(players.size()), m_deck(deck)
{    
}

void Game::set_positions()
{
    int x = m_button_location;
    for (int i; i < m_number_of_players; i++ )
    {
        m_players[x].m_position = i;
        x++;
        x % m_number_of_players;
    }
}

void Game::move_button()
{
    m_button_location = (m_button_location + 1) % m_number_of_players;
    set_positions();
    std::sort(m_players.begin(), m_players.end(), &Player::compare_player_positions);
}

void Game::raise(const float& ammount)
{
    float ammount_extra = ammount - (*m_action_player).m_ammount_bet; 
    (*m_action_player).bet(ammount_extra);
    m_aggressor = m_action_player;
    m_highest_bet = ammount;
}

void Game::call()
{
    float ammount_extra = m_highest_bet - (*m_action_player).m_ammount_bet; 
}

void Game::fold()
{
    m_folded_players.push_back(*m_action_player);
}

void Game::end_round()
{
    m_folded_players = {};
    move_button();
}

void Game::deal_hands()
{
    for (Player player: m_players)
    {
        player.hand = m_deck.deal_hand();
    }
}

