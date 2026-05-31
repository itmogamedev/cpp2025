#include "Game.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

Game::Game() : window(sf::VideoMode(600, 850), "Card Game") {
  window.setFramerateLimit(60);
  if (!font.loadFromFile("arial.ttf")) {
    std::cerr << "Failed .ttf\n";
  }
  initGame();
}

void Game::initGame() {
  cards.clear();
  first_selected_idx = -1;
  second_selected_idx = -1;  // сброс выбранных карт
  moves_count = 0;
  consecutive_mistakes = 0;
  matched_pairs = 0;
  is_waiting_for_delay = false;
  is_game_over = false;
  is_showing_shuffle_msg = false;

  std::vector<char> symbols = {'!', '!', '*', '*', '+', '+', '@', '@',
                               '=', '=', '&', '&', '%', '%', '#', '#'};

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(symbols.begin(), symbols.end(), g);  // рандомно перемешиваем

  // размер карт
  float card_width = 120.0f;
  float card_height = 160.0f;
  // настройка сетки
  float gap = 20.0f;
  float start_x = 30.0f;
  float start_y = 30.0f;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      float x = start_x + j * (card_width + gap);  // вычисление координат
      float y = start_y + i * (card_height + gap);
      cards.push_back(Card(x, y, card_width, card_height, symbols[i * 4 + j]));
    }
  }
}

void Game::shuffleRemaining() {
  std::vector<int> unmatched_indices;  // индекс неразгаданных
  std::vector<char> remaining_symbols;

  for (size_t i = 0; i < cards.size(); ++i) {
    if (!cards[i].is_matched) {
      unmatched_indices.push_back(i);
      remaining_symbols.push_back(cards[i].symbol);
      cards[i].is_face_up = false;
    }
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(remaining_symbols.begin(), remaining_symbols.end(),
               g);  // перемешивание символов неразгаданных

  for (size_t i = 0; i < unmatched_indices.size(); ++i) {
    cards[unmatched_indices[i]].symbol = remaining_symbols[i];
  }
}

void Game::run() {
  while (window.isOpen()) {
    handleInput();
    update();
    render();
  }
}

void Game::handleInput() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }

    if (is_waiting_for_delay || is_showing_shuffle_msg || is_game_over) {
      continue;
    }  // блок нажатий

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mouse_pos(
          static_cast<float>(event.mouseButton.x),
          static_cast<float>(event.mouseButton.y));  // координаты клика

      for (size_t i = 0; i < cards.size(); ++i) {
        if (!cards[i].is_matched && !cards[i].is_face_up &&
            cards[i].shape.getGlobalBounds().contains(mouse_pos)) {
          cards[i].is_face_up = true;

          if (first_selected_idx == -1) {
            first_selected_idx = static_cast<int>(i);
          } else {
            second_selected_idx = static_cast<int>(i);
            is_waiting_for_delay = true;
            delay_clock.restart();
            moves_count++;
          }
          break;
        }
      }
    }
  }
}

void Game::update() {
  if (is_showing_shuffle_msg) {
    if (shuffle_msg_clock.getElapsedTime().asSeconds() >= 1.5f) {
      is_showing_shuffle_msg = false;
    }
    return;
  }

  if (is_waiting_for_delay &&
      delay_clock.getElapsedTime().asSeconds() >= 1.0f) {
    if (cards[first_selected_idx].symbol == cards[second_selected_idx].symbol) {
      cards[first_selected_idx].is_matched = true;
      cards[second_selected_idx].is_matched = true;
      matched_pairs++;
      consecutive_mistakes = 0;

      if (matched_pairs == 8) {
        is_game_over = true;
      }
    } else {
      cards[first_selected_idx].is_face_up = false;
      cards[second_selected_idx].is_face_up = false;
      consecutive_mistakes++;

      if (consecutive_mistakes == 2) {
        shuffleRemaining();
        consecutive_mistakes = 0;
        is_showing_shuffle_msg = true;
        shuffle_msg_clock.restart();
      }
    }

    first_selected_idx = -1;
    second_selected_idx = -1;
    is_waiting_for_delay = false;
  }
}

void Game::render() {
  window.clear(sf::Color(40, 40, 40));

  for (const auto& card : cards) {
    card.draw(window, font);
  }

  sf::Text ui_text;
  ui_text.setFont(font);
  ui_text.setCharacterSize(28);
  ui_text.setFillColor(sf::Color::White);

  if (is_game_over) {
    std::string win_str =
        "You won\nTotal moves: " + std::to_string(moves_count);
    ui_text.setString(win_str);

    sf::FloatRect text_rect = ui_text.getLocalBounds();  // границы строки
    ui_text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                      text_rect.top + text_rect.height / 2.0f);
    ui_text.setPosition(window.getSize().x / 2.0f,
                        window.getSize().y - 85.0f);  // выравнивание
    window.draw(ui_text);
  } else {
    std::string moves_str = "Moves: " + std::to_string(moves_count);
    ui_text.setString(moves_str);

    sf::FloatRect text_rect = ui_text.getLocalBounds();
    ui_text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                      text_rect.top + text_rect.height / 2.0f);
    ui_text.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100.0f);
    window.draw(ui_text);

    if (is_showing_shuffle_msg) {
      sf::Text shuffle_text;
      shuffle_text.setFont(font);
      shuffle_text.setString("Cards shuffled");
      shuffle_text.setCharacterSize(26);
      shuffle_text.setFillColor(sf::Color::White);
      shuffle_text.setStyle(sf::Text::Bold);

      sf::FloatRect shuffle_rect = shuffle_text.getLocalBounds();
      shuffle_text.setOrigin(shuffle_rect.left + shuffle_rect.width / 2.0f,
                             shuffle_rect.top + shuffle_rect.height / 2.0f);
      shuffle_text.setPosition(window.getSize().x / 2.0f,
                               window.getSize().y - 45.0f);
      window.draw(shuffle_text);
    }
  }

  window.display();
}
