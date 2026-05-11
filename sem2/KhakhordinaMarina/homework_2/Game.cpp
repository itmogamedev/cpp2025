#include "Game.h"

Game::Game() :
  mWindow(sf::VideoMode(WIN_W, WIN_H), "Fast Typer"),
  mScore(0), mTimeLimit(START_TIME), mIsGameOver(false)
{
  mFont.loadFromFile("Bitrimus.ttf");

  mTargetText.setFont(mFont);
  mTargetText.setCharacterSize(150);
  mTargetText.setFillColor(sf::Color::Yellow);
  mTargetText.setPosition(CHAR_X, CHAR_Y); 

  mScoreText.setFont(mFont);
  mScoreText.setCharacterSize(25);
  mScoreText.setPosition(SCORE_X, SCORE_Y);
  mScoreText.setFillColor(sf::Color::Green);

  mTimerText.setFont(mFont);
  mTimerText.setCharacterSize(25);
  mTimerText.setPosition(TIMER_X, SCORE_Y);
  mTimerText.setFillColor(sf::Color::Green);

  mGameOverText.setFont(mFont);
  mGameOverText.setCharacterSize(60);
  mGameOverText.setFillColor(sf::Color::Red);
  mGameOverText.setString("GAME OVER");
  mGameOverText.setPosition(OVER_X, OVER_Y);

  mFinalScoreText.setFont(mFont);
  mFinalScoreText.setCharacterSize(30);
  mFinalScoreText.setFillColor(sf::Color::White);
  mFinalScoreText.setPosition(OVER_X, OVER_Y + SCORE_OFFSET); 

  srand(static_cast<unsigned int>(time(NULL)));
  generateNewTarget();
}

void Game::generateNewTarget() {
  const char pool[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  mCurrentTarget = pool[rand() % (sizeof(pool) - 1)];
  mTargetText.setString(mCurrentTarget);
}

void Game::processEvents() {
  sf::Event e;
  while (mWindow.pollEvent(e)) {
    if (e.type == sf::Event::Closed) mWindow.close();

    if (e.type == sf::Event::TextEntered && !mIsGameOver) {
      if (e.text.unicode < ASCII_LIMIT) {
        char typed = static_cast<char>(e.text.unicode);
        if (toupper(typed) == mCurrentTarget) {
          mScore++;
          generateNewTarget();
        }
        else {
          mTimeLimit -= PENALTY;
        }
      }
    }
    if (mIsGameOver && e.type == sf::Event::KeyPressed) {
      if (e.key.code == sf::Keyboard::Enter) resetGame();
    }
  }
}

void Game::update(sf::Time dt) {
  if (mIsGameOver) return;

  mTimeLimit -= dt.asSeconds();
  if (mTimeLimit <= 0) {
    mTimeLimit = 0;
    mIsGameOver = true;
    mFinalScoreText.setString("Score: " + std::to_string(mScore) + "\n[ENTER] RESTART");
  }
  mScoreText.setString("Score: " + std::to_string(mScore));
  mTimerText.setString("Time: " + std::to_string(static_cast<int>(mTimeLimit)));
}

void Game::render() {
  mWindow.clear(sf::Color::Black);
  mWindow.draw(mScoreText);
  mWindow.draw(mTimerText);
  if (mIsGameOver) {
    mWindow.draw(mGameOverText);
    mWindow.draw(mFinalScoreText);
  }
  else {
    mWindow.draw(mTargetText);
  }
  mWindow.display();
}

void Game::resetGame() {
  mScore = 0;
  mTimeLimit = START_TIME;
  mIsGameOver = false;
  generateNewTarget();
}

void Game::run() {
  sf::Clock clock;
  while (mWindow.isOpen()) {
    processEvents();
    update(clock.restart());
    render();
  }
}


