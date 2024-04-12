#include "holdemui.h"

HoldEmUI::HoldEmUI(std::vector<PokerPlayer> &players, Deck& deck)
    : BaseGame(players, deck)
{
}

std::pair<std::string, double> HoldEmUI::get_user_input()
{
    std::pair<std::string, int> input;
    std::string& action = input.first;
    int& desired_raise = input.second;
    desired_raise = - 1;
    clear_cin();
    if (!(std::cin >> action))
    {
        std::cout << "invalid input\n";
        input = get_user_input();
        return input;
    }

    if (!is_valid_action(action))
    {
        std::cout << "invalid input\n";
        input = get_user_input();
        return input;
    }

    if (action != "r")
    {
        return input;
    }

    if (!(std::cin >> desired_raise))
    {
        std::cout << "invalid raise\n";
        input = get_user_input();
        return input;
    }
    
    if (!is_valid_raise(desired_raise))
    {
        std::cout << "invalid raise\n";
        input = get_user_input();
        return input;
    }
    return input;
}

void HoldEmUI::request_input_message()
{
    std::cout << "Player " << m_action_player->m_id << ": ";
    std::cout << "Your options are:\n";
    print_options(valid_inputs());
}

void HoldEmUI::print_options(std::vector<std::string> valid_inputs)
{
    int option_number = 1;
    for (auto [action, input]: s_input_map)
    {
        if (is_element_of(input, valid_inputs))
        {
            std::cout << option_number << ". " << action << '('<< input << ')' << std::endl;
            option_number++;
        }
    }
}

std::vector<std::string> HoldEmUI::valid_inputs()
{
    std::vector<std::string> inputs;
    if (m_action_player->m_can_fold) {inputs.push_back(s_input_map["fold"]);}
    if (m_action_player->m_can_check) {inputs.push_back(s_input_map["check"]);}
    if (m_action_player->m_can_call) {inputs.push_back(s_input_map["call"]);}
    if (m_action_player->m_can_raise) {inputs.push_back(s_input_map["raise"]);}
    if (m_action_player->m_can_go_all_in) {inputs.push_back(s_input_map["all in"]);}
    return inputs;
}

bool HoldEmUI::is_valid_action(std::string action)
{
    return is_element_of(action, valid_inputs());
}

void HoldEmUI::execute_action(std::pair<std::string, int> input)
{
    std::string action = input.first;
    int ammount_raised = input.second;
    if (action == s_input_map["check"])
    {
        return;
    }
    if (action == s_input_map["call"])
    {
        call();
        return;
    }
    if (action == s_input_map["fold"])
    {
        fold();
        return;
    }
    if (action == s_input_map["raise"])
    {
        raise(ammount_raised);
        return;
    }
    if (action == s_input_map["all in"])
    {
        all_in();
        return;
    }
}

std::map<std::string, std::string> HoldEmUI::s_input_map = {{"fold", "f"}, {"check", "ch"}, {"call", "c"}, {"raise", "r"}, {"all in", "a"}};