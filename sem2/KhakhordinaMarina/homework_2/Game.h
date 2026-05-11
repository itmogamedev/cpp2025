#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

#define WIN_W 600
#define WIN_H 400
#define BG_RGB 20
#define START_TIME 10.0f
#define PENALTY 1.5f
#define ASCII_LIMIT 128
#define SCORE_OFFSET 100.0f
#define CHAR_X 275.0f
#define CHAR_Y 80.0f
#define SCORE_X 20.0f
#define SCORE_Y 20.0f
#define TIMER_X 450.0f
#define OVER_X 150.0f
#define OVER_Y 150.0f

class Game {
public:
  Game();
  void run();

private:
  void processEvents();
  void update(sf::Time dt);
  void render();
  void generateNewTarget();
  void resetGame();

  sf::RenderWindow mWindow;
  sf::Font mFont;
  sf::Text mTargetText, mScoreText, mTimerText, mGameOverText, mFinalScoreText;

  char mCurrentTarget;
  int mScore;
  float mTimeLimit;
  bool mIsGameOver;
};

#endif
