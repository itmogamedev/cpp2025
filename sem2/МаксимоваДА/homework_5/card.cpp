#include "card.h"

Card::Card() : card_symbol(0), is_open(false), is_matched(false) {}

int Card::getSymbol() const { return card_symbol; }

bool Card::isOpened() const { return is_open; }

bool Card::isMatched() const { return is_matched; }

void Card::setSymbol(int s) { card_symbol = s; }

void Card::setOpened(bool op) { is_open = op; }

void Card::setMatched(bool m) { is_matched = m; }