#ifndef game_h
#define game_h

#include <SFML/Graphics.hpp>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int TARGET_COUNT = 5;
const float TARGET_RADIUS = 30.0f;
const float START_TIME = 30.0f;
const float PENALTY_TIME = 2.0f;
const float BASE_SPEED = 150.0f;

struct Target {
    sf::CircleShape shape;
    float speed_x;
    float speed_y;
};

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float delta_time);
    void render();
    void spawnTarget(int index);
    void handleMouseClick(int mouse_x, int mouse_y);

    sf::RenderWindow window;
    std::vector<Target> targets;
    sf::Font font;
    sf::Text time_text;
    sf::Text score_text;
    sf::Text game_over_text;

    int score;
    float time_left;
    bool is_game_over;
};
#endif