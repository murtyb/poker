#pragma once

#include "..\game_logic\basegame.h"


class HoldEmUI: virtual public BaseGame 
{
public:
    HoldEmUI(PokerPlayerGroup& players, Deck& deck);
    void request_input_message(); 
    void print_options(std::vector<std::string> valid_inputs);
    void execute_action(std::pair<std::string, Chips> input);
    bool is_valid_action(std::string action);
    std::vector<std::string> valid_inputs();
    std::pair<std::string, Chips> get_user_input();

private:
    static std::map<std::string, std::string> s_input_map;
};