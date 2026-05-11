#include "start.h"

#include <random>

#include "GameMenu.h"

void InitText(sf::Text& mtext, float xpos, float ypos, sf::String str,
              int size_font = 60, sf::Color menu_text_color = sf::Color::White,
              int bord = 0, sf::Color border_color = sf::Color::Black);

void GamåStart(sf::RenderWindow& window) {
  sf::Font font;
  if (!font.openFromFile("font/Cyrulik.otf")) exit(32);
  sf::Text timer(font);
  timer.setCharacterSize(100);
  timer.setFillColor(sf::Color::Black);

  sf::Text score(font);
  score.setCharacterSize(100);
  score.setFillColor(sf::Color::Black);

  sf::Text task(font);
  task.setCharacterSize(150);
  task.setFillColor(sf::Color::Black);

  sf::CircleShape shape(100.f);
  sf::Clock clock;

  timer.setPosition(sf::Vector2f(20, 0));
  score.setPosition(sf::Vector2f(20, 100));
  task.setPosition(sf::Vector2f(920, 440));
  score.setString("score");
  task.setString("A");
  float timer_time = 15;
  float timer_minus = 1;
  Play(timer, score, task, window, clock, timer_time, timer_minus);
}

bool Play(sf::Text& timer_text, sf::Text& score_text, sf::Text& task_text,
          sf::RenderWindow& window, sf::Clock& clock, float& timer_time,
          float& timer_minus) {
  float width = sf::VideoMode::getDesktopMode().size.x;
  float height = sf::VideoMode::getDesktopMode().size.y;

  sf::RectangleShape background2(sf::Vector2f(width, height));
  sf::Texture texture_window2;
  if (!texture_window2.loadFromFile("image/menu4.png")) exit(4);
  background2.setTexture(&texture_window2);

  std::string alfabet = "abcdefghijklmnopqrstuvwxyz1234567890";
  std::random_device rd;
  std::mt19937 gen(rd());
  int char_idx = gen() % (alfabet.size());
  task_text.setString(alfabet[char_idx]);
  int score = 0;
  score_text.setString("score: " + std::to_string(score));
  float time = timer_time;
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return 0;
      }
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
          return 1;
        }
      }
    }
    if (time > 0) {
      time = timer_time - clock.getElapsedTime().asSeconds();
      char buffer[32];
      std::snprintf(buffer, sizeof(buffer), "%.2f", time);
      timer_text.setString(buffer);
    } else {
      timer_text.setString("0");
      task_text.setString("GameOver");
      task_text.setPosition(sf::Vector2f(680, 440));
    }
    window.clear();
    window.draw(background2);
    window.draw(timer_text);
    window.draw(score_text);
    window.draw(task_text);
    window.display();
  }
  return 0;
}

void startGame() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"Typing Train");

  float width = sf::VideoMode::getDesktopMode().size.x;
  float height = sf::VideoMode::getDesktopMode().size.y;

  sf::RectangleShape background(sf::Vector2f(width, height));
  sf::Texture texture_window;
  if (!texture_window.loadFromFile("image/menu9.png")) exit(4);
  background.setTexture(&texture_window);

  sf::Font font;
  if (!font.openFromFile("font/Cyrulik.otf")) exit(5);
  sf::Text Titul(font);

  InitText(Titul, 600, 50, "Typing Train", 150, sf::Color::White, 3);

  sf::String name_menu[]{"PLAY", "Exit"};

  GameMenu mymenu(window, 950, 450, 2, name_menu, 100, 120);

  mymenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);

  mymenu.AlignMenu(2);

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();

      if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
        if (keyReleased->code == sf::Keyboard::Key::Up) mymenu.MoveUp();

        if (keyReleased->code == sf::Keyboard::Key::Down) mymenu.MoveDown();

        if (keyReleased->code == sf::Keyboard::Key::Enter) {
          switch (mymenu.getSelectedMenuNumber()) {
            case 0:
              GamåStart(window);
              break;
            case 1:
              window.close();
              break;
          }
        }
      }
    }

    window.clear();
    window.draw(background);
    window.draw(Titul);
    mymenu.draw();
    window.display();
  }
}

void InitText(sf::Text& mtext, float xpos, float ypos, sf::String str,
              int size_font, sf::Color menu_text_color, int bord,
              sf::Color border_color) {
  mtext.setCharacterSize(size_font);
  mtext.setPosition({xpos, ypos});
  mtext.setString(str);
  mtext.setFillColor(menu_text_color);
  mtext.setOutlineThickness(bord);
  mtext.setOutlineColor(border_color);
}
