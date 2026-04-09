#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& win) : window(win) {}

void Renderer::clear(const sf::Color& color) { window.clear(color); }

void Renderer::draw(const sf::Drawable& drawable) { window.draw(drawable); }

void Renderer::display() { window.display(); }