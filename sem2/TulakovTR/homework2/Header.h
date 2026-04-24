#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <Windows.h>
struct GameCircle {
    sf::CircleShape shape;    // SFML-объект круга (как его рисовать)
    float velocityX;          // Скорость движения по X (пикселей в секунду)
    float velocityY;          // Скорость движения по Y
    // Конструктор - создает круг с заданными параметрами
    GameCircle(float x, float y, float radius, sf::Color color) {
        shape.setRadius(radius);           // Устанавливаем радиус
        shape.setPosition(sf::Vector2f(x, y));           // Устанавливаем позицию
        shape.setFillColor(color);         // Устанавливаем цвет
        shape.setOutlineThickness(2);      // Толщина обводки
        shape.setOutlineColor(sf::Color::White);  // Цвет обводки 
        // Случайная скорость от -100 до +100 пикселей в секунду
        velocityX = (rand() % 200) - 100;  // -100...100
        velocityY = (rand() % 200) - 100;
        // Чтобы круги не стояли на месте, если выпал 0
        if (velocityX == 0 && velocityY == 0) {
            velocityX = 50;
            velocityY = 50;
        }
    }
    // Обновление позиции круга (вызывается каждый кадр)
    void update(float deltaTime, int windowWidth, int windowHeight, float radius) {
        // deltaTime - сколько времени прошло с прошлого кадра (в секундах)
        // Умножаем скорость на время, чтобы движение было плавным
        float newX = shape.getPosition().x + velocityX * deltaTime;
        float newY = shape.getPosition().y + velocityY * deltaTime;
        // Отскок от стен (меняем направление, если круг касается границы)
        // Левая стена (x = 0)
        if (newX <= 0) {
            newX = 0;
            velocityX = -velocityX;  // Разворачиваем скорость
        }
        // Правая стена (x = ширина окна - диаметр круга)
        if (newX >= windowWidth - radius * 2) {
            newX = windowWidth - radius * 2;
            velocityX = -velocityX;
        }
        // Верхняя стена (y = 0)
        if (newY <= 0) {
            newY = 0;
            velocityY = -velocityY;
        }
        // Нижняя стена (y = высота окна - диаметр круга)
        if (newY >= windowHeight - radius * 2) {
            newY = windowHeight - radius * 2;
            velocityY = -velocityY;
        }
        shape.setPosition(sf::Vector2f(newX, newY));
    }
    // Проверка, попал ли клик по этому кругу
    bool isClicked(int mouseX, int mouseY) const {
        // Центр круга = позиция + радиус
        float centerX = shape.getPosition().x + shape.getRadius();
        float centerY = shape.getPosition().y + shape.getRadius();
        // Расстояние от точки клика до центра круга
        float deltaX = mouseX - centerX;
        float deltaY = mouseY - centerY;
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
        // Если расстояние меньше радиуса - клик ПОПАЛ в круг
        return distance <= shape.getRadius();
    }
};
