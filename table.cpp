#include "table.h"

std::string chips_to_string(float bet, int precision)
{
    std::string no_dec_point;
    bet = std::round(bet * std::pow(10, precision)) / std::pow(10, precision);
    //std::cout << "bet:" << bet <<std::endl;
    if (int(bet) == bet) {return std::to_string(int(bet));}
    for (int i = 1; i <= precision; i++)
    {
        float x = std::pow(10, i) * bet;
        //std::cout << "x:" << x <<std::endl;
        if (int(x) == x)
        {
            no_dec_point = std::to_string(int(x));
            break;
        }
    }
    if (bet < 1) {return "0." + no_dec_point;}

    int ordr_of_mag = std::to_string(int(bet)).size();
    return no_dec_point.insert(ordr_of_mag, 1, '.');
}

Table::Table(std::vector<Player*> players, int table_width)
    :m_top_player(players[0]),
     m_table_width(table_width),
     m_vertical_edges_segment(vertical_edges(3))
{
    set_bottom_player(players);
    set_side_players(players);
}

void Table::set_bottom_player(const std::vector<Player*>& players)
{
    if (players.size() % 2 == 0) {m_bottom_player = players[players.size()/2 - 1];}
    else {m_bottom_player = nullptr;}
}

void Table::set_side_players(const std::vector<Player*>& players)
{
    int n = players.size();
    for (int i = 1; i < n / 2.0 ; i++)
    {
        m_side_players.push_back(std::pair(players[n - i], players[i]));
    }
}

std::string Table::left_seat_format(Player* left_player)
{
    std::string stack_string = chips_to_string(left_player->m_stack, m_precision);
    std::string left_player_info = stack_string + "bb P" + std::to_string(left_player->m_id);
    left_player_info += " " + left_player->m_hand.get_symbols() + " ";
    return left_player_info;
}

std::string Table::right_seat_format(Player* right_player)
{
    std::string stack_string = chips_to_string(right_player->m_stack, m_precision);
    std::string right_player_info = right_player->m_hand.get_symbols();
    right_player_info +=  " P" + std::to_string(right_player->m_id) + " " + stack_string + "bb";
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

void Table::draw_midddle_section(Player* left_player, Player* right_player)
{
    std::cout << m_vertical_edges_segment;
    draw_player_line(left_player, right_player);
    std::cout << m_vertical_edges_segment;
}

void Table::draw_player_line(Player* left_player, Player* right_player)
{
    draw_left_player(left_player);
    draw_bets_and_sides(left_player, right_player);
    draw_right_player(right_player);
}

void Table::draw_left_player(Player* left_player)
{
    std::string left_player_stats = left_seat_format(left_player);
    std::string margin = std::string(m_left_margin.size() - left_player_stats.size(), ' ');
    std::cout << margin << left_player_stats;
}

void Table::draw_right_player(Player* right_player)
{
    std::string right_player_stats = right_seat_format(right_player);
    std::cout << " " << right_player_stats << std::endl;
}

void Table::draw_bets_and_sides(Player* left_player, Player* right_player)
{
    std::string right_bet = chips_to_string(right_player->m_ammount_bet, m_precision) + "bb";
    std::string left_bet = chips_to_string(left_player->m_ammount_bet, m_precision) + "bb";
    std::string middle_spacing = std::string(m_table_width - left_bet.size() - right_bet.size() - 4, ' ');
    std::cout << "|  " << left_bet << middle_spacing << right_bet << "  |";
}

void Table::draw_top()
{
    std::string spacing = std::string(m_table_width / 2, ' ') + m_left_margin;
    std::string top_edge_of_table = std::string(m_table_width, '_');
    std::cout << spacing << chips_to_string(m_top_player->m_stack, m_precision) << "bb" << '\n'; 
    std::cout << spacing << 'P' << m_top_player->m_id << '\n'; 
    std::cout << spacing << m_top_player->m_hand  << '\n'; 
    std::cout << m_left_margin + " " << top_edge_of_table << '\n';
    std::cout << vertical_edges(1);
    draw_bet_line(m_top_player);
}

void Table::draw_bet_line(Player* player)
{
    std::string bet_string;
    if (player == nullptr) {bet_string = "";}
    else {bet_string = chips_to_string(player->m_ammount_bet, m_precision) + "bb";}
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
    draw_bet_line(m_bottom_player);
    std::cout << m_left_margin;
    std::cout  << bottom_edge_of_table << '\n';
    std::cout << bottom_player_format(m_bottom_player);   
}

std::string Table::bottom_player_format(Player* player)
{
    if (m_bottom_player == nullptr) {return "\n";}
    std::string spacing = std::string(m_table_width / 2, ' ') + m_left_margin;
    std::string bottom_player_details = '\n' + spacing + player->m_hand.get_symbols()  + '\n';
    bottom_player_details += spacing + "P" + std::to_string(player->m_id) + '\n';
    bottom_player_details += spacing + chips_to_string(player->m_stack, m_precision) + "bb" + '\n';
    return bottom_player_details;
}

void Table::draw()
{
    draw_top();
    draw_middle();
    draw_bottom();
}

