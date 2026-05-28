#pragma once
#include <SFML/Graphics.hpp>
#include "../model/BoardModel.h"
#include "../view/BoardView.h"

class BoardController {
public:
    BoardController(BoardModel& model, BoardView& view);

    void handleClick(sf::Vector2f mousePos);
    void update();

    bool isWaitingToResolve() const;

private:
    BoardModel& model;
    BoardView& view;
    sf::Clock revealClock;
    bool waiting;
};
