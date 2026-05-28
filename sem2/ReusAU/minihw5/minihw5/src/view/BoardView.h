#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../model/BoardModel.h"

class BoardView {
public:
    BoardView();

    bool loadResources();

    void draw(sf::RenderWindow& window, const BoardModel& model);
    void drawEndScreen(sf::RenderWindow& window, const BoardModel& model);

    // Индекс карты под точкой клика, или -1 если клик мимо
    int getCardIndexAtPosition(sf::Vector2f pos) const;

private:
    sf::Font font;
    std::vector<sf::Texture> symbolTextures;

    sf::Vector2f cardTopLeft(int row, int col) const;
    void drawCard(sf::RenderWindow& window, const CardModel& card);
};
