#ifndef TYPING_GAME_H_
#define TYPING_GAME_H_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <string>

// Window
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Typing Trainer"

// File paths
#define FONT_PATH "D:/For cpp/AlwaysType/x64/Debug/arial.ttf"
#define SOUND_CORRECT "D:/For cpp/AlwaysType/x64/Debug/correct.wav"
#define SOUND_WRONG "D:/For cpp/AlwaysType/x64/Debug/wrong.wav"
#define HIGHSCORE_FILE "highscore.txt"

// Font sizes
#define CHAR_SIZE_TARGET 180
#define CHAR_SIZE_SCORE 28
#define CHAR_SIZE_TIMER 28
#define CHAR_SIZE_GAMEOVER 60
#define CHAR_SIZE_FINAL 40
#define CHAR_SIZE_COMBO 24
#define CHAR_SIZE_HIGHSCORE 22
#define CHAR_SIZE_HINT 24

// Positions
#define POS_TARGET_X 400
#define POS_TARGET_Y 250
#define POS_SCORE_X 20
#define POS_SCORE_Y 20
#define POS_TIMER_X 20
#define POS_TIMER_Y 55
#define POS_HIGHSCORE_X 620
#define POS_HIGHSCORE_Y 20
#define POS_COMBO_X 20
#define POS_COMBO_Y 100
#define POS_HINT_X 400
#define POS_HINT_Y 420
#define POS_GAMEOVER_X 250
#define POS_GAMEOVER_Y 250
#define POS_FINAL_X 250
#define POS_FINAL_Y 320

// Game mechanics
#define START_TIME 15.0f
#define TIME_PENALTY 1.0f
#define TIME_BONUS 3.0f
#define SPEED_INCREASE 0.03f
#define SCORE_BONUS 20
#define BONUS_CHANCE 8
#define TIME_LOW_THRESHOLD 3.0f
#define COMBO_MIN_FOR_DISPLAY 2
#define SCORE_MULTIPLIER_BASE 10
#define COMBO_MIN_VALUE 1

// Animation
#define PULSE_INCREMENT 0.15f
#define PULSE_AMP 40
#define PULSE_FREQ 12
#define EFFECT_DURATION 0.12f
#define EFFECT_SCALE_FACTOR 3.0f
#define SCALE_NORMAL 1.0f
#define PULSE_G_MIN 0

// Ranges
#define ASCII_MIN 33
#define ASCII_MAX 126
#define BONUS_RANGE 100
#define BONUS_TIME_THRESHOLD 3
#define BONUS_POINTS_THRESHOLD 6

// Gradients
#define BG_GRADIENT_VERTICES 4
#define BG_GRADIENT_TYPE sf::PrimitiveType::TriangleStrip

// Russian keyboard conversion
#define RUSSIAN_UPPER "®…÷” ≈Õ√ÿŸ«’⁄‘€¬¿œ–ŒÀƒ∆›ﬂ◊—Ã»“‹¡ﬁ"
#define RUSSIAN_LOWER "∏ÈˆÛÍÂÌ„¯˘Áı˙Ù˚‚‡ÔÓÎ‰Ê˝ˇ˜ÒÏËÚ¸·˛"
#define ENGLISH_UPPER "~QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?"
#define ENGLISH_LOWER "`qwertyuiop[]asdfghjkl;'zxcvbnm,./"

// UI text
#define HINT_DIGIT "[  D I G I T  ]"
#define HINT_LETTER "[  L E T T E R  ]"
#define HINT_SYMBOL "[  S Y M B O L  ]"
#define TEXT_SCORE "Score: "
#define TEXT_TIME "Time: "
#define TEXT_BEST "Best: "
#define TEXT_GAME_OVER "GAME OVER"
#define TEXT_FINAL_SCORE "Final Score: "
#define TEXT_MISS "MISS!"
#define TEXT_BONUS_TIME "+3 SEC!"
#define TEXT_BONUS_POINTS "+20 PTS!"
#define TEXT_BONUS_COMBO "SUPER COMBO!"
#define COMBO_PREFIX "COMBO x"

// Colors - Background
#define COLOR_BG_TOP_R 15
#define COLOR_BG_TOP_G 15
#define COLOR_BG_TOP_B 35
#define COLOR_BG_BOTTOM_R 35
#define COLOR_BG_BOTTOM_G 25
#define COLOR_BG_BOTTOM_B 55

// Colors - Text
#define COLOR_SCORE_R 120
#define COLOR_SCORE_G 255
#define COLOR_SCORE_B 120
#define COLOR_TIMER_R 255
#define COLOR_TIMER_G 220
#define COLOR_TIMER_B 100
#define COLOR_TIMER_LOW_R 255
#define COLOR_TIMER_LOW_B 50
#define COLOR_GAMEOVER_R 255
#define COLOR_GAMEOVER_G 70
#define COLOR_GAMEOVER_B 70
#define COLOR_HIGHSCORE_R 255
#define COLOR_HIGHSCORE_G 180
#define COLOR_HIGHSCORE_B 100
#define COLOR_COMBO_R 100
#define COLOR_COMBO_G 200
#define COLOR_COMBO_B 255

// Colors - Characters
#define COLOR_DIGIT_R 100
#define COLOR_DIGIT_G 180
#define COLOR_DIGIT_B 255
#define COLOR_LETTER_R 180
#define COLOR_LETTER_G 180
#define COLOR_LETTER_B 180
#define COLOR_SYMBOL_R 255
#define COLOR_SYMBOL_G 220
#define COLOR_SYMBOL_B 100

// Colors - Effects
#define COLOR_MISS_R 255
#define COLOR_MISS_G 0
#define COLOR_MISS_B 0
#define COLOR_BONUS_GREEN_R 0
#define COLOR_BONUS_GREEN_G 255
#define COLOR_BONUS_GREEN_B 0
#define COLOR_BONUS_YELLOW_R 255
#define COLOR_BONUS_YELLOW_G 255
#define COLOR_BONUS_YELLOW_B 0
#define COLOR_BONUS_MAGENTA_R 255
#define COLOR_BONUS_MAGENTA_G 0
#define COLOR_BONUS_MAGENTA_B 255

class TypingGame {
 public:
  TypingGame();
  void run();

 private:
  void generateRandomChar();
  void updateUI();
  void drawBackground();
  void draw();
  void loadHighScore();
  void saveHighScore();
  void playSound(bool correct);

  char convertRussianToEnglish(char input);
  std::string getCharCategory(char c);
  sf::Color getCharColor(char c);

  sf::RenderWindow window;
  sf::Font font;
  sf::Text targetCharText;
  sf::Text scoreText;
  sf::Text timerText;
  sf::Text gameOverText;
  sf::Text finalScoreText;
  sf::Text comboText;
  sf::Text highScoreText;
  sf::Text hintText;

  sf::VertexArray background;

  sf::SoundBuffer correctBuffer;
  sf::SoundBuffer wrongBuffer;
  std::unique_ptr<sf::Sound> correctSound;
  std::unique_ptr<sf::Sound> wrongSound;

  char current_char;
  int score;
  int highScore;
  int combo;
  float time_left;
  float speed_multiplier;
  bool game_running;
  bool correct_effect;
  float pulse_timer;

  sf::Clock game_clock;
  sf::Clock effectClock;

  std::mt19937 rng;
  std::uniform_int_distribution<int> charDist;
  std::uniform_int_distribution<int> bonusDist;
};

#endif
