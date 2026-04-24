#include "Assemble.h"
#include "DataSettings.h"
void Start() { 
    sf::Font font;
    font.openFromFile("CyrilicOld.ttf");
    sf::Text timer_text(font);
    sf::Text score_text(font);
    sf::Text task_text(font);
    sf::Clock clock;
    timer_text.setPosition(sf::Vector2f(timer_text_x, timer_text_y));
    score_text.setPosition(sf::Vector2f(score_text_x, score_text_y));
    task_text.setPosition(sf::Vector2f(task_text_x, task_text_y));
    score_text.setString("score");
    task_text.setString("A");
    sf::RenderWindow window(sf::VideoMode({window_widght, window_height}),game_name);
    float timer_time = timer_time_def;
    float timer_minus = timer_minus_def;
    Play(timer_text, score_text, task_text, window, clock,timer_time,timer_minus);

}
void Play(sf::Text& timer_text, sf::Text& score_text, sf::Text& task_text,
          sf::RenderWindow& window, sf::Clock& clock,float&timer_time,float &timer_minus) {
  std::string alfabet = alfabet_def;
  std::random_device rd; 
  std::mt19937 gen(rd());
  int char_idx = gen() % (alfabet.size());
  task_text.setString(alfabet[char_idx]);
  int score = 0;
  score_text.setString("score: " + std::to_string(score));
  float time = timer_time;
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      if (time > 0) {
        if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
          if (keyPressed->unicode == alfabet[char_idx]) {
            char_idx = gen() % (alfabet.size());
            task_text.setString(alfabet[char_idx]);
            score++;
            score_text.setString("score: " + std::to_string(score));
          } else {
            timer_time -= timer_minus;
          }
        }
      } else {
        if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
          window.close();
          Start();
        }
      }
    }
    if (time > 0) {
      time = timer_time-clock.getElapsedTime().asSeconds();
      timer_text.setString(
          std::to_string(time));
    } else {
      timer_text.setString("0");
      task_text.setString("GameOver");
    }
    window.clear();
    window.draw(timer_text);
    window.draw(score_text);
    window.draw(task_text);
    window.display();
  }
}