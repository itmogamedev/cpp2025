#include "Cards.h"
Card::Card() : symbol_card(0), opened_card(false), matched_cards(false) {}
int Card::getSymbol() const { return symbol_card; }
bool Card::isOpened() const { return opened_card; }
bool Card::isMatched() const { return matched_cards; }

void Card::setSymbol(int s) { symbol_card = s; }
void Card::setOpened(bool op) { opened_card = op; }
void Card::setMatched(bool m) { matched_cards = m; }
