#include "BoardView.h"

#include "../Constants.h"

BoardView::BoardView(const BoardModel& boardModel) : boardModel(boardModel) {
  tileset.loadFromFile("tileset.png");
  font.openFromFile("font.ttf");
}

void BoardView::render(sf::RenderWindow& window) {
  for (int i = 0; i < (int)boardModel.cardModels.size(); i++) {
    const CardModel& card = boardModel.cardModels[i];

    if (card.cardState == CardState::Matched) continue;

    int col = i % COLS;
    int row = i / COLS;

    float x = OFFSET_X + col * (CARD_W + GAP);
    float y = OFFSET_Y + row * (CARD_H + GAP);

    sf::Sprite sprite(tileset);

    if (card.cardState == CardState::FaceDown) {
      sf::RectangleShape back({CARD_W, CARD_H});
      back.setPosition({x, y});
      back.setFillColor(sf::Color(70, 70, 120));
      back.setOutlineColor(sf::Color::White);
      back.setOutlineThickness(2.f);
      window.draw(back);
    } else {
      sprite.setTextureRect(sf::IntRect({card.typeId * 120, 0}, {120, 160}));
      sprite.setPosition({x, y});
      window.draw(sprite);

      if (card.cardState == CardState::Matched) {
        sf::RectangleShape overlay({CARD_W, CARD_H});
        overlay.setPosition({x, y});
        overlay.setFillColor(sf::Color(0, 255, 0, 60));
        window.draw(overlay);
      }
    }
  }

  sf::Text scoreText(font);
  scoreText.setString("Score: " + std::to_string(boardModel.score));
  scoreText.setCharacterSize(36);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({1050.f, 320.f});
  window.draw(scoreText);

  sf::Text movesText(font);
  movesText.setString("Moves: " + std::to_string(boardModel.moves));
  movesText.setCharacterSize(36);
  movesText.setFillColor(sf::Color::White);
  movesText.setPosition({1050.f, 370.f});
  window.draw(movesText);

  if (boardModel.isGameOver()) {
    sf::RectangleShape overlay({1280.f, 720.f});
    overlay.setPosition({0.f, 0.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 160));
    window.draw(overlay);

    sf::Text winText(font);
    winText.setString("You Win!");
    winText.setCharacterSize(72);
    winText.setFillColor(sf::Color::Yellow);
    auto bounds = winText.getLocalBounds();
    winText.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    winText.setPosition({640.f, 300.f});
    window.draw(winText);

    sf::Text movesText(font);
    movesText.setString("Moves: " + std::to_string(boardModel.moves));
    movesText.setCharacterSize(42);
    movesText.setFillColor(sf::Color::White);
    auto mb = movesText.getLocalBounds();
    movesText.setOrigin({mb.size.x / 2.f, mb.size.y / 2.f});
    movesText.setPosition({640.f, 400.f});
    window.draw(movesText);
  }
}
