#include "typingGame.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>

TypingGame::TypingGame()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_TITLE),
      targetCharText(font),
      scoreText(font),
      timerText(font),
      gameOverText(font),
      finalScoreText(font),
      comboText(font),
      highScoreText(font),
      hintText(font),
      background(BG_GRADIENT_TYPE, BG_GRADIENT_VERTICES),
      correctSound(nullptr),
      wrongSound(nullptr),
      score(0),
      highScore(0),
      combo(0),
      time_left(START_TIME),
      speed_multiplier(SCALE_NORMAL),
      game_running(true),
      correct_effect(false),
      pulse_timer(0.0f),
      rng(static_cast<unsigned>(std::time(nullptr))),
      charDist(ASCII_MIN, ASCII_MAX),
      bonusDist(COMBO_MIN_VALUE, BONUS_RANGE) {
  if (!font.openFromFile(FONT_PATH)) {
    std::cerr << "Warning: Font not found\n";
  }

  background[0].position = sf::Vector2f(0, 0);
  background[1].position = sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 0);
  background[2].position = sf::Vector2f(0, static_cast<float>(WINDOW_HEIGHT));
  background[3].position = sf::Vector2f(static_cast<float>(WINDOW_WIDTH),
                                        static_cast<float>(WINDOW_HEIGHT));

  background[0].color =
      sf::Color(COLOR_BG_TOP_R, COLOR_BG_TOP_G, COLOR_BG_TOP_B);
  background[1].color =
      sf::Color(COLOR_BG_TOP_R, COLOR_BG_TOP_G, COLOR_BG_TOP_B);
  background[2].color =
      sf::Color(COLOR_BG_BOTTOM_R, COLOR_BG_BOTTOM_G, COLOR_BG_BOTTOM_B);
  background[3].color =
      sf::Color(COLOR_BG_BOTTOM_R, COLOR_BG_BOTTOM_G, COLOR_BG_BOTTOM_B);

  if (correctBuffer.loadFromFile(SOUND_CORRECT)) {
    correctSound = std::make_unique<sf::Sound>(correctBuffer);
  }

  if (wrongBuffer.loadFromFile(SOUND_WRONG)) {
    wrongSound = std::make_unique<sf::Sound>(wrongBuffer);
  }

  loadHighScore();

  targetCharText.setFont(font);
  targetCharText.setCharacterSize(CHAR_SIZE_TARGET);
  targetCharText.setPosition(sf::Vector2f(POS_TARGET_X - CHAR_SIZE_TARGET / 3,
                                          POS_TARGET_Y - CHAR_SIZE_TARGET / 2));

  scoreText.setFont(font);
  scoreText.setCharacterSize(CHAR_SIZE_SCORE);
  scoreText.setFillColor(
      sf::Color(COLOR_SCORE_R, COLOR_SCORE_G, COLOR_SCORE_B));
  scoreText.setPosition(sf::Vector2f(static_cast<float>(POS_SCORE_X),
                                     static_cast<float>(POS_SCORE_Y)));
  scoreText.setStyle(sf::Text::Bold);

  timerText.setFont(font);
  timerText.setCharacterSize(CHAR_SIZE_TIMER);
  timerText.setFillColor(
      sf::Color(COLOR_TIMER_R, COLOR_TIMER_G, COLOR_TIMER_B));
  timerText.setPosition(sf::Vector2f(static_cast<float>(POS_TIMER_X),
                                     static_cast<float>(POS_TIMER_Y)));
  timerText.setStyle(sf::Text::Bold);

  highScoreText.setFont(font);
  highScoreText.setCharacterSize(CHAR_SIZE_HIGHSCORE);
  highScoreText.setFillColor(
      sf::Color(COLOR_HIGHSCORE_R, COLOR_HIGHSCORE_G, COLOR_HIGHSCORE_B));
  highScoreText.setPosition(sf::Vector2f(static_cast<float>(POS_HIGHSCORE_X),
                                         static_cast<float>(POS_HIGHSCORE_Y)));

  gameOverText.setFont(font);
  gameOverText.setCharacterSize(CHAR_SIZE_GAMEOVER);
  gameOverText.setFillColor(
      sf::Color(COLOR_GAMEOVER_R, COLOR_GAMEOVER_G, COLOR_GAMEOVER_B));
  gameOverText.setString(TEXT_GAME_OVER);
  gameOverText.setPosition(sf::Vector2f(static_cast<float>(POS_GAMEOVER_X),
                                        static_cast<float>(POS_GAMEOVER_Y)));
  gameOverText.setStyle(sf::Text::Bold);

  finalScoreText.setFont(font);
  finalScoreText.setCharacterSize(CHAR_SIZE_FINAL);
  finalScoreText.setFillColor(sf::Color::White);
  finalScoreText.setPosition(sf::Vector2f(static_cast<float>(POS_FINAL_X),
                                          static_cast<float>(POS_FINAL_Y)));

  comboText.setFont(font);
  comboText.setCharacterSize(CHAR_SIZE_COMBO);
  comboText.setFillColor(
      sf::Color(COLOR_COMBO_R, COLOR_COMBO_G, COLOR_COMBO_B));
  comboText.setPosition(sf::Vector2f(static_cast<float>(POS_COMBO_X),
                                     static_cast<float>(POS_COMBO_Y)));
  comboText.setStyle(sf::Text::Bold);

  hintText.setFont(font);
  hintText.setCharacterSize(CHAR_SIZE_HINT);
  hintText.setStyle(sf::Text::Italic);

  generateRandomChar();
  updateUI();
}

void TypingGame::playSound(bool correct) {
  if (correct && correctSound) {
    correctSound->play();
  } else if (!correct && wrongSound) {
    wrongSound->play();
  }
}

void TypingGame::loadHighScore() {
  std::ifstream file(HIGHSCORE_FILE);
  if (file.is_open()) {
    file >> highScore;
    file.close();
  }
}

void TypingGame::saveHighScore() {
  std::ofstream file(HIGHSCORE_FILE);
  if (file.is_open()) {
    file << highScore;
    file.close();
  }
}

char TypingGame::convertRussianToEnglish(char input) {
  std::string russianLower = RUSSIAN_LOWER;
  std::string englishLower = ENGLISH_LOWER;
  std::string russianUpper = RUSSIAN_UPPER;
  std::string englishUpper = ENGLISH_UPPER;

  for (size_t i = 0; i < russianLower.length(); ++i) {
    if (input == russianLower[i]) return englishLower[i];
  }
  for (size_t i = 0; i < russianUpper.length(); ++i) {
    if (input == russianUpper[i]) return englishUpper[i];
  }
  return input;
}

std::string TypingGame::getCharCategory(char c) {
  if (c >= '0' && c <= '9') return "DIGIT";
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return "LETTER";
  return "SYMBOL";
}

sf::Color TypingGame::getCharColor(char c) {
  if (c >= '0' && c <= '9') {
    return sf::Color(COLOR_DIGIT_R, COLOR_DIGIT_G, COLOR_DIGIT_B);
  }
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
    return sf::Color(COLOR_LETTER_R, COLOR_LETTER_G, COLOR_LETTER_B);
  }
  return sf::Color(COLOR_SYMBOL_R, COLOR_SYMBOL_G, COLOR_SYMBOL_B);
}

void TypingGame::generateRandomChar() {
  int ascii_code = charDist(rng);
  current_char = static_cast<char>(ascii_code);
  targetCharText.setString(std::string(1, current_char));
  targetCharText.setFillColor(getCharColor(current_char));

  std::string category = getCharCategory(current_char);
  if (category == "DIGIT") {
    hintText.setString(HINT_DIGIT);
    hintText.setFillColor(
        sf::Color(COLOR_DIGIT_R, COLOR_DIGIT_G, COLOR_DIGIT_B));
  } else if (category == "LETTER") {
    hintText.setString(HINT_LETTER);
    hintText.setFillColor(
        sf::Color(COLOR_LETTER_R, COLOR_LETTER_G, COLOR_LETTER_B));
  } else {
    hintText.setString(HINT_SYMBOL);
    hintText.setFillColor(
        sf::Color(COLOR_SYMBOL_R, COLOR_SYMBOL_G, COLOR_SYMBOL_B));
  }

  float hintWidth = hintText.getLocalBounds().size.x;
  hintText.setPosition(sf::Vector2f((WINDOW_WIDTH - hintWidth) / 2,
                                    static_cast<float>(POS_HINT_Y)));
}

void TypingGame::updateUI() {
  scoreText.setString(TEXT_SCORE + std::to_string(score));
  timerText.setString(TEXT_TIME + std::to_string(static_cast<int>(time_left)));
  highScoreText.setString(TEXT_BEST + std::to_string(highScore));

  if (combo >= COMBO_MIN_FOR_DISPLAY) {
    comboText.setString(COMBO_PREFIX + std::to_string(combo));
    comboText.setFillColor(
        sf::Color(COLOR_COMBO_R, COLOR_COMBO_G, COLOR_COMBO_B));
  } else {
    comboText.setString("");
  }

  if (time_left < TIME_LOW_THRESHOLD) {
    pulse_timer += PULSE_INCREMENT;
    int g = COLOR_TIMER_G - PULSE_AMP +
            static_cast<int>(PULSE_AMP * std::sin(pulse_timer * PULSE_FREQ));
    if (g < PULSE_G_MIN) g = PULSE_G_MIN;
    timerText.setFillColor(sf::Color(COLOR_TIMER_LOW_R, g, COLOR_TIMER_LOW_B));
  } else {
    timerText.setFillColor(
        sf::Color(COLOR_TIMER_R, COLOR_TIMER_G, COLOR_TIMER_B));
  }
}

void TypingGame::drawBackground() { window.draw(background); }

void TypingGame::draw() {
  drawBackground();

  if (game_running) {
    if (correct_effect &&
        effectClock.getElapsedTime().asSeconds() < EFFECT_DURATION) {
      float scale = SCALE_NORMAL + (EFFECT_DURATION -
                                    effectClock.getElapsedTime().asSeconds()) *
                                       EFFECT_SCALE_FACTOR;
      targetCharText.setScale(sf::Vector2f(scale, scale));
    } else {
      targetCharText.setScale(sf::Vector2f(SCALE_NORMAL, SCALE_NORMAL));
      correct_effect = false;
    }

    window.draw(targetCharText);
    window.draw(hintText);
    window.draw(scoreText);
    window.draw(timerText);
    window.draw(highScoreText);
    window.draw(comboText);
  } else {
    window.draw(gameOverText);
    finalScoreText.setString(TEXT_FINAL_SCORE + std::to_string(score));
    window.draw(finalScoreText);
    window.draw(highScoreText);
  }

  window.display();
}

void TypingGame::run() {
  game_clock.restart();
  effectClock.restart();

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      if (game_running && event->is<sf::Event::TextEntered>()) {
        const auto& textEvent = event->getIf<sf::Event::TextEntered>();
        char input = static_cast<char>(textEvent->unicode);

        char converted = convertRussianToEnglish(input);
        bool isMatch = (std::tolower(converted) == std::tolower(current_char));

        if (isMatch) {
          playSound(true);
          correct_effect = true;
          effectClock.restart();

          int pointsGained =
              SCORE_MULTIPLIER_BASE * std::max(COMBO_MIN_VALUE, combo);
          score += pointsGained;
          combo++;

          int bonus = bonusDist(rng);
          if (bonus <= BONUS_CHANCE) {
            if (bonus <= BONUS_TIME_THRESHOLD) {
              time_left += TIME_BONUS;
              comboText.setString(TEXT_BONUS_TIME);
              comboText.setFillColor(sf::Color(COLOR_BONUS_GREEN_R,
                                               COLOR_BONUS_GREEN_G,
                                               COLOR_BONUS_GREEN_B));
            } else if (bonus <= BONUS_POINTS_THRESHOLD) {
              score += SCORE_BONUS;
              comboText.setString(TEXT_BONUS_POINTS);
              comboText.setFillColor(sf::Color(COLOR_BONUS_YELLOW_R,
                                               COLOR_BONUS_YELLOW_G,
                                               COLOR_BONUS_YELLOW_B));
            } else {
              combo += 2;
              comboText.setString(TEXT_BONUS_COMBO);
              comboText.setFillColor(sf::Color(COLOR_BONUS_MAGENTA_R,
                                               COLOR_BONUS_MAGENTA_G,
                                               COLOR_BONUS_MAGENTA_B));
            }
          }

          speed_multiplier += SPEED_INCREASE;
          generateRandomChar();
        } else {
          playSound(false);
          time_left -= TIME_PENALTY;
          combo = 0;
          if (time_left < 0) time_left = 0;

          comboText.setString(TEXT_MISS);
          comboText.setFillColor(
              sf::Color(COLOR_MISS_R, COLOR_MISS_G, COLOR_MISS_B));
        }
        updateUI();
      }
    }

    if (game_running) {
      float delta_time = game_clock.restart().asSeconds();
      time_left -= delta_time * speed_multiplier;
      updateUI();

      if (time_left <= 0.0f) {
        time_left = 0.0f;
        game_running = false;
        updateUI();

        if (score > highScore) {
          highScore = score;
          saveHighScore();
        }
      }
    }

    draw();
  }
}
