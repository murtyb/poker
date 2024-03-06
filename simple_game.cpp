#include "simple_game.h"

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
    std::cout << "You are in position" << m_action_player->m_position << ", ";
    std::cout << "your stack size is: " << m_action_player->m_stack << ", ";
    std::cout << "and so far you have bet" << m_action_player->m_ammount_bet << ".\n ";
    std::cout << "You have " << m_action_player->hand << "and the current price is " << m_highest_bet << "\n";
    std::cout << "Your options are:\n";
    print_options();
}

void SimpleGame::print_options()
{
    int option_number = 1;
    if (m_action_player ->m_can_fold) 
    {
        std::cout << option_number << '. ' << "fold" << '('<< s_input_map["fold"] << ')';
        option_number++;
    }

    if (m_action_player ->m_can_check) 
    {
        std::cout << option_number << '. ' << "check" << '(' << s_input_map["check"] << ')' << std::endl;
        option_number++;
    }

    if (m_action_player ->m_can_call) 
    {
        std::cout << option_number << '. ' << "call" << '(' << s_input_map["call"] << ')' << std::endl;
        option_number++;
    }
    if (m_action_player ->m_can_raise) 
    {
        std::cout << option_number << '. ' << "raise" << '(' << s_input_map["raise"] << ')' << std::endl;
        option_number++;
    }

    if (m_action_player ->m_can_go_all_in) 
    {
        std::cout << option_number << '. ' << "all in" << '(' << s_input_map["all in"] << ')' << std::endl;
        option_number++;
    }
}

void SimpleGame::run()
{
    while (true)
    {
        pre_flop_setup();
        play_pre_flop();
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
    std::vector<Player> remaining_players = get_remaining_players();
    assign_winnings(remaining_players);
}

bool SimpleGame::in_betting_phase()
{
    if (all_but_one_players_folded()){return false;}
    if (&m_action_player == &m_aggressor){return false;}
    if (all_players_folded_or_all_in()){return false;}

    return true;
}


