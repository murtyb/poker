#include "holdemprefloplogic.h"


HoldEmPreFlopLogic::HoldEmPreFlopLogic(std::vector<PokerPlayer>& players, Deck& deck, double small_blind, double big_blind)
    : m_small_blind(small_blind),
      m_big_blind(big_blind),
      BaseGame(players, deck)
{
}

void HoldEmPreFlopLogic::calculate_valid_options()
{
    if (m_action_player->m_ammount_bet == m_highest_bet)
    {
        m_action_player->m_can_check = true;
    }
    else
    {
        m_action_player->m_can_check = false;
    }

    if (all_in_to_call())
    {
        m_action_player->m_can_go_all_in = true;
        m_action_player->m_can_call = false;
        m_action_player->m_can_raise = false;
        return;
    }

    m_action_player->m_can_call = true;
    if (all_but_one_players_folded_or_all_in())
    {
        m_action_player->m_can_go_all_in = false;
        m_action_player->m_can_raise = false;
        return;
    }

    m_action_player->m_can_go_all_in = true;
    if (all_in_to_raise())
    {
        m_action_player->m_can_raise = false;
        return;
    }
    m_action_player->m_can_raise = true;
}

void HoldEmPreFlopLogic::pre_flop_setup()
{
    m_players.move_button();
    post_blinds(m_small_blind, m_big_blind);  
    m_last_raise = m_big_blind;
    deal_hands(2);
}

bool HoldEmPreFlopLogic::in_betting_phase()
{
    if (all_but_one_players_folded()) {return false;}
    if (m_action_player == m_aggressor) {return false;}
    if (all_players_folded_or_all_in()) {return false;}
    if (m_limped_to_big_blind && m_aggressor == nullptr) {return false;}
    check_if_limped_to_big_blind();
    return true;
}

void HoldEmPreFlopLogic::check_if_limped_to_big_blind()
{
    m_limped_to_big_blind = (m_aggressor == nullptr && m_action_player == m_players.bb_player());
}

void HoldEmPreFlopLogic::allocate_winnings()
{
    PotArray SidePots(m_players);
    SidePots.find_and_pay_winners();
}

void HoldEmPreFlopLogic::end_round()
{
    m_num_of_all_in_players = 0;
    m_num_of_folded_players = 0;
    m_limped_to_big_blind = false;
    for (int i = 0; i < m_players.size(); i++)
    {
        m_players.position(i)->m_folded = false;
    }
    m_deck.reset_deck();
}




