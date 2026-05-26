#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class UI {
 public:
  UI();
  bool init();
  void update(int score, float remainingTime);
  void draw(sf::RenderWindow& window);
  void showGameOver(sf::RenderWindow& window, int finalScore);

 private:
  sf::Font m_font;
  std::unique_ptr<sf::Text> m_scoreText;
  std::unique_ptr<sf::Text> m_timerText;
  std::unique_ptr<sf::Text> m_gameOverText;
  std::unique_ptr<sf::Text> m_finalScoreText;
  std::unique_ptr<sf::Text> m_restartText;
  std::unique_ptr<sf::Text> m_exitText;
  bool m_fontLoaded;
};
#endif
