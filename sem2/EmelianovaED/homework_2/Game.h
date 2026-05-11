#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Counter.h"
#include "RandomSymbol.h"
#include "Renderer.h"
#include "Timer.h"

class Game {
  Timer timer_game;
  Counter counter_game;
  RandomSymbol rand_symbol;
  Renderer renderer_game;
  bool isGameOver;
  char symbol_current;
  sf::Font font;  
  sf::RenderWindow window;
  

  void processEvents();
  void updateTime(float deltaTime);
  void renderGame();
  void generateNewSymbol();
  void restartGame();

 public:
  Game();
  void run();
};
#endif  // !GAME_H
