#include "score.h"

#include <string>

#include "constants.h"

int Score::increase(int score) { return score + Constants::BASE_BUST; }

void Score::updateText(sf::Text& scoreText, int score) {
  scoreText.setString("Score: " + std::to_string(score));
}
