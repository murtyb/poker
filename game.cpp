
#include "game.h"


#define SMALL_BLIND 0.5
#define BIG_BLIND 1
#define TABLE_WIDTH 30



Game::Game(std::vector<Player>& players, Deck deck, double small_blind = SMALL_BLIND, double big_blind = BIG_BLIND)
    : m_players(players), 
      m_number_of_players(players.size()), 
      m_deck(deck), 
      m_small_blind(small_blind), 
      m_big_blind(big_blind),
      m_big_blind_position(2 % m_number_of_players),
      m_utg_position(3 % m_number_of_players),
      m_aggressor(nullptr),
      m_action_player(nullptr),
      m_button_location(0),
      m_table(Table(pointer_copy(m_players), 30))
{
}

void Game::set_positions()
{
    int x = 0;
    for (Player& p: m_players)
    {
        p.m_position = x;
        x++;
    }
}

void Game::move_button()
{
    std::rotate(m_players.begin(), m_players.begin() + 1, m_players.end());
    set_positions();
}

void Game::raise(const double& ammount_raised_to)// "
{
    float ammount_extra = ammount_raised_to - (*m_action_player).m_ammount_bet; 
    m_action_player->bet(ammount_extra);
    m_aggressor = m_action_player;
    m_last_raise = ammount_raised_to - m_highest_bet;
    m_highest_bet = ammount_raised_to;
}

void Game::call()
{
    float ammount_extra = m_highest_bet - m_action_player->m_ammount_bet;
    m_action_player->bet(ammount_extra); 
}

void Game::fold()
{
    m_action_player->m_folded = true;
    m_folded_players.push_back(m_action_player);
}

void Game::all_in()
{
    m_action_player->bet(m_action_player->m_stack);
    m_all_in_players.push_back(m_action_player);
    if (m_action_player->m_ammount_bet > m_highest_bet)
    {
        m_highest_bet = m_action_player->m_ammount_bet;
        m_aggressor = m_action_player;
    }  
}

void Game::end_round()
{
    m_all_in_players = {};
    m_folded_players = {};
    m_deck.reset_deck();
    move_button();
}

void Game::deal_hands()
{
    for (Player& player: m_players)
    {
        player.m_hand = m_deck.deal_hand();
    }
}

void Game::post_blinds()
{
    m_players[1].bet(m_small_blind);
    m_players[m_big_blind_position].bet(m_big_blind);
    m_highest_bet = m_big_blind;
}

void Game::pre_flop_setup()
{
    move_button();
    post_blinds();  
    m_aggressor = nullptr;
    m_last_raise = m_big_blind;
    m_action_player_location = m_utg_position;
    m_action_player = &m_players[m_utg_position];
    deal_hands();
}

bool Game::is_valid_raise(const double& desired_raise)
{
    if (desired_raise <= BIG_BLIND){return false;}
    return m_last_raise <= desired_raise - m_highest_bet;
}

bool Game::all_in_to_raise()
{
    return m_last_raise >= (*m_action_player).m_ammount_bet + (*m_action_player).m_stack - m_highest_bet;
}

bool Game::all_in_to_call()
{
    return  m_highest_bet >= (*m_action_player).m_ammount_bet + (*m_action_player).m_stack;
}

bool Game::all_but_one_players_folded()//checks if all but one player has folded.
{
    return m_players.size() - m_folded_players.size() == 1;
}

bool Game::all_but_one_players_folded_or_all_in()//checks if all but one player has folded.
{
    return m_players.size() - m_folded_players.size() - m_all_in_players.size() == 1;
}

bool Game::all_players_folded_or_all_in()//checks if all but one player has folded.
{
    return m_players.size() == m_folded_players.size() + m_all_in_players.size();
}

void Game::calculate_valid_options()
{
    m_valid_inputs = {"f"};
    if (m_action_player->m_ammount_bet == m_highest_bet)
    {
        m_action_player->m_can_check = true;
        m_valid_inputs.push_back(s_input_map["check"]);
    }
    else
    {
        m_action_player->m_can_check = false;
    }
    if (all_in_to_call())
    {
        m_action_player->m_can_go_all_in = true;
        m_valid_inputs.push_back(s_input_map["all in"]);
        m_action_player->m_can_call = false;
        m_action_player->m_can_raise = false;
        return;
    }

    m_action_player->m_can_call = true;
    m_valid_inputs.push_back(s_input_map["call"]);
    if (all_but_one_players_folded_or_all_in())
    {
        return;
    }

    m_action_player->m_can_go_all_in = true;
    m_valid_inputs.push_back(s_input_map["all in"]);
    if (all_in_to_raise())
    {
        m_action_player->m_can_raise = false;
        return;
    }

    m_action_player->m_can_raise = true;
    m_valid_inputs.push_back(s_input_map["raise"]);
}

bool Game::is_valid_action()
{
    return is_element_of(m_action, m_valid_inputs);
}

void Game::execute_inputted_action()
{
    if (m_action == "ch")
    {
        return;
    }
    if (m_action == "c")
    {
        call();
        return;
    }
    if (m_action == "f")
    {
        fold();
        return;
    }
    if (m_action == "r")
    {
        raise(m_desired_raise);
        return;
    }
    if (m_action == "a")
    {
        all_in();
        return;
    }
}

void Game::next_player()
{
    m_action_player_location = (m_action_player_location + 1) % m_number_of_players;
    m_action_player = &m_players[m_action_player_location];
    if (m_aggressor == m_action_player) {return;}
    if (is_element_of(m_action_player, m_folded_players)) {next_player(); return;}
    if (is_element_of(m_action_player, m_all_in_players)) {next_player(); return;}   
}


std::map<std::string, std::string> Game::s_input_map = {{"fold", "f"}, {"check", "ch"}, {"call", "c"}, {"raise", "r"}, {"all in", "a"}};

bool is_element_of(Player* x, std::vector<Player*>& v)
{
    for (Player* element : v)
    {
        if (element == x)
        {
            return true;
        }
    }
    return false;
}

void Game::draw_table()
{
    m_table.draw();
}
 