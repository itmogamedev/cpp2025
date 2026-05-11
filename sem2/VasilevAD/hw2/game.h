#pragma once
#include "rendering.h"
#include "typing.h"

#include <SFML/Graphics.hpp>

class Game {
 public:
  Game();
  void Run();

 private:
  void ProcessEvents();
  void Update(float dt);
  void Render();

  sf::RenderWindow screen;
  Typing type;
  Rendering render;
};