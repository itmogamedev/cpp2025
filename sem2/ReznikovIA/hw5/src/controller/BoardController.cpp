#include "BoardController.h"

#include "../Constants.h"
#include "../model/BoardModel.h"
#include "../view/BoardView.h"

BoardController::BoardController(BoardModel& boardModel, BoardView& boardView)
    : boardModel(boardModel), boardView(boardView) {}

void BoardController::handleEvent(const std::optional<sf::Event>& event) {
  if (event->is<sf::Event::MouseButtonPressed>()) {
    auto pos = event->getIf<sf::Event::MouseButtonPressed>()->position;

    float relX = static_cast<float>(pos.x) - OFFSET_X;
    float relY = static_cast<float>(pos.y) - OFFSET_Y;

    int col = static_cast<int>(relX / (CARD_W + GAP));
    int row = static_cast<int>(relY / (CARD_H + GAP));

    if (col < 0 || col >= COLS || row < 0 || row >= ROWS) return;

    float localX = relX - col * (CARD_W + GAP);
    float localY = relY - row * (CARD_H + GAP);
    if (localX > CARD_W || localY > CARD_H) return;

    int index = row * COLS + col;
    boardModel.flipCard(index);
  }
}
