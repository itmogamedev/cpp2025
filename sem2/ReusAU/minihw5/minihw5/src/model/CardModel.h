#pragma once

enum class CardState {
    Hidden,    // рубашкой вверх
    Revealed,  // открыта
    Matched    // пара найдена, убрана с поля
};

struct CardModel {
    int symbolId = 0;
    CardState state = CardState::Hidden;
    int row = 0;
    int col = 0;
};
