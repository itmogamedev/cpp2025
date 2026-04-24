#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Target {
 public:
  Target(float radius, const std::vector<sf::Texture>& textures);

  void randomize(unsigned int field_w, unsigned int field_h);

  void update(float dt, unsigned int field_w, unsigned int field_h);
  void draw(sf::RenderWindow& window) const;

  bool isClicked(sf::Vector2f mouse_pos) const;

 private:
  float radius_;
  sf::Vector2f position_;
  sf::Vector2f velocity_;
  sf::Sprite sprite_;
  sf::CircleShape fallback_;
  const std::vector<sf::Texture>* textures_;

  void applyTexture(std::size_t idx);
  void bounceWalls(unsigned int field_w, unsigned int field_h);
};
