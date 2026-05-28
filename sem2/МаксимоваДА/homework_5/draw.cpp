#include "draw.h"

#include <iostream>

#include "const.h"

Draw::Draw()
    : game_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
      wait_accumulator(0.0f),
      font_ready(false) {
  if (!game_font.loadFromFile(FONT_MAIN)) {
  } else {
    font_ready = true;
  }
}

int Draw::detectCardClick(int mouse_x, int mouse_y) const {
  int column =
      static_cast<int>((mouse_x - FIELD_MARGIN) / (CARD_WIDTH + FIELD_MARGIN));
  int row = static_cast<int>((mouse_y - 80) / (CARD_HEIGHT + FIELD_MARGIN));

  if (column < 0 || column >= GRID_SIZE || row < 0 || row >= GRID_SIZE)
    return -1;
  return row * GRID_SIZE + column;
}

void Draw::processEvents(Game& current_game, float delta_time) {
  sf::Event event_data;
  while (game_window.pollEvent(event_data)) {
    if (event_data.type == sf::Event::Closed) {
      game_window.close();
    } else if (!current_game.isWaiting() &&
               event_data.type == sf::Event::MouseButtonPressed) {
      if (event_data.mouseButton.button == sf::Mouse::Left) {
        int clicked_card =
            detectCardClick(event_data.mouseButton.x, event_data.mouseButton.y);
        if (clicked_card != -1) {
          current_game.openCard(clicked_card);
        }
      }
    }
  }
}

void Draw::renderField(const Game& current_game) {
  game_window.clear(COLOR_BG);

  const auto& game_cards = current_game.getField();

  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      int card_id = row * GRID_SIZE + col;
      const Card& current_card = game_cards[card_id];

      float pos_x = FIELD_MARGIN + col * (CARD_WIDTH + FIELD_MARGIN);
      float pos_y = 80 + row * (CARD_HEIGHT + FIELD_MARGIN);

      sf::RectangleShape card_rectangle(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
      card_rectangle.setPosition(sf::Vector2f(pos_x, pos_y));

      if (current_card.isMatched()) {
        continue;
      } else if (current_card.isOpened()) {
        card_rectangle.setFillColor(COLOR_CARD_OPEN);
        game_window.draw(card_rectangle);

        if (font_ready) {
          sf::Text symbol_display;
          symbol_display.setFont(game_font);
          char displayed_char = 'A' + current_card.getSymbol();
          symbol_display.setString(std::string(1, displayed_char));
          symbol_display.setCharacterSize(TEXT_SIZE_SYMBOL);
          symbol_display.setFillColor(COLOR_TEXT);

          sf::FloatRect text_bounds = symbol_display.getLocalBounds();
          symbol_display.setOrigin(
              sf::Vector2f(text_bounds.left + text_bounds.width / 2,
                           text_bounds.top + text_bounds.height / 2));
          symbol_display.setPosition(
              sf::Vector2f(pos_x + CARD_WIDTH / 2, pos_y + CARD_HEIGHT / 2));
          game_window.draw(symbol_display);
        }
      } else {
        card_rectangle.setFillColor(COLOR_CARD_CLOSED);
        game_window.draw(card_rectangle);
      }
    }
  }

  if (font_ready) {
    sf::Text score_label;
    score_label.setFont(game_font);
    score_label.setCharacterSize(TEXT_SIZE_INFO);
    score_label.setFillColor(COLOR_TEXT);
    score_label.setPosition(sf::Vector2f(FIELD_MARGIN, INFO_OFFSET));
    score_label.setString(
        "Pairs found: " + std::to_string(current_game.getScore()) + "/" +
        std::to_string(TOTAL_PAIRS));

    sf::Text moves_label;
    moves_label.setFont(game_font);
    moves_label.setCharacterSize(TEXT_SIZE_INFO);
    moves_label.setFillColor(COLOR_TEXT);
    moves_label.setPosition(sf::Vector2f(FIELD_MARGIN + 250, INFO_OFFSET));
    moves_label.setString("Attempts: " +
                          std::to_string(current_game.getMoves()));

    game_window.draw(score_label);
    game_window.draw(moves_label);
  }

  game_window.display();
}

void Draw::renderFinalScreen(const Game& current_game) {
  game_window.clear(COLOR_BG);

  if (font_ready) {
    sf::Text victory_text;
    victory_text.setFont(game_font);
    victory_text.setString(
        "Victory!\nTotal moves: " + std::to_string(current_game.getMoves()) +
        "\nClick anywhere to exit");
    victory_text.setCharacterSize(TEXT_SIZE_INFO);
    victory_text.setFillColor(COLOR_TEXT);

    sf::FloatRect text_area = victory_text.getLocalBounds();
    victory_text.setOrigin(sf::Vector2f(text_area.left + text_area.width / 2,
                                        text_area.top + text_area.height / 2));
    victory_text.setPosition(
        sf::Vector2f(static_cast<float>(game_window.getSize().x) / 2,
                     static_cast<float>(game_window.getSize().y) / 2));
    game_window.draw(victory_text);
  } 

  game_window.display();

  while (true) {
    sf::Event closing_event;
    while (game_window.pollEvent(closing_event)) {
      if (closing_event.type == sf::Event::MouseButtonPressed ||
          closing_event.type == sf::Event::Closed) {
        return;
      }
    }
  }
}

void Draw::startGame(Game& current_game) {
  sf::Clock game_timer;

  while (game_window.isOpen()) {
    float delta_time = game_timer.restart().asSeconds();

    processEvents(current_game, delta_time);

    if (current_game.isWaiting()) {
      wait_accumulator += delta_time;
      if (wait_accumulator >= WAIT_SECONDS) {
        current_game.processMatch();
        wait_accumulator = 0.0f;
      }
    }

    renderField(current_game);

    if (current_game.isGameComplete()) {
      renderFinalScreen(current_game);
      game_window.close();
    }
  }
}