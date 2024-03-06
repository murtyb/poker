#pragma once

#include <vector>
#include <algorithm>
#include "player.h"
#include "deck.h"
#include "misc.h"


class Game
{
    public:
        std::vector<Player> m_players;
        std::vector<Player> m_folded_players;
        std::vector<Player> m_all_in_players;
        int m_button_location;
        int m_action_player_location;
        Player* m_action_player;
        Player* m_aggressor;
        double m_small_blind;
        double m_big_blind;
        double m_utg_position;
        double m_last_raise;
        double m_highest_bet;
        double m_desired_raise;
        std::string m_action;
        std::vector<std::string>  m_valid_inputs;

        static std::map<std::string, std::string> s_input_map;

        Game(std::vector<Player>& players, Deck deck, double small_blind, double big_blind);
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
        bool all_but_one_players_folded_or_all_in();
        bool all_players_folded_or_all_in(); 
        std::vector<Player> get_remaining_players();
        void assign_winnings(std::vector<Player> remaining_players);
        std::vector<Player> extract_winning_players(std::vector<Player> &remaining_players);
        std::vector<Player>find_other_winners(std::vector<Player> &remaining_players, std::vector<Player> &winning_players);                                    
        void execute_inputted_action();
        void next_player(); 
        void transfer_chips(std::vector<Player> winning_players, const std::vector<Player>& losing_players);

    private:
        int m_number_of_players;
        int m_big_blind_position;
};