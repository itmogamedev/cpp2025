#pragma once
#include "consta.h"

struct Cell {
    bool isHidden = true;   // По умолчанию — скрыт
    bool isFood = false;  // По умолчанию — еды нет
    CellType cellType = CellType::Type_Grass;
};