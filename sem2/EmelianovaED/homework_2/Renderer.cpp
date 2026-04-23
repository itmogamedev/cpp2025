#include "Renderer.h"

#include <sstream>

#define SIZE_SYMBOL 200
#define COLOR_TEXT {20, 15, 11}
#define SIZE_COUNTER 30
#define POSITION_COUNTER {20.0f, 20.0f}
#define SIZE_TIMER 30
#define WINDOW_OVER_COLOR {0, 0, 0, 45}
#define COLOR_TEXT_OVER {146, 0, 10}
#define SIZE_TEXT_OVER 80
#define COEF_CENTER 2.0f
#define COEF_WINDOW 20.0f
#define COEF_TEXT_OVER 60.0f
#define COEF_TEXT_RESTART 100.0f
#define SIZE_RESTART 25
#define SIZE_COUNTER_FINAL 40

Renderer::Renderer(sf::RenderWindow& window, const sf::Font& font)
    : window(window), font(font) {};
void Renderer::drawGame(char symbol_current, int counter,
                        float remaining_time) {
  sf::Text symbolText(font);
  symbolText.setString(std::string(1, symbol_current));
  symbolText.setCharacterSize(SIZE_SYMBOL);
  symbolText.setFillColor(COLOR_TEXT);
  sf::FloatRect symbolBounds = symbolText.getLocalBounds();
  symbolText.setOrigin(
      {symbolBounds.position.x + symbolBounds.size.x / COEF_CENTER,
       symbolBounds.position.y + symbolBounds.size.y / COEF_CENTER});
  symbolText.setPosition(
      {static_cast<float>(window.getSize().x) / COEF_CENTER,
       static_cast<float>(window.getSize().y) / COEF_CENTER});

  
  sf::Text counterText(font);
  counterText.setString("Counter: " + std::to_string(counter));
  counterText.setCharacterSize(SIZE_COUNTER);
  counterText.setFillColor(COLOR_TEXT);
  counterText.setPosition(POSITION_COUNTER);

 
  sf::Text timerText(font);
  std::ostringstream timerStream;
  timerStream << "Time: " << static_cast<int>(std::max(0.0f, remaining_time));
  timerText.setString(timerStream.str());
  timerText.setCharacterSize(SIZE_TIMER);
  timerText.setFillColor(COLOR_TEXT);
  sf::FloatRect timerBounds = timerText.getLocalBounds();
  timerText.setPosition({static_cast<float>(window.getSize().x) -
                             timerBounds.size.x - COEF_WINDOW,
                         COEF_WINDOW});

  window.draw(symbolText);
  window.draw(counterText);
  window.draw(timerText);
}
void Renderer::drawGameOver(int final_counter) {
  sf::RectangleShape overlay({static_cast<float>(window.getSize().x),
                              static_cast<float>(window.getSize().y)});
  overlay.setFillColor(sf::Color(WINDOW_OVER_COLOR));
  window.draw(overlay);

  sf::Text gameOverText(font);
  gameOverText.setString("GAME OVER");
  gameOverText.setCharacterSize(SIZE_TEXT_OVER);
  gameOverText.setFillColor(COLOR_TEXT_OVER);
  sf::FloatRect go_bounds = gameOverText.getLocalBounds();
  gameOverText.setOrigin(
      {go_bounds.position.x + go_bounds.size.x / COEF_CENTER,
       go_bounds.position.y + go_bounds.size.y / COEF_CENTER});
  gameOverText.setPosition(
      {static_cast<float>(window.getSize().x) / COEF_CENTER,
       static_cast<float>(window.getSize().y) / COEF_CENTER - COEF_TEXT_OVER});

  
  sf::Text finalCounterText(font);
  finalCounterText.setString("Final Counter: " + std::to_string(final_counter));
  finalCounterText.setCharacterSize(SIZE_COUNTER_FINAL);
  finalCounterText.setFillColor(COLOR_TEXT);
  sf::FloatRect fs_bounds = finalCounterText.getLocalBounds();
  finalCounterText.setOrigin(
      {fs_bounds.position.x + fs_bounds.size.x / COEF_CENTER,
       fs_bounds.position.y + fs_bounds.size.y / COEF_CENTER});
  finalCounterText.setPosition(
      {static_cast<float>(window.getSize().x) / COEF_CENTER,
       static_cast<float>(window.getSize().y) / COEF_CENTER + COEF_WINDOW});

  
  sf::Text restartText(font);
  restartText.setString("Press R to restart or ESC to quit");
  restartText.setCharacterSize(SIZE_RESTART);
  restartText.setFillColor(COLOR_TEXT);
  sf::FloatRect rt_bounds = restartText.getLocalBounds();
  restartText.setOrigin(
      {rt_bounds.position.x + rt_bounds.size.x / COEF_CENTER,
       rt_bounds.position.y + rt_bounds.size.y / COEF_CENTER});
  restartText.setPosition(
      {static_cast<float>(window.getSize().x) / COEF_CENTER,
       static_cast<float>(window.getSize().y) / COEF_CENTER +
           COEF_TEXT_RESTART});

  window.draw(gameOverText);
  window.draw(finalCounterText);
  window.draw(restartText);
}
