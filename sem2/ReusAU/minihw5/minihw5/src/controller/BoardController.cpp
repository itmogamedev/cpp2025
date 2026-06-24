#include "BoardController.h"
#include "../Constants.h"

BoardController::BoardController(BoardModel& model, BoardView& view)
    : model(model), view(view), waiting(false) {}

void BoardController::handleClick(sf::Vector2f mousePos) {
    if (waiting) return;
    if (model.isFinished()) return;

    int idx = view.getCardIndexAtPosition(mousePos);
    if (idx < 0) return;
    if (!model.canFlip(idx)) return;

    model.flip(idx);

    // Открыта вторая карта — запускаем задержку показа
    if (model.flippedCount() == 2) {
        waiting = true;
        revealClock.restart();
    }
}

void BoardController::update() {
    if (!waiting) return;
    if (revealClock.getElapsedTime().asMilliseconds() >= REVEAL_DELAY_MS) {
        model.resolveFlipped();
        waiting = false;
    }
}

bool BoardController::isWaitingToResolve() const {
    return waiting;
}
