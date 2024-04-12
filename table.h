#pragma once
#include "pokerplayer.h"
#include <sstream>
#include <iomanip>
#include <cmath>


std::string chips_to_string(float bet, int precision);

class Table
{
public:
    Table(std::vector<PokerPlayer*> players, int table_width);
    Table() = default;
    void draw();
    void update_players(std::vector<PokerPlayer*> players);


private:
    const std::string m_left_margin = std::string(30, ' ');
    const int m_precision = 2;
    const int m_table_width;
    PokerPlayer* m_top_player;
    PokerPlayer* m_bottom_player;
    std::vector<std::pair<PokerPlayer*, PokerPlayer*>> m_side_players;
    std::string m_bottom_edge;
    std::string m_vertical_edges_segment;
    
    std::string button_space(PokerPlayer* player);
    std::string left_seat_format(PokerPlayer* left_player);
    std::string vertical_edges(const int height);
    std::string right_seat_format(PokerPlayer* right_player);
    std::string bottom_player_format(PokerPlayer* player);
    void set_side_players(const std::vector<PokerPlayer*>& players);
    void set_bottom_player(const std::vector<PokerPlayer*>& players);
    void draw_button_line(PokerPlayer* player);
    void draw_player_line(PokerPlayer* left_player, PokerPlayer* right_player);
    void draw_end_bet_line(PokerPlayer* player);
    void draw_middle_bets_and_sides(PokerPlayer* left_player,PokerPlayer* right_player);
    void draw_left_player(PokerPlayer* left_player);
    void draw_right_player(PokerPlayer* right_player);
    void draw_midddle_section(PokerPlayer* left_player, PokerPlayer* right_player);
    void draw_top();
    void draw_middle();
    void draw_bottom();
};