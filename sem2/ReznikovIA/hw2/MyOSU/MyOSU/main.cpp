#include "GameController.h"
#include "GameModel.h"
#include "GameView.h"
#include "SFML/Graphics/RenderWindow.hpp";
#include "SFML/Window/VideoMode.hpp";

int main() {
  unsigned int windowWidth = 800;
  unsigned int windowHeight = 600;

  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "My OSU");

  GameModel model = GameModel(3, 25, 175, windowWidth, windowHeight, 3.f);
  GameView view(model, window, "Roboto-Medium.ttf");
  GameController controller(model, view);

  controller.run();

  return 0;
}
