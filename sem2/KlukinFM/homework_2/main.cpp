#include <SFML/Graphics.hpp>
#include "game.h"
#include <cctype>

#define TITLE_POS sf::Vector2f{720, 55}
#define START_BUTTON_POS sf::Vector2f{785, 235}
#define EXIT_BUTTON_POS sf::Vector2f{870, 340}
#define START_BUTTON_SIZE sf::IntRect({785, 235}, {290, 55}
#define EXIT_BUTTON_SIZE sf::IntRect({870, 340}, {110, 50}

void mainGame(sf::RenderWindow& win) {
  Game game = Game();

  while (win.isOpen()) {
      while (const std::optional event = win.pollEvent()) {
          if (event->is<sf::Event::Closed>())
              win.close();
          else {
              if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
                  if (key_pressed->scancode == sf::Keyboard::Scancode::Escape)
                      win.close();
              if (const auto* text_entered = event->getIf<sf::Event::TextEntered>())
                  game.enter(text_entered->unicode);
          }
      }
    win.clear();
    game.draw(win);
    win.display();
  }
}

void menu(sf::RenderWindow& win) {
  sf::Texture menuBackground, menuButtonStart, menuButtonExit;
  menuBackground.loadFromFile("images/menuBackground.png");
  sf::Font font;
  font.openFromFile("fonts/Comic Sans MS.ttf");

  sf::Text textTitle(font, "Cool Game", 80);
  textTitle.setFillColor(sf::Color::Magenta);
  textTitle.setStyle(sf::Text::Bold);

  sf::Text textStartGame(font, "Start Game", 48);
  textStartGame.setFillColor(sf::Color::White);
  textStartGame.setStyle(sf::Text::Bold);

  sf::Text textExitGame(font, "Exit", 48);
  textExitGame.setFillColor(sf::Color::White);
  textExitGame.setStyle(sf::Text::Bold);

  sf::Sprite menuBg(menuBackground);
  bool isMenu = 1;
  int menuNum = 0;
  menuBg.setPosition(sf::Vector2f{0, 0});
  textTitle.setPosition(TITLE_POS);
  textStartGame.setPosition(START_BUTTON_POS);
  textExitGame.setPosition(EXIT_BUTTON_POS);
  while (win.isOpen()) {
    while (isMenu) {
      textStartGame.setFillColor(sf::Color::White);
      textExitGame.setFillColor(sf::Color::White);

      menuNum = 0;

      if (START_BUTTON_SIZE)
              .contains(sf::Mouse::getPosition(win))) {
                textStartGame.setFillColor(sf::Color::Magenta);
                menuNum = 1;
              }

      if (EXIT_BUTTON_SIZE)
              .contains(sf::Mouse::getPosition(win))) {
                textExitGame.setFillColor(sf::Color::Magenta);
                menuNum = 2;
              }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (menuNum == 1) {
          isMenu = 0;
          mainGame(win);
        }

        if (menuNum == 2) {
          win.close();
          isMenu = 0;
        }
      }
      while (const std::optional event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          win.close();
          isMenu = 0;
        }
      }
      win.clear();

      win.draw(menuBg);
      win.draw(textTitle);
      win.draw(textStartGame);
      win.draw(textExitGame);

      win.display();
    }
  }
}

int main() {
  srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode({1280, 731}), "Typing Game");
  menu(window);
}