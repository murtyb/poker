#pragma once

#include <vector>
#include "player.h"
#include "deck.h"


class Game
{
    public:
        std::vector<Player> m_players;
        std::vector<Player> m_folded_players;
        int m_button_location;
        Player* m_action_player;

        Game(std::vector<Player>& players, Deck deck);
        Deck m_deck;
        void set_positions();
        void move_button();
        void raise(const float &ammount);
        void call();
        void fold();
        void end_round();
        void deal_hands();

    private:
        int m_number_of_players;
        Player* m_aggressor;
        double m_highest_bet;
};