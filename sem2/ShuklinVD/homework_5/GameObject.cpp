#include "GameObject.h"

GameObject::GameObject()
    : m_x(0.f), m_y(0.f), m_width(0.f), m_height(0.f), m_alive(true)
{
}

GameObject::GameObject(float x, float y, float width, float height)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_alive(true)
{
}

void GameObject::setPosition(float x, float y)
{
    m_x = x;
    m_y = y;
}

void GameObject::move(float dx, float dy)
{
    m_x += dx;
    m_y += dy;
}

float GameObject::getX() const { return m_x; }
float GameObject::getY() const { return m_y; }
float GameObject::getWidth() const { return m_width; }
float GameObject::getHeight() const { return m_height; }

sf::FloatRect GameObject::getBounds() const
{
    return sf::FloatRect(m_x, m_y, m_width, m_height);
}

bool GameObject::collidesWith(const GameObject& other) const
{
    return getBounds().intersects(other.getBounds());
}

void GameObject::setSprite(const sf::Texture& texture)
{
    m_sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0)
    {
        float scaleX = m_width / static_cast<float>(texSize.x);
        float scaleY = m_height / static_cast<float>(texSize.y);
        m_sprite.setScale(scaleX, scaleY);
    }
}

sf::Sprite& GameObject::getSprite()
{
    m_sprite.setPosition(m_x, m_y);
    return m_sprite;
}

bool GameObject::isAlive() const { return m_alive; }
void GameObject::kill() { m_alive = false; }
void GameObject::revive() { m_alive = true; }
