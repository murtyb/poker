
#include "game.h"
#include "player.h"
#include <vector>
#include <algorithm>


Game::Game(std::vector<Player>& players)
    :m_players(players), m_number_of_players(players.size())
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
    m_current_players = std::sort(m_current_players.begin(), m_current_players.end(), bool (Player p1, Player p2) ->p1.position < p2.position)
}

void Game::raise(const float& ammount)
{
    float ammount_extra = ammount - m_action_player.m_ammount_bet; 
    m_action_player.bet(ammount_extra);
    m_aggressor = m_action_player;
}