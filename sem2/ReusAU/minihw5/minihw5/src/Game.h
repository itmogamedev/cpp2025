#pragma once
#include <SFML/Graphics.hpp>
#include "model/BoardModel.h"
#include "view/BoardView.h"
#include "controller/BoardController.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    BoardModel model;
    BoardView view;
    BoardController controller;
    bool resourcesOk;

    void processEvents();
    void update();
    void render();
};
