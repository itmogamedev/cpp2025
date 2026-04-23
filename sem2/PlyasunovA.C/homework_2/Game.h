#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float dt);
  void render();
  void initializeCircles();
  void spawnRandomPosition(int index);
  void spawnRandomVelocity(int index);
  void updateTexts();
  int checkCircleClick(int mouse_x, int mouse_y) const;

  sf::RenderWindow window;
  std::vector<sf::CircleShape> circles;
  std::vector<sf::Vector2f> velocities;
  int score;
  float time_left;
  bool game_over;

  sf::Font font;
  sf::Text score_text;
  sf::Text time_text;
  sf::Text game_over_text;

  sf::Clock delta_clock;

  const float radius;
  const float penalty_amount;
  const int window_width;
  const int window_height;

  std::mt19937 rng;
  std::uniform_real_distribution<float> pos_dist_x;
  std::uniform_real_distribution<float> pos_dist_y;
  std::uniform_real_distribution<float> vel_dist;
};

#endif
