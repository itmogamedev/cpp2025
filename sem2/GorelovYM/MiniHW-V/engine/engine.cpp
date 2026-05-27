// include libs
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// include engine
#include "define.h"
#include "engine.h"
#include "scene.h"
#include "resource.h"
#include "input.h"
#include "utilities.h"

// constants
#define FPS 60

// initialize the window size variables
int    Engine::width;
int    Engine::height;
float  Engine::scale;

// booter callback
void (*Engine::start)(void);

// screen
Image Engine::screen(0, 0);

// default font
Resources::Font* Engine::font;

// tick stuff
double Engine::ticks = 0;
double Engine::tickspeed = 1;

// constructor
Engine::Engine(std::string title, int width, int height, int scale, void (*start)(void)) {
  Engine::Title() = title;
  Engine::width   = width;
  Engine::height  = height;
  Engine::scale   = scale;
  Engine::start   = start;
}

// static variables
sf::RenderWindow window;

// function to quit the game
void Engine::Quit(void) {
  window.close();
};

// main
int main(void)
{
  // set seed
  Utilities::RandSeed();

  // before everything
  if (Engine::start != nullptr)
    Engine::start();

  // fullscreen check
  if (Engine::scale == 0)
    Engine::scale =
      static_cast<float>(sf::VideoMode::getDesktopMode().height) / Engine::height,
    window.create(
      sf::VideoMode::getDesktopMode(),
      Engine::Title(),
      sf::Style::None);
  else
    window.create(
      sf::VideoMode(
          Engine::width * Engine::scale, 
          Engine::height * Engine::scale),
      Engine::Title(), sf::Style::Titlebar | sf::Style::Close);

  // creating the view
  sf::View view(sf::FloatRect(0, 0, Engine::width, Engine::height));
  window.setView(view);

  // set the settingss
  window.setFramerateLimit(FPS);
  window.setKeyRepeatEnabled(false);
  window.setVerticalSyncEnabled(true);

  // initialize the buffer
  Engine::screen.Resize(Engine::width, Engine::height);
  sf::Texture texture;
  sf::Sprite sprite;

  // adjust texture and sprite
  texture.create(Engine::width, Engine::height);
  texture.setSmooth(false);
  sprite.setTexture(texture);

  // allocate pixels
  std::vector<sf::Uint8> pixels(Engine::width * Engine::height * 4);

  // initialize all scenes
  Scene::InitAll();

  // main loop
  while (window.isOpen()) {

    // process events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // close window event
      if (event.type == sf::Event::Closed)
        Engine::Quit();
      
      // key event
      else if (event.type == sf::Event::KeyPressed ||
               event.type == sf::Event::KeyReleased)
        Input::keys[static_cast<int>(event.key.code)] =
          event.type == sf::Event::KeyPressed;

      // mouse moved event
      else if (event.type == sf::Event::MouseMoved)
        Input::mouseX = event.mouseMove.x / Engine::scale,
        Input::mouseY = event.mouseMove.y / Engine::scale;

      // mouse button pressed event
      else if (event.type == sf::Event::MouseButtonPressed ||
               event.type == sf::Event::MouseButtonReleased)
        Input::buttons[event.mouseButton.button] =
          event.type == sf::Event::MouseButtonPressed;
    }

    // clear the screen
    std::vector<uint>& buffer = Engine::screen.pixels;
    // for (int i = 0; i < buffer.size(); i++)
    //   buffer[i] = 0;

    // update the scene
    Scene::UpdateCurrent();
    Scene::DrawCurrent();

    // reverse byte order
    for (int i = 0; i < buffer.size(); i++) {
      pixels[i * 4 + 0] = (buffer[i] >> 16) & 0xff;
      pixels[i * 4 + 1] = (buffer[i] >> 8) & 0xff;
      pixels[i * 4 + 2] = buffer[i] & 0xff;
      pixels[i * 4 + 3] = 255;
    }

    // display the buffer to the screen
    texture.update(pixels.data());
    window.clear();
    window.draw(sprite);
    window.display();

    // update the ticks
    Engine::ticks += Engine::tickspeed;
  }

  // close the window
  window.close();
}

// function to delay the game
void Engine::Delay(int time) {
  sf::sleep(sf::milliseconds(time));
}