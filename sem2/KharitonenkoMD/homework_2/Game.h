#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Game {
 public:
  Game();
  void Run();

 private:
  void ProcessEvents();
  void Update(sf::Time delta_time);
  void Render();
  void SpawnTarget();

  struct Target {
    sf::CircleShape shape;
    sf::Vector2f velocity;
  };

  sf::RenderWindow window_;
  sf::Font font_;
  sf::Text score_text_;
  int score_;
  sf::Time game_time_;
  bool is_game_over_;
  std::vector<Target> targets_;
};

#endif  // GAME_H_
