#include "simple_game.h"
#include "pot.h"

void SimpleGame::get_user_input()
{
    clear_cin();
    if (!(std::cin >> m_action))
    {
        std::cout << "invalid input\n";
        get_user_input();
        return;
    }

    if (! is_valid_action())
    {
        std::cout << "invalid input\n";
        get_user_input();
        return;
    }

    if (m_action != "r")
    {
        return;
    }

    if (!(std::cin >> m_desired_raise))
    {
        std::cout << "invalid raise\n";
        get_user_input();
        return;
    }
    
    if (! is_valid_raise(m_desired_raise))
    {
        std::cout << "invalid raise\n";
        get_user_input();
        return;
    }

}

void SimpleGame::request_input_message()
{
    std::cout << "Player " << m_action_player->m_id << ": ";
    std::cout << "You are in position " << m_action_player->m_position << ", ";
    std::cout << "your stack size is: " << m_action_player->m_stack << "bb, ";
    std::cout << "and so far you have bet " << m_action_player->m_ammount_bet << "bb.\n";
    std::cout << "You have " << m_action_player->m_hand << "and the current price is " << m_highest_bet << "\n";
    std::cout << "Your options are:\n";
    print_options();
}

void SimpleGame::print_options()
{
    int option_number = 1;
    if (m_action_player ->m_can_fold) 
    {
        std::cout << option_number << ". " << "fold" << '('<< s_input_map["fold"] << ')' << std::endl;
        option_number++;
    }

    if (m_action_player ->m_can_check) 
    {
        std::cout << option_number << ". " << "check" << '(' << s_input_map["check"] << ')' << std::endl;
        option_number++;
    }

    if (m_action_player ->m_can_call) 
    {
        std::cout << option_number << ". " << "call" << '(' << s_input_map["call"] << ')' << std::endl;
        option_number++;
    }
    if (m_action_player ->m_can_raise) 
    {
        std::cout << option_number << ". " << "raise" << '(' << s_input_map["raise"] << ')' << std::endl;
        option_number++;
    }

    if (m_action_player ->m_can_go_all_in) 
    {
        std::cout << option_number << ". " << "all in" << '(' << s_input_map["all in"] << ')' << std::endl;
        option_number++;
    }
}

void SimpleGame::run()
{
    while (true)
    {
        pre_flop_setup();
        play_pre_flop();
        end_round();
    }
}

void SimpleGame::play_pre_flop()
{
    while (in_betting_phase())
    {
        calculate_valid_options();
        request_input_message();
        get_user_input();
        execute_inputted_action();
        next_player();
    }
    allocate_winnings();
}

bool SimpleGame::in_betting_phase()
{
    if (all_but_one_players_folded()) {return false;}
    if (m_action_player == m_aggressor) {return false;}
    if (all_players_folded_or_all_in()) {return false;}
    if (m_limped_to_big_blind && m_aggressor == nullptr) {return false;}
    check_if_limped_to_big_blind();
    return true;
}

void SimpleGame::check_if_limped_to_big_blind()
{
    m_limped_to_big_blind = (m_aggressor == nullptr && m_action_player == &m_players[m_big_blind_position]);
}

void SimpleGame::allocate_winnings()
{
    std::vector<Player*> temp = pointer_copy(m_players);
    PotArray SidePots(temp);
    SidePots.find_and_pay_winners();
}

void SimpleGame::end_round()
{
    m_limped_to_big_blind = false;
    m_folded_players = {};
    for (Player player: m_players)
    {
        player.m_folded = false;
    }
    m_deck.reset_deck();
}


