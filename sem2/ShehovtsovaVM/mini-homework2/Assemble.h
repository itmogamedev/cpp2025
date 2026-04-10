#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
void Start();
void Play(sf::Text& timer_text, sf::Text& score_text, sf::Text& task_text,
          sf::RenderWindow& window, sf::Clock& clock, float& timer_time,
          float& timer_minus);