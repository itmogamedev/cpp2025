#include "BoardView.h"
#include "../Constants.h"
#include <algorithm>
#include <string>

BoardView::BoardView() {}

bool BoardView::loadResources() {
    if (!font.openFromFile("assets/arial.ttf")) {
        return false;
    }

    for (int i = 1; i <= PAIR_COUNT; ++i) {
        sf::Texture tex;
        std::string path = "assets/symbols/" + std::to_string(i) + ".png";
        if (!tex.loadFromFile(path)) {
            // если png нет — пробуем jpg
            path = "assets/symbols/" + std::to_string(i) + ".jpg";
            if (!tex.loadFromFile(path)) {
                return false;
            }
        }
        tex.setSmooth(true);
        symbolTextures.push_back(std::move(tex));
    }
    return true;
}

sf::Vector2f BoardView::cardTopLeft(int row, int col) const {
    float x = BOARD_OFFSET_X + col * (CARD_SIZE + CARD_MARGIN);
    float y = BOARD_OFFSET_Y + row * (CARD_SIZE + CARD_MARGIN);
    return sf::Vector2f(x, y);
}

void BoardView::drawCard(sf::RenderWindow& window, const CardModel& card) {
    if (card.state == CardState::Matched) return;

    sf::Vector2f pos = cardTopLeft(card.row, card.col);

    sf::RectangleShape rect(sf::Vector2f(CARD_SIZE, CARD_SIZE));
    rect.setPosition(pos);
    rect.setOutlineColor(OUTLINE_COLOR);
    rect.setOutlineThickness(3.f);

    if (card.state == CardState::Hidden) {
        rect.setFillColor(BACK_COLOR);
        window.draw(rect);
        return;
    }

    rect.setFillColor(FACE_COLOR);
    window.draw(rect);

    int id = card.symbolId;
    if (id >= 0 && id < (int)symbolTextures.size()) {
        const sf::Texture& tex = symbolTextures[id];
        sf::Sprite sprite(tex);
        sf::Vector2u tsize = tex.getSize();

        // Вписываем спрайт в карточку с отступом и центрируем
        float pad = 15.f;
        float target = CARD_SIZE - 2 * pad;
        float maxDim = (float)std::max(tsize.x, tsize.y);
        float scale = (maxDim > 0.f) ? (target / maxDim) : 1.f;
        sprite.setScale(sf::Vector2f(scale, scale));
        float sw = tsize.x * scale;
        float sh = tsize.y * scale;
        sprite.setPosition(sf::Vector2f(
            pos.x + (CARD_SIZE - sw) / 2.f,
            pos.y + (CARD_SIZE - sh) / 2.f
        ));
        window.draw(sprite);
    }
}

void BoardView::draw(sf::RenderWindow& window, const BoardModel& model) {
    window.clear(BG_COLOR);

    sf::Text movesText(font, "Moves: " + std::to_string(model.getMoves()), 32);
    movesText.setFillColor(TEXT_COLOR);
    movesText.setPosition(sf::Vector2f(30.f, 35.f));
    window.draw(movesText);

    std::string scoreStr = "Pairs: " + std::to_string(model.getScore()) +
                           " / " + std::to_string(PAIR_COUNT);
    sf::Text scoreText(font, scoreStr, 32);
    scoreText.setFillColor(TEXT_COLOR);
    auto sb = scoreText.getLocalBounds();
    scoreText.setPosition(sf::Vector2f(
        (float)WINDOW_WIDTH - sb.size.x - 30.f,
        35.f
    ));
    window.draw(scoreText);

    for (const auto& card : model.getCards()) {
        drawCard(window, card);
    }
}

void BoardView::drawEndScreen(sf::RenderWindow& window, const BoardModel& model) {
    window.clear(BG_COLOR);

    sf::Text title(font, "You Won!", 80);
    title.setFillColor(sf::Color(255, 220, 100));
    auto tb = title.getLocalBounds();
    title.setPosition(sf::Vector2f(
        ((float)WINDOW_WIDTH - tb.size.x) / 2.f,
        260.f
    ));
    window.draw(title);

    sf::Text info(font, "Moves: " + std::to_string(model.getMoves()), 48);
    info.setFillColor(TEXT_COLOR);
    auto ib = info.getLocalBounds();
    info.setPosition(sf::Vector2f(
        ((float)WINDOW_WIDTH - ib.size.x) / 2.f,
        410.f
    ));
    window.draw(info);

    sf::Text hint(font, "Press R to restart, Esc to quit", 26);
    hint.setFillColor(sf::Color(200, 200, 200));
    auto hb = hint.getLocalBounds();
    hint.setPosition(sf::Vector2f(
        ((float)WINDOW_WIDTH - hb.size.x) / 2.f,
        520.f
    ));
    window.draw(hint);
}

int BoardView::getCardIndexAtPosition(sf::Vector2f pos) const {
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            sf::Vector2f tl = cardTopLeft(row, col);
            if (pos.x >= tl.x && pos.x <= tl.x + CARD_SIZE &&
                pos.y >= tl.y && pos.y <= tl.y + CARD_SIZE) {
                return row * GRID_SIZE + col;
            }
        }
    }
    return -1;
}
