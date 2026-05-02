#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <Windows.h>
#include "Header.h"

//class MissEffect {
//private:
//    sf::Font font;
//    if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf")) {
//        std::cerr << "Ошибка: не удалось загрузить шрифт!" << std::endl;
//        return -1;
//    }
//    sf::Text text(font);
//    float lifetime;
//    float x, y;
//public:
//    MissEffect(const sf::Font& font, float posX, float posY) {
//        text.setString("-0.5 сек");
//        text.setCharacterSize(24);
//        text.setFillColor(sf::Color::Red);
//        text.setPosition(sf::Vector2f(posX, posY));
//        lifetime = 0.5f; // Эффект живет 0.5 секунды
//        x = posX;
//        y = posY;
//    }
//    bool update(float deltaTime) {
//        lifetime -= deltaTime;
//        y -= 50 * deltaTime; // Поднимаем текст вверх
//        //text.setPosition(x, y);
//        //// Делаем текст прозрачнее со временем
//        //sf::Color color = text.getFillColor();
//        //color.a = static_cast<sf::Uint8>(255 * (lifetime / 0.5f));
//        //text.setFillColor(color);
//        return lifetime > 0;
//    }
//    void draw(sf::RenderWindow& window) {
//        window.draw(text);
//    }
//};
int main()
{// Пытаемся загрузить шрифт
    //std::vector<MissEffect> missEffects; // Визуальные эффекты промахов
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf")) {
        std::cerr << "Ошибка: не удалось загрузить шрифт!" << std::endl;
        return -1;
    }
     setlocale(LC_ALL, "Russian");
     SetConsoleCP(1251);
     SetConsoleOutputCP(1251);
     srand(static_cast<unsigned int>(time(nullptr)));
     const int WINDOW_WIDTH = 1024;   // Ширина окна
     const int WINDOW_HEIGHT = 768;   // Высота окна
     const float CIRCLE_RADIUS = 30.f; // Радиус круга (30 пикселей)
     sf::Text scoreText(font);
     scoreText.setCharacterSize(36);        // Размер шрифта
     scoreText.setFillColor(sf::Color::White);
     scoreText.setPosition(sf::Vector2f(20, 20));
     // Текст для отображения времени
     sf::Text timerText(font);
     timerText.setCharacterSize(36);
     timerText.setFillColor(sf::Color::White);
     timerText.setPosition(sf::Vector2f(WINDOW_WIDTH - 200, 20));  // В правом верхнем углу
     std::vector<GameCircle> circles;  // Список всех кругов
     int score = 0;                    // Счет игрока
     float timerLeft = 32.0f;           // Оставшееся время (30 секунд)
     float timerstart = 32.0f;
     bool gameRunning = true;  // Игра активна?// Создаем 5 кругов в случайных позициях
     for (int i = 0; i < 5; i++) {
         float randX = static_cast<float>(rand() % (WINDOW_WIDTH - 120));
         float randY = static_cast<float>(rand() % (WINDOW_HEIGHT - 120));
         // Случайный цвет для каждого круга
         sf::Color randomColor(
             rand() % 200 + 55,   // Красный (55-255)
             rand() % 200 + 55,   // Зеленый
             rand() % 200 + 55    // Синий
         );
         circles.push_back(GameCircle(randX, randY, CIRCLE_RADIUS, randomColor));
    }
     sf::Clock deltaClock;    // Для измерения времени между кадрами
     sf::Clock gameClock;     // Для отсчета общего времени игры
    // create the window
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Круги");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            // Обработка клика мыши (только если игра активна)
            if ((event->is<sf::Event::MouseButtonPressed>()) && gameRunning) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int mouseX = mousePos.x;
                    int mouseY = mousePos.y;
                    bool hitSomething = false;  // Попали ли хоть в один круг?
                    // Проверяем каждый круг
                    for (auto& circle : circles) {
                        if (circle.isClicked(mouseX, mouseY)) {
                            // ПОПАДАНИЕ!
                            hitSomething = true;
                            score++;  // Увеличиваем счет
                            // Перемещаем круг в новое случайное место
                            float newX = static_cast<float>(rand() % (WINDOW_WIDTH - 120));
                            float newY = static_cast<float>(rand() % (WINDOW_HEIGHT - 120));
                            circle.shape.setPosition(sf::Vector2f(newX, newY));
                            // Меняем цвет круга для разнообразия
                            sf::Color newColor(
                                rand() % 200 + 55,
                                rand() % 200 + 55,
                                rand() % 200 + 55
                            );
                            circle.shape.setFillColor(newColor);
                            break;  // Обработали только один круг за клик
                        }
                    }
                    // Если не попали ни в один круг - ПРОМАХ!
                    if (!hitSomething) {
                        timerstart -= 2.0f;  // Штраф 0.5 секунды
                       /* missEffects.push_back(MissEffect(font, mouseX, mouseY - 20));*/
                        // Визуальный эффект: можно добавить звук "промаха" здесь
                    }
                }
        }
        if (gameRunning) {
            // Вычисляем, сколько времени прошло с прошлого кадра
            float deltaTime = deltaClock.restart().asSeconds();
            // Ограничиваем deltaTime, чтобы при лагах круги не улетали
            if (deltaTime > 0.033f) deltaTime = 0.033f;
            // Обновляем таймер игры
            float elapsedTotal = gameClock.getElapsedTime().asSeconds();
            timerLeft = timerstart - elapsedTotal;  // 30 секунд - сколько прошло
            // Проверяем, не закончилось ли время
            if (timerLeft <= 0.0f) {
                timerLeft = 0.0f;
                gameRunning = false;  // Игра окончена!
            }
            // Обновляем позиции всех кругов
            for (auto& circle : circles) {
                circle.update(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT, CIRCLE_RADIUS);
            }
            // Обновляем визуальные эффекты промахов
            /*for (auto it = missEffects.begin(); it != missEffects.end();) {
                if (!it->update(deltaTime)) {
                    it = missEffects.erase(it);
                } else {
                    ++it;
                }
            }*/
        }
        // clear the window with black color
        window.clear(sf::Color::Black);
        for (const auto& circle : circles) {
            window.draw(circle.shape);
        }
        // Обновляем и рисуем текст счета
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        // Обновляем и рисуем таймер
        timerText.setString("time: " + std::to_string(static_cast<int>(timerLeft)));
        if (timerLeft < 5.0f) {
            timerText.setFillColor(sf::Color::Red);
        } else {
            timerText.setFillColor(sf::Color::White);
        }
        window.draw(timerText);
        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }
}
