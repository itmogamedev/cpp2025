
#ifndef MINIHW_GAME_H
#define MINIHW_GAME_H
#include <cstdint>
#include <memory>
#include <random>
#include <vector>

#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Clock.hpp"
#include "circle.h"

struct Circle;

class Game {
public:
  std::vector<Circle> circles{};
  int score;
  int64_t begin_time;
  int64_t end_time;
  std::random_device rand;
  sf::Font font;
  bool font_loaded;

  float dt;

  void update(sf::RenderTarget &tgt);

  bool isGameOver() const {
    int64_t time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    return time >= end_time;
  }

  void run();

  Game() {
    int64_t time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    begin_time = time;
    score = 0;
    dt = 0;
    end_time = time + 30 * 1000L; // 30 secs
    font_loaded = font.openFromFile(R"(C:\Windows\Fonts\arial.ttf)");
  }

private:
  sf::Clock clock;
};

#endif // MINIHW_GAME_H
