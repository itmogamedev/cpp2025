#include "main.h"
#include "circle.h"


void loop(sf::RenderWindow& window) {
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    std::vector<Circle*> circles;
    sf::Font font;
    if (!font.openFromFile("sem2/SamokhvalovAD/homework_2/pixel.otf")) {
        std::cerr << "Font error" << std::endl;
        return;
    }
    sf::Text scoreText(font);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(24);
    scoreText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - scoreText.getGlobalBounds().size.x / 2, 30));
    for (int i = 0; i < CIRCLE_COUNT; i++) {
        circles.push_back(new Circle());
    }
    while (window.isOpen())
    {
        for (Circle* circle : circles) {
            circle->move();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            bool collisionDetected = false;
            for (Circle* circle : circles) {
                if (circle->checksCollision(mousePos.x, mousePos.y)) {
                    std::cout << "Circle clicked!" << std::endl;
                    circle->updateCircle();
                    collisionDetected = true;
                    break;
                }
            }
            if (!collisionDetected) {
                std::cout << "No circle clicked!" << std::endl;
            }
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
        window.display();
    }
}


int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "OSU");
    loop(window);
    return 0;
}