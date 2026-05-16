#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include "model.h"
#include "observer.h"

namespace fs = std::filesystem;

// View — отображает состояние Model; обновляется через Observer::update()
class View : public Observer {
public:
    sf::RenderWindow* window = nullptr;

    explicit View(GameModel* _model) : model(_model) {

        // --- Шрифт ---
        if (!font.openFromFile(FONT_FILE)) {
            std::cout << "Error! Can't find " << FONT_FILE
                << " at: " << fs::current_path() << "\n";
            std::cout << (fs::exists(FONT_FILE)
                ? "File exists but SFML can't load it!\n"
                : "File NOT found!\n");
        }

        // --- Тексты HUD ---
        textEnergy = new sf::Text(font);
        textCondition = new sf::Text(font);

        textEnergy->setCharacterSize(HUD_ENERGY_FONT_SIZE);
        textEnergy->setFillColor(HUD_ENERGY_COLOR);
        textEnergy->setStyle(sf::Text::Bold);
        textEnergy->setPosition({ HUD_ENERGY_POS_X, HUD_ENERGY_POS_Y });

        textCondition->setCharacterSize(HUD_CONDITION_FONT_SIZE);
        textCondition->setFillColor(HUD_CONDITION_COLOR);
        textCondition->setStyle(sf::Text::Bold);
        textCondition->setPosition({
            CELLSIZE_SCREEN * CELLSIZE_M / HUD_CONDITION_POS_SCALE,
            CELLSIZE_SCREEN * CELLSIZE_N / HUD_CONDITION_POS_SCALE
            });

        // --- Окно ---
        window = new sf::RenderWindow(
            sf::VideoMode({
                static_cast<unsigned>(CELLSIZE_SCREEN * CELLSIZE_M),
                static_cast<unsigned>(CELLSIZE_SCREEN * CELLSIZE_N)
                }),
            WINDOW_TITLE,
            sf::State::Windowed
        );

        // --- Текстуры тайлов и персонажа ---
        for (int i = 0; i < TextureType::Texture_End; i++)
            textures[i].loadFromFile(textureFiles[i] + TEXTURE_EXTENSION);

        // --- Фигуры тайлов ---
        for (int x = 0; x < CELLSIZE_M; x++) {
            for (int y = 0; y < CELLSIZE_N; y++) {
                shapes[x][y].setSize({ CELLSIZE_SCREEN, CELLSIZE_SCREEN });
                shapes[x][y].setPosition(sf::Vector2f(x * CELLSIZE_SCREEN, y * CELLSIZE_SCREEN));
            }
        }

        // --- Спрайт персонажа ---
        // sf::Sprite в SFML 3.x не имеет конструктора по умолчанию —
        // создаём через указатель уже после загрузки текстуры.
        playerSprite = new sf::Sprite(textures[TextureType::Texture_Player]);
        auto texSize = textures[TextureType::Texture_Player].getSize();
        if (texSize.x > 0 && texSize.y > 0) {
            playerSprite->setScale({
                CELLSIZE_SCREEN / static_cast<float>(texSize.x),
                CELLSIZE_SCREEN / static_cast<float>(texSize.y)
                });
        }

        // Подписываемся на уведомления модели
        model->addObserver(this);

        // Первоначальная синхронизация
        update();
    }

    ~View() {
        delete textEnergy;
        delete textCondition;
        delete playerSprite;
        delete window;
    }

    // Вызывается автоматически при изменении модели (Observer pattern)
    void update() override {
        // Обновляем текстуры тайлов
        for (int x = 0; x < CELLSIZE_M; x++) {
            for (int y = 0; y < CELLSIZE_N; y++) {
                TextureType tex;
                if (model->isHidden(x, y))
                    tex = TextureType::Texture_Hide;
                else if (model->isFood(x, y))
                    tex = TextureType::Texture_Soup;
                else
                    tex = static_cast<TextureType>(model->getCellType(x, y));

                shapes[x][y].setTexture(&textures[tex]);
            }
        }

        // Позиция спрайта персонажа
        playerSprite->setPosition(sf::Vector2f(
            model->getPlayerX() * CELLSIZE_SCREEN,
            model->getPlayerY() * CELLSIZE_SCREEN
        ));

        // HUD: энергия
        textEnergy->setString("Energy: " + std::to_string(model->getEnergy()));
    }

    void setConditionText(const std::string& text) {
        textCondition->setString(text);
    }

    void draw() {
        window->clear(sf::Color(WINDOW_BG_R, WINDOW_BG_G, WINDOW_BG_B));

        for (int x = 0; x < CELLSIZE_M; x++)
            for (int y = 0; y < CELLSIZE_N; y++)
                window->draw(shapes[x][y]);

        window->draw(*playerSprite);
        window->draw(*textEnergy);
        window->draw(*textCondition);
        window->display();
    }

    bool windowIsOpen() const { return window->isOpen(); }
    void windowClose() { window->close(); }

private:
    GameModel* model;

    sf::RectangleShape shapes[CELLSIZE_M][CELLSIZE_N];
    sf::Texture        textures[TextureType::Texture_End];
    sf::Sprite* playerSprite = nullptr;

    sf::Font  font;
    sf::Text* textEnergy = nullptr;
    sf::Text* textCondition = nullptr;
};