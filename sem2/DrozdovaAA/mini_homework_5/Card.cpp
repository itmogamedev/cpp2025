#include "Card.h"
#include <string>

Card::Card(float x, float y, float width, float height, char sym) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    symbol = sym;
    is_face_up = false;
    is_matched = false;
}

void Card::draw(sf::RenderWindow& window, const sf::Font& font) const {
    if (is_matched) {
        return;
    }

    sf::RectangleShape draw_shape = shape;
    if (is_face_up) {
        draw_shape.setFillColor(sf::Color::White); //меняем фон открытой 
        window.draw(draw_shape);

        sf::Text text;
        text.setFont(font);
        text.setString(std::string(1, symbol));
        text.setCharacterSize(55);
        text.setFillColor(sf::Color::Black);

        sf::FloatRect text_rect = text.getLocalBounds();
        text.setOrigin(text_rect.left + text_rect.width / 2.0f,
            text_rect.top + text_rect.height / 2.0f);
        text.setPosition(shape.getPosition().x + shape.getSize().x / 2.0f,
            shape.getPosition().y + shape.getSize().y / 2.0f); //перемещение текста в центр
        window.draw(text);
    }
    else {
        draw_shape.setFillColor(sf::Color(109, 135, 100));
        window.draw(draw_shape);
    }
}