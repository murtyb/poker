#pragma once

#include <vector>
#include "player.h"


class Game
{
    public:
        std::vector<Player> m_players;
        std::vector<Player> m_current_players;
        int m_button_location;
        Player& m_action_player;

        Game(std::vector<Player>& players);
        void set_positions();
        void move_button();
        void raise(const float &ammount);
 
    private:
        int m_number_of_players;
        Player& m_aggressor;
};