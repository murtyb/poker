#include "..\..\include\cards\deck.h"
#include "deck.h"


Deck::Deck(const std::vector<Card>& cards)
    : m_default_deck(cards), m_current_deck(cards)
{   
}

Deck::Deck(const std::vector<std::string>& card_symbols)
    : Deck(symbols_to_cards(card_symbols))
{
}

std::vector<Card> Deck::symbols_to_cards(const std::vector<std::string>& card_symbols)
{
    std::vector<Card> cards;
    for(const std::string symbol : card_symbols)
    {
        cards.push_back(Card(symbol));
    }
    return cards;
}

void Deck::reset_deck()
{
    m_current_deck = m_default_deck;
}

Card& Deck::deal_card()
{
    check_if_deck_empty();
    Card& card = m_current_deck.back();
    m_current_deck.pop_back();
    return card;
}

Hand Deck::deal_hand(int size)
{
    std::vector<Card> cards;
    for (int i = 0; i < size; i++)
    {
        cards.push_back(deal_card());
    }
    return Hand(cards);
}

void Deck::check_if_deck_empty() const
{
   if (m_current_deck.empty())
   {
        throw std::runtime_error("Tried to deal card when deck was empty.");
   }
}

void Deck::shuffle_deck()
{
    std::shuffle(m_current_deck.begin(), m_current_deck.end(), eng);
}

std::random_device Deck::rd;
std::mt19937 Deck::eng(rd());