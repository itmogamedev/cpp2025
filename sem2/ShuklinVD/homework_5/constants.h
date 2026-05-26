#pragma once

const unsigned int SCREEN_WIDTH        = 800;
const unsigned int SCREEN_HEIGHT       = 600;
const float        SCREEN_WIDTH_F      = static_cast<float>(SCREEN_WIDTH);
const float        SCREEN_HEIGHT_F     = static_cast<float>(SCREEN_HEIGHT);
const unsigned int FRAMERATE_LIMIT     = 60;

const float SHIP_WIDTH           = 64.f;
const float SHIP_HEIGHT          = 64.f;
const float SHIP_SPEED           = 400.f;
const int   SHIP_INITIAL_LIVES   = 3;
const float SHIP_SPAWN_OFFSET_X  = 32.f;
const float SHIP_SPAWN_OFFSET_Y  = 90.f;

const float BULLET_WIDTH          = 10.f;
const float BULLET_HEIGHT         = 24.f;
const float BULLET_SPEED          = 600.f;
const float BULLET_SPAWN_OFFSET_Y = 10.f;

const float ASTEROID_WIDTH         = 56.f;
const float ASTEROID_HEIGHT        = 56.f;
const float ASTEROID_DEFAULT_SPEED = 150.f;
const float ASTEROID_BASE_SPEED    = 130.f;
const float ASTEROID_SPEED_ACCEL   = 6.f;
const float ASTEROID_SPAWN_Y       = -60.f;

const float SHOOT_COOLDOWN_BASE  = 0.6f;
const float SHOOT_COOLDOWN_MIN   = 0.15f;
const float SHOOT_COOLDOWN_STEP  = 0.01f;
const float SPAWN_INTERVAL_INIT  = 1.2f;
const int   SCORE_PER_ASTEROID   = 1;

const int BG_R = 10;
const int BG_G = 10;
const int BG_B = 30;

const int BULLET_COLOR_R = 255;
const int BULLET_COLOR_G = 230;
const int BULLET_COLOR_B = 80;

const int GAMEOVER_COLOR_R = 255;
const int GAMEOVER_COLOR_G = 80;
const int GAMEOVER_COLOR_B = 80;

const int OVERLAY_ALPHA = 180;

const unsigned int HUD_TEXT_SIZE      = 28;
const float        HUD_SCORE_X        = 15.f;
const float        HUD_Y              = 12.f;
const float        HUD_LIVES_OFFSET_X = 150.f;

const unsigned int GAMEOVER_TEXT_SIZE    = 64;
const unsigned int FINAL_SCORE_TEXT_SIZE = 36;
const float        GAMEOVER_Y_OFFSET     = 80.f;
const float        FINAL_SCORE_Y_OFFSET  = 10.f;
