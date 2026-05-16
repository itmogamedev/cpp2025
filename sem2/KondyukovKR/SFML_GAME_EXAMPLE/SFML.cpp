#include <ctime>
#include "gameController.h"
#include "view.h"

// MVC + Observer:
//   Model  (GameModel)          — данные, наследует Observable
//   View   (View)               — отображение, наследует Observer
//   Controller (GameController) — обрабатывает клавиатурный ввод, изменяет Model
//
// Поток:
//   Нажата клавиша → Controller.moveXxx() → Model.movePlayer() →
//   Model.notifyObservers() → View.update() — автоматически

void mainLoop(GameController& ctrl, View& view) {
    auto* window = view.window;

    while (view.windowIsOpen()) {

        while (const std::optional event = window->pollEvent()) {

            if (event->is<sf::Event::Closed>())
                view.windowClose();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {

                if (key->scancode == sf::Keyboard::Scancode::Escape)
                    view.windowClose();

                if (!ctrl.isWinOfGame() && !ctrl.isLoseOfGame()) {
                    switch (key->scancode) {
                    case sf::Keyboard::Scancode::W:
                    case sf::Keyboard::Scancode::Up:
                        ctrl.moveUp();    break;

                    case sf::Keyboard::Scancode::S:
                    case sf::Keyboard::Scancode::Down:
                        ctrl.moveDown();  break;

                    case sf::Keyboard::Scancode::A:
                    case sf::Keyboard::Scancode::Left:
                        ctrl.moveLeft();  break;

                    case sf::Keyboard::Scancode::D:
                    case sf::Keyboard::Scancode::Right:
                        ctrl.moveRight(); break;

                    default: break;
                    }
                }
            }
        }

        if (ctrl.isWinOfGame())
            view.setConditionText(TEXT_WIN);
        else if (ctrl.isLoseOfGame())
            view.setConditionText(TEXT_LOSE);
        else
            view.setConditionText(TEXT_EMPTY);

        view.draw();
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    GameModel* model = new GameModel();
    GameController ctrl(model);
    View           view(model);

    mainLoop(ctrl, view);

    delete model;
    return 0;
}