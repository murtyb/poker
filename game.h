#pragma once

#include <vector>
#include <algorithm>
#include "pokerplayer.h"
#include "deck.h"
#include "misc.h"
#include "table.h"


class Game
{
    public:
        std::vector<PokerPlayer*> m_players;
        Table m_table;
        PokerPlayer* m_action_player = nullptr;
        PokerPlayer* m_aggressor = nullptr;
        int m_number_of_players;
        int m_num_of_folded_players = 0;
        int m_num_of_all_in_players = 0;
        double m_small_blind;
        double m_big_blind;
        double m_utg_position;
        double m_last_raise;
        double m_highest_bet;
        double m_desired_raise;
        std::string m_action = "";
        std::vector<std::string> m_valid_inputs;
        int m_big_blind_position;
        
        static std::map<std::string, std::string> s_input_map;

        Game(std::vector<PokerPlayer>& players, Deck deck, double small_blind, double big_blind);
        Deck m_deck;
        void set_positions();
        void move_button();
        void raise(const double &ammount);
        void call();
        void fold();
        void end_round();
        void deal_hands();
        void post_blinds();
        void pre_flop_setup();
        bool is_valid_raise(const double& ammount_raised_to);
        void all_in();
        bool all_in_to_raise();
        bool is_valid_action();
        bool all_in_to_call();
        bool all_but_one_players_folded();
        void calculate_valid_options();
        void draw_table();
        bool all_but_one_players_folded_or_all_in();
        bool all_players_folded_or_all_in();                             
        void execute_inputted_action();
        void next_player(); 

    private:

};