#include "game.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>

// Собираем играшку
Game::Game() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LOWBUDGET OSU)))0");
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    score = 0;
    time_left = START_TIME;
    is_game_over = false;

    font.loadFromFile("arial.ttf");

    time_text.setFont(font);
    time_text.setCharacterSize(24);
    time_text.setFillColor(sf::Color::White);
    time_text.setPosition(10.0f, 10.0f);

    score_text.setFont(font);
    score_text.setCharacterSize(24);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(10.0f, 40.0f);

    game_over_text.setFont(font);
    game_over_text.setCharacterSize(40);
    game_over_text.setFillColor(sf::Color::Red);
    game_over_text.setPosition(WINDOW_WIDTH / 3.0f, WINDOW_HEIGHT / 2.0f);

    // Генерим кружочки
    targets.resize(TARGET_COUNT);
    for (int i = 0; i < TARGET_COUNT; ++i) {
        targets[i].shape.setRadius(TARGET_RADIUS);
        targets[i].shape.setOrigin(TARGET_RADIUS, TARGET_RADIUS);
        targets[i].shape.setFillColor(sf::Color::Red);
        spawnTarget(i);
    }
}

// Запускаем играшку
void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float delta_time = clock.restart().asSeconds();
        processEvents();

        if (!is_game_over) {
            update(delta_time);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!is_game_over) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}

void Game::handleMouseClick(int mouse_x, int mouse_y) {
    bool hit = false;

    for (int i = 0; i < TARGET_COUNT; ++i) {
        float target_x = targets[i].shape.getPosition().x;
        float target_y = targets[i].shape.getPosition().y;

        float dx = mouse_x - target_x;
        float dy = mouse_y - target_y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= TARGET_RADIUS) {
            score += 1;
            spawnTarget(i);
            hit = true;
            break;
        }
    }
    if (!hit) {
        time_left -= PENALTY_TIME;
    }
}

void Game::spawnTarget(int index) {
    int max_x = WINDOW_WIDTH - static_cast<int>(TARGET_RADIUS * 2);
    int max_y = WINDOW_HEIGHT - static_cast<int>(TARGET_RADIUS * 2);

    float random_x = static_cast<float>(std::rand() % max_x + TARGET_RADIUS);
    float random_y = static_cast<float>(std::rand() % max_y + TARGET_RADIUS);

    targets[index].shape.setPosition(random_x, random_y);

    targets[index].speed_x = static_cast<float>((std::rand() % 200 - 100) / 100.0) * BASE_SPEED;
    targets[index].speed_y = static_cast<float>((std::rand() % 200 - 100) / 100.0) * BASE_SPEED;
}

void Game::update(float delta_time) {
    time_left -= delta_time;
    if (time_left <= 0) {
        time_left = 0;
        is_game_over = true;
    }

    for (int i = 0; i < TARGET_COUNT; ++i) {
        targets[i].shape.move(targets[i].speed_x * delta_time, targets[i].speed_y * delta_time);

        sf::Vector2f pos = targets[i].shape.getPosition();
        if (pos.x - TARGET_RADIUS < 0 || pos.x + TARGET_RADIUS > WINDOW_WIDTH) {
            targets[i].speed_x = -targets[i].speed_x;
        }
        if (pos.y - TARGET_RADIUS < 0 || pos.y + TARGET_RADIUS > WINDOW_HEIGHT) {
            targets[i].speed_y = -targets[i].speed_y;
        }
    }

    time_text.setString("Time left: " + std::to_string(static_cast<int>(std::ceil(time_left))));
    score_text.setString("Score: " + std::to_string(score));
    if (is_game_over) {
        game_over_text.setString("GAME OVER!\nFinal Score: " + std::to_string(score));
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (!is_game_over) {
        for (int i = 0; i < TARGET_COUNT; ++i) {
            window.draw(targets[i].shape);
        }
        window.draw(time_text);
        window.draw(score_text);
    }
    else {
        window.draw(game_over_text);
    }

    window.display();
}