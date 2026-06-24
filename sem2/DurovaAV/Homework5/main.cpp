#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 8.0f;
const int PLAYER_RADIUS = 20;
const int ASTEROID_RADIUS = 25;
const int BULLET_RADIUS = 5;

const float BASE_SHOOT_DELAY = 0.8f;
const float MIN_SHOOT_DELAY = 0.25f;
const float BASE_ASTEROID_SPEED = 2.5f;
const float MAX_ASTEROID_SPEED = 10.0f;
const float SPEED_INCREMENT_PER_SECOND = 0.15f;

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Cosmic Shooter");
  window.setFramerateLimit(60);

  // Корабль
  sf::CircleShape player(static_cast<float>(PLAYER_RADIUS));
  player.setFillColor(sf::Color::Cyan);
  player.setOutlineColor(sf::Color::White);
  player.setOutlineThickness(2.0f);
  player.setOrigin(static_cast<float>(PLAYER_RADIUS),
                   static_cast<float>(PLAYER_RADIUS));
  player.setPosition(static_cast<float>(WINDOW_WIDTH) / 2.0f,
                     static_cast<float>(WINDOW_HEIGHT) - 50.0f);

  std::vector<sf::CircleShape> bullets;
  std::vector<sf::CircleShape> asteroids;
  std::vector<float> asteroidSpeeds;

  int lives = 3;
  int score = 0;
  float gameTime = 0.0f;
  float currentAsteroidSpeed = BASE_ASTEROID_SPEED;
  float shootCooldown = 0.0f;
  float currentShootDelay = BASE_SHOOT_DELAY;
  float asteroidSpawnTimer = 0.0f;
  const float ASTEROID_SPAWN_DELAY = 0.7f;

  // Шрифт
  sf::Font font;
  bool hasFont = false;

  if (font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
    hasFont = true;
  } else if (font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
    hasFont = true;
  } else if (font.loadFromFile("C:/Windows/Fonts/consola.ttf")) {
    hasFont = true;
  }

  // Текст
  sf::Text scoreText;
  sf::Text livesText;
  sf::Text speedText;
  sf::Text gameOverText;
  sf::Text finalScoreText;
  sf::Text restartText;

  if (hasFont) {
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.0f, 10.0f);

    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10.0f, 40.0f);

    speedText.setFont(font);
    speedText.setCharacterSize(18);
    speedText.setFillColor(sf::Color(200, 200, 100));
    speedText.setPosition(10.0f, 70.0f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(static_cast<float>(WINDOW_WIDTH) / 2.0f - 120.0f,
                             static_cast<float>(WINDOW_HEIGHT) / 2.0f - 50.0f);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(32);
    finalScoreText.setFillColor(sf::Color::White);

    restartText.setFont(font);
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::White);
    restartText.setString("Press R to restart | ESC to exit");
    restartText.setPosition(static_cast<float>(WINDOW_WIDTH) / 2.0f - 180.0f,
                            static_cast<float>(WINDOW_HEIGHT) / 2.0f + 70.0f);
  }

  // Полоска перезарядки
  sf::RectangleShape reloadBarBg(sf::Vector2f(150.0f, 12.0f));
  reloadBarBg.setFillColor(sf::Color(50, 50, 50));
  reloadBarBg.setOutlineColor(sf::Color(150, 150, 150));
  reloadBarBg.setOutlineThickness(1.0f);
  reloadBarBg.setPosition(static_cast<float>(WINDOW_WIDTH) - 170.0f, 40.0f);

  sf::RectangleShape reloadBarFill(sf::Vector2f(150.0f, 10.0f));
  reloadBarFill.setFillColor(sf::Color::Green);
  reloadBarFill.setPosition(static_cast<float>(WINDOW_WIDTH) - 169.0f, 41.0f);

  sf::Text reloadText;
  if (hasFont) {
    reloadText.setFont(font);
    reloadText.setCharacterSize(14);
    reloadText.setFillColor(sf::Color::White);
    reloadText.setString("RELOAD");
    reloadText.setPosition(static_cast<float>(WINDOW_WIDTH) - 165.0f, 17.0f);
  }

  // Полоска сложности
  sf::RectangleShape difficultyBarBg(sf::Vector2f(200.0f, 12.0f));
  difficultyBarBg.setFillColor(sf::Color(50, 50, 50));
  difficultyBarBg.setOutlineColor(sf::Color(150, 150, 150));
  difficultyBarBg.setOutlineThickness(1.0f);
  difficultyBarBg.setPosition(10.0f, 95.0f);

  sf::RectangleShape difficultyBarFill(sf::Vector2f(200.0f, 10.0f));
  difficultyBarFill.setFillColor(sf::Color(255, 165, 0));
  difficultyBarFill.setPosition(11.0f, 96.0f);

  sf::Clock clock;
  bool gameRunning = true;
  bool gameOver = false;

  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();
    if (deltaTime > 0.033f) deltaTime = 0.033f;

    if (shootCooldown > 0) shootCooldown -= deltaTime;
    if (asteroidSpawnTimer > 0) asteroidSpawnTimer -= deltaTime;

    // Сложность
    if (gameRunning && lives > 0) {
      gameTime += deltaTime;
      currentAsteroidSpeed =
          BASE_ASTEROID_SPEED + gameTime * SPEED_INCREMENT_PER_SECOND;
      if (currentAsteroidSpeed > MAX_ASTEROID_SPEED) {
        currentAsteroidSpeed = MAX_ASTEROID_SPEED;
      }
    }

    // События
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
        if (gameOver && event.key.code == sf::Keyboard::R) {
          player.setPosition(static_cast<float>(WINDOW_WIDTH) / 2.0f,
                             static_cast<float>(WINDOW_HEIGHT) - 50.0f);
          bullets.clear();
          asteroids.clear();
          asteroidSpeeds.clear();
          lives = 3;
          score = 0;
          gameTime = 0.0f;
          currentAsteroidSpeed = BASE_ASTEROID_SPEED;
          currentShootDelay = BASE_SHOOT_DELAY;
          shootCooldown = 0.0f;
          asteroidSpawnTimer = 0.0f;
          gameRunning = true;
          gameOver = false;
        }
      }
    }

    if (gameRunning && lives > 0) {
      // Управление
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.move(-PLAYER_SPEED, 0);
        if (player.getPosition().x < static_cast<float>(PLAYER_RADIUS)) {
          player.setPosition(static_cast<float>(PLAYER_RADIUS),
                             player.getPosition().y);
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.move(PLAYER_SPEED, 0);
        if (player.getPosition().x > static_cast<float>(WINDOW_WIDTH) -
                                         static_cast<float>(PLAYER_RADIUS)) {
          player.setPosition(static_cast<float>(WINDOW_WIDTH) -
                                 static_cast<float>(PLAYER_RADIUS),
                             player.getPosition().y);
        }
      }

      // Стрельба
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
          shootCooldown <= 0) {
        shootCooldown = currentShootDelay;
        sf::CircleShape bullet(static_cast<float>(BULLET_RADIUS));
        bullet.setFillColor(sf::Color::Yellow);
        bullet.setOrigin(static_cast<float>(BULLET_RADIUS),
                         static_cast<float>(BULLET_RADIUS));
        bullet.setPosition(
            player.getPosition().x,
            player.getPosition().y - static_cast<float>(PLAYER_RADIUS));
        bullets.push_back(bullet);
      }

      // Спавн астероидов
      if (asteroidSpawnTimer <= 0) {
        asteroidSpawnTimer = ASTEROID_SPAWN_DELAY;
        sf::CircleShape asteroid(static_cast<float>(ASTEROID_RADIUS));
        asteroid.setFillColor(sf::Color(139, 69, 19));
        asteroid.setOutlineColor(sf::Color(100, 50, 10));
        asteroid.setOutlineThickness(2.0f);
        asteroid.setOrigin(static_cast<float>(ASTEROID_RADIUS),
                           static_cast<float>(ASTEROID_RADIUS));
        float x = static_cast<float>(std::rand() %
                                         (WINDOW_WIDTH - 2 * ASTEROID_RADIUS) +
                                     ASTEROID_RADIUS);
        asteroid.setPosition(x, -static_cast<float>(ASTEROID_RADIUS));
        asteroids.push_back(asteroid);
        asteroidSpeeds.push_back(currentAsteroidSpeed);
      }

      // Обновление снарядов
      for (int i = 0; i < static_cast<int>(bullets.size()); i++) {
        bullets[i].move(0, -12);
        if (bullets[i].getPosition().y + BULLET_RADIUS < 0) {
          bullets.erase(bullets.begin() + i);
          i--;
        }
      }

      // Обновление астероидов
      for (int i = 0; i < static_cast<int>(asteroids.size()); i++) {
        asteroids[i].move(0, asteroidSpeeds[i]);
        if (asteroids[i].getPosition().y - ASTEROID_RADIUS > WINDOW_HEIGHT) {
          asteroids.erase(asteroids.begin() + i);
          asteroidSpeeds.erase(asteroidSpeeds.begin() + i);
          i--;
        }
      }

      // Столкновения снарядов с астероидами
      for (int i = 0; i < static_cast<int>(bullets.size()); i++) {
        for (int j = 0; j < static_cast<int>(asteroids.size()); j++) {
          float dx = bullets[i].getPosition().x - asteroids[j].getPosition().x;
          float dy = bullets[i].getPosition().y - asteroids[j].getPosition().y;
          float distance = std::sqrt(dx * dx + dy * dy);
          if (distance < BULLET_RADIUS + ASTEROID_RADIUS) {
            bullets.erase(bullets.begin() + i);
            asteroids.erase(asteroids.begin() + j);
            asteroidSpeeds.erase(asteroidSpeeds.begin() + j);
            score += 10;

            currentShootDelay =
                BASE_SHOOT_DELAY - (static_cast<float>(score) / 80.0f) *
                                       (BASE_SHOOT_DELAY - MIN_SHOOT_DELAY);
            if (currentShootDelay < MIN_SHOOT_DELAY) {
              currentShootDelay = MIN_SHOOT_DELAY;
            }

            i--;
            break;
          }
        }
      }

      // Столкновения корабля с астероидами
      for (int j = 0; j < static_cast<int>(asteroids.size()); j++) {
        float dx = player.getPosition().x - asteroids[j].getPosition().x;
        float dy = player.getPosition().y - asteroids[j].getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance < PLAYER_RADIUS + ASTEROID_RADIUS) {
          asteroids.erase(asteroids.begin() + j);
          asteroidSpeeds.erase(asteroidSpeeds.begin() + j);
          lives--;
          j--;

          player.setFillColor(sf::Color::Red);
        }
      }

      if (player.getFillColor() == sf::Color::Red) {
        player.setFillColor(sf::Color::Cyan);
      }

      if (lives <= 0) {
        gameRunning = false;
        gameOver = true;
      }
    }

    // Отрисовка
    window.clear(sf::Color(10, 10, 30));

    // Звёзды
    static sf::CircleShape star(1.5f);
    star.setFillColor(sf::Color::White);
    for (int i = 0; i < 80; i++) {
      star.setPosition(static_cast<float>(std::rand() % WINDOW_WIDTH),
                       static_cast<float>(std::rand() % WINDOW_HEIGHT));
      window.draw(star);
    }

    window.draw(player);

    for (auto& bullet : bullets) {
      window.draw(bullet);
    }

    for (auto& asteroid : asteroids) {
      window.draw(asteroid);
    }

    // Текст и полоски
    if (hasFont) {
      scoreText.setString("SCORE: " + std::to_string(score));
      livesText.setString("LIVES: " + std::to_string(lives));
      speedText.setString(
          "ASTEROID SPEED: " +
          std::to_string(static_cast<int>(currentAsteroidSpeed * 10)) + "%");
      window.draw(scoreText);
      window.draw(livesText);
      window.draw(speedText);
      window.draw(reloadText);
    }

    // Полоска перезарядки
    float reloadPercent = 1.0f;
    if (currentShootDelay > 0) {
      reloadPercent = shootCooldown / currentShootDelay;
      if (reloadPercent < 0) reloadPercent = 0;
      if (reloadPercent > 1) reloadPercent = 1;
    }
    float reloadWidth = 150.0f * (1.0f - reloadPercent);
    reloadBarFill.setSize(sf::Vector2f(reloadWidth, 10.0f));
    if (shootCooldown <= 0) {
      reloadBarFill.setFillColor(sf::Color::Green);
    } else if (reloadPercent > 0.7f) {
      reloadBarFill.setFillColor(sf::Color(255, 100, 100));
    } else if (reloadPercent > 0.3f) {
      reloadBarFill.setFillColor(sf::Color(255, 200, 100));
    } else {
      reloadBarFill.setFillColor(sf::Color(100, 255, 100));
    }
    window.draw(reloadBarBg);
    window.draw(reloadBarFill);

    // Полоска сложности
    float difficultyPercent = (currentAsteroidSpeed - BASE_ASTEROID_SPEED) /
                              (MAX_ASTEROID_SPEED - BASE_ASTEROID_SPEED);
    if (difficultyPercent < 0) difficultyPercent = 0;
    if (difficultyPercent > 1) difficultyPercent = 1;
    float difficultyWidth = 200.0f * difficultyPercent;
    difficultyBarFill.setSize(sf::Vector2f(difficultyWidth, 10.0f));
    if (difficultyPercent < 0.33f) {
      difficultyBarFill.setFillColor(sf::Color(0, 255, 0));
    } else if (difficultyPercent < 0.66f) {
      difficultyBarFill.setFillColor(sf::Color(255, 255, 0));
    } else {
      difficultyBarFill.setFillColor(sf::Color(255, 0, 0));
    }
    window.draw(difficultyBarBg);
    window.draw(difficultyBarFill);

    if (gameOver) {
      finalScoreText.setString("FINAL SCORE: " + std::to_string(score));
      finalScoreText.setPosition(
          static_cast<float>(WINDOW_WIDTH) / 2.0f - 110.0f,
          static_cast<float>(WINDOW_HEIGHT) / 2.0f + 20.0f);
      window.draw(gameOverText);
      window.draw(finalScoreText);
      window.draw(restartText);
    }

    window.display();
  }

  return 0;
}
