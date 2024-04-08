#pragma once
#include "player.h"
#include <sstream>
#include <iomanip>
#include <cmath>


std::string chips_to_string(float bet, int precision);

class Table
{
    public:
    const std::string m_left_margin = std::string(30, ' ');
    const int m_precision = 2;
    std::string m_bottom_edge;
    Player* m_top_player;
    const int m_table_width;
    std::string m_vertical_edges_segment;
    Player* m_bottom_player;
    std::vector<std::pair<Player*, Player*>> m_side_players;
    Table(std::vector<Player*> players, int table_width);
    Table() = default;
    void set_side_players(const std::vector<Player*>& players);
    void draw_left_player(Player *left_player);
    void draw_right_player(Player *right_player);
    void draw_bets_and_sides(Player *left_player, Player *right_player);
    void draw_top();
    void draw_bottom();
    void draw_midddle_section(Player *left_player, Player *right_player);
    void draw_player_line(Player *left_player, Player *right_player);
    void draw_bet_line(Player *player);
    void set_bottom_player(const std::vector<Player *> &players);
    void draw();
    void draw_middle();
    std::string left_seat_format(Player *left_player);
    std::string vertical_edges(const int height);
    std::string right_seat_format(Player *right_player);
    std::string bottom_player_format(Player *player);
};