//
// Created by Admin on 06.04.2026.
//

#ifndef MINIHW2_DB_H
#define MINIHW2_DB_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>

inline bool game = true;

inline float timer = 20.f;
inline int counter = 0;

inline float time_over = 0.f;

inline float lives_new = 0.f;
inline float lifeTime = 3;

inline float normal_size = 1.f;

inline int circle_count = 5;

inline int radius = 100;

inline int win_w_stop = 1000;
inline int win_h_stop = 700;

inline int win_w = 1280;
inline int win_h = 720;
inline int icon_size = 512;

inline int text_size = 30;
inline int text_size_over = 50;

inline float text_x = 1000.f;
inline float text_timer_y = 10.f;
inline float text_points_y = 50.f;
inline float text_over_x = 400.f;
inline float text_over_y = 300.f;


#endif //MINIHW2_DB_H
