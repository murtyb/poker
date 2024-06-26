#include "..\..\include\holdem\preflopgame.h"

PreFlopGame::PreFlopGame(PokerPlayerGroup& players, Deck &deck, Chips small_blind, Chips big_blind)
    : HoldEmPreFlopLogic(players, deck, small_blind, big_blind),
      HoldEmUI(players, deck),
      BaseGame(players, deck)
{
}

void PreFlopGame::run()
{
    while (true)
    {
        pre_flop_setup();
        play_pre_flop();
        end_round();
        if (one_player_left())
        {
            print_winner_message();
            break;
        }
    }
}

void PreFlopGame::play_pre_flop()
{
    while (in_betting_phase())
    {
        calculate_valid_options();
        m_players.draw_table();
        request_input_message();
        std::pair<std::string, Chips> input = get_user_input();
        execute_action(input);
        m_players.next_player();
    }
    allocate_winnings();
    m_players.eliminate_bankrupt_players();
}