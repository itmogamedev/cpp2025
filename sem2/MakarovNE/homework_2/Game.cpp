#include "Game.h"

Game::Game(unsigned int width, unsigned int height, const std::string& title)
    : window_(sf::VideoMode({width, height}), title),
      font_(),
      score_text_(font_),
      timer_text_(font_),
      game_time_limit_(sf::seconds(60.0f)),
      elapsed_game_time_(sf::Time::Zero),
      score_(0),
      is_game_over_(false) {
  window_.setFramerateLimit(60);

  if (font_.openFromFile("arial.ttf")) {
    const sf::Texture& tex = font_.getTexture(24);
    std::cout << "Texture size: " << tex.getSize().x << "x" << tex.getSize().y
              << std::endl;
  }

  score_text_.setFont(font_);
  score_text_.setCharacterSize(24);
  score_text_.setFillColor(sf::Color::White);
  score_text_.setPosition({10.f, 10.f});

  timer_text_.setFont(font_);
  timer_text_.setCharacterSize(24);
  timer_text_.setFillColor(sf::Color::White);
  timer_text_.setPosition({static_cast<float>(width) - 150.f, 10.f});

  resetGame();
}

void Game::run() {
  while (window_.isOpen()) {
    processEvents();

    sf::Time deltaTime = clock_.restart();

    if (!is_game_over_) {
      update(deltaTime);
    }

    render();
  }
}

void Game::processEvents() {
  while (const std::optional<sf::Event> event = window_.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_.close();
    }

    if (const auto* mousePressed =
            event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mousePressed->button == sf::Mouse::Button::Left) {
        handleClick(static_cast<float>(mousePressed->position.x),
                    static_cast<float>(mousePressed->position.y));
      }
    }

    if (is_game_over_ && event->is<sf::Event::KeyPressed>()) {
      resetGame();
    }
  }
}

void Game::update(sf::Time deltaTime) {
  elapsed_game_time_ += deltaTime;
  if (elapsed_game_time_ >= game_time_limit_) {
    is_game_over_ = true;
  }

  sf::Time remainingTime = game_time_limit_ - elapsed_game_time_;
  if (remainingTime < sf::Time::Zero) {
    remainingTime = sf::Time::Zero;
  }
  int remainingSeconds = static_cast<int>(remainingTime.asSeconds());
  timer_text_.setString("Time: " + std::to_string(remainingSeconds));

  score_text_.setString("Score: " + std::to_string(score_));

  for (auto& target : targets_) {
    target.move(deltaTime);
  }
}

void Game::render() {
  window_.clear(sf::Color::Blue);

  for (const auto& target : targets_) {
    target.draw(window_);
  }

  window_.draw(score_text_);
  window_.draw(timer_text_);

  if (is_game_over_) {
    sf::Text gameOverText(font_,
                          "Game Over!\nFinal Score: " + std::to_string(score_) +
                              "\nPress any key to restart",
                          40);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.getCenter());
    sf::Vector2f windowSize = sf::Vector2f(window_.getSize());
    gameOverText.setPosition(windowSize / 2.0f);

    window_.draw(gameOverText);
  }
  window_.display();
}

void Game::resetGame() {
  targets_.clear();
  score_ = 0;
  elapsed_game_time_ = sf::Time::Zero;
  is_game_over_ = false;

  for (int i = 0; i < initial_target_count_; ++i) {
    spawnTarget();
  }
}

void Game::spawnTarget() {
  float windowWidth = static_cast<float>(window_.getSize().x);
  float windowHeight = static_cast<float>(window_.getSize().y);

  float radius = Utils::randomFloat(20.0f, 50.0f);
  float x = Utils::randomFloat(radius, windowWidth - radius);
  float y = Utils::randomFloat(radius, windowHeight - radius);

  sf::Color color(Utils::randomInt(0, 255), Utils::randomInt(0, 255),
                  Utils::randomInt(0, 255));

  targets_.emplace_back(x, y, radius, color, windowWidth, windowWidth);
}

bool Game::isMouseOverTarget(const CircleTarget& target, float mouseX,
                             float mouseY) {
  float dx = mouseX - target.getPosition().x;
  float dy = mouseY - target.getPosition().y;
  return (dx * dx + dy * dy) <= (target.getRadius() * target.getRadius());
}

void Game::handleClick(float mouseX, float mouseY) {
  if (is_game_over_) {
    return;
  }

  bool hit = false;

  for (size_t i = 0; i < targets_.size(); ++i) {
    if (isMouseOverTarget(targets_[i], mouseX, mouseY)) {
      score_++;
      hit = true;

      targets_[i] = CircleTarget(
          Utils::randomFloat(targets_[i].getRadius(),
                             static_cast<float>(window_.getSize().x) -
                                 targets_[i].getRadius()),
          Utils::randomFloat(targets_[i].getRadius(),
                             static_cast<float>(window_.getSize().y) -
                                 targets_[i].getRadius()),
          Utils::randomFloat(20.0f, 50.0f),
          sf::Color(Utils::randomInt(0, 255), Utils::randomInt(0, 255),
                    Utils::randomInt(0, 255)),
          static_cast<float>(window_.getSize().x),
          static_cast<float>(window_.getSize().y));
      break;
    }
  }
  if (!hit) {
    elapsed_game_time_ += sf::seconds(miss_penalty_time);
  }
}
