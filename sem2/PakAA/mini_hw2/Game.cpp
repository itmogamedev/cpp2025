
#include "Game.h"

#include <iomanip>
#include <sstream>
#include <string>

Game::Game()
    : window(sf::VideoMode(window_width, window_height), "OSU at Home"),
      font_loaded(false),
      game_over_texture_loaded(false),
      time_left(start_time),
      score(0),
      game_over(false) {
  window.setFramerateLimit(60);

  font_loaded = font.loadFromFile("arial.ttf");

  if (font_loaded) {
    score_text.setFont(font);
    score_text.setCharacterSize(28);
    score_text.setFillColor(sf::Color::White);
    score_text.setOutlineColor(sf::Color::Black);
    score_text.setOutlineThickness(2.f);
    score_text.setPosition(10.f, 10.f);

    timer_text.setFont(font);
    timer_text.setCharacterSize(28);
    timer_text.setFillColor(sf::Color::White);
    timer_text.setOutlineColor(sf::Color::Black);
    timer_text.setOutlineThickness(2.f);
    timer_text.setPosition(static_cast<float>(window_width) - 200.f, 10.f);

    game_over_text.setFont(font);
    game_over_text.setCharacterSize(64);
    game_over_text.setFillColor(sf::Color(200, 0, 0));
    game_over_text.setOutlineColor(sf::Color::Black);
    game_over_text.setOutlineThickness(4.f);

    hint_text.setFont(font);
    hint_text.setCharacterSize(24);
    hint_text.setFillColor(sf::Color::White);
    hint_text.setOutlineColor(sf::Color::Black);
    hint_text.setOutlineThickness(2.f);
  }

  loadTextures();

  circles.reserve(circle_count);
  for (int i = 0; i < circle_count; ++i) {
    circles.emplace_back(circle_radius, static_cast<float>(window_width),
                         static_cast<float>(window_height), top_offset);
  }

  if (!textures.empty()) {
    for (int i = 0; i < circle_count; ++i) {
      const sf::Texture& tex = textures[i % textures.size()];
      circles[i].setTexture(&tex);
    }
  }
}

void Game::loadTextures() {
  for (int i = 0; i < circle_count; ++i) {
    sf::Texture tex;
    std::string path = "circle_" + std::to_string(i) + ".png";
    if (tex.loadFromFile(path)) {
      tex.setSmooth(true);
      textures.push_back(std::move(tex));
    }
  }

  if (game_over_texture.loadFromFile("gameover.png")) {
    game_over_texture.setSmooth(true);
    game_over_texture_loaded = true;
    game_over_sprite.setTexture(game_over_texture);
    sf::Vector2u size = game_over_texture.getSize();
    float scale_x = static_cast<float>(window_width) / size.x;
    float scale_y = static_cast<float>(window_height) / size.y;
    float scale = std::min(scale_x, scale_y);
    game_over_sprite.setScale(scale, scale);
    float w = size.x * scale;
    float h = size.y * scale;
    game_over_sprite.setPosition((window_width - w) / 2.f,
                                 (window_height - h) / 2.f);
  }
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
    processEvents();
    if (!game_over) {
      update(dt);
    }
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::MouseButtonPressed &&
               event.mouseButton.button == sf::Mouse::Left) {
      if (game_over) {
        reset();
      } else {
        handleClick(static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y));
      }
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::R && game_over) {
      reset();
    }
  }
}

void Game::handleClick(float mx, float my) {
  for (auto& c : circles) {
    if (c.contains(mx, my)) {
      c.respawn();
      ++score;
      time_left += hit_bonus;
      return;
    }
  }
  time_left -= miss_penalty;
  if (time_left < 0.f) {
    time_left = 0.f;
  }
}

void Game::update(float dt) {
  time_left -= dt;
  if (time_left <= 0.f) {
    time_left = 0.f;
    game_over = true;
  }
  for (auto& c : circles) {
    c.update(dt);
  }
}

void Game::render() {
  window.clear(sf::Color(15, 15, 30));

  if (game_over) {
    if (game_over_texture_loaded) {
      window.draw(game_over_sprite);
    }
  } else {
    for (auto& c : circles) {
      c.draw(window);
    }
  }

  if (font_loaded) {
    std::ostringstream ss;
    ss << "Score: " << score;
    score_text.setString(ss.str());
    window.draw(score_text);

    std::ostringstream ts;
    ts << "Time: " << std::fixed << std::setprecision(1) << time_left;
    timer_text.setString(ts.str());
    window.draw(timer_text);

    if (game_over) {
      std::ostringstream gs;
      gs << "GAME OVER  " << score;
      game_over_text.setString(gs.str());
      sf::FloatRect bounds = game_over_text.getLocalBounds();
      game_over_text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
      game_over_text.setPosition(static_cast<float>(window_width) / 2.f, 60.f);
      window.draw(game_over_text);

      hint_text.setString("Click or press R to restart");
      sf::FloatRect hb = hint_text.getLocalBounds();
      hint_text.setOrigin(hb.width / 2.f, hb.height / 2.f);
      hint_text.setPosition(static_cast<float>(window_width) / 2.f,
                            static_cast<float>(window_height) - 30.f);
      window.draw(hint_text);
    }
  }

  window.display();
}

void Game::reset() {
  score = 0;
  time_left = start_time;
  game_over = false;
  for (auto& c : circles) {
    c.respawn();
  }
}
