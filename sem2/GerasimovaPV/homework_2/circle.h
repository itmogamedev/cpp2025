//
// Created by Admin on 06.04.2026.
//
#ifndef MINIHW2_CIRCLE_H
#define MINIHW2_CIRCLE_H
#include "db.h"

sf::CircleShape addCircle();

float getTimer(sf::Clock &clock, float totalTime);

void respawnCircle(std::vector<sf::CircleShape> &circles, int n, float &live);

void circleAnimation(std::vector<sf::Clock> &c_l, std::vector<sf::CircleShape> &c, int n, float &live);

bool circleClick(sf::Vector2f mousePos, std::vector<sf::CircleShape> &c, int n, float &live);

int notMain();

#endif //MINIHW2_CIRCLE_H
