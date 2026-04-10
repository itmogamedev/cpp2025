
#include "Score.h"

Score::Score()

    : m_value(0) {}

void Score::increment() { ++m_value; }

void Score::reset() { m_value = 0; }

int Score::getValue() const { return m_value; }
