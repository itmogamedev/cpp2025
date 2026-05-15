#include "gameMenu.h"

void GameMenu::setInitText(sf::Text& text, sf::String str, float xpos,
                           float ypos) {
  text.setFont(font);
  text.setFillColor(menu_text_color);
  text.setString(str);
  text.setCharacterSize(size_font);
  text.setPosition({xpos, ypos});
  text.setOutlineThickness(3);
  text.setOutlineColor(border_color);
}

void GameMenu::AlignMenu(int posx) {
  float nullx = 0;
  for (int i = 0; i < max_menu; i++) {
    switch (posx) {
      case 0:
        nullx = 0;
        break;
      case 1:
        nullx = mainMenu[i].getLocalBounds().size.x;
        break;
      case 2:
        nullx = nullx = mainMenu[i].getLocalBounds().size.x / 2;
        break;
    }
    mainMenu[i].setPosition(
        {mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y});
  }
}

GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy,
                   int index, sf::String name[], int sizeFont, int step)
    : mywindow(window),
      x(menux),
      y(menuy),
      size_font(sizeFont),
      menu_Step(step) {
  if (!font.openFromFile("font/Cyrulik.otf")) exit(32);
  max_menu = index;
  mainMenu.clear();
  for (int i = 0, ypos = y; i < max_menu; i++, ypos += menu_Step) {
    mainMenu.emplace_back(font);
    setInitText(mainMenu.back(), name[i], x, ypos);
  }

  mainMenuSelected = 0;
  mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}

void GameMenu::MoveUp() {
  mainMenuSelected--;

  if (mainMenuSelected >= 0) {
    mainMenu[mainMenuSelected].setFillColor(chose_text_color);
    mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
  } else {
    mainMenu[0].setFillColor(menu_text_color);
    mainMenuSelected = max_menu - 1;
    mainMenu[mainMenuSelected].setFillColor(chose_text_color);
  }
}

void GameMenu::MoveDown() {
  mainMenuSelected++;

  if (mainMenuSelected < max_menu) {
    mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
    mainMenu[mainMenuSelected].setFillColor(chose_text_color);
  } else {
    mainMenu[max_menu - 1].setFillColor(menu_text_color);
    mainMenuSelected = 0;
    mainMenu[mainMenuSelected].setFillColor(chose_text_color);
  }
}

void GameMenu::draw() {
  for (int i = 0; i < max_menu; i++) mywindow.draw(mainMenu[i]);
}
void GameMenu::setColorTextMenu(sf::Color menColor, sf::Color choColor,
                                sf::Color bordrColor) {
  menu_text_color = menColor;
  chose_text_color = choColor;
  border_color = bordrColor;

  for (int i = 0; i < max_menu; i++) {
    mainMenu[i].setFillColor(menu_text_color);
    mainMenu[i].setOutlineColor(border_color);
  }

  mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}
