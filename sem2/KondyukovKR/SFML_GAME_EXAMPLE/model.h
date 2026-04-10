#pragma once

#include "cell.h"
#include "observer.h"
#include "consta.h"
#include <cstdlib>

// Model — хранит данные и уведомляет наблюдателей (Observer pattern)
class GameModel : public Observable {
public:

    GameModel() {
        for (int x = 0; x < CELLSIZE_M; x++)
            for (int y = 0; y < CELLSIZE_N; y++)
                cells[x][y] = new Cell();
    }

    ~GameModel() {
        for (int x = 0; x < CELLSIZE_M; x++)
            for (int y = 0; y < CELLSIZE_N; y++)
                delete cells[x][y];
    }

    // --- Energy ---
    int  getEnergy()  const { return energy; }
    void energySetMax() { energy = ENERGY_MAX; notifyObservers(); }

    // --- Player position ---
    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }

    // Раскрыть туман на стартовой позиции без траты энергии
    void initReveal() {
        revealAround(playerX, playerY, FOG_RADIUS);
        notifyObservers();
    }

    // Попытка переместить игрока на (dx, dy).
    // Возвращает true если ход совершён.
    bool movePlayer(int dx, int dy) {
        int nx = playerX + dx;
        int ny = playerY + dy;

        // Проверка границ поля
        if (nx < 0 || nx >= CELLSIZE_M || ny < 0 || ny >= CELLSIZE_N)
            return false;

        // Проверка непроходимых тайлов: Камень и Лес
        CellType ct = cells[nx][ny]->cellType;
        if (ct == Type_Stone || ct == Type_Forest)
            return false;

        playerX = nx;
        playerY = ny;

        // Подбор еды — восстанавливает энергию до максимума
        if (cells[playerX][playerY]->isFood) {
            cells[playerX][playerY]->isFood = false;
            energy = ENERGY_MAX;
        }

        // Рассеиваем туман вокруг новой позиции
        revealAround(playerX, playerY, FOG_RADIUS);

        // Тратим энергию за шаг
        energy -= ENERGY_STEP_COST;
        if (energy < 0) energy = 0;

        notifyObservers();
        return true;
    }

    // --- Cell accessors ---
    const Cell* getCell(int x, int y)  const { return cells[x][y]; }
    void setCellHidden(int x, int y) { cells[x][y]->isHidden = true; }

    void setCellFood(int x, int y) {
        cells[x][y]->isFood = (rand() % FOOD_RAND_BASE) < CHANCE_FOOD;
    }

    void setCellType(int x, int y) {
        cells[x][y]->cellType =
            static_cast<CellType>(rand() % (CellType::Type_End - 1));
    }

    bool     isHidden(int x, int y) const { return cells[x][y]->isHidden; }
    bool     isFood(int x, int y) const { return cells[x][y]->isFood; }
    CellType getCellType(int x, int y) const { return cells[x][y]->cellType; }

private:
    int   energy = ENERGY_MAX;
    int   playerX = PLAYER_START_X;
    int   playerY = PLAYER_START_Y;
    Cell* cells[CELLSIZE_M][CELLSIZE_N];

    // Раскрыть все клетки в квадрате радиуса r вокруг (cx, cy)
    void revealAround(int cx, int cy, int r) {
        for (int dx = -r; dx <= r; dx++) {
            for (int dy = -r; dy <= r; dy++) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx >= 0 && nx < CELLSIZE_M && ny >= 0 && ny < CELLSIZE_N)
                    cells[nx][ny]->isHidden = false;
            }
        }
    }
};