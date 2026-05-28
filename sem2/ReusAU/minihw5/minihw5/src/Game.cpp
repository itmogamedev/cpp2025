#include "Game.h"
#include "Constants.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
             "Memory - hw5"),
      model(),
      view(),
      controller(model, view),
      resourcesOk(false)
{
    window.setFramerateLimit(60);
    resourcesOk = view.loadResources();
    if (!resourcesOk) {
        std::cerr << "Failed to load resources. Expected files:\n"
                  << "  assets/arial.ttf\n"
                  << "  assets/symbols/1.png ... 8.png  (or .jpg)\n";
    }
}

void Game::run() {
    if (!resourcesOk) return;

    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
            else if (key->code == sf::Keyboard::Key::R && model.isFinished()) {
                model.reset();
            }
        }
        else if (auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mb->button == sf::Mouse::Button::Left) {
                // Перевод координат клика из пиксельных в мировые
                sf::Vector2f pos = window.mapPixelToCoords(mb->position);
                controller.handleClick(pos);
            }
        }
    }
}

void Game::update() {
    controller.update();
}

void Game::render() {
    if (model.isFinished() && !controller.isWaitingToResolve()) {
        view.drawEndScreen(window, model);
    } else {
        view.draw(window, model);
    }
    window.display();
}
