#include "Controller.h"

Controller::Controller(unsigned int width, unsigned int height,
                       const std::string& title)
    : window(sf::VideoMode({width, height}), title),
      model(static_cast<float>(width), static_cast<float>(height)),
      view(window, model) {}

void Controller::run() {
  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();
    if (deltaTime > 0.1f) deltaTime = 0.1f;

    processEvents();
    if (model.isActive()) {
      model.update(deltaTime);
      model.decreaseTime(deltaTime);
    }
    view.draw();
  }
}

void Controller::processEvents() {
  while (const std::optional event = window.pollEvent())
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->code == sf::Keyboard::Key::R) {
        model.reset();
      }
    } else if (const auto* mousePressed =
                   event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mousePressed->button == sf::Mouse::Button::Left) {
        if (model.isActive()) {
          handleMouseClick(mousePressed->position);
        }
      }
    }
}

void Controller::update(float deltaTime) {
  if (model.isActive()) {
    model.update(deltaTime);
    model.decreaseTime(deltaTime);
  }
}

void Controller::handleMouseClick(const sf::Vector2i& mousePos) {
  int hitIndex = model.checkHit(mousePos);
  if (hitIndex != -1) {
    model.handleHit(hitIndex);
  } else {
    model.handleMiss();
  }
}
