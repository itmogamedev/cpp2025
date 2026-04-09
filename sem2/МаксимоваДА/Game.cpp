#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <string>

Game::Game()
{
  srand(static_cast<unsigned>(time(nullptr)));
  font.loadFromFile("fonts/ofont.ru_Geoform.ttf");
  init();
}

void Game::init()
{
  score = 0;
  time_left = 30.0f;
  game_time = 30.0f;
  is_game_over = false;
  generateNewChar();
  updateTexts();
}

void Game::generateNewChar()
{
  int type = rand() % 2;

  if (type == 0) {
	current_char = 'A' + (rand() % 26);
  }
  else {
	current_char = '0' + (rand() % 10);
  }
}

void Game::updateTexts()
{
  current_char_text.setString(std::string(1, current_char));

  score_text.setString("score: " + std::to_string(score));

  int seconds = static_cast<int>(time_left);
  timer_text.setString("time: " + std::to_string(seconds));

  if (isGameOver()) 
  {
	game_over_text.setString("       time's up!\n     final score: " + std::to_string(score) +
			"\n\npress R to restart");
  }
}

void Game::handleInput(sf::Keyboard::Key key, bool shiftPressed)
{
  if (isGameOver() && key == sf::Keyboard::R) {
	init();
	return;
  }

  char pressedChar = '\0';

  if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
	pressedChar = 'A' + (key - sf::Keyboard::A);
  }
  else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
	pressedChar = '0' + (key - sf::Keyboard::Num0);
  }

  if (pressedChar != '\0') {
	if (pressedChar == current_char) {
	  score++;
	  generateNewChar();
	  updateTexts();
	}
	else {
	  time_left -= 2.0f;
	  if (time_left <= 0.0f) {
		time_left = 0.0f;
		is_game_over = true;
	    updateTexts();
		}
	  }
	}
}

void Game::update(float deltaTime)
{
  if (!isGameOver() && time_left > 0.0f) {
    time_left -= deltaTime;
    if (time_left < 0.0f) time_left = 0.0f;
    updateTexts();
        
    if (time_left <= 0.0f) {
	  is_game_over = true;
      updateTexts();
    }
  }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  sf::RectangleShape background(sf::Vector2f(800, 600));
  background.setFillColor(sf::Color(229, 204, 255));
  target.draw(background, states);

  sf::Text displayChar("", font, 180);
  displayChar.setFillColor(sf::Color(204, 0, 102));
  displayChar.setString(current_char_text.getString());

  sf::FloatRect textRect = displayChar.getLocalBounds();
  displayChar.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
  displayChar.setPosition(400, 280);
  target.draw(displayChar, states);

  sf::RectangleShape frame(sf::Vector2f(200, 200));
  frame.setOutlineThickness(3.f);
  frame.setOutlineColor(sf::Color(204, 0, 102));
  frame.setFillColor(sf::Color::Transparent);
  frame.setPosition(300, 180);
  target.draw(frame, states);

  sf::Text score("", font, 36);
  score.setFillColor(sf::Color(76, 0, 153));
  score.setString(score_text.getString());
  score.setPosition(30, 30);
  target.draw(score, states);

  sf::Text timer("", font, 36);
  timer.setFillColor(sf::Color(76, 0, 153));
  timer.setString(timer_text.getString());
  timer.setPosition(600, 30);
  target.draw(timer, states);

  sf::Text instruction("press the keys that you see on the screen", font, 20);
  instruction.setFillColor(sf::Color(255, 102, 178));
  instruction.setPosition(180, 520);
  target.draw(instruction, states);

  if (isGameOver()) {
	sf::RectangleShape overlay(sf::Vector2f(800, 600));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));
	target.draw(overlay, states);

	sf::Text gameOver("", font, 48);
	gameOver.setFillColor(sf::Color(102, 0, 204));
	gameOver.setString(game_over_text.getString());
	gameOver.setPosition(200, 150);
	target.draw(gameOver, states);
  }
}

void Game::run()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Typing Trainer");
  window.setFramerateLimit(60);

  sf::Clock clock;
  sf::Event event;

  while (window.isOpen()) {
	float deltaTime = clock.restart().asSeconds();
	bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

	while (window.pollEvent(event)) {
	  if (event.type == sf::Event::Closed) window.close();
	  if (event.type == sf::Event::KeyPressed) {
		handleInput(event.key.code, shiftPressed);
	  }
	}

	update(deltaTime);
	window.clear();
	window.draw(*this);
	window.display();
  }
}