#include "Game.h"
#include <cctype>
#include <iostream>

Game::Game()
    : window_(nullptr),
      current_char_(' '),
      score_(0),
      time_remaining_(10.0f),
      game_active_(true),
      random_engine_(random_device_()) {
  initWindow();
  initFont();
  initVariables();
}

Game::~Game() = default;

void Game::initWindow() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;
  
  window_ = new sf::RenderWindow(
      sf::VideoMode({static_cast<unsigned int>(WINDOW_WIDTH),
                     static_cast<unsigned int>(WINDOW_HEIGHT)}),
      "Typing Trainer",
      sf::State::Windowed,
      settings);
  window_->setFramerateLimit(60);
}

void Game::initFont() {
  if (!font_.openFromFile("/System/Library/Fonts/SFNS.ttf")) {
    if (!font_.openFromFile("/System/Library/Fonts/Helvetica.ttc")) {
      std::cerr << "Error loading font!" << std::endl;
    }
  }
}

void Game::initVariables() {
  current_char_ = generateRandomChar();
  
  current_char_text_ = std::make_unique<sf::Text>(font_, std::string(1, current_char_), 200);
  current_char_text_->setFillColor(sf::Color::White);
  current_char_text_->setPosition(sf::Vector2f(
      WINDOW_WIDTH / 2 - current_char_text_->getGlobalBounds().size.x / 2,
      WINDOW_HEIGHT / 2 - 100));
  
  score_text_ = std::make_unique<sf::Text>(font_, "Score: 0", 30);
  score_text_->setFillColor(sf::Color::White);
  score_text_->setPosition(sf::Vector2f(20, 20));
  
  timer_text_ = std::make_unique<sf::Text>(font_, "Time: 10", 30);
  timer_text_->setFillColor(sf::Color::White);
  timer_text_->setPosition(sf::Vector2f(WINDOW_WIDTH - 150, 20));
  
  game_over_text_ = std::make_unique<sf::Text>(font_, "GAME OVER!", 50);
  game_over_text_->setFillColor(sf::Color::Red);
  game_over_text_->setPosition(sf::Vector2f(
      WINDOW_WIDTH / 2 - game_over_text_->getGlobalBounds().size.x / 2,
      WINDOW_HEIGHT / 2));
  
  restart_text_ = std::make_unique<sf::Text>(font_, "Press R to restart", 30);
  restart_text_->setFillColor(sf::Color::White);
  restart_text_->setPosition(sf::Vector2f(
      WINDOW_WIDTH / 2 - restart_text_->getGlobalBounds().size.x / 2,
      WINDOW_HEIGHT / 2 + 100));
}

char Game::generateRandomChar() {
  // Генерируем только строчные буквы (a-z) и цифры (0-9)
  int range = random_engine_() % 2;
  if (range == 0) {
    // Цифры 0-9
    return '0' + (random_engine_() % 10);
  } else {
    // Строчные буквы a-z
    return 'a' + (random_engine_() % 26);
  }
}

void Game::run() {
  sf::Clock clock;
  
  while (window_->isOpen()) {
    float delta_time = clock.restart().asSeconds();
    
    if (delta_time > 0.1f) {
      delta_time = 0.1f;
    }
    
    handleInput();
    
    if (game_active_) {
      update(delta_time);
    }
    
    render();
  }
}

void Game::handleInput() {
  while (const std::optional<sf::Event> event = window_->pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_->close();
    }
    
    if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
      if (!game_active_ && key_pressed->scancode == sf::Keyboard::Scancode::R) {
        resetGame();
      } else if (game_active_) {
        processKeyPress(key_pressed->scancode);
      }
    }
  }
}

void Game::processKeyPress(sf::Keyboard::Scancode scancode) {
  char pressed_char = ' ';
  
  // Выводим код нажатой клавиши для отладки
  std::cout << "Scancode: " << static_cast<int>(scancode) << std::endl;
  
  // Обработка цифр (основной ряд)
  if (scancode == sf::Keyboard::Scancode::Num0) pressed_char = '0';
  else if (scancode == sf::Keyboard::Scancode::Num1) pressed_char = '1';
  else if (scancode == sf::Keyboard::Scancode::Num2) pressed_char = '2';
  else if (scancode == sf::Keyboard::Scancode::Num3) pressed_char = '3';
  else if (scancode == sf::Keyboard::Scancode::Num4) pressed_char = '4';
  else if (scancode == sf::Keyboard::Scancode::Num5) pressed_char = '5';
  else if (scancode == sf::Keyboard::Scancode::Num6) pressed_char = '6';
  else if (scancode == sf::Keyboard::Scancode::Num7) pressed_char = '7';
  else if (scancode == sf::Keyboard::Scancode::Num8) pressed_char = '8';
  else if (scancode == sf::Keyboard::Scancode::Num9) pressed_char = '9';
  // Обработка букв
  else if (scancode >= sf::Keyboard::Scancode::A && scancode <= sf::Keyboard::Scancode::Z) {
    pressed_char = 'a' + (static_cast<int>(scancode) - static_cast<int>(sf::Keyboard::Scancode::A));
  }
  // Обработка цифр на numpad (если нужно)
  else if (scancode >= sf::Keyboard::Scancode::Numpad0 && scancode <= sf::Keyboard::Scancode::Numpad9) {
    pressed_char = '0' + (static_cast<int>(scancode) - static_cast<int>(sf::Keyboard::Scancode::Numpad0));
  }
  else {
    // Игнорируем другие клавиши
    return;
  }
  
  std::cout << "Pressed: '" << pressed_char << "' Expected: '" << current_char_ << "'" << std::endl;
  
  if (pressed_char == current_char_) {
    // Правильное нажатие
    score_++;
    current_char_ = generateRandomChar();
    if (current_char_text_) {
      current_char_text_->setString(std::string(1, current_char_));
      current_char_text_->setPosition(sf::Vector2f(
          WINDOW_WIDTH / 2 - current_char_text_->getGlobalBounds().size.x / 2,
          WINDOW_HEIGHT / 2 - 100));
      current_char_text_->setFillColor(sf::Color::Green);
    }
    std::cout << "Correct! Score: " << score_ << std::endl;
  } else {
    // Неправильное нажатие
    time_remaining_ -= TIME_PENALTY;
    if (time_remaining_ <= 0.0f) {
      game_active_ = false;
      time_remaining_ = 0.0f;
    }
    
    if (current_char_text_) {
      current_char_text_->setFillColor(sf::Color::Red);
    }
    std::cout << "Wrong! Time left: " << time_remaining_ << std::endl;
  }
}

void Game::update(float delta_time) {
  if (game_active_) {
    time_remaining_ -= delta_time;
    if (time_remaining_ <= 0.0f) {
      game_active_ = false;
      time_remaining_ = 0.0f;
    }
  }
  
  // Возвращаем цвет символа на белый через 0.1 секунды
  static float color_timer = 0.0f;
  color_timer += delta_time;
  if (color_timer >= 0.1f) {
    if (current_char_text_) {
      current_char_text_->setFillColor(sf::Color::White);
    }
    color_timer = 0.0f;
  }
  
  // Обновляем тексты
  if (score_text_) {
    score_text_->setString("Score: " + std::to_string(score_));
  }
  
  if (timer_text_) {
    int display_time = static_cast<int>(time_remaining_ + 0.5f);
    if (display_time < 0) display_time = 0;
    timer_text_->setString("Time: " + std::to_string(display_time));
  }
}

void Game::resetGame() {
  score_ = 0;
  time_remaining_ = 10.0f;
  game_active_ = true;
  current_char_ = generateRandomChar();
  if (current_char_text_) {
    current_char_text_->setString(std::string(1, current_char_));
    current_char_text_->setFillColor(sf::Color::White);
    current_char_text_->setPosition(sf::Vector2f(
        WINDOW_WIDTH / 2 - current_char_text_->getGlobalBounds().size.x / 2,
        WINDOW_HEIGHT / 2 - 100));
  }
}

void Game::render() {
  window_->clear(sf::Color::Black);
  
  if (current_char_text_) window_->draw(*current_char_text_);
  if (score_text_) window_->draw(*score_text_);
  if (timer_text_) window_->draw(*timer_text_);
  
  if (!game_active_) {
    if (game_over_text_) window_->draw(*game_over_text_);
    if (restart_text_) window_->draw(*restart_text_);
  }
  
  window_->display();
}