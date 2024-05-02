#include "..\..\include\chips\chips.h"
#include "chips.h"

Chips::Chips(): m_num_of_chips(0), m_num_of_bb(0) {}

Chips::Chips(float amnt, char currency = 'c')
    : m_num_of_chips(num_of_chips(amnt, currency)),
      m_num_of_bb(num_of_bb(amnt, currency))
{
}

float Chips::num_of_bb(float amnt, char currency)
{
    return float(num_of_chips(amnt, currency)) / s_bb;
}

int Chips::num_of_chips(float amnt, char currency)
{
    if (currency == s_currency_map["big_blinds"])
    {
        return int(amnt * s_bb);
    }
    if (currency == s_currency_map["chips"])
    {
        return int(amnt);
    }
    else
    {
        throw std::runtime_error("invalid currency symbol: " + currency);
    }
    return - 1;
}

Chips Chips::remainder(int x)
{
    return m_num_of_chips % x;
}

void Chips::update_bb()
{
    m_num_of_bb = float(m_num_of_chips)/s_bb;
}

void Chips::operator+=(const Chips& chips)
{
    m_num_of_chips += chips.m_num_of_chips;
    update_bb();
}

void Chips::operator-=(const Chips& chips)
{
    m_num_of_chips -= chips.m_num_of_chips;
    update_bb();
}

bool Chips::operator<=(const Chips& chips) const
{
    return m_num_of_chips <= chips.m_num_of_chips;
}

bool Chips::operator==(const Chips& chips) const
{
    return m_num_of_chips == chips.m_num_of_chips;
}

Chips Chips::operator/(int x) const
{
    return Chips(m_num_of_chips / x);
}

Chips Chips::operator-(Chips chips) const
{
    return Chips(m_num_of_chips - chips.m_num_of_chips);
}

Chips Chips::operator+(Chips chips) const
{
    return Chips(m_num_of_chips + chips.m_num_of_chips);
}

std::string Chips::bb_string()
{
    std::string no_dec_point;
    float bb_rnded = std::round(m_num_of_bb * std::pow(10, m_bb_precision)) / std::pow(10, m_bb_precision);
    if (int(bb_rnded) == bb_rnded) {return std::to_string(int(bb_rnded)) + "bb";}
    for (int i = 1; i <= m_bb_precision; i++)
    {
        float x = std::pow(10, i) * bb_rnded;
        if (int(x) == x)
        {
            no_dec_point = std::to_string(int(x));
            break;
        }
    }
    if (bb_rnded < 1) {return "0." + no_dec_point + "bb";}
    int ordr_of_mag = std::to_string(int(bb_rnded)).size();
    return no_dec_point.insert(ordr_of_mag, 1, '.') + "bb";
}


int Chips::s_bb = 2;
int Chips::s_sb = 1;
std::map<std::string, char> Chips::s_currency_map ={{"chips", 'c'}, {"big_blinds", 'b'}};