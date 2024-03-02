#pragma once

#include <vector>
#include "cards.h"
#include "hands.h"
#include "player.h"


class Deck
{
    public:
    Deck(const std::vector<Card>& cards);
    Deck(const std::vector<std::string>& card_symbols);
    Card& deal_card();
    Hand deal_hand();
    void reset_deck();

private:
    const std::vector<Card> m_default_deck;
    std::vector<Card> m_current_deck;
    void check_if_deck_empty() const;

    static std::vector<Card> symbols_to_cards(const std::vector<std::string> &card_symbols);
};