#include "..\..\include\players\table.h"


Table::Table(std::vector<PokerPlayer*> players, int table_width)
    : m_table_width(table_width),
      m_vertical_edges_segment(vertical_edges(3))
{
    update_players(players);
}

void Table::set_bottom_player(const std::vector<PokerPlayer*>& players)
{
    if (players.size() % 2 == 0) {m_bottom_player = players[players.size()/2];}
    else {m_bottom_player = nullptr;}
}

void Table::set_side_players(const std::vector<PokerPlayer*>& players)
{
    m_side_players = {};
    int n = players.size();
    for (int i = 1; i < n / 2.0 ; i++)
    {
        m_side_players.push_back(std::pair(players[n - i], players[i]));
    }
}

std::string Table::left_seat_format(PokerPlayer* left_player)
{
    std::string left_player_info = left_player->m_stack.bb_string() + " P" + std::to_string(left_player->m_id);
    left_player_info += " " + left_player->m_hand.get_symbols() + " ";
    return left_player_info;
}

std::string Table::right_seat_format(PokerPlayer* right_player)
{
    std::string right_player_info = right_player->m_hand.get_symbols();
    right_player_info +=  " P" + std::to_string(right_player->m_id) + " " +right_player->m_stack.bb_string();
    return right_player_info;
}

std::string Table::vertical_edges(const int height)
{
    std::string output = "";
    std::string vertical_edge_element = m_left_margin + "|" + std::string(m_table_width, ' ') + "|\n";
    for (int i = 0; i < height; i++)
    {
        output += vertical_edge_element;
    }
    return output;
}

void Table::draw_midddle_section(PokerPlayer* left_player, PokerPlayer* right_player)
{
    std::cout << m_vertical_edges_segment;
    draw_player_line(left_player, right_player);
    std::cout << m_vertical_edges_segment;
}

void Table::draw_player_line(PokerPlayer* left_player, PokerPlayer* right_player)
{
    draw_left_player(left_player);
    draw_middle_bets_and_sides(left_player, right_player);
    draw_right_player(right_player);
}

void Table::draw_left_player(PokerPlayer* left_player)
{
    std::string left_player_stats = left_seat_format(left_player);
    std::string margin = std::string(m_left_margin.size() - left_player_stats.size(), ' ');
    std::cout << margin << left_player_stats;
}

void Table::draw_right_player(PokerPlayer* right_player)
{
    std::string right_player_stats = right_seat_format(right_player);
    std::cout << " " << right_player_stats << std::endl;
}

void Table::draw_middle_bets_and_sides(PokerPlayer* left_player, PokerPlayer* right_player)
{
    std::string right_bet = right_player->m_amount_bet.bb_string();
    std::string left_bet = left_player->m_amount_bet.bb_string();
    std::string middle_spacing = std::string(m_table_width - left_bet.size() - right_bet.size() - 8, ' ');
    std::cout << "|  " << left_bet << " " + button_space(left_player) << middle_spacing << button_space(right_player) + " " << right_bet << "  |";
}

void Table::draw_top()
{
    std::string spacing = std::string(m_table_width / 2, ' ') + m_left_margin;
    std::string top_edge_of_table = std::string(m_table_width, '_');
    std::cout << spacing << m_top_player->m_stack.bb_string() << '\n'; 
    std::cout << spacing << 'P' << m_top_player->m_id << '\n'; 
    std::cout << spacing << m_top_player->m_hand  << '\n'; 
    std::cout << m_left_margin + " " << top_edge_of_table << '\n';
    std::cout << vertical_edges(1);
    draw_end_bet_line(m_top_player);
    draw_button_line(m_top_player);
}

void Table::draw_end_bet_line(PokerPlayer* player)
{
    std::string bet_string;
    if (player == nullptr) {bet_string = "";}
    else {bet_string = player->m_amount_bet.bb_string();}
    std::string left_spacing = std::string(m_table_width / 2 - 1, ' ');
    int right_spacing_size = m_table_width/2 - bet_string.size() + 1;
    std::string right_spacing = std::string(right_spacing_size, ' ');
    std::cout << m_left_margin << "|" << left_spacing << bet_string << right_spacing << "|" << std::endl;
}

void Table::draw_middle()
{
    for(const auto& [left_player, right_player] : m_side_players)
    {
        draw_midddle_section(left_player, right_player);
    }
}

void Table::draw_bottom()
{
    
    std::string spacing = std::string(m_table_width / 2, ' ') + m_left_margin;
    std::string bottom_edge_of_table = '|' + std::string(m_table_width, '_') + '|';
    draw_button_line(m_bottom_player);
    draw_end_bet_line(m_bottom_player);
    std::cout << m_left_margin;
    std::cout  << bottom_edge_of_table << '\n';
    std::cout << bottom_player_format(m_bottom_player);   
}

std::string Table::bottom_player_format(PokerPlayer* player)
{
    if (m_bottom_player == nullptr) {return "\n";}
    std::string spacing = std::string(m_table_width / 2, ' ') + m_left_margin;
    std::string bottom_player_details = '\n' + spacing + player->m_hand.get_symbols()  + '\n';
    bottom_player_details += spacing + "P" + std::to_string(player->m_id) + '\n';
    bottom_player_details += spacing + player->m_stack.bb_string() + '\n';
    return bottom_player_details;
}

void Table::draw_button_line(PokerPlayer* player)
{
    if (player == nullptr) {return;}
    std::string button_line;
    std::string spacing = std::string(m_table_width / 2 - 1, ' ');
    std::cout << m_left_margin << "|" << spacing << button_space(player) + " " << spacing << "|" << std::endl;
}

std::string Table::button_space(PokerPlayer* player)
{
    if (player->m_on_button){return "*";}
    else {return " ";}
}

void Table::draw()
{
    draw_top();
    draw_middle();
    draw_bottom();
}

void Table::update_players(std::vector<PokerPlayer*> players)
{
    m_top_player = players[0];
    set_bottom_player(players);
    set_side_players(players);
}
