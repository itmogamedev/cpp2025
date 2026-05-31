#include "Graphics.h"

#include <iostream>
#include <optional>

#define CARD_SIZE 90.f
#define INDENT 20.f
#define WAIT_DURATION 0.5f
#define SCORE_CARD 4
#define SCORE_INDENT 5
#define EXTRA_SPACE 50
#define COLOR_BACK {240, 245, 249}
#define COLOR_CARD_OP {170, 193, 207}
#define COLOR_CARD_CL {185, 193, 207}
#define COLOR_TEXT {30, 32, 34}
#define COEF 2
#define COEF_F 2
#define SIZE_TEXT 24
#define SIZE_SYMBOL 50
#define X_SCORE 10
#define X_MOVES 300

Graphics::Graphics()
    : window_game(
          sf::VideoMode(sf::Vector2u(
              static_cast<unsigned int>(SCORE_CARD * CARD_SIZE +
                                        SCORE_INDENT * INDENT),
              static_cast<unsigned int>(SCORE_CARD * CARD_SIZE +
                                        SCORE_CARD * INDENT + EXTRA_SPACE))),
          "Memory Game - Find Pairs"),
      wait_timer(0.0f) {
  if (!font_game.openFromFile("impact.ttf")) {
    if (!font_game.openFromFile("C:/Windows/Fonts/impact.ttf")) {
      std::cerr << "Warning: Could not load font. Text will be invisible.\n";
    }
  }
}

int Graphics::getCardClick(int x, int y) const {
  int col_board = static_cast<int>((x - INDENT) / (CARD_SIZE + INDENT));
  int row_board = static_cast<int>((y - INDENT) / (CARD_SIZE + INDENT));
  if (col_board < 0 || col_board >= SCORE_CARD || row_board < 0 ||
      row_board >= SCORE_CARD)
    return -1;
  return row_board * SCORE_CARD + col_board;
}

void Graphics::handEvents(Game& logic, float dt) {
  while (const std::optional event = window_game.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_game.close();
    } else if (!logic.isWaiting() &&
               event->is<sf::Event::MouseButtonPressed>()) {
      const auto* mouse_event = event->getIf<sf::Event::MouseButtonPressed>();
      if (mouse_event && mouse_event->button == sf::Mouse::Button::Left) {
        int index_cr =
            getCardClick(mouse_event->position.x, mouse_event->position.y);
        if (index_cr != -1) {
          logic.handOpen(index_cr);
        }
      }
    }
  }
}

void Graphics::renderWindow(const Game& logic) {
  window_game.clear(sf::Color(COLOR_BACK));

  const auto& board_cr = logic.getBoard();
  for (int row_board = 0; row_board < SCORE_CARD; ++row_board) {
    for (int col_board = 0; col_board < SCORE_CARD; ++col_board) {
      int idx = row_board * SCORE_CARD + col_board;
      const Card& card_spec = board_cr[idx];

      float x_cur = INDENT + col_board * (CARD_SIZE + INDENT);
      float y_cur = INDENT + row_board * (CARD_SIZE + INDENT);

      sf::RectangleShape rect_card(sf::Vector2f(CARD_SIZE, CARD_SIZE));
      rect_card.setPosition(sf::Vector2f(x_cur, y_cur));

      if (card_spec.isMatched()) {
        continue;
      } else if (card_spec.isOpened()) {
        rect_card.setFillColor(sf::Color(COLOR_CARD_OP));
        window_game.draw(rect_card);

        sf::Text symbol_text(font_game);
        symbol_text.setString(std::string(1, 'A' + card_spec.getSymbol()));
        symbol_text.setCharacterSize(SIZE_SYMBOL);
        symbol_text.setFillColor(sf::Color(COLOR_TEXT));

        sf::FloatRect text_rect = symbol_text.getLocalBounds();
        symbol_text.setOrigin(
            sf::Vector2f(text_rect.position.x + text_rect.size.x / COEF_F,
                         text_rect.position.y + text_rect.size.y / COEF_F));
        symbol_text.setPosition(
            sf::Vector2f(x_cur + CARD_SIZE / COEF, y_cur + CARD_SIZE / COEF));
        window_game.draw(symbol_text);
      } else {
        rect_card.setFillColor(sf::Color(COLOR_CARD_CL));
        window_game.draw(rect_card);
      }
    }
  }

  sf::Text score_text(font_game);
  score_text.setCharacterSize(SIZE_TEXT);
  score_text.setFillColor(sf::Color(COLOR_TEXT));
  score_text.setPosition(sf::Vector2f(
      X_SCORE, SCORE_CARD * CARD_SIZE + SCORE_INDENT * INDENT + SCORE_INDENT));
  score_text.setString("Score: " + std::to_string(logic.getScore()));

  sf::Text moves_text(font_game);
  moves_text.setCharacterSize(SIZE_TEXT);
  moves_text.setFillColor(sf::Color(COLOR_TEXT));
  moves_text.setPosition(sf::Vector2f(
      X_MOVES, SCORE_CARD * CARD_SIZE + SCORE_INDENT * INDENT + SCORE_INDENT));
  moves_text.setString("Moves: " + std::to_string(logic.getMoves()));

  window_game.draw(score_text);
  window_game.draw(moves_text);

  window_game.display();
}

void Graphics::showEndScreen(const Game& logic) {
  window_game.clear(sf::Color(COLOR_BACK));

  sf::Text end_text(font_game);
  end_text.setString("You won!\nTotal moves: " +
                     std::to_string(logic.getMoves()) + "\nClick to exit");
  end_text.setCharacterSize(SIZE_TEXT);
  end_text.setFillColor(sf::Color(COLOR_TEXT));
  sf::FloatRect text_rect = end_text.getLocalBounds();
  end_text.setOrigin(
      sf::Vector2f(text_rect.position.x + text_rect.size.x / COEF_F,
                   text_rect.position.y + text_rect.size.y / COEF_F));
  end_text.setPosition(
      sf::Vector2f(static_cast<float>(window_game.getSize().x) / COEF_F,
                   static_cast<float>(window_game.getSize().y) / COEF_F));
  window_game.draw(end_text);
  window_game.display();

  while (true) {
    while (const std::optional event = window_game.pollEvent()) {
      if (event->is<sf::Event::MouseButtonPressed>() ||
          event->is<sf::Event::Closed>()) {
        return;
      }
    }
  }
}

void Graphics::runGame(Game& logic) {
  sf::Clock clock_game;

  while (window_game.isOpen()) {
    float dt = clock_game.restart().asSeconds();

    handEvents(logic, dt);

    if (logic.isWaiting()) {
      wait_timer += dt;
      if (wait_timer >= WAIT_DURATION) {
        logic.updateMatch();
        wait_timer = 0.0f;
      }
    }

    renderWindow(logic);

    if (logic.isGameFinished()) {
      showEndScreen(logic);
      window_game.close();
    }
  }
}
