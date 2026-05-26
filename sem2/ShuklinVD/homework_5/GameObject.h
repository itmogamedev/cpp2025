#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    GameObject();
    GameObject(float x, float y, float width, float height);

    void setPosition(float x, float y);
    void move(float dx, float dy);

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    sf::FloatRect getBounds() const;
    bool collidesWith(const GameObject& other) const;

    void setSprite(const sf::Texture& texture);
    sf::Sprite& getSprite();

    bool isAlive() const;
    void kill();
    void revive();

protected:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    bool m_alive;
    sf::Sprite m_sprite;
};
