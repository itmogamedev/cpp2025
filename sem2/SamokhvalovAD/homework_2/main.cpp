#include "main.h"
#include "circle.h"


void loop(sf::RenderWindow& window) {
    int score = 0;
    bool clicked = false;
    sf::Clock clock;
    std::vector<Circle*> circles;
    sf::Font font;
    if (!font.openFromFile("sem2/SamokhvalovAD/homework_2/pixel.otf")) {
        std::cerr << "Font error" << std::endl;
        return;
    }
    // Score text
    sf::Text scoreText(font);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(24);
    scoreText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - scoreText.getGlobalBounds().size.x / 2, 30));
    // Timer text
    sf::Text timerText(font);
    timerText.setCharacterSize(24);
    for (int i = 0; i < CIRCLE_COUNT; i++) {
        circles.push_back(new Circle());
    }

    while (window.isOpen())
    {

        timerText.setString("Time: " + std::to_string(GAME_DURATION - (int)clock.getElapsedTime().asSeconds()));
        timerText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - timerText.getGlobalBounds().size.x / 2, WINDOW_HEIGHT - 60));

        for (Circle* circle : circles) {
            circle->move();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !clicked) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            clicked = true;
            bool collisionDetected = false;
            for (Circle* circle : circles) {
                if (circle->checksCollision(mousePos.x, mousePos.y)) {
                    std::cout << "Circle clicked!" << std::endl;
                    score++;
                    scoreText.setString("Score: " + std::to_string(score));
                    circle->updateCircle();
                    collisionDetected = true;
                    break;
                }
            }
            if (!collisionDetected) {
                std::cout << "No circle clicked!" << std::endl;
            }
        } else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clicked) {
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
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "OSU");
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    loop(window);
    return 0;
}