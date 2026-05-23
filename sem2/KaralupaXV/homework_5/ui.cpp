#include "game.h"

UI::UI(const sf::Font& font) : font(font), scoreText(font, "", 22), livesText(font, "", 22) {
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 8.f});

    livesText.setFillColor(sf::Color::White);
    livesText.setPosition({(float)WINDOW_W - 140.f, 8.f});
}

void UI::draw(sf::RenderWindow& win, int score, int lives) {
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
    win.draw(scoreText);
    win.draw(livesText);
}

void UI::drawGameOver(sf::RenderWindow& win, int score) {
    sf::RectangleShape overlay({(float)WINDOW_W, (float)WINDOW_H});
    overlay.setFillColor(sf::Color(0, 0, 0, 160));
    win.draw(overlay);

    auto centeredText = [&](const std::string& str, unsigned size, sf::Color col, float y) {
        sf::Text t(font, str, size);
        t.setFillColor(col);
        auto bounds = t.getLocalBounds();
        t.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
        t.setPosition({WINDOW_W / 2.f, y});
        win.draw(t);
    };

    centeredText("GAME OVER", 48, sf::Color::Red, 200.f);
    centeredText("Score: " + std::to_string(score), 32, sf::Color::Red,  270.f);
    centeredText("Press R to Restart",  24, sf::Color::White, 340.f);
}