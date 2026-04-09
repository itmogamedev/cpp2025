#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include <optional>
char generateRandomChar() {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, static_cast<int>(chars.size() - 1));
    return chars[dis(gen)];
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Typing Trainer");
    window.setFramerateLimit(60);

    sf::Font font;
        if (!font.openFromFile("/System/Library/Fonts/Monaco.ttf")) {
            std::cerr << "Ошибка: Не удалось загрузить шрифт!\n";
            return -1;
        }
    int score = 0;
    float timeLeft = 30.0f;
    float penaltyTime = 2.0f;
    char targetChar = generateRandomChar();
    bool isGameOver = false;

    sf::Text charText(font);
    charText.setString(std::string(1, targetChar));
    charText.setCharacterSize(120);
    charText.setFillColor(sf::Color::White);
    charText.setPosition({350.f, 200.f});

    sf::Text scoreText(font);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition({20.f, 20.f});

    sf::Text timerText(font);
    timerText.setString("Time: 30");
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::Yellow);
    timerText.setPosition({600.f, 20.f});

    sf::Text gameOverText(font);
    gameOverText.setString("");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({200.f, 250.f});

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (!isGameOver) {
                if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
                    if (textEntered->unicode < 128 && textEntered->unicode > 31) {
                        char typedChar = static_cast<char>(textEntered->unicode);
                        
                        if (typedChar == targetChar) {
                            score++;
                            targetChar = generateRandomChar();
                            charText.setString(std::string(1, targetChar));
                        } else {
                            timeLeft -= penaltyTime;
                        }
                    }
                }
            }
        }

        if (!isGameOver) {
            float dt = clock.restart().asSeconds();
            timeLeft -= dt;

            if (timeLeft <= 0.0f) {
                timeLeft = 0.0f;
                isGameOver = true;
                gameOverText.setString("Game Over!\nFinal Score: " + std::to_string(score));
            }

            scoreText.setString("Score: " + std::to_string(score));
            timerText.setString("Time: " + std::to_string(static_cast<int>(timeLeft)));
        } else {
            clock.restart();
        }

        window.clear(sf::Color::Black);

        if (!isGameOver) {
            window.draw(charText);
            window.draw(scoreText);
            window.draw(timerText);
        } else {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
