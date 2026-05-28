#include "game.h"

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <optional>
#include <random>
#include <string>
#include <vector>

struct Card {
  Card() : shape(sf::Vector2f()) {}

  char symbol = '?';
  bool is_revealed = false;
  bool is_matched = false;
  sf::RectangleShape shape;
};

void runGame() {
  const int grid_size = 4;
  const int card_count = 16;
  const int pair_count = 8;
  const unsigned int window_size = 820;
  const float reveal_delay_seconds = 0.9f;
  const float side_margin = 40.0f;
  const float top_area_height = 70.0f;
  const float bottom_margin = 40.0f;
  const float gap = 14.0f;

  sf::RenderWindow window(
      sf::VideoMode({window_size, window_size}), sf::String(L"Запоминашки"),
      sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.openFromFile("arial.ttf")) {
    return;
  }

  std::random_device random_device;
  std::mt19937 generator(random_device());

  const float float_window_size = static_cast<float>(window_size);
  const float board_size = std::min(float_window_size - side_margin * 2.0f,
                                    float_window_size - top_area_height -
                                        bottom_margin);
  const float card_size = (board_size - gap * (grid_size - 1)) / grid_size;
  const float start_x = (float_window_size - board_size) / 2.0f;
  const float start_y = top_area_height;

  std::vector<sf::Vector2f> positions;
  for (int row = 0; row < grid_size; ++row) {
    for (int column = 0; column < grid_size; ++column) {
      positions.push_back(
          {start_x + column * (card_size + gap),
           start_y + row * (card_size + gap)});
    }
  }

  std::vector<Card> cards(card_count);
  for (Card& card : cards) {
    card.shape.setSize({card_size, card_size});
    card.shape.setFillColor(sf::Color::White);
    card.shape.setOutlineThickness(1.0f);
    card.shape.setOutlineColor(sf::Color::Black);
  }

  std::vector<char> symbols = {'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D',
                               'E', 'E', 'F', 'F', 'G', 'G', 'H', 'H'};
  std::shuffle(symbols.begin(), symbols.end(), generator);
  std::shuffle(positions.begin(), positions.end(), generator);

  for (int index = 0; index < card_count; ++index) {
    cards[index].symbol = symbols[index];
    cards[index].shape.setPosition(positions[index]);
  }

  unsigned int symbol_size = static_cast<unsigned int>(card_size * 0.42f);
  if (symbol_size < 36) {
    symbol_size = 36;
  }

  sf::Text symbol_text(font, "", symbol_size);
  symbol_text.setFillColor(sf::Color::Black);
  symbol_text.setStyle(sf::Text::Bold);

  sf::Text moves_text(font, "", 28);
  moves_text.setPosition({side_margin, 18.0f});
  moves_text.setFillColor(sf::Color::White);

  sf::Text errors_text(font, "", 28);
  errors_text.setFillColor(sf::Color::White);

  sf::Text win_text(font, "", 38);
  win_text.setFillColor(sf::Color::White);
  win_text.setStyle(sf::Text::Bold);

  std::vector<int> opened_cards;
  int move_count = 0;
  int matched_pair_count = 0;
  int wrong_streak_count = 0;
  bool is_checking_pair = false;
  bool is_game_finished = false;
  sf::Clock reveal_clock;

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      if (is_game_finished || is_checking_pair) {
        continue;
      }

      const auto* mouse_pressed =
          event->getIf<sf::Event::MouseButtonPressed>();
      if (mouse_pressed == nullptr ||
          mouse_pressed->button != sf::Mouse::Button::Left) {
        continue;
      }

      const sf::Vector2f mouse_position(
          static_cast<float>(mouse_pressed->position.x),
          static_cast<float>(mouse_pressed->position.y));

      for (int index = 0; index < card_count; ++index) {
        if (cards[index].is_matched || cards[index].is_revealed) {
          continue;
        }

        if (!cards[index].shape.getGlobalBounds().contains(mouse_position)) {
          continue;
        }

        cards[index].is_revealed = true;
        opened_cards.push_back(index);

        if (opened_cards.size() == 2) {
          ++move_count;
          is_checking_pair = true;
          reveal_clock.restart();
        }

        break;
      }
    }

    if (is_checking_pair &&
        reveal_clock.getElapsedTime() >= sf::seconds(reveal_delay_seconds)) {
      const int first_card = opened_cards[0];
      const int second_card = opened_cards[1];

      if (cards[first_card].symbol == cards[second_card].symbol) {
        cards[first_card].is_matched = true;
        cards[second_card].is_matched = true;
        cards[first_card].is_revealed = false;
        cards[second_card].is_revealed = false;
        ++matched_pair_count;
        wrong_streak_count = 0;

        if (matched_pair_count == pair_count) {
          is_game_finished = true;
        }
      } else {
        cards[first_card].is_revealed = false;
        cards[second_card].is_revealed = false;
        ++wrong_streak_count;

        if (wrong_streak_count == 3) {
          std::vector<int> remaining_indexes;
          std::vector<char> remaining_symbols;
          std::vector<sf::Vector2f> remaining_positions;

          for (int index = 0; index < card_count; ++index) {
            if (cards[index].is_matched) {
              continue;
            }

            remaining_indexes.push_back(index);
            remaining_symbols.push_back(cards[index].symbol);
            remaining_positions.push_back(cards[index].shape.getPosition());
          }

          std::shuffle(remaining_symbols.begin(), remaining_symbols.end(),
                       generator);
          std::shuffle(remaining_positions.begin(), remaining_positions.end(),
                       generator);

          for (std::size_t index = 0; index < remaining_indexes.size();
               ++index) {
            cards[remaining_indexes[index]].symbol = remaining_symbols[index];
            cards[remaining_indexes[index]].shape.setPosition(
                remaining_positions[index]);
          }

          wrong_streak_count = 0;
        }
      }

      opened_cards.clear();
      is_checking_pair = false;
    }

    moves_text.setString(
        sf::String(std::wstring(L"Ходы: ") + std::to_wstring(move_count)));
    errors_text.setString(sf::String(std::wstring(L"Ошибки: ") +
                                     std::to_wstring(wrong_streak_count) +
                                     L"/3"));

    {
      const sf::FloatRect bounds = errors_text.getLocalBounds();
      errors_text.setOrigin(
          {bounds.position.x + bounds.size.x, bounds.position.y});
      errors_text.setPosition({float_window_size - side_margin, 18.0f});
    }

    if (is_game_finished) {
      win_text.setString(sf::String(L"Победа"));

      const sf::FloatRect bounds = win_text.getLocalBounds();
      win_text.setOrigin(bounds.position + bounds.size / 2.0f);
      win_text.setPosition(
          {start_x + board_size / 2.0f, start_y + board_size / 2.0f});
    } else {
      win_text.setString(sf::String());
    }

    window.clear(sf::Color::Black);
    window.draw(moves_text);
    window.draw(errors_text);

    for (const Card& card : cards) {
      if (card.is_matched) {
        continue;
      }

      window.draw(card.shape);

      if (card.is_revealed) {
        symbol_text.setString(std::string(1, card.symbol));
        {
          const sf::FloatRect bounds = symbol_text.getLocalBounds();
          symbol_text.setOrigin(bounds.position + bounds.size / 2.0f);
          symbol_text.setPosition(card.shape.getPosition() +
                                  card.shape.getSize() / 2.0f);
        }
        window.draw(symbol_text);
      }
    }

    window.draw(win_text);
    window.display();
  }
}
