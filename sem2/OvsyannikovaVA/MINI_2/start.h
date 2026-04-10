#pragma once
#include <SFML/Graphics.hpp>

void startGame();
bool Play(sf::Text& timer_text, sf::Text& score_text, sf::Text& task_text,
          sf::RenderWindow& window, sf::Clock& clock, float& timer_time,
          float& timer_minus);
