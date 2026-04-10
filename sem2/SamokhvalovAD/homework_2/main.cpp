#include "main.h"
#include "circle.h"


void loop(sf::RenderWindow& window) {
    int score = 0;
    int timeLeft = GAME_DURATION;
    int increacedTime = 0;
    bool clicked = false;
    sf::Clock clock;
    std::vector<Circle*> circles;
    sf::Font font;
    if (!font.openFromFile(FONT_PATH)) {
        std::cerr << FONT_ERROR_TEXT << std::endl;
        return;
    }
    // Score text
    sf::Text scoreText(font);
    scoreText.setString(BEFORE_SCORE_TEXT + std::to_string(score));
    scoreText.setCharacterSize(TEXT_SIZE);
    scoreText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - scoreText.getGlobalBounds().size.x / 2, SCORE_TEXT_OFFSET));
    // Timer text
    sf::Text timerText(font);
    timerText.setCharacterSize(TEXT_SIZE);
    for (int i = 0; i < CIRCLE_COUNT; i++) {
        circles.push_back(new Circle());
    }

    while (window.isOpen())
    {
        timeLeft = GAME_DURATION - (int)clock.getElapsedTime().asSeconds() - increacedTime;
        if (timeLeft > 0) {
            timerText.setString(BEFORE_TIMER_TEXT + std::to_string(timeLeft));
            for (Circle* circle : circles) {
                circle->move();
            }
        } else {
            timerText.setString(GAME_OVER_TEXT);
        }
        timerText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - timerText.getGlobalBounds().size.x / 2, WINDOW_HEIGHT - TIMER_TEXT_OFFSET));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !clicked && timeLeft > 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            clicked = true;
            bool collisionDetected = false;
            for (Circle* circle : circles) {
                if (circle->checksCollision(mousePos.x, mousePos.y)) {
                    score++;
                    scoreText.setString(BEFORE_SCORE_TEXT + std::to_string(score));
                    circle->updateCircle();
                    collisionDetected = true;
                    break;
                }
            }
            if (!collisionDetected) {
                increacedTime += INCREACE_TIME;
            }
        } else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clicked && timeLeft > 0) {
            clicked = false;
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        for (Circle* circle : circles) {
            window.draw(circle->getCircle());
        }
        window.draw(scoreText);
        window.draw(timerText);
        window.display();
    }
}


int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_TITLE);
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    loop(window);
    return 0;
}