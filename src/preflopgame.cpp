#include "preflopgame.h"

PreFlopGame::PreFlopGame(std::vector<PokerPlayer> &players, Deck &deck, double small_blind, double big_blind)
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
    }
}

void PreFlopGame::play_pre_flop()
{
    while (in_betting_phase())
    {
        calculate_valid_options();
        m_players.draw_table();
        request_input_message();
        std::pair<std::string, double> input = get_user_input();
        execute_action(input);
        m_players.next_player();
    }
    allocate_winnings();
}