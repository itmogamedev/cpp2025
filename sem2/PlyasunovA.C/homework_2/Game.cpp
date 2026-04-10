#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game()
    : window(sf::VideoMode(800, 600), "Circle Clicker Game"),
    score(0),
    time_left(60.0f),
    game_over(false),
    radius(30.0f),
    penalty_amount(2.0f),
    window_width(800),
    window_height(600),
    rng(std::random_device{}()),
    pos_dist_x(radius, window_width - radius),
    pos_dist_y(radius, window_height - radius),
    vel_dist(-100.0f, 100.0f) {
    if (!font.loadFromFile("A:/C++/MiniHW2/x64/Material/arial.ttf")) {
        std::cerr << "Error: Cannot load arial.ttf. Place the font file in the same folder as the executable.\n";
        std::exit(EXIT_FAILURE);
    }

    score_text.setFont(font);
    score_text.setCharacterSize(24);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(10.0f, 10.0f);

    time_text.setFont(font);
    time_text.setCharacterSize(24);
    time_text.setFillColor(sf::Color::White);
    time_text.setPosition(10.0f, 40.0f);

    game_over_text.setFont(font);
    game_over_text.setCharacterSize(36);
    game_over_text.setFillColor(sf::Color::Red);
    game_over_text.setPosition(window_width / 2.0f - 150.0f, window_height / 2.0f - 50.0f);

    initializeCircles();
    updateTexts();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();

        float dt = delta_clock.restart().asSeconds();
        if (dt > 0.02f) dt = 0.02f;

        if (!game_over) {
            update(dt);
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
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!game_over) {
                int mouse_x = event.mouseButton.x;
                int mouse_y = event.mouseButton.y;
                int hit_index = checkCircleClick(mouse_x, mouse_y);
                if (hit_index != -1) {
                    score++;
                    spawnRandomPosition(hit_index);
                    spawnRandomVelocity(hit_index);
                    updateTexts();
                }
                else {
                    time_left -= penalty_amount;
                    if (time_left < 0.0f) time_left = 0.0f;
                    updateTexts();
                    if (time_left <= 0.0f) {
                        game_over = true;
                    }
                }
            }
        }
    }
}

void Game::update(float dt) {
    for (size_t i = 0; i < circles.size(); ++i) {
        sf::Vector2f pos = circles[i].getPosition();
        pos += velocities[i] * dt;

        if (pos.x - radius < 0.0f) {
            pos.x = radius;
            velocities[i].x = -velocities[i].x;
        }
        else if (pos.x + radius > window_width) {
            pos.x = window_width - radius;
            velocities[i].x = -velocities[i].x;
        }

        if (pos.y - radius < 0.0f) {
            pos.y = radius;
            velocities[i].y = -velocities[i].y;
        }
        else if (pos.y + radius > window_height) {
            pos.y = window_height - radius;
            velocities[i].y = -velocities[i].y;
        }

        circles[i].setPosition(pos);
    }

    time_left -= dt;
    if (time_left <= 0.0f) {
        time_left = 0.0f;
        game_over = true;
    }
    updateTexts();
}

void Game::render() {
    window.clear(sf::Color::Black);

    for (const auto& circle : circles) {
        window.draw(circle);
    }

    window.draw(score_text);
    window.draw(time_text);

    if (game_over) {
        window.draw(game_over_text);
    }

    window.display();
}

void Game::initializeCircles() {
    circles.resize(5);
    velocities.resize(5);
    for (int i = 0; i < 5; ++i) {
        circles[i].setRadius(radius);
        circles[i].setFillColor(sf::Color::Green);
        circles[i].setOrigin(radius, radius);
        spawnRandomPosition(i);
        spawnRandomVelocity(i);
    }
}

void Game::spawnRandomPosition(int index) {
    float x = pos_dist_x(rng);
    float y = pos_dist_y(rng);
    circles[index].setPosition(x, y);
}

void Game::spawnRandomVelocity(int index) {
    velocities[index] = sf::Vector2f(vel_dist(rng), vel_dist(rng));
}

void Game::updateTexts() {
    score_text.setString("Score: " + std::to_string(score));
    time_text.setString("Time: " + std::to_string(static_cast<int>(time_left)) + "s");
    if (game_over) {
        game_over_text.setString("Game Over!\nFinal Score: " + std::to_string(score) + "\nClose window to exit");
    }
}

int Game::checkCircleClick(int mouse_x, int mouse_y) const {
    sf::Vector2f mouse_point(static_cast<float>(mouse_x), static_cast<float>(mouse_y));
    for (size_t i = 0; i < circles.size(); ++i) {
        sf::Vector2f center = circles[i].getPosition();
        float dx = mouse_point.x - center.x;
        float dy = mouse_point.y - center.y;
        if (std::hypot(dx, dy) < radius) {
            return static_cast<int>(i);
        }
    }
    return -1;
}