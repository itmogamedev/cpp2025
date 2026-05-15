#pragma once
#include "model.h"

// Controller — принимает клавиатурный ввод, изменяет Model
class GameController {
public:

    explicit GameController(GameModel* _model) : model(_model) {
        // Инициализация всех клеток
        for (int x = 0; x < CELLSIZE_M; x++) {
            for (int y = 0; y < CELLSIZE_N; y++) {
                model->setCellHidden(x, y);
                model->setCellFood(x, y);
                model->setCellType(x, y);
            }
        }
        // Раскрываем туман на стартовой позиции (0,0)
        model->initReveal();
    }

    // --- Game state ---
    bool isWinOfGame() const {
        for (int x = 0; x < CELLSIZE_M; x++)
            for (int y = 0; y < CELLSIZE_N; y++)
                if (model->isHidden(x, y))
                    return false;
        return true;
    }

    bool isLoseOfGame() const { return model->getEnergy() <= 0; }
    int  getEnergy()    const { return model->getEnergy(); }

    // --- Keyboard input -> Model ---
    void moveUp() { model->movePlayer(0, -1); }
    void moveDown() { model->movePlayer(0, 1); }
    void moveLeft() { model->movePlayer(-1, 0); }
    void moveRight() { model->movePlayer(1, 0); }

private:
    GameModel* model;
};